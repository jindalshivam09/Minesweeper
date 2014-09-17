int newgame()
{
    ALLEGRO_EVENT_QUEUE *event_queue;
    event_queue= al_create_event_queue();
   	ALLEGRO_KEYBOARD_STATE *keystate;
   	al_register_event_source(event_queue,al_get_display_event_source(display));
   	al_register_event_source(event_queue,al_get_mouse_event_source());
    al_draw_bitmap(newpage,0,0,0);
	al_flip_display();    
    while(1)
	{
	        ALLEGRO_EVENT events;
	        al_wait_for_event(event_queue,&events);
	        if((events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)&&events.mouse.button & 1)
    	    {
                   al_play_sample(ticksound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0); 
                     float x=events.mouse.x;
                     float y=events.mouse.y;
         
                   

                     if(x<402&&y<620&&x>138&&y>334)
                                                    return EASY;
                     else if(x<666&&y<620&&x>409&&y>334)
                                                    return MEDIUM;

                     else if(x<934&&y<620&&x>677&&y>334)
                                                    return HARD;

                     else if(x<1202&&y<620&&x>945&&y>334)
                                                    return CUSTOM;
          }
    }   
}
