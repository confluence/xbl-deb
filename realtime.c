/*
  XBlockOut a 3D Tetris

  Copyright (C) 1992,1993,1994,2001  Thierry EXCOFFIER

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 1, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  Contact: Thierry.EXCOFFIER@liris.univ-lyon1.fr
*/
#include "bl.h"
#include "transfo.h"
#include <math.h>
#if HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#if HAVE_TIME_H
#include <time.h>
#endif
#if HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif



void inittime(struct realtime *r, int waitone)
{
  time_t currenttime ;

  /* Wait the second changement */
  r->lastcurrenttime = currenttime = 0 ;
  while( r->lastcurrenttime==currenttime )
    {
      currenttime = r->lastcurrenttime ;
      time( &r->lastcurrenttime ) ;
      if ( waitone==0 ) break ;
    }

  r->lastimagenumber = 0 ;
  r->imagenumber     = 0 ;
  if ( r->displaytime==0. ) r->displaytime     = OPTIMUM_DISPLAY_TIME ;
  r->starttime       = r->lastcurrenttime ;
  r->lrtime          = 0. ;
  r->lastfall        = 0. ;
  r->nocalcdisplaytime = 0 ;
}


void nextframe(struct bl *bl, struct realtime *r)
{
  time_t currenttime ;
  int i ;
#ifdef BAD_SELECT
  int j ;
#endif
  float realtime ;

  /* First stage : compute "displaytime" which is the time en second
     use to display a frame.
  */
  if ( bl->opt.fps )
    {
      r->displaytime = 1./bl->opt.fps ;
      realtime = r->imagenumber*r->displaytime ;
      r->lastimagenumber = r->imagenumber ;

      if ( r->nocalcdisplaytime )
	{
	  display_button(bl->menu.frame,
			 bl->menu.frame->x,bl->menu.frame->y,1,1) ;
	  r->nocalcdisplaytime = 0 ;
	}
    }
  else
    {
      time( &currenttime ) ;
      if ( r->lastcurrenttime!=currenttime )
	{
	  if ( r->nocalcdisplaytime==0 )
	    {
	      r->displaytime = (currenttime-r->lastcurrenttime)/
		(r->imagenumber-r->lastimagenumber+.01) ;
	      display_button(bl->menu.frame,
			     bl->menu.frame->x,bl->menu.frame->y,1,1) ;
	    }
	  else r->nocalcdisplaytime = 0 ;

	  i = r->imagenumber-r->lastimagenumber ;
	  if ( i<MAXFRAMESEC ) r->framesec[i]++ ;
	  r->lastcurrenttime = currenttime ;
	  r->lastimagenumber = r->imagenumber ;
	}
      else
	if ( (r->imagenumber-r->lastimagenumber)*r->displaytime > 1 )
	  r->displaytime = 1./(r->imagenumber-r->lastimagenumber) ;


      /* Evaluate a pseudo realtime */
      realtime = (r->lastcurrenttime-r->starttime) 
	+ (r->imagenumber-r->lastimagenumber)*r->displaytime ;
    }

  if ( bl->bloc.depth == PERSP )
    r->lrtime = -r->displaytime ;

  r->imagenumber++ ;

  r->falltime = 8.*pow(1/1.5,(float)bl->currentlevel) ;
  if ( realtime >= r->lastfall &&
       ( bl->opt.mode!=TRAINING || bl->opt.state==DEMO ) )
    {
      if ( bl->opt.verbose )
	{
	  fprintf(stderr,"falltime=%f realtime=%f lastfall=%f\n",
		  r->falltime,realtime,r->lastfall) ;
	}
      i = r->falltime/OPTIMUM_DISPLAY_TIME ;
      if ( i==0 || bl->opt.smooth==0 ) i=1 ;
      while( realtime >= r->lastfall )
	{
	  if ( addtransfo(FALL,i,&bl->bloc,i)==0 )
	    {
	      if ( splash(bl,r) )
		{
		  return ;
		}
	    }
	  r->lastfall += r->falltime ;
	}
    }

  i = 0 ;
  while ( r->lrtime < realtime )
    {
      r->lrtime += OPTIMUM_DISPLAY_TIME ;
      i += nextime( &bl->bloc ) ;
    }
  if(0)
    fprintf(stderr,"lrtime=%g realtime=%g i=%d\n",  r->lrtime, realtime, i) ;

  if ( i ) 
    displaymoving(&bl->opt,&bl->x,&bl->bloc,&bl->draw) ;
  else
    {
      i = (r->lrtime-realtime)/r->displaytime+1 ;
      if ( bl->opt.fps )
	displaymoving(&bl->opt,&bl->x,&bl->bloc,&bl->draw) ;
      else
	{
#ifndef BAD_SELECT
	  /* In this case microsleep is OK */
	  microsleep( (int)(i*r->displaytime*1000000) - r->microsleepdelay ) ;
#else
	  for(j=0;j<i;j++)
	    displaymoving(&bl->opt,&bl->x,&bl->bloc,&bl->draw) ;
#endif
	}
      r->imagenumber += i-1 ;
    }

  if ( bl->opt.verbose )
    fprintf(stderr,"RT=%f LRT=%f LF=%f in=%d lin=%d d=%f\n",
	    realtime,r->lrtime,r->lastfall,
	    r->imagenumber,r->lastimagenumber,
	    r->displaytime);

}



void microsleep(int t)
{
#ifdef HAVE_USLEEP

  usleep(t) ;

#else

  fd_set i,j,k ;
  struct timeval timeout ;

  if ( t<=0 ) t=1 ;
  timeout.tv_sec  = t/1000000 ;
  timeout.tv_usec = t%1000000 ; 
  FD_ZERO(&i) ;
  FD_ZERO(&j) ;
  FD_ZERO(&k) ;
  FD_SET(0, &i) ;
  select(0,&i,&j,&k,&timeout) ;

#endif
}
