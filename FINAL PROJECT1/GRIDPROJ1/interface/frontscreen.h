#define NEWGAME 1
#define OPENGAME 2
#define ABOUT 3
#define EXIT 4
int frontscreen()
{
    ALLEGRO_EVENT_QUEUE *event_queue;
    event_queue= al_create_event_queue();
   	ALLEGRO_KEYBOARD_STATE *keystate;
   	al_register_event_source(event_queue,al_get_display_event_source(display));
   	al_register_event_source(event_queue,al_get_mouse_event_source());
    al_draw_bitmap(homepage,0,0,0);
	al_flip_display();    
    while(1)
	{
	        ALLEGRO_EVENT events;
	        al_wait_for_event(event_queue,&events);
	        if((events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)&&events.mouse.button & 1)
    	    {
                     
                     float x=events.mouse.x;
                     float y=events.mouse.y;
                     al_play_sample(ticksound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                     if(x<1330&&y<228&&x>965&&y>146)
                                                    return NEWGAME;
                     else if(x<1330&&y<319&&x>965&&y>240)
                                                    return OPENGAME;

                     else if(x<1330&&y<411&&x>965&&y>330)
                                                    return ABOUT;

                     else if(x<1330&&y<504&&x>965&&y>422)
                                                    return EXIT;
          }
    }   
}
