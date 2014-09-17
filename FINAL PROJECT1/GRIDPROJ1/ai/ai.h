#define ERRNO -1
#define SETFLAG(i,j) {tile[i][j]=-3;flag[i][j]=true;opened[i][j]=true;}
//------------------------------------------------------------------------------

class ai
{
		int tile[MAX][MAX];

		int height,width;
		int mines;
		public:
		
        ai(GRID Grid)
			{
				height=Grid.H();
				width=Grid.W();
				
				for(int i=0;i<height;i++)
				{
					for(int j=0;j<width;j++)
					{
						tile[i][j]=Grid.gettile(i,j);	
					}	
				}
				
				mines=Grid.MINES();
				cout<<"a....."<<endl;
				DISPLAY();
				cout<<"sasaa";
			}
			//debug function
			void DISPLAY()
			{
				for(int i=0;i<height;i++)
				{
					for(int j=0;j<width;j++)
					{
							if(tile[i][j]==MINE) 		 printf("M\t");
							else if(tile[i][j]==EMPTY) 	 printf("E\t");
							else if(tile[i][j]==FLAG)	 printf("F\t");
							else printf("%d\t",tile[i][j]);
					}		
					printf("\n");
				}
			}
			inline int emptytiles(int,int);
			inline int flags(int i,int j);
			inline int numbers(int,int);
			bool classic();
			bool tanksolver();
			void dfs(int i,int j,bool border[MAX][MAX],int k,stack *borders);
			void open(int i,int j,int status)
            {
                 cout<<"hi....";
                 char position[100]="(";
                 char temp[100];
                 itoa(i+1,temp,10);
                 strcat(position,temp);
                 strcat(position,", ");
                 itoa(j+1,temp,10);
                 strcat(position,temp);
                 strcat(position,")");
                 if(status==EMPTY)
                 {
                                  selectedI=i;
                                  selectedJ=j;
                                  al_show_native_message_box(display,"AI help!!!","Open tile at position",position,NULL,NULL);
                                  cout<<"Open"<<i<<" "<<j<<endl;
                 }
                 else if(status==FLAG)
                 {                 selectedI=i;
                                   selectedJ=j;
                                   al_show_native_message_box(display,"AI help!!!","Place Flag at position",position,NULL,NULL);
                                   cout<<"Flag"<<i<<" "<<j<<endl;
                 }
            }
			void tanksolverbk(bool isflag[MAX][MAX],int Mines[MAX][MAX],bool isborder[MAX][MAX],stack border,int i);
			inline int flags2(bool flags[MAX][MAX],int i,int j);
			bool isconsistent(bool flag[MAX][MAX]);
			bool check(int i,int j,bool flag[MAX][MAX]);
};


inline int ai:: emptytiles(int i,int j)
{
		int count=0;
		if(i-1>=0&&j-1>=0 			&&tile[i-1][j-1]==EMPTY) count++; 
		if(i-1>=0         			&&tile[i-1][j]==EMPTY) count++; 
		if(i-1>=0&&j+1<width		&&tile[i-1][j+1]==EMPTY) count++; 
		if(		   j-1>=0   		&&tile[i][j-1]==EMPTY) count++; 
		if(        j+1<width		&&tile[i][j+1]==EMPTY) count++; 
		if(i+1<height&&j-1>=0 		&&tile[i+1][j-1]==EMPTY) count++; 
		if(i+1<height&&j>=0 		&&tile[i+1][j]==EMPTY) count++; 
		if(i+1<height&&j+1<width	&&tile[i+1][j+1]==EMPTY) count++; 
		return count;
}

inline int ai::flags(int i,int j)
{
		int count=0;
		if(i-1>=0&&j-1>=0 			&&tile[i-1][j-1]==FLAG) count++; 
		if(i-1>=0         			&&tile[i-1][j]==FLAG) count++; 
		if(i-1>=0&&j+1<width		&&tile[i-1][j+1]==FLAG) count++; 
		if(		   j-1>=0   		&&tile[i][j-1]==FLAG) count++; 
		if(        j+1<width		&&tile[i][j+1]==FLAG) count++; 
		if(i+1<height&&j-1>=0 		&&tile[i+1][j-1]==FLAG) count++; 
		if(i+1<height&&j>=0 		&&tile[i+1][j]==FLAG) count++; 
		if(i+1<height&&j+1<width	&&tile[i+1][j+1]==FLAG) count++; 
		return count;
}

