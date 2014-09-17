#define MINE -1
#define ALREADY_OPENED -100

class GRID
{
	int w,h;
	int mines;
	int minesleft;
	int grid[MAX][MAX];
	bool isopen[MAX][MAX];
	
	public:
		GRID(int W=0,int H=0,int M=0)
		{
				if(W*H<M)
				{	cerr<<"Mines greater than available tiles.";
					return;
				}
					
				w=W;
				h=H;
				mines=M;
				minesleft=mines;
				
				memset(grid,0,sizeof(grid));
				memset(isopen,0,sizeof(isopen));
				
				addmines();
				initgrid();
		}
		
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
		
		int open(int i,int j)
		{
			if(!isOpen(i,j))
			{
					isopen[i][j]=true;
					return grid[i][j]; 
			}
			return ALREADY_OPENED;
		}
		
		bool isOpen(int i,int j){return isopen[i][j];}
		void print();
};

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



int main()
{
	srand(time(NULL));
	GRID g(10,10,20);
	g.print();

}
