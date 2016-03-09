# include <iostream>
# include <math.h>
# include <stdlib.h>
# define LEFT 0
# define RIGHT 1

using namespace std;

class Interface
{
bool REQ,ACK,DATA,CLK,CHOKE;
//Pin Definition
char Receive_Register[/*sizeof(packet)*/50];
// Register Definition
char Send_Register[/*sizeof(packet)*/50];
char Receive_Buffer[50];
//Buffer Definition
char Send_Buffer[50];
bool Busy_Bit, Recieve_Bit, Transfer_Bit;
// Status Bits
void Routing_Algorithm(struct packet,int);
// Routing Algorithm
void Control_Logic(struct packet,int nnodes);
// Control Logic
void Buffer_Operations();
// Circular Buffer Operations
};

struct packet
{
int source_address;
int dest_address;
int data;
int start_timer;
int end_timer;
};

int randomnum (int a,int b)
{
int r;
if(b==1)
srand(time(NULL));
r = rand()%a;
return r;
}
void Routing_Algorithm (packet p,int nnodes)
{
float src,dest,start,end,nstages;
float mid;
int loc,grp,dir;
int i,s[10000];
/*cout<<"\nEnter The Nodes>>>";
cin>>nnodes;*/
nstages=0;
for (i=0;pow(2,i)<nnodes;i++)
nstages++;
cout<<"\nNo: Of Stages="<<nstages;
//Stages Corresponding To Nodes Are Created Successfuly
//cout<<"\nEnter The Source>>>";
src=p.source_address;
//cout<<"\nEnter The Destination>>>";
dest=p.dest_address;
grp=1;
start=0;
end=nnodes-1;
mid=(start+end)/2;
s[0]=src/2;
//cout<<src<<"="<<s[0];
cout<<"\n";
for(i=0;grp<nnodes;i++)
{
if ((start<mid)&&(dest<mid))
 loc=0;
if ((start<mid)&&(dest>mid))
 loc=1;
if ((start>mid)&&(dest<mid))
 loc=3;
if ((start>mid)&&(dest>mid))
 loc=3;
src=s[i];
switch(loc)
{ 
case 0:dir=LEFT;
       s[i+1]=src;
       end=mid;
       cout<<"\nLEFT";
       break;
case 1:dir=RIGHT;
       if(src<=(nnodes/(4*grp)))
       s[i+1]=src+(nnodes/(4*grp));
       else
       s[i+1]=src;
       start=mid+1;
       cout<<"\nRIGHT";
       break;
case 2:dir=LEFT;
       if(src>=(nnodes/(4*grp)))
       s[i+1]=src-(nnodes/(4*grp));
       else
       s[i+1]=src;
       end=mid;
       cout<<"\nLEFT";
       break;
case 3:dir=RIGHT;
       s[i+1]=src;
       start=mid+1;
       cout<<"\nRIGHT";
       break;
}
grp=grp*2;
//cout <<"\n";
//cout<<s[i]<<"="<<s[i+1];
mid=(start+end)/2;
}
cout<<"\n";
}
 
int toInteger(int *array,int size)
{
  int total=0;
  int i;
  for(i=0;i<size;i++)
    total+=array[i]*pow(2,(size-i-1));
  return total;
}

void Control_Logic (packet p,int nnodes)
{
  int nNodes;
  int nStages;
  int *outputString;
  int *controlString;
  int src,dest,i,j,temp;
  int direction;
  nNodes=nnodes;
  src=p.source_address;
  dest=p.dest_address;
  for(i=0;pow(2,i)!=nNodes;i++);
  nStages=i;
  outputString=(int *)malloc(sizeof(int)*nStages);
  controlString=(int *)malloc(sizeof(int)*(nNodes/4));
  outputString[0]=src/2;
  outputString[nStages-1]=dest/2;
  cout<<"\n"<<nStages<<" Stages, "<<outputString[0]<<" in stage 0 and "<<outputString[nStages-1]<<" in stage "<<(nStages-1)<<"\n";
  j=outputString[0];
  for(i=(nNodes/4)-1;i>=0;i--)
  {
    temp=j%2;
    controlString[i]=temp;
    j/=2;
  }
  for(i=0;i<(nNodes/4);i++)
    cout<<controlString[i];
  for(i=0;i<(nStages-1);i++)
  {
    cout<<"\nControl string:"<<toInteger(controlString,nnodes/4)<<"\tStage N-1:"<<outputString[nStages-1];
    if((toInteger(controlString,nNodes/4)<outputString[nStages-1])&&(controlString[i]==0))
      direction=RIGHT;
    else
      direction=LEFT;
    if((toInteger(controlString,nNodes/4)>outputString[nStages-1])&&(controlString[i]==1))
      direction=LEFT;
    else
      direction=RIGHT;
    cout<<"\tDirection:"<<direction;
    controlString[i+1]=direction;
    outputString[i+1]=toInteger(controlString,nNodes/4);
    cout<<"\n";
    for(j=0;j<(nNodes/4);j++)
     cout<<controlString[j];
  }
  cout<<"\n";
  for(i=0;i<nStages;i++)
    cout<<outputString[i]<<"\t";
  cout<<"\n";
}

int main ()
{
int nnodes;
cout <<" Enter The No:Of Nodes ";
cin >>nnodes;

packet p;
time_t begin,end;

p.data=0;
p.source_address=randomnum(nnodes,1);
cout<<"\n\nSource="<<p.source_address;
p.dest_address=randomnum(nnodes,0);
cout<<"\n\nDestination="<<p.dest_address;
begin=time(NULL);

p.start_timer=begin;

Routing_Algorithm(p,nnodes);

end=time(NULL);

p.end_timer=end;

float diff=difftime(end,begin);

cout<<diff;

begin=time(NULL);
p.start_timer=begin;
Control_Logic(p,nnodes);
end=time(NULL);
p.end_timer=end;
cout<<difftime(end,begin);

}



