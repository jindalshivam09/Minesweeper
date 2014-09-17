bool save(GRID grid)
{
	char path[100];
	int i=0;
	char token[100];
	while(1)
	{
		strcpy(path,SAVEFILEBASEPATH);
		strcat(path,itoa(i,token,10));
		strcat(path,EXTENSION);
		if(!ifstream(path))break;
		i++;
	}
	
	if(grid.puttofile(path))
		al_show_native_message_box(display,"Saved","Save Successfully to",path,NULL,NULL);
	else
		al_show_native_message_box(display,"Error","Save Error",strerror(errno),NULL,1);
}

bool open(GRID &grid)
{
	char name[100];
	scanf("%s",name);	
	char path[100];
		
	strcpy(path,SAVEFILEBASEPATH);
	strcat(path,name);
	strcat(path,EXTENSION);
	cout<<path;
	ifstream infile(path);
	if(infile)
	{
              
		      infile.close();
		grid=GRID(path);
		return true;
	}
	return false;
}

