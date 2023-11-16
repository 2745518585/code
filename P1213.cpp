#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=10,M=500001;
const short d[10][10]={{},
{0,1,1,0,1,1,0,0,0,0},
{0,1,1,1,0,0,0,0,0,0},
{0,0,1,1,0,1,1,0,0,0},
{0,1,0,0,1,0,0,1,0,0},
{0,0,1,0,1,1,1,0,1,0},
{0,0,0,1,0,0,1,0,0,1},
{0,0,0,0,1,1,0,1,1,0},
{0,0,0,0,0,0,0,1,1,1},
{0,0,0,0,0,1,1,0,1,1}};
int a[N],g[M],h[M];
struct Queue
{
    int a[N],t;
};
int sum(int a[])
{
    int x=0;
    for(int i=1;i<=9;++i)
    {
        x=x*4+a[i];
    }
    return x;
}
void print(int x)
{
    int c[10001],t=0;
    while(x!=sum(a))
    {
        c[++t]=g[x];
        x=h[x];
    }
    for(int i=t;i>=1;--i)
    {
        printf("%d ",c[i]);
    }
}
int main()
{
    for(int i=1;i<=9;++i)
    {
        scanf("%d",&a[i]);
        a[i]=(a[i]/3)%4;
    }
    queue<Queue> Q;
    Q.push((Queue){a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],0});
    while(!Q.empty())
    {
        Queue k=Q.front();
        Q.pop();
        for(int i=1;i<=9;++i)
        {
            int x[10];
            for(int j=1;j<=9;++j)
            {
                x[j]=(k.a[j]+d[i][j])%4;
            }
            if(h[sum(x)]==0)
            {
                g[sum(x)]=i;
                h[sum(x)]=sum(k.a);
                Q.push((Queue){x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7],x[8],x[9],k.t+1});
            }
            if(sum(x)==0)
            {
                print(sum(x));
                return 0;
            }
        }
    }
}