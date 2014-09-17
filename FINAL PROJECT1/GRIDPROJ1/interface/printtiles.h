
void printmines(GRID grid)
{
     float cx=(1366-(35.0*grid.W()))/2,cy=(768-(35.0*grid.H()))/2;
     float x=cx;
   	 float y=cy;
     
     for(int i=0;i<grid.H();i++)
   	 {
       for(int j=0;j<grid.W();j++)
       {
               if(grid.gettile(i,j)==MINE)
               {
                   al_draw_bitmap(mineimg,x,y,0);
               }
               x+=TILEIMAGESIZE;
       }
          x=cx;        
          y+=TILEIMAGESIZE; 
     }
     al_flip_display();
     
     x=cx;
   	 y=cy;
     for(int i=0;i<grid.H();i++)
   	 {
       for(int j=0;j<grid.W();j++)
       {
               if(grid.gettile(i,j)==MINE)
               {
                   
                   al_play_sample(blastsound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                   al_rest(0.1);
                   al_draw_bitmap(blastimg,x,y,0);
                   al_flip_display();
               }
               x+=TILEIMAGESIZE;
       }
          x=cx;        
          y+=TILEIMAGESIZE; 
     }
}

void printtiles(GRID grid,bool buffering=true)
{
	float cx=(1366-(35.0*grid.W()))/2,cy=(768-(35.0*grid.H()))/2;
   	float x=cx;
   	float y=cy;
   	for(int i=0;i<grid.H();i++)
   	{
       for(int j=0;j<grid.W();j++)
       {
       		  int data=grid.gettile(i,j);
       		  
              if(data==FLAG)
              	al_draw_bitmap(flagimg,x,y,0);	
			  else if(data==CLOSED)
			  	al_draw_bitmap(closedimg,x,y,0);
			  else
			  	al_draw_bitmap(tileImg[data],x,y,0);
              
              if(i==selectedI&&j==selectedJ)
                al_draw_bitmap(selected,x,y,0);
              x+=TILEIMAGESIZE;
              if(!buffering)
              	al_flip_display();
       }        
          x=cx;        
          y+=TILEIMAGESIZE; 
   	}
   	//al_flip_display();
   	al_flip_display();
   	selectedI=-1;
   	selectedJ=-1;
}

void printicons(GRID grid) // to be considered latter..
{
     
	float cx=(1366-(35.0*grid.W()))/2,cy=(768-(35.0*grid.H()))/2;
	al_draw_bitmap(aiimg,1300,20,0);
    al_draw_bitmap(backimg,20,20,2);
    //al_draw_bitmap(clockimg,cx+grid.H()*35+TILEIMAGESIZE,cy+TILEIMAGESIZE,2);
    al_draw_bitmap(mineiconimg,cx+grid.H()*35+TILEIMAGESIZE,cy+3*TILEIMAGESIZE,2);
    al_draw_bitmap(saveimg,1220,20,0); 	
}


