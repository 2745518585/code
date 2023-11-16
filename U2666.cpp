#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
int a[N][2],k,x,y,s,u1=1,u2=1;
void print()
{
    printf("%d\n",s);
    for(int i=s;i>=1;--i)
    {
        printf("%d %d\n",u1*a[i][0],u2*a[i][1]);
    }
}
int main()
{
    scanf("%d%d%d",&k,&x,&y);
    if(x<0) u1=-1,x=-x;
    if(y<0) u2=-1,y=-y;
    if((x+y)%2==1&&k%2==0)
    {
        printf("-1");
        return 0;
    }
    while(x>=k&&(x+y)>=k*2)
    {
        a[++s][0]=x,a[s][1]=y;
        x-=k;
    }
    while(y>=k&&(x+y)>=k*2)
    {
        a[++s][0]=x,a[s][1]=y;
        y-=k;
    }
    if(x+y==k)
    {
        a[++s][0]=x,a[s][1]=y;
        print();
        return 0;
    }
    if(x+y==0)
    {
        print();
        return 0;
    }
    if((x+y)%2==1&&x+y<k)
    {
        a[++s][0]=x,a[s][1]=y;
        x+=k;
    }
    if((x+y)%2==1)
    {
        a[++s][0]=x,a[s][1]=y;
        int p=x-k;
        x-=p;
        y-=k-abs(p);
    }
    int p=x+y-k;
    a[++s][0]=x,a[s][1]=y;
    if(x>=(k+p)/2)
    {
        x-=(k+p)/2;
        y+=(k-p)/2;
    }
    else
    {
        x+=(k-p)/2;
        y-=(k+p)/2;
    }
    a[++s][0]=x,a[s][1]=y;
    print();
    return 0;
}