class GRID
{
	int w,h;
	int mines;
	int grid[MAX][MAX];
	bool isopen[MAX][MAX];
	bool isflag[MAX][MAX];
	int flagcount;
	public:
	bool tanksolverallowed()
	{
         for(int i=0;i<h;i++)
         {
          for(int j=0;j<w;j++)
          {
                  if(isOpen(i,j)||isFlag(i,j))
                                              return true;
          }
          
         }
         return false;     
    }
	public:
		//----------------------------------------------------------------------
		int W(){return w;}
		int H(){return h;}
	    bool checkFlags()// required for artificial intellegence...
	    {
             for(int i=0;i<h;i++)
             {
                     for(int j=0;j<w;j++)
                     {
                             if(isFlag(i,j)&&grid[i][j]!=MINE) 
                             {
                                   char position[100]="(";
                                   char temp[100];
                                   itoa(i+1,temp,10);
                                   strcat(position,temp);
                                   strcat(position,", ");
                                   itoa(j+1,temp,10);
                                   strcat(position,temp);
                                   strcat(position,")");
                                   
                                   al_show_native_message_box(display,"AI help!!!","Wrong flag placed at",position,NULL,2);
                                   return true;       
                             }
                     }        
             }
             return false;
        }
     
		bool won()
		{
             for(int i=0;i<h;i++)
             {
                    for(int j=0;j<w;j++)
                    {
                            if(!isOpen(i,j)&&!isFlag(i,j))
                                      return false;
                            if(isFlag(i,j)&&grid[i][j]!=MINE)
                                      return false;                  
                    }             
                             
             }     
             return true;
        }
        
		GRID(int W=0,int H=0,int M=0)
		{
				if(W>MAX)
				{	
                    al_show_native_message_box(NULL,"ERROR!!!","Tiles limit exceeded.", NULL,NULL,2);
					return;
				}
                if(W*H<M)
				{	
                    al_show_native_message_box(NULL,"ERROR!!!","Error!!", "Mine number too large",NULL,2);
					return;
				}
					
				w=W;
				h=H;
				mines=M;
				flagcount=0;
				
				memset(grid,0,sizeof(grid));
				memset(isopen,0,sizeof(isopen));
				memset(isflag,0,sizeof(isflag));
				addmines();
				initgrid();
		}
		//----------------------------------------------------------------------
		GRID(char *PATH)
		{
				ifstream infile(PATH,ios::binary);
				if(!infile) 
				{
					cerr<<"Unable to open file "<<PATH<<strerror(errno);
					return;
				}
				
				infile.read((char *)this,sizeof(GRID));					
				
				if(w*h<mines)
				{	al_show_native_message_box(NULL,NULL,NULL,"Mine number to large",NULL,1);
					return;
				}
		}
		//----------------------------------------------------------------------
		bool puttofile(char *PATH)
		{
				ofstream outfile(PATH,ios::binary);
				if(!outfile) 
				{
					cerr<<"Unable to open file "<<PATH<<strerror(errno);
					return false;
				}
				
				outfile.write((char *)this,sizeof(GRID));
				return true;					
		}
		//----------------------------------------------------------------------
		void addmines()
		{
			for(int k=0;k<mines;k++)
			{
			
				int i=-1,j=-1;
				while(i==-1||grid[i][j]==MINE)
				{
					i=rand()%h;
					j=rand()%w;
				}
			//	cout<<"putting mine at"<<i<<" "<<j<<endl;
				grid[i][j]=MINE;
			}
		}
		//----------------------------------------------------------------------
		void initgrid()
		{
			for(int i=0;i<w;i++)
			{
				for(int j=0;j<h;j++)
				{
					if(grid[i][j]==MINE)
					{
						  if((i-1)>=0           &&grid[i-1][j]  >=0)          grid[i-1][j]++;
                          if((i-1)>=0&&(j-1)>=0 &&grid[i-1][j-1]>=0)          grid[i-1][j-1]++;
                          if((i-1)>=0&&(j+1)<w  &&grid[i-1][j+1]>=0)		  grid[i-1][j+1]++;
                          if((j-1)>=0           &&grid[i][j-1]  >=0)		  grid[i][j-1]++;
                          if((j+1)<w            &&grid[i][j+1]  >=0)		  grid[i][j+1]++;
                          if((i+1)<h&&(j-1)>=0  &&grid[i+1][j-1]>=0)	      grid[i+1][j-1]++;
                          if((i+1)<h            &&grid[i+1][j]  >=0)		  grid[i+1][j]++;
                          if((i+1)<h&&(j+1)<w   &&grid[i+1][j+1]>=0)		  grid[i+1][j+1]++;								
					}	
				}
			}	
		}
		bool isFlag(int i,int j)	{ return isflag[i][j];}
		bool setFlag(int i,int j)	{ if(!isOpen(i,j)&&!isFlag(i,j)){ isflag[i][j]=true; flagcount++; return true;}return false;}
		bool removeFlag(int i,int j)	{ if(isFlag(i,j)){ isflag[i][j]=false; flagcount--; return true;}return false;}
		int MINES(){return mines-flagcount;}
		//----------------------------------------------------------------------
		int open(int i,int j)
		{
            if(i<0||j<0||i>=h||j>=w)
				return NOT_POSSIBLE;
			cout<<"opening "<<i<<" "<<j<<endl;
			if(!isOpen(i,j)&&!isFlag(i,j))
			{
					isopen[i][j]=true;
					if(grid[i][j]==0)
					{
						open(i-1,j-1);
						open(i-1,j);
						open(i-1,j+1);
						open(i,j-1);
						open(i,j+1);
						open(i+1,j-1);
						open(i+1,j);
						open(i+1,j+1);
					}
					if(grid[i][j]==MINE)
					                    openallmines();
                    return grid[i][j];
                     
			}
			return ALREADY_OPENED;
		}
		void openallmines()
		{
             for(int i=0;i<h;i++)
             {
                     for(int j=0;j<w;j++)
                     {
                             if(grid[i][j]==MINE)
                                                 isopen[i][j]=true;
                     }           
             }    
         }
		//----------------------------------------------------------------------
		int gettile(int i,int j)
		{
			if(isFlag(i,j))
				return FLAG;
			if(isOpen(i,j))
			{
				return grid[i][j];	
			}
			else return CLOSED;
		}
		int tileinfo(int i,int j){ return grid[i][j];}
		
		bool isOpen(int i,int j){return isopen[i][j];}
		int getmines(){ return mines;}
		
		//---------- debug functionss----------------------------------
		void print();
		void printgrid();
};

// jus to debug------
void GRID::print()
{
			for(int i=0;i<w;i++)
			{
				for(int j=0;j<h;j++)
				{
					printf("%d\t",grid[i][j]); 
				}
				printf("\n");
			}
}

void GRID::printgrid()
{
	for(int i=0;i<w;i++)
	{
			for(int j=0;j<h;j++)
			{
				int data=gettile(i,j);
				if(data==FLAG) printf("F\t");
				else if(data==CLOSED) printf("C\t");
				else printf("%d\t",data); 
			}
			printf("\n");
	}
}

