#define SIZE 401

class point
{
		public:
			int i,j;
			point(int I=0,int J=0)
			{
				i=I;
				j=J;
			}
};
struct node
{
		point data;
		node *next;
};

class stack
{
	   public:
	   int top;
       point points[SIZE];
       
       		stack()
       		{
				top=-1;	
			}
		
		int push(point p);
		point pop();
			
};

int stack::push(point p)
{
	cout<<"Pushing "<<p.i<<" "<<p.j<<endl;
 	points[++top]=p;   
}

point stack::pop()
{
    return points[top--]; 
}
