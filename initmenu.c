/*
  XBlockOut a 3D Tetris

  Copyright (C) 1992,1993,1994,2001,2003  Thierry EXCOFFIER

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
#include "buttons.h"
#include <X11/Xutil.h>

#if HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#define CSTP d,w,bl->opt.button_height

void inittext(struct menu *m, struct opt *opt, struct x *x) ;
void initmenuwindow(struct menu *m, struct opt *opt, struct x *x, unsigned int dxmax, unsigned int dymax);
void initzoo(struct menu *m, struct opt *opt, struct x *x) ;

void initmenu(struct bl *bl)
{
  struct menu *m ;
  static struct movinggc movinggc ;
  Display *d ;
  Window w ;
  struct row_column *col1,*col2,*col3 ;
  Pixmap createhelpbitmap(struct bl *bl, int l, int h, int *tx, int *ty) ;

  m = &bl->menu ;
  m->display = bl->x.display ;
  m->white = bl->x.white ;
  m->black = bl->x.black ;
  m->bl = bl ;
  d = m->display ;
  w = bl->x.root ;
  if ( bl->opt.verbose ) fprintf(stderr,"OPT VERBOSE\n") ;

  m->helpkey = 0 ; 
  inittext(m,&bl->opt,&bl->x) ;
  bl->x.xfont = m->xfont2 ;
  bl->x.text = m->text2 ;

  init_movinggc(d,w,&movinggc,bl->x.back_pixel,bl->x.white_pixel,bl->x.black_pixel) ;

  m->score = create_button(CSTP,FLAT_TEXT,&movinggc,(void(*)()) NULL,textthescore,
			   create_line("Score",m->xfont,m->text1),
			   create_line("000000",m->xfont2,m->text2),
			   NULL) ;
  m->hiscore = create_button(CSTP,FLAT_TEXT,&movinggc,(void(*)())NULL,texthiscore,
			     create_line("High Score",m->xfont,m->text1),
			     create_line("000000",m->xfont2,m->text2),
			     NULL) ;
  m->cube = create_button(CSTP,FLAT_TEXT,&movinggc,(void(*)())NULL,textcube,
			  create_line("#cubes 00000",m->xfont,m->text1),
			  NULL) ;
  m->bloc = create_button(CSTP,FLAT_TEXT,&movinggc,(void(*)())NULL,textbloc,
			  create_line("#blocs 00000",m->xfont,m->text1),
			  NULL) ;
  m->destroylevel = create_button(CSTP,FLAT_TEXT,&movinggc,(void(*)())NULL,textdlevel,
				  create_line("#destroy level",m->xfont,m->text1),
				  create_line("0000",m->xfont,m->text1),
				  NULL) ;
  m->level = create_button(CSTP,FLAT_TEXT,&movinggc,(void(*)())NULL,textlevel,
			   create_line("current level",m->xfont,m->text1),
			   create_line("00",m->xfont,m->text1),
			   NULL) ;
  m->nextpiece = create_button(CSTP,RELIEF_TEXT,&movinggc,fctnextpiece,textnextpiece,
			       create_line("Click me",m->xfont,m->text1),
			       create_line("to see",m->xfont,m->text1),
			       create_line("next piece",m->xfont,m->text1),
			       NULL) ;

  col1 = scotch((struct row_column*)m->score, m->hiscore, m->cube, m->bloc, m->destroylevel,
		m->level, m->nextpiece, NULL ) ;
  m->score->menu = m ;
  m->hiscore->menu = m ;
  m->cube->menu = m ;
  m->bloc->menu = m ;
  m->destroylevel->menu = m ;
  m->level->menu = m ;
  m->nextpiece->menu = m ;

  m->land = create_button(CSTP,RELIEF_TEXT,&movinggc,fctland,textland,
			  create_line(SMALL_LAND,m->xfont,m->text1),
			  NULL) ;
  m->typepiece=create_button(CSTP,RELIEF_TEXT,&movinggc,fcttype,texttype,
			     create_line(COMPLEX_PIECE,m->xfont,m->text1),
			     NULL) ;
  m->width = create_button(CSTP,RELIEF_TEXT,&movinggc,fctwidth,textwidth,
			   create_line("Width 00",m->xfont,m->text1),
			   NULL) ;
  m->height = create_button(CSTP,RELIEF_TEXT,&movinggc,fctheight,textheight,
			    create_line("Height 00",m->xfont,m->text1),
			    NULL) ;
  m->depth = create_button(CSTP,RELIEF_TEXT,&movinggc,fctdepth,textdepth,
			   create_line("Depth 00",m->xfont,m->text1),
			   NULL) ;
  m->startlevel=create_button(CSTP,RELIEF_TEXT,&movinggc,fctlevel,textstartlevel,
			      create_line("Start level 00",m->xfont,m->text1),
			      NULL) ;
  m->training = create_button(CSTP,RELIEF_TEXT,&movinggc,fcttraining,texttraining,
			      create_line(NORMAL_PLAY,m->xfont,m->text1),
			      NULL) ;
  m->volume = create_button(CSTP,RELIEF_TEXT,&movinggc,fctvolume,textvolume,
			    create_line("Sound volume 00",m->xfont,m->text1),
			    NULL) ;
  m->viewzoo = create_button(CSTP,RELIEF_TEXT,&movinggc,fctzoo,textzoo,
			     create_line(SHOW_ZOO,m->xfont,m->text1),
			     NULL) ;
  m->viewscore=create_button(CSTP,RELIEF_TEXT,&movinggc,fctscore,textscore,
			     create_line(SHOW_SCORE,m->xfont,m->text1),
			     NULL) ;
  m->stereo = create_button(CSTP,RELIEF_TEXT,&movinggc,fctstereo,textstereo,
			    create_line("Eye Distance 9.9",m->xfont,m->text1),
			    NULL) ;
  m->frame=create_button(CSTP,FLAT_TEXT,&movinggc,(void(*)())NULL,textframe,
			 create_line("Frame/Sec. 000",m->xfont,m->text1),
			 NULL) ;

  col2 = scotch((struct row_column*)m->land, m->width,m->height,m->depth,m->typepiece, 
		m->startlevel, m->training,
                m->viewzoo,m->viewscore,m->stereo, NULL ) ;
  m->land->menu = m ;
  m->typepiece->menu = m ;
  m->width->menu = m ;
  m->height->menu = m ;
  m->depth->menu = m ;
  m->startlevel->menu = m ;
  m->training->menu = m ;
  m->volume->menu = m ;
  m->viewzoo->menu = m ;
  m->viewscore->menu = m ;
  m->frame->menu = m ;
  m->stereo->menu = m ;

  m->smooth = create_button(CSTP,RELIEF_TEXT,&movinggc,fctsmooth,textsmooth,
			    create_line(SMOOTH_DRAW,m->xfont,m->text1),
			    NULL) ;
  m->draw = create_button(CSTP,RELIEF_TEXT,&movinggc,fctdraw,textdraw,
			  create_line(TRANSP_DRAW,m->xfont,m->text1),
			  NULL) ;
  m->key = create_button(CSTP,RELIEF_TEXT,&movinggc,fctkey,textkey,
			 create_line("QWERTY -",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 create_line("^X DownLeft  ^X Cancel-",m->xfont,m->text1),
			 NULL) ;
  createhelp(m->key,bl->key) ;

  m->quit = create_button(CSTP,RELIEF_TEXT,&movinggc,fctquit,(void(*)())NULL,
			  create_line("QUIT",m->xfont,m->text1),
			  NULL) ;
  m->state = create_button(CSTP,FLAT_TEXT,&movinggc,(void(*)())NULL,textstate,
			   create_line(SUSPENDED_GAME,m->xfont,m->text1),
			   NULL) ;

  col3 = scotch((struct row_column*)m->key,m->volume,m->smooth, m->draw,
		scotch(scotch((struct row_column*)m->state,m->frame, NULL), m->quit, NULL ),
		NULL ) ;
  m->smooth->menu = m ;
  m->draw->menu = m ;
  m->key->menu = m ;
  /* m->help->menu = m ; */
  m->quit->menu = m ;
  m->state->menu = m ;

  m->copyright = create_button(CSTP,RELIEF_TEXT,&movinggc,fctcopyright,(void(*)())NULL,
			       create_line("Copyright (C) 1992-1994,2001,2003 Thierry EXCOFFIER",m->xfont,m->text1),
			       create_line("XBlockOut comes with ABSOLUTELY NO WARRANTY, This is",m->xfont,m->text1),
			       create_line("free software, and you are welcome to redistribute it",m->xfont,m->text1),
			       create_line("under certain conditions; Click here for more detail.",m->xfont,m->text1),
			       NULL) ;
  if ( 0 )
    {
      m->all = scotch( 
		      scotch((struct row_column*)col1,col2,col3, NULL ),
		      m->copyright,
		      NULL
		      ) ;
    }
  else
    m->all = scotch((struct row_column*)col1,col2,col3, NULL ) ;

  m->copyright->menu = m ;

  m->layersize = compute_height( m->all ) ;
  compute_stretch( m->all,m->layersize ) ;
  compute_rowcol( m->all ) ;
  resizex(m->all,m->all->dx) ;
  if ( m->nextpiece->dx < col1->dx ) m->nextpiece->dx = col1->dx ;
  stretch(m->nextpiece,m->nextpiece->dx) ;
  m->nextpiece->dy = m->nextpiece->dx ;
  compute_rowcol( m->all ) ;
  compute_posit( m->all,m->layersize ) ;
  m->copyright->x = 0 ;
  m->copyright->dx += m->layersize ;

  initmenuwindow(m,&bl->opt,&bl->x,(unsigned int)(m->all->dx+m->layersize),
		 (unsigned int)m->all->dy) ;

  windowset(m->all,m->window) ;

  m->helpkey = createhelpbitmap(bl,
				m->key->dx -2*(m->key->dz+2) ,
				m->key->dy -3*(m->char_height+1) - 2*(m->key->dz+2),
				m->tx,m->ty);

  initzoo(m,&bl->opt,&bl->x) ;

  if ( bl->opt.verbose )
    {
      fprintf(stderr,"font=%lu xfont=%p white=%p text=%p \n",
	      m->font,m->xfont,m->white,m->text1 ) ;
    }
}

