//-------------------GLOBAL HEADER FILES----------------------------------------
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<fstream>
#include<process.h>
#include<dos.h>
#include<stdio.h>
#include<time.h>
#include<errno.h>
using namespace std;
//-------------------------ALLEGRO HEADER FILES---------------------------------
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_primitives.h>
//------------------------GLOBAL DEFINITIONS------------------------------------

ALLEGRO_DISPLAY *display;
#define MAX 20

#define EMPTY -4 // needed only for AI
#define MINE  -2
#define FLAG -1  
#define ALREADY_OPENED -3
#define CLOSED -4
#define NOT_POSSIBLE -5
//------------------------------------------------------------------------------

#define EASY 0
#define MEDIUM 1
#define HARD 2
#define CUSTOM 3
#define OPEN 4
//------------------------------------------------------------------------------
#define HRESOLUTION 1366
#define VRESOLUTION 768
//------------------------------------------------------------------------------
#define MAXCTILES 30
#define MAXRIILES 20
//------------------------------------------------------------------------------
#define WON 1
#define LOST 2
#define BACK 3

#define AI 4
#define SAVE 5
//--------------------FILE DEFINITIONS------------------------------------------
#define STATFILE "stat.dat"
//------------------------------------------------------------------------------
void exit()
{
     al_destroy_display(display);     
}

int selectedI=-1,selectedJ=-1;