inline int ai::flags2(bool flag[MAX][MAX],int i,int j)
{
		int count=0;
		if(i-1>=0&&j-1>=0 			&&flag[i-1][j-1]) 	count++; 
		if(i-1>=0         			&&flag[i-1][j]) 	count++; 
		if(i-1>=0&&j+1<width		&&flag[i-1][j+1]) 	count++; 
		if(		   j-1>=0   		&&flag[i][j-1]) 	count++; 
		if(        j+1<width		&&flag[i][j+1]) 	count++; 
		if(i+1<height&&j-1>=0 		&&flag[i+1][j-1]) 	count++; 
		if(i+1<height&&j>=0 		&&flag[i+1][j]) 	count++; 
		if(i+1<height&&j+1<width	&&flag[i+1][j+1]) 	count++; 
		return count;
}

inline int ai::numbers(int i,int j)
{
		int count=0;
		if(i-1>=0&&j-1>=0 			&&tile[i-1][j-1]>=0) count++; 
		if(i-1>=0         			&&tile[i-1][j]>=0) count++; 
		if(i-1>=0&&j+1<width		&&tile[i-1][j+1]>=0) count++; 
		if(		   j-1>=0   		&&tile[i][j-1]>=0) count++; 
		if(        j+1<width		&&tile[i][j+1]>=0) count++; 
		if(i+1<height&&j-1>=0 		&&tile[i+1][j-1]>=0) count++; 
		if(i+1<height&&j>=0 		&&tile[i+1][j]>=0) count++; 
		if(i+1<height&&j+1<width	&&tile[i+1][j+1]>=0) count++; 
		return count;
}

bool ai::classic()
{

		for(int i=0;i<height;i++)
		{
				for(int j=0;j<width;j++)
				{
					
						if(tile[i][j]>=1)
						{
								//cout<<"Listening "<<i<<","<<j<<"tiles="<<emptytiles(i,j)<<"flags="<<flags(i,j)<<endl;
								int flgs=flags(i,j);
								int empty=emptytiles(i,j);
								if(flgs==tile[i][j]&&empty)
								{
											
											if(i-1>=0&&j-1>=0 			&&tile[i-1][j-1]==EMPTY) 		open(i-1,j-1,EMPTY);
											else if(i-1>=0         			&&tile[i-1][j]==EMPTY) 	 	open(i-1,j,EMPTY);
											else if(i-1>=0&&j+1<width		&&tile[i-1][j+1]==EMPTY) 	open(i-1,j+1,EMPTY);
											else if(		   j-1>=0   		&&tile[i][j-1]==EMPTY)  open(i,j-1,EMPTY);
											else if(        j+1<width		&&tile[i][j+1]==EMPTY)   	open(i,j+1,EMPTY);
											else if(i+1<height&&j-1>=0 		&&tile[i+1][j-1]==EMPTY) 	open(i+1,j-1,EMPTY);
											else if(i+1<height&&j>=0 		&&tile[i+1][j]==EMPTY)   	open(i+1,j,EMPTY);
											else if(i+1<height&&j+1<width	&&tile[i+1][j+1]==EMPTY) 	open(i+1,j+1,EMPTY);
										   
										    return true;
								}
								else if (tile[i][j]==empty+flgs&&empty)
								{
											
                                            if(i-1>=0&&j-1>=0 			&&tile[i-1][j-1]==EMPTY) 		open(i-1,j-1,FLAG);
											else if(i-1>=0         			&&tile[i-1][j]==EMPTY) 	 	open(i-1,j,FLAG);
											else if(i-1>=0&&j+1<width		&&tile[i-1][j+1]==EMPTY) 	open(i-1,j+1,FLAG);
											else if(		   j-1>=0   		&&tile[i][j-1]==EMPTY)  open(i,j-1,FLAG);
											else if(        j+1<width		&&tile[i][j+1]==EMPTY)   	open(i,j+1,FLAG);
											else if(i+1<height&&j-1>=0 		&&tile[i+1][j-1]==EMPTY) 	open(i+1,j-1,FLAG);
											else if(i+1<height&&j>=0 		&&tile[i+1][j]==EMPTY)   	open(i+1,j,FLAG);
											else if(i+1<height&&j+1<width	&&tile[i+1][j+1]==EMPTY) 	open(i+1,j+1,FLAG);
										   
											return true;
								}
						}
				}
		}
		return false;
}