/* Create the help bitmap */

Pixmap createhelpbitmap(struct bl *bl, int l, int h, int *tx, int *ty)
{
  char *helpbitmap() ;

  bl->menu.widthhelpkey = l ;
  bl->menu.heighthelpkey = h ;
  bl->menu.key->linestretching = 0 ;
  return(XCreateBitmapFromData( bl->x.display, bl->x.window,
				helpbitmap(l,h,tx,ty),l,h));
}

/************************************************************************/
/* Create zoo window							*/
/************************************************************************/
void initzoo(struct menu *m, struct opt *opt, struct x *x)
{
  XSetWindowAttributes wa ;
  XSizeHints sh ;
  char buf[LINE_LENGTH] ; /* For window name */
  int xx,yy ;

  m->yzoo = ZOO_WIDTH ;
  m->xzoo = (m->yzoo*ZOO_NBX_PIECES)/ZOO_NBY_PIECES ;

  xx = 0 ; 
  yy = 0 ;
  if ( opt->zoogeometry[0]!='\0' )
    MyXParseGeometry(x->display,x->screen,
		     opt->zoogeometry,&xx,&yy,&m->xzoo,&m->yzoo) ;

  wa.event_mask = ExposureMask|StructureNotifyMask ;

  if ( opt->use_bw )
    wa.background_pixel = x->black_pixel ;
  else    wa.background_pixel = x->back_pixel ;

  m->zoo = XCreateWindow(
			 x->display,
			 x->root,
			 xx,yy,(int)m->xzoo,(int)m->yzoo,
			 0,
			 x->depth,
			 InputOutput,
			 x->visual,
			 CWEventMask|CWBackPixel,
			 &wa);
  XSetWindowColormap(x->display,m->zoo,x->colormap) ;
  sprintf(buf,"XBlockOut %s zoo",XBLVERSION) ;
  XSetStandardProperties(x->display,m->zoo,buf,
			 "Zoo",
			 x->icone,
			 (char**)NULL,0,
			 NULL ) ;

  /* The zoo ration must not be changed (not beautiful) */
  sh.flags = PAspect ;
  if ( opt->zoogeometry[0]!='\0' ) sh.flags |= PPosition ;
  sh.min_aspect.x = sh.max_aspect.x = ZOO_NBX_PIECES ;
  sh.min_aspect.y = sh.max_aspect.y = ZOO_NBY_PIECES ;
  sh.x = xx ;
  sh.y = yy ;
  XSetWMNormalHints( x->display,m->zoo,&sh ) ;

  if ( m->showzoo )
    {
      m->showzoo = 0 ;
      fctzoo(m->viewzoo,0) ;
    }
}
/************************************************************************/
/* Create menu window							*/
/************************************************************************/
void initmenuwindow(struct menu *m, struct opt *opt, struct x *x, unsigned int dxmax, unsigned int dymax)
{
  XSetWindowAttributes wa ;
  char buf[LINE_LENGTH] ; /* For window name */
  unsigned long wmask ;
  int xx,yy ;
  unsigned int odxmax,odymax ;
  XSizeHints sh ;

  wa.event_mask = ButtonPressMask|ButtonReleaseMask|ExposureMask|StructureNotifyMask ;
  wmask = CWEventMask|CWBackPixel ;
  if ( opt->use_bw )
    wa.background_pixel = x->black_pixel ;
  else    wa.background_pixel = x->back_pixel ;

  xx = 0 ; 
  yy = 0 ;
  odxmax = dxmax ;
  odymax = dymax ;
  if ( opt->menugeometry[0]!='\0' )
    MyXParseGeometry(x->display,x->screen,
		     opt->menugeometry,&xx,&yy,&dxmax,&dymax) ;

  m->window = XCreateWindow(
			    x->display,
			    x->root,
			    xx,yy,(int)dxmax,(int)dymax,
			    0,
			    x->depth,
			    InputOutput,
			    x->visual,
			    (int)wmask,
			    &wa);
  XSetWindowColormap(x->display,m->window,x->colormap) ;
  sprintf(buf,"XBlockOut %s menu",XBLVERSION) ;
  XSetStandardProperties(x->display,m->window,buf,
			 "Menu",
			 x->icone,
			 (char**)NULL,0,
			 NULL ) ;

  /* Not interesting to increase window menu size */
  sh.flags = PMaxSize ;
  if ( opt->zoogeometry[0]!='\0' ) sh.flags |= PPosition ;
  sh.max_width = odxmax ;
  sh.max_height = odymax ;
  sh.x = xx ;
  sh.y = yy ;
  XSetWMNormalHints( x->display,m->window,&sh ) ;

  /* If speedtest : no window menu */
  if ( opt->speedtest==0 ) XMapWindow( x->display,m->window) ;
}
/************************************************************************/
/*									*/
/************************************************************************/
void createhelp(struct moving_button *b, char *blkey)
{
  int i ;
  char key[KEY_LAST][4] ;
  struct text_line *t ;
 
  for(i=0;i<KEY_LAST;i++)
    if ( blkey[i]<' ' ) sprintf(key[i],"^%c",(char)(blkey[i]+'@')) ;
    else
      sprintf(key[i],"%c ",blkey[i]) ;

  t = b->text->next ;
  sprintf(t->current_text,"%s Launch    %s Cancel" ,
	  key[KEY_DROP],key[KEY_CANCEL]) ; t = t->next ;
  sprintf(t->current_text,"%s Suspend   %s Quit  " ,
	  key[KEY_PAUSE],key[KEY_QUIT]) ; t = t->next ;

  /* Blank space for the bitmap */
  for(i=0;i<9;i++)
    {
      strcpy(t->current_text,""  ) ; 
      t = t->next ;
    }
}
/************************************************************************/
/* Text, font gc initialisations					*/
/************************************************************************/
void inittext(struct menu *m, struct opt *opt, struct x *x)
{
  XGCValues xgc ;
  int ascent,descent,dir ;
  XCharStruct overall_return ;

  m->xfont = XLoadQueryFont( x->display , opt->thefont ) ;
  m->font = XLoadFont( x->display , opt->thefont ) ;
  if ( opt->verbose )
    {
      fprintf(stderr,"font=%s\n", opt->thefont) ;
    }
  if ( m->font==BadAlloc || m->font==BadName || m->xfont==0 )
    {
      fprintf(stderr,"Some problems when loading a font... trying others\n") ;
      m->xfont = XLoadQueryFont( x->display , 
				 "-*-*-*-*-*-*-*-*-*-*-*-*-*-*" ) ;
      m->font = XLoadFont( x->display , 
			   "-*-*-*-*-*-*-*-*-*-*-*-*-*-*" ) ;
      if ( m->font==BadAlloc || m->font==BadName || m->xfont==0 )
	{
	  fprintf(stderr,"You haven't -*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	  fprintf(stderr,"Have you A font?\n");
	  fprintf(stderr,"Retry with -font option\n");
	  exit(1) ;
	}
    }
  m->xfont2 = XLoadQueryFont( x->display , opt->thefont2 ) ;
  m->font2 = XLoadFont( x->display , opt->thefont2 ) ;
  if ( opt->verbose )
    {
      fprintf(stderr,"font2=%s\n", opt->thefont2) ;
    }
  if ( m->font2==BadAlloc || m->font2==BadName || m->xfont2==0 )
    {
      m->font2 = m->font ;
      m->xfont2 = m->xfont ;
    }

  xgc.background = x->back_pixel ;
  xgc.foreground = opt->backcolor!=7 ? x->white_pixel : x->black_pixel;
  xgc.font       = m->font ;
  xgc.fill_style = FillSolid ;
  xgc.function   = GXcopy ;
  m->text        = XCreateGC(x->display,x->root,
			     (unsigned long)(GCFunction|GCFillStyle|
					     GCFont|GCForeground|GCBackground),
			     &xgc) ;
  xgc.fill_style = FillOpaqueStippled ;
  m->text1       = XCreateGC(x->display,x->root,
			     (unsigned long)(GCFillStyle|GCFont|
					     GCForeground|GCBackground),
			     &xgc) ;
  xgc.font       = m->font2 ;
  m->text2        = XCreateGC(x->display,x->root,
			      (unsigned long)(GCFillStyle|GCFont
					      |GCForeground|GCBackground),&xgc) ;

  /* Maximum height of text */
  XTextExtents(m->xfont,"pl0|",4,&dir,&ascent,&descent,&overall_return) ;
  m->char_height = ascent+descent ;

  if ( opt->button_height==-1 )
    opt->button_height = m->char_height/2+1 ;

  if ( opt->use_bw )
    {
      m->flat = m->black ;
      m->upleft = m->white ;
      m->downright = m->white ;
    }
  else
    {
      m->upleft = m->white ;
      m->downright = m->black ;
      switch( opt->backcolor )
	{
	case 0 : m->flat = m->black ;
	  m->downright = m->white ;
	  break ;
	case 7 : m->flat = m->white ;
	  m->upleft = m->black ;
	  break ;
	default:
	  m->flat = x->face[opt->backcolor-1] ;
	  break ;
	}
    }
}
