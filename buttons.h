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

/* If the widthest text change (no more the much long) then
   modify initmenu.c in consequence */

#define HARD_DRAW	"To hard drawing"
#define SMOOTH_DRAW	"To smooth drawing"
#define WIRE_DRAW	"To wire frame"
#define TRANSP_DRAW	"To transparent faces"
#define USER_LAND	"User land"
#define SMALL_LAND	"Small land"
#define BIG_LAND	"Big land"
#define FLAT_PIECE	"Flat pieces"
#define SIMPLE_PIECE	"Simple pieces"
#define COMPLEX_PIECE	"Complex pieces"
#define TRAINING_PLAY	"To normal play"
#define NORMAL_PLAY	"To training play"
#define SHOW_ZOO	"Show zoo"
#define HIDE_ZOO	"Hide zoo"
#define SHOW_SCORE	"Show score"
#define HIDE_SCORE	"Hide score"
#define STOPPED_GAME	"STOPPED"
#define RUNNING_GAME	"RUNNING"
#define SUSPENDED_GAME	"SUSPENDED"
#define SHOW_GAME	"SHOW"
#define DEMO_GAME	"DEMO"
#define SPEED_GAME	"SPEEDTEST"



extern void fctnextpiece(struct moving_button *b,int but) ;
extern void fctland(struct moving_button *b,int but) ;
extern void fcttype(struct moving_button *b,int but) ;
extern void fctwidth(struct moving_button *b,int but) ;
extern void fctheight(struct moving_button *b,int but) ;
extern void fctdepth(struct moving_button *b,int but) ;
extern void fctlevel(struct moving_button *b,int but) ;
extern void fcttraining(struct moving_button *b,int but) ;
extern void fctvolume(struct moving_button *b,int but) ;
extern void fctzoo(struct moving_button *b,int but) ;
extern void fctscore(struct moving_button *b,int but) ;
extern void fctsmooth(struct moving_button *b,int but) ;
extern void fctdraw(struct moving_button *b,int but) ;
extern void fctkey(struct moving_button *b,int but) ;
extern void fctquit(struct moving_button *b,int but) ;
extern void fctstereo(struct moving_button *b,int but) ;
extern void fctcopyright(struct moving_button *b,int but) ;

extern void  textscore(struct moving_button *b) ;
extern void  textthescore(struct moving_button *b) ;
extern void  texthiscore(struct moving_button *b) ;
extern void  textcube(struct moving_button *b) ;
extern void  textbloc(struct moving_button *b) ;
extern void  textdlevel(struct moving_button *b) ;
extern void  textlevel(struct moving_button *b) ;
extern void  textnextpiece(struct moving_button *b) ;
extern void  textland(struct moving_button *b) ;
extern void  texttype(struct moving_button *b) ;
extern void  textwidth(struct moving_button *b) ;
extern void  textheight(struct moving_button *b) ;
extern void  textdepth(struct moving_button *b) ;
extern void  textstartlevel(struct moving_button *b) ;
extern void  texttraining(struct moving_button *b) ;
extern void  textvolume(struct moving_button *b) ;
extern void  textzoo(struct moving_button *b) ;
extern void  textframe(struct moving_button *b) ;
extern void  textsmooth(struct moving_button *b) ;
extern void  textdraw(struct moving_button *b) ;
extern void  textkey(struct moving_button *b) ;
extern void  textstereo(struct moving_button *b) ;
extern void  textstate(struct moving_button *b) ;


extern void displaystairs(struct menu *m) ;
extern void displaynextpiece(struct bl *bl) ;
extern void displayzoo(struct bl *bl,int doclear,int dodraw) ;
extern void displaystat(struct bl *bl,int i) ;

