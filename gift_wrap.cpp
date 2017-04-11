#include<iostream>
#include <time.h>
using namespace std;

bool counter_clock(int p[],int q[],int r[])
{
	int a = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
	return (a<0);
}

int main()
{
int n;

// to take input from the user

cout<<"Enter number of points :"<<endl;
cin>>n; int p[n][2];
cout<<"Enter the "<<n<<" points x y"<<endl;
for(int i=0;i<n;i++)
{cin>>p[i][0]>>p[i][1];
}


//initialise manually
//n=7;
//int p[n][2]={0, 3, 2, 2, 1, 1, 2, 1, 3, 0, 0, 0, 3, 3};

clock_t t1,t2;
t1=clock();

if(n<3) cout<<"Not enough points"<<endl;
else
{   int hull[n][2];int s=0; // number of points in convex hull
	int a,b,c;
	a=0;             // leftmost point
	for(int i=0;i<n;i++)
	if(p[i][0]<p[a][0]) a=i;
	
	hull[s][0]=p[a][0];
	hull[s][1]=p[a][1];
	s++;
	
	b=a;

	
	do
	{     c=(b+1)%n;
		  for (int i = 0; i < n; i++)
        {
           if (counter_clock(p[b], p[i], p[c]))
               c = i;                               // point at extreme counter-clockwise with respect to b
        }
        b=c;
        if(b!=a)
        {
		
        hull[s][0]=p[b][0];
		hull[s][1]=p[b][1];
		s++;
		}
		
	}while(b!=a);
	
	t2=clock();
    float diff= ((float)t2-(float)t1);
	
	cout<<"Points in Convex Hull are: "<<endl;
	
	for(int i=0;i<s;i++)
	
	cout<<hull[i][0]<<" "<<hull[i][1]<<endl;
	
	cout<<"Time taken: "<<diff<<endl;
}
}
