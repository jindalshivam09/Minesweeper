#include"header.h"

#include"gridinit.h"
#include"path.h"
//nclude"stats.h"
#include".\\ai\\stack.h"
#include".\\ai\\ai.h"

#include"time.h"
#include"save.h"

//#include".\\AI\\stack.h"

#include".\\interface\\init.h"
#include".\\interface\frontscreen.h"
#include".\\interface\\newgame.h"
#include".\\interface\\printtiles.h"
#include".\\interface\\gameplay.h"

int main()
{
	//------------------------------initialisations...--------------------------
	ALLEGRO_EVENT_QUEUE *event_queue;
    srand(time(NULL));
	display =initDisplay();
	event_queue= al_create_event_queue();
   	ALLEGRO_KEYBOARD_STATE *keystate;
   	al_register_event_source(event_queue,al_get_display_event_source(display));
   	al_register_event_source(event_queue,al_get_mouse_event_source()); 
	
	//-------------------------------------------------------------------------
	initImg();
    initSound();
    initFont();
	//--------------------------------------------------------------------------
	al_draw_bitmap(splashimg,0,0,0);
	al_flip_display();
	al_play_sample(startsound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
	for(int i=0;i<1680;i+=2)
	{                            
                                 al_draw_bitmap(backimg,i/2-1,575,0);
                                 al_draw_bitmap(title,i/2,575,0);
                                 al_flip_display();
    }
    
    GRID grid;
	while(1)
	{
            int result=-1;
    grid=GRID();
    bool flag=true;
	switch(frontscreen())
	{
          case NEWGAME:switch(newgame())
                       {
                                        
                          case EASY: grid=GRID(9,9,20); break;
                          case MEDIUM: grid=GRID(16,16,40); break;
                          case HARD: grid=GRID(20,20,80); break;
                          case CUSTOM: 
                             al_show_native_message_box(display,"Sorry","Switch to second screen.","Bug will be fixed soon",NULL,NULL);
                             int w,m;
                             cout<<"Enter the side of matrix and number of mines=>";
                             scanf("%d %d",&w,&m);
                             grid=GRID(w,w,m); 
                             if(grid.H()==0)
                                            flag=false;
                             break;
                                                
                       }
                       if(flag)
                               result=playgame(grid);
                       break;
                       
                       case OPENGAME:al_show_native_message_box(display,"Sorry","Switch to second screen.","Bug will be fixed soon",NULL,NULL);
                                    cout<<"Enter the game number to open=>";
                        if(!open(grid))
                         {
                                    cout<<"Open Failed\n";
                                    al_show_native_message_box(NULL,"ERROR!!!",strerror(errno), NULL,NULL,2);        
                         }
                         else result=playgame(grid);
                         break;
                         case ABOUT:al_show_native_message_box(display,"About us","Developed by:","Keshav Goel\nGaurav Gupta\nShivam Jindal\nShobhit Saxena",NULL,NULL);break;
                         case EXIT:exit();
                     return 0; 
    }
    if(result==WON)
    {
                   al_draw_bitmap(congoimg,0,0,0);
                   al_flip_display();
                   al_rest(4);
    }
    else if(result==LOST)
    {
                   al_draw_bitmap(lossimg,0,0,0);
                   al_flip_display();
                   al_rest(4);
    }
    }	
}


