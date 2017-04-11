#include<iostream>
#include <time.h>
using namespace std;

int p0_x,p0_y;  //leftmost top point

int dist(int x, int y) // distance from p0
{
    return (p0_x - x)*(p0_x - x) +
          (p0_y - y)*(p0_y - y);
}

int ang(int x1,int y1,int x2,int y2) //angle p0,p1,p2

{return (int)((y1 - p0_y) * (x2 - x1) -
              (x1 - p0_x) * (y2 - y1));
}

int partition(int x[],int y[],int l,int u) // for quick sort wrt angle
{
    int vx,vy,i,j;
    vx=x[l];vy=y[l];
    i=l;
    j=u+1;
    
    do
    {
        do
            i++;
            
        while((ang(x[i],y[i],vx,vy)<0 || (ang(x[i],y[i],vx,vy)==0 && dist(x[i],y[i])<dist(vx,vy)))&& i<=u);
        
        do
            j--;
        while(ang(x[j],y[j],vx,vy)>0 || (ang(x[j],y[j],vx,vy)==0 && dist(x[j],y[j])>dist(vx,vy)));
        
        if(i<j)
        {
            swap(x[i],x[j]);
            swap(y[i],y[j]);
        }
    }while(i<j);
    
    x[l]=x[j];y[l]=y[j];
    x[j]=vx;y[j]=vy;
    
    return(j);
}


void quick_sort(int x[],int y[],int l,int u) // wrt angle
{
    int j;
    if(l<u)
    {
        j=partition(x,y,l,u);
        quick_sort(x,y,l,j-1);
        quick_sort(x,y,j+1,u);
    }
}
 


int main()
{
int n;

// to take input from the user

cout<<"Enter number of points :"<<endl;
cin>>n; int p[2][n];
cout<<"Enter the "<<n<<" points x y"<<endl;
for(int i=0;i<n;i++)
{cin>>p[0][i]>>p[1][i];
}


//initialise manually
//n=7;
//int p[2][n]={0, 2,  1,  2,  3,  0,  3,3, 2 , 1 ,1 , 0 ,0,3};

if(n<3) cout<<"Not enough points"<<endl;

cout<<"The points are: "<<endl;
for(int i=0;i<n;i++)
cout<<p[0][i]<<" "<<p[1][i]<<endl;

clock_t t1,t2;
t1=clock();

int xmin=p[0][0],min=0;

 for(int i=1;i<n;i++)
   {
     int x = p[0][i];
     if ((x < xmin) || (xmin == x && p[1][i]>p[1][min]))
        xmin = p[0][i], min = i;
   }
   swap(p[0][min],p[0][0]);
   swap(p[1][min],p[1][0]);
   
   
   p0_x=p[0][0];p0_y=p[1][0];    //leftmost top point
   
   quick_sort(p[0],p[1],1,n-1);
   
   int m = 1; // Initialize size of modified array
   for (int i=1; i<n; i++)
   {
       
       while (i < n-1 && ang(p[0][i],p[1][i],p[0][i+1],p[1][i+1]) == 0)
          i++;                                                             // Keep removing i while angle of i and i+1 is same with respect to p0
 
       p[0][m] = p[0][i];
       p[1][m] = p[1][i];
       m++;  // Update size of modified array
   }
   
   if (m < 3) cout<<"Not enough points"<<endl;
 
 int hull[2][m];int s=0;   //size of hull
 
 hull[0][s]=p[0][0]; hull[1][s]=p[1][0];s++;
 hull[0][s]=p[0][1]; hull[1][s]=p[1][1];s++;
 hull[0][s]=p[0][2]; hull[1][s]=p[1][2];s++;
 
  for (int i = 3; i < m; i++)
   {

      p0_x=hull[0][s-2];p0_y=hull[1][s-2];  // second last point in hull
      
      while (ang(hull[0][s-1],hull[1][s-1], p[0][i],p[1][i]) >= 0)  // if second last, last and new point are not in anti-clockwise order
        
		 {
		  s--; p0_x=hull[0][s-2];p0_y=hull[1][s-2];    // remove the last point
		 }
      
	  hull[0][s]=p[0][i]; hull[1][s]=p[1][i];s++;
   }
   
    t2=clock();
    float diff= ((float)t2-(float)t1);
    
    
   cout<<"Points in convex hull are: "<<endl;
   
   for(int i=0;i<s;i++)
   
   cout<<hull[0][i]<<" "<<hull[1][i]<<endl;

   cout<<"Time taken: "<<diff<<endl;
}