//--------------------------------------------------------------------------------

bool ai::check(int i,int j,bool flag[MAX][MAX])
{
     bool count=true;
     if(i-1>=0&&j-1>=0 			&&tile[i-1][j-1] <(flags(i-1,j-1)+flags2(flag,i-1,j-1))&& tile[i-1][j-1]>0) count=false; 
     if(i-1>=0         			&&tile[i-1][j]   <(flags(i-1,j)  +flags2(flag,i-1,j))  && tile[i-1][j]  >0) count=false; 
     if(i-1>=0&&j+1<width		&&tile[i-1][j+1] <(flags(i-1,j+1)+flags2(flag,i-1,j+1))&& tile[i-1][j+1]>0) count=false;
     if(		   j-1>=0   	&&tile[i][j-1]   <(flags(i,j-1)  +flags2(flag,i,j-1))  && tile[i][j-1]  >0) count=false;
     if(        j+1<width		&&tile[i][j+1]   <(flags(i,j+1)  +flags2(flag,i,j+1))  && tile[i][j+1]  >0) count=false; 
     if(i+1<height&&j-1>=0 		&&tile[i+1][j-1] <(flags(i+1,j-1)+flags2(flag,i+1,j-1))&& tile[i+1][j-1]>0) count=false; 
     if(i+1<height&&j>=0 		&&tile[i+1][j]   <(flags(i+1,j)  +flags2(flag,i+1,j))  && tile[i+1][j]  >0) count=false;
     if(i+1<height&&j+1<width	&&tile[i+1][j+1] <(flags(i+1,j+1)+flags2(flag,i+1,j+1))&& tile[i+1][j+1]>0) count=false;
     return count;
}

//-------------------------------------------------------------------------------------


void ai:: dfs(int i,int j,bool border[MAX][MAX],int k,stack *borders)
{
		if(i<0||j<0||i>=height||j>=width||!border[i][j])
			return;
		else
		{
			cout<<"pushing "<<i<<" "<<j<<endl;
			border[i][j]=false;
			borders[k].push(point(i,j));
			dfs(i-1,j-1,border,k,borders);
			dfs(i-1,j,border,k,borders);
			dfs(i-1,j+1,border,k,borders);
			dfs(i,j-1,border,k,borders);
			dfs(i,j+1,border,k,borders);
			dfs(i+1,j-1,border,k,borders);
			dfs(i+1,j,border,k,borders);
			dfs(i+1,j+1,border,k,borders);
            if((j-2)>=0&&(i-2)>=0)             //edited
			{
				for(int g=0;g<5&&(i-2+g)<height;g++)
				dfs(i-2+g,j-2,border,k,borders);
			}
			if((j+2)<height&&(i-2)>=0)
			{
                 for(int g=0;g<5&&(i-2+g)<height;g++)
				 dfs(i-2+g,j+2,border,k,borders);
			}
			if((j-2)>=0&&(i+2)<height)
			{
                 for(int g=0;g<5&&(j-2+g)<width;g++)
			     dfs(i-2,j-2+g,border,k,borders);
            }
			if ((j+2)<height&&(i+2)<width)
			{
                 for(int g=0;g<5&&(j-2+g)<height;g++)
				 dfs(i+2,j-2+g,border,k,borders);}
			}
}

