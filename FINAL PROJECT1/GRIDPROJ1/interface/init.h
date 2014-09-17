

ALLEGRO_BITMAP *backimg;
//----------------------side icons------------------------------------------
ALLEGRO_BITMAP *clockimg;
ALLEGRO_BITMAP *mineiconimg;
ALLEGRO_BITMAP *splashimg;
   	
//-----------------------tiles-----------------------------------------------
ALLEGRO_BITMAP *tileImg[9];
ALLEGRO_BITMAP *flagimg;
ALLEGRO_BITMAP *mineimg;
ALLEGRO_BITMAP *closedimg;
ALLEGRO_BITMAP *blastimg;
ALLEGRO_BITMAP *saveimg;
ALLEGRO_BITMAP *aiimg;
ALLEGRO_BITMAP *title;
ALLEGRO_BITMAP *selected;
ALLEGRO_BITMAP *congoimg;
ALLEGRO_BITMAP *lossimg;
ALLEGRO_BITMAP *backimage;
ALLEGRO_BITMAP *homepage;
ALLEGRO_BITMAP *newpage;
ALLEGRO_SAMPLE *opensound, *blastsound;
ALLEGRO_SAMPLE *ticksound;
ALLEGRO_SAMPLE *startsound;
//-----------------sound--------------------



ALLEGRO_FONT *font;


ALLEGRO_DISPLAY*  initDisplay()
{
   ALLEGRO_DISPLAY *display = NULL;
  
   if(!al_init()) {
      al_show_native_message_box(NULL,NULL,NULL,"Unable to initialise allegro. Please check your installation",NULL,1);
      return NULL;
   }
   al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
   al_init_image_addon();
   al_init_primitives_addon();
   al_install_mouse();
   al_install_audio();
   al_init_acodec_addon();
   al_install_keyboard();
   al_init_font_addon();
   al_init_ttf_addon();
   
   display = al_create_display(HRESOLUTION,VRESOLUTION);
   return display;
}

void printbackground()
{
	backimage=al_load_bitmap(BACKGROUND);
	for(int i=0;i<HRESOLUTION;i+=80)
           for(int j=0;j<VRESOLUTION;j+=80)
                   al_draw_bitmap(backimage,i,j,NULL);  
}



void initTileImages(ALLEGRO_BITMAP *tileImages[9])
{
	for(int i=0;i<9;i++)
		tileImages[i]=al_load_bitmap(TILEPATH[i]);	
}

void initSound()
{
     opensound=al_load_sample(OPENSOUND);
     blastsound=al_load_sample(BLASTSOUND);
     ticksound=al_load_sample(TICKSOUND);
      startsound=al_load_sample(STARTSOUND);
     al_reserve_samples(10000);
}
void initFont()
{
     font=al_load_font(FONT,30,NULL);
}
void initImg()
{
	title=al_load_bitmap(TITLE);
    splashimg=al_load_bitmap(SPLASH);
    backimg=al_load_bitmap(BACKGROUND);
   	newpage=al_load_bitmap(NEWIMAGE);
   	congoimg=al_load_bitmap(CONGOPATH);
   	lossimg=al_load_bitmap(LOSSPATH);
   	//----------------------side icons------------------------------------------
   	selected=al_load_bitmap(SELECTEDPATH);
    clockimg=al_load_bitmap(CLOCKPATH);
	mineiconimg=al_load_bitmap(MINEICONPATH);
   	backimg=al_load_bitmap(BACKBUTTONPATH);
   	saveimg=al_load_bitmap(SAVEPATH);
   	aiimg=al_load_bitmap(AIPATH);
   //	congo=al_load_bitmap(CONGOPATH);
   	//loss=al_load_bitmap(LOSSPATH);
   	//saveimg=al_load_bitmap(SAVEPATH);
   	
   //-----------------------tiles-----------------------------------------------
	mineimg=al_load_bitmap(MINEPATH);
	initTileImages(tileImg);
	flagimg=al_load_bitmap(FLAGPATH);
	
    
    closedimg=al_load_bitmap(CLOSEDPATH);
   	blastimg=al_load_bitmap(BLASTPATH);
    homepage=al_load_bitmap(HOMEPAGE);
}
