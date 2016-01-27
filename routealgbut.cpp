# include <iostream>
# include <math.h>
# define LEFT 0
# define RIGHT 1

using namespace std;

int main ()
{
int src,dest,start,end,nnodes,nstages;
float mid;
int loc,grp,dir;
int i,s[100];

cout<<"\nEnter The Nodes>>>";
cin>>nnodes;

nstages=0;

for (i=0;pow(2,i)<nnodes;i++)
nstages++;

cout<<"\nNo: Of Stages="<<nstages;

//Stages Corresponding To Nodes Are Created Successfuly

cout<<"\nEnter The Source>>>";
cin>>src;

cout<<"\nEnter The Destination>>>";
cin>>dest;

grp=1;
start=0;
end=nnodes-1;
mid=(start+end)/2;

s[0]=src/2;

cout<<src<<"="<<s[0];
for(i=0;grp<nnodes;i++)
{

if ((start<mid)&&(dest<mid))
 loc=0;
if ((start<mid)&&(dest>mid))
 loc=1;
if ((start>mid)&&(dest<mid))
 loc=2;
if ((start>mid)&&(dest>mid))
 loc=3;

src=s[i];
switch(loc)
{ 
case 0:dir=LEFT;
       s[i+1]=src;      
       end=mid+1;
       break;
case 1:dir=RIGHT;
       if(src<=(nnodes/(4*grp)))
       s[i+1]=src+(nnodes/(4*grp));
       else
       s[i+1]=src;
       start=mid;
       break;
case 2:dir=LEFT;
       if(src>=(nnodes/(4*grp)))
       s[i+1]=src-(nnodes/(4*grp));
       else
       s[i+1]=src;
       end=mid+1;
       break;
case 3:dir=RIGHT;
       s[i+1]=src;
       start=mid;
       break;
}

grp=grp*2;

cout <<"\n";
cout<<s[i]<<"="<<s[i+1];

mid=(start+end)/2;
}
cout<<"\n";
return 0;
}

