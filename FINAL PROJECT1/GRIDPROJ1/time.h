class TIME
{
	clock_t start,current;
	
	public:
		
		TIME()
		{
			reset();
		}
		
		void reset()
		{
			start=clock();
		}
		
		int gettime()
		{
			current = clock();
			return (int)((float)(current - start) / CLK_TCK);
		}
};
