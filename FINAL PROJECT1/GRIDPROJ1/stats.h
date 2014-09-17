class stats
{
	int played;
	int won;
	int disarmed;
	int bestspeed;
	
	public:
		
		stats(int PLAYED=0,int WON=0,int DISARMED=0,int BESTSPEED=0)
		{
			played=PLAYED;
			won=WON;
			disarmed=DISARMED;
			bestspeed=BESTSPEED;		
		}
		
		void reset()
		{
			*this=stats();
		}
		
		int   incplayed() {return ++played;}
		int   incwon() 	{return ++won;}
		int   incdisarmed(int d=0)
		{
			disarmed+=d; 
			return disarmed;
		}
		
		bool changebestspeed(int newspeed)
		{
			if(bestspeed==0) {bestspeed=newspeed;return true;}
			else if(newspeed<bestspeed)	{bestspeed=newspeed;return true;}
			return false;
		}
		
		int   getplayed() 	{return played;}
		int   getwon() 		{return won;}
		int   getdisarmed()	{return disarmed;}
		int   getspeed()	{return bestspeed;}
};


void initstats(stats STATS[])
{
	ifstream statfile(STATFILE,ios::binary);
	if(!statfile) 
	{
		for(int i=0;i<3;i++)
		{
			cerr<<"Unable to open file "<<STATFILE<<strerror(errno)<<". Setting default values";
			STATS[i].reset();
		}
	}
	else
	{
			statfile.read((char *)STATS,3*sizeof(stats));		
	}
	statfile.close();
}


bool writestats(stats STATS[])
{
	ofstream statfile(STATFILE,ios::binary);
	if(!statfile) {cerr<<"Unable to open "<<STATFILE<<":" <<strerror(errno); return false;}
	statfile.write((char *)STATS,3*sizeof(stats));
	return true;
}
