/*
    XBlockOut a 3D Tetris

    Copyright (C) 1992,1993,1994  Thierry EXCOFFIER

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

#include <stdio.h>

#include "define.h"
#include "menu.h"
#include "realtime.h"
#include "movingbloc.h"
#include "opt.h"
#include "x.h"
#include "draw.h"


struct bl
	{
	struct x x ;
	struct opt opt ;

	struct draw draw ;
	struct movingbloc bloc ;
	struct menu menu ;
	struct realtime realtime ;

	int nbbloc,nbcube,nblevel,score ;
	int hiscore ;
	int currentlevel ;
	int endplay ;
	char *boardkey[NB_KEYBOARD] ;
	char *key ;
	char *progname ;
	} ;

extern void initdisp(struct opt* opt,struct x* x) ;
extern void initdisp2(struct opt* opt,struct x* x) ;
extern void displaymoving(struct opt *opt, struct x *x,
			     struct movingbloc *bloc,struct draw *draw) ;
extern void initwin(struct opt *opt,struct x *x) ;
extern void setargs(struct bl *bl) ;
extern void initgc(struct opt *opt,struct x *x) ;
extern void initbuffer(struct opt *opt,struct x *x) ;
extern void zooevent(struct bl *bl,XEvent *e) ;
extern void gameevent(struct bl *bl,XEvent *e) ;


/* loop.c */
extern void loop(struct bl *bl) ;
extern void newworld(struct bl *bl) ;
extern void updateworld(struct bl *bl) ;
extern int splash(struct bl *bl,struct realtime *r) ;
extern void unsuspend(struct bl *bl,struct realtime *r) ;
extern void startgame(struct bl *bl) ;
extern void endgame(struct bl *bl,int music) ;
extern void updatework(struct opt *opt,struct x *x,struct draw *draw) ;


/* sound.c */
extern void savebell(Display *d) ;
extern void restorebell(Display *d) ;
extern void setbell(Display *d,int p,int dur) ;
extern void sound(Display *d,int p,int dur,int vol) ;
extern void playsound(Display *d,int type,int vol) ;
