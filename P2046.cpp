#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=10000001,M=10000001;
int n,s1,s2,t[N],p=1,f[N];
bool h[N];
struct road
{
    int m,q,w;
}a[M];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
int sum(int x,int y)
{
    return (x-1)*n+y;
}
int main()
{
    scanf("%d",&n);
    s1=n*n+1,s2=n*n+2;
    for(int i=1;i<=n+1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int r;
            scanf("%d",&r);
            if(i==1) road(s1,sum(i,j),r);
            else if(i==n+1) road(sum(i-1,j),s2,r);
            else road(sum(i-1,j),sum(i,j),r);
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n+1;++j)
        {
            int r;
            scanf("%d",&r);
            if(j==1) road(sum(i,j),s2,r);
            else if(j==n+1) road(s1,sum(i,j-1),r);
            else road(sum(i,j),sum(i,j-1),r);
        }
    }
    for(int i=1;i<=n+1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int r;
            scanf("%d",&r);
            if(i==1) road(sum(i,j),s1,r);
            else if(i==n+1) road(s2,sum(i-1,j),r);
            else road(sum(i,j),sum(i-1,j),r);
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n+1;++j)
        {
            int r;
            scanf("%d",&r);
            if(j==1) road(s2,sum(i,j),r);
            else if(j==n+1) road(sum(i,j-1),s1,r);
            else road(sum(i,j-1),sum(i,j),r);
        }
    }
    queue<int> Q;
    for(int i=1;i<=s2;++i) f[i]=1e9;
    f[s1]=0;
    h[s1]=true;
    Q.push(s1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                h[a[i].m]=true;
                Q.push(a[i].m);
            }
        }
    }
    printf("%d",f[s2]);
    return 0;
}