void ai::tanksolverbk(bool isflag[MAX][MAX],int Mines[MAX][MAX],bool isborder[MAX][MAX],stack border,int i=0)
{
		if(i>border.top)
		{
			if(isconsistent(isflag))
			{
                                   
					for(int I=0;I<height;I++)
					{
						for(int J=0;J<width;J++)
						{
								if(isborder[I][J]&&isflag[I][J])
								{
                                                                
									Mines[I][J]++;
									//cout<<"mines number "<<Mines[I][J]<<" i="<<I<<" j="<<J<<endl;
                                }
						}
					
					}			
			}
			return;
		}
		else
		{
				isflag[border.points[i].i][border.points[i].j]=true;
				if(check(border.points[i].i,border.points[i].j,isflag)) 
				{
					tanksolverbk(isflag,Mines,isborder,border,i+1);
                }
                isflag[border.points[i].i][border.points[i].j]=false;
					tanksolverbk(isflag,Mines,isborder,border,i+1);
		}
}

bool ai::isconsistent(bool flag[MAX][MAX])
{
        for(int i=0;i<width;i++)
        {
		      for(int j=0;j<height;j++)
		      {
			       if(tile[i][j]>0)
			       {
			       		if(tile[i][j]!=flags(i,j)+flags2(flag,i,j))
			       		{	
			       			return false;
						}			       	
			       }
			  }
		}
		return true;
}

bool ai::tanksolver()
{
		bool  border[MAX][MAX];
		stack borders[MAX];
		
		memset(border,0,sizeof(border));
		for(int i=0;i<height;i++)
		{
				for(int j=0;j<width;j++)
				{
					if(tile[i][j]==EMPTY&&numbers(i,j))
							border[i][j]=true;			
				}
		}
		
		int top=0;
//--------------------------------------------------------------------------		
		for(int i=0;i<height;i++)
		{
				for(int j=0;j<width;j++)
				{
					        if(border[i][j])
							{
									cout<<"Got.... "<<i<<" "<<j<<endl;
										dfs(i,j,border,top,borders);// to be corrected later....
										//top++;
							}			
				}
		}
//----------------------------------------------------------------------
		
            for(int i=0;i<height;i++)//added by kg
            {
				for(int j=0;j<width;j++)
				{
					if(tile[i][j]==EMPTY&&numbers(i,j))
							border[i][j]=true;			
				}
		    }
//---------------------------------------------------------------------------        
        	int Mines[MAX][MAX];
			bool isflag[MAX][MAX];
			memset(Mines,0,sizeof(Mines));
			memset(isflag,0,sizeof(isflag));
			tanksolverbk(isflag,Mines,border,borders[0]);			
//-------------------------------------------------------------------------------------
			int min=INT_MAX;
			int mini;
			int minj;
            for(int i=0;i<height;i++)
			{
				for(int j=0;j<width;j++)
				{
					if(border[i][j]&&min>Mines[i][j]) ////////might be error by kg/////as border[i][j] now is all false
					{
                                                                           /// mines[][] of other empty title will be zero
						min=Mines[i][j];
						mini=i;
						minj=j;
						//cout<<"i="<<mini<<" j="<<minj<<" min="<<min<<endl;
					}
				}
			}
			if(min==0)
			{
                      open(mini,minj,OPEN);
                      return true;
            }
            else
            {
                      char position[100]="(";
                      char temp[100];
                      itoa(mini+1,temp,10);
                      strcat(position,temp);
                      strcat(position,", ");
                      itoa(minj+1,temp,10);
                      strcat(position,temp);
                      strcat(position,")");
                 
                      al_show_native_message_box(display,"AI help!!!","Probablistic Chances of not having mine at position",position,NULL,NULL);
                      return true;
            }
			//if(Mines[i][j])
			//		cout<<"MINES "<<Mines[i][j]<<"\ti "<<i<<"\tj "<<j<<endl;
			/*if(min)
			{
				open(mini,minj,EMPTY);
				return true;
			}
			else
			{
			//part to be configured later...
			       cout<<"keshav error in tanks solver";
			}*/

}

