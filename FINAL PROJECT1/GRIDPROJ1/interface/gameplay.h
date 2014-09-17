void arti(GRID grid)
{
     int x;
     if(x=grid.checkFlags())
                 {cout<<x;
                 return;
                 }                                                  
     else 
     {
          cout<<x;
          ai intellegence(grid);
          if(!intellegence.classic())
          {
                                     if(grid.tanksolverallowed())
                                          intellegence.tanksolver();
                                     else
                                         al_show_native_message_box(display,"Error!!!","Open at least one mine to use AI.",NULL,NULL,NULL);
          } 
     }
}


int checkaction(float x,float y)
{ 
    if(x<60 && x>=20 && y<60 && y>=20)
                          return BACK;
    else if(x>1220&&x<1270&&y>20&&y<68)
         return SAVE;
    else if(x>1300&&x<1350&&y>20&&y<68)
         return AI;
    return 0;    
}



int playgame(GRID grid)
{
    ALLEGRO_EVENT_QUEUE *event_queue;
    event_queue= al_create_event_queue();
   	ALLEGRO_KEYBOARD_STATE *keystate;
   	al_register_event_source(event_queue,al_get_display_event_source(display));
   	al_register_event_source(event_queue,al_get_mouse_event_source()); 
    printbackground();
	
	printicons(grid);
    printtiles(grid,false);
    TIME clock;
 //   al_text_mode(makecol(18,103,72);
	float cx=(1366-(35.0*grid.W()))/2,cy=(768-(35.0*grid.H()))/2;
	int newX,newY;
	char temp[100];
    al_draw_text(font, al_map_rgb(255,255,255),cx+grid.H()*35+3*TILEIMAGESIZE,cy+TILEIMAGESIZE+80,ALLEGRO_ALIGN_LEFT,itoa(grid.MINES(),temp,10));
	while(1)
	{
		
        bool flag=false;
        ALLEGRO_EVENT events;
		
		
       
         al_draw_bitmap(backimage,cx+grid.H()*35+3*TILEIMAGESIZE,cy+TILEIMAGESIZE,NULL);
         al_draw_bitmap(backimage,cx+grid.H()*35+3*TILEIMAGESIZE,cy+TILEIMAGESIZE+80,NULL);
         al_draw_text(font, al_map_rgb(255,255,255),cx+grid.H()*35+3*TILEIMAGESIZE,cy+TILEIMAGESIZE+80,ALLEGRO_ALIGN_LEFT,itoa(grid.MINES(),temp,10));
         //al_draw_text(font, al_map_rgb(255,255,255),cx+grid.H()*35+3*TILEIMAGESIZE,cy+TILEIMAGESIZE,ALLEGRO_ALIGN_LEFT,itoa(clock.gettime(),temp,10));
         al_flip_display();
         al_wait_for_event(event_queue,&events);
         
        

        if((events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN))
    	{
                     
                     float x=events.mouse.x;
                     float y=events.mouse.y;
                     
					 
					 newX=(int)(x-cx)/35;
                     newY=(int)(y-cy)/35;
                     
					 //al_textout_centre(display,
					 if(events.mouse.button & 1)
                             {
                                            
                                            int action=checkaction(x,y);
                                            cout<<x<<" "<<y<<endl;
                                            switch(action)
                                            {
                                              case BACK: al_play_sample(ticksound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);cout<<"Returning ";return BACK;
                                              case SAVE: al_play_sample(ticksound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);cout<<"Calling save";save(grid); break;
                                              case AI: al_play_sample(ticksound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);cout<<"Calling AI";arti(grid); break;              
                                            }
                                            
                                            cout<<"Opening"<<newY<<" "<<newX<<endl;
                                            if(newY>=0&&newX>=0&&newY<grid.H()&&newX<grid.W())
                                                     al_play_sample(opensound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);

                                            if(grid.open(newY,newX)==MINE)
                                                  flag=true;
                                            
                             }
            
                     else if(events.mouse.button & 2)
                     		{
                                                 if(!grid.setFlag(newY,newX))
                                                                             grid.removeFlag(newY,newX);
                                                 if(newY>=0&&newX>=0&&newY<grid.H()&&newX<grid.W())
                                                     al_play_sample(opensound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);

                                                 cout<<"Setting"<<newY<<" "<<newX<<endl;
                           }
      grid.printgrid();
      al_draw_bitmap(backimage,cx+grid.H()*35+3*TILEIMAGESIZE,cy+TILEIMAGESIZE+80,NULL);
       
       // al_draw_text(font, al_map_rgb(255,255,255),cx+grid.H()*35+3*TILEIMAGESIZE,cy+TILEIMAGESIZE,ALLEGRO_ALIGN_LEFT,itoa(clock.gettime(),temp,10));
        al_draw_text(font, al_map_rgb(255,255,255),cx+grid.H()*35+3*TILEIMAGESIZE,cy+TILEIMAGESIZE+80,ALLEGRO_ALIGN_LEFT,itoa(grid.MINES(),temp,10));

      if(!flag)
      {               
                        
                        printtiles(grid);
                        if(grid.won())
                                      return WON;
      }
      else
      {
                       printmines(grid);
                       al_rest(1);
                       return LOST;
      }     
       cout<<"------------------\n\n";
       }			 			  
	}
}
