#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=100001,M=1000001;
int m,n,d1,d2,T,p=1,s1,s2,t1,t2,t[N],t0[N],f[N];
ll b[N];
bool h[N];
struct str
{
    int m,q;
    ll r;
}a[M];
int sum(int x,int y)
{
    return (x-1)*n+y;
}
bool check(int x,int y)
{
    return x>=1&&x<=m&&y>=1&&y<=n&&!h[sum(x,y)];
}
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
bool bfs()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=T;++i) f[i]=0;
    f[s1]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]==0&&a[i].r!=0)
            {
                f[a[i].m]=f[k]+1;
                Q.push(a[i].m);
            }
        }
    }
    return f[s2]!=0;
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[a[i].m]==f[x]+1&&a[i].r!=0)
        {
            int z=dfs(a[i].m,min(r,a[i].r));
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
            }
            else f[a[i].m]=0;
            if(r==0) return s; 
        }
    }
    return s;
}
int main()
{
    scanf("%d%d%d%d",&m,&n,&d1,&d2);
    t1=m*n*2+1,t2=m*n*2+2,s1=m*n*2+3,s2=m*n*2+4,T=m*n*2+4;
    int dx[4]={d1,d1,d2,d2},dy[4]={-d2,d2,-d1,d1};
    if(d1==d2) dx[2]=dx[3]=dy[2]=dy[3]=1e9;
    for(int i=1;i<=m;++i)
    {
        scanf("\n");
        for(int j=1;j<=n;++j)
        {
            char c=getchar();
            h[sum(i,j)]=(c=='x');
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(h[sum(i,j)]==true) continue;
            road(t1,sum(i,j),1);
            road(sum(i,j),t1,0);
            road(m*n+sum(i,j),t2,1);
            road(t2,m*n+sum(i,j),0);
            road(sum(i,j),m*n+sum(i,j),0);
            road(m*n+sum(i,j),sum(i,j),0);
            ++b[sum(i,j)];
            --b[m*n+sum(i,j)];
            for(int k=0;k<4;++k)
            {
                if(check(i+dx[k],j+dy[k]))
                {
                    road(m*n+sum(i,j),sum(i+dx[k],j+dy[k]),1e18);
                    road(sum(i+dx[k],j+dy[k]),m*n+sum(i,j),0);
                }
            }
        }
    }
    for(int i=1;i<=T;++i)
    {
        if(b[i]<0)
        {
            road(s1,i,-b[i]);
            road(i,s1,0);
        }
        else if(b[i]>0)
        {
            road(i,s2,b[i]);
            road(s2,i,0);
        }
    }
    road(t2,t1,1e18);
    road(t1,t2,0);
    while(bfs())
    {
        for(int i=1;i<=T;++i) t0[i]=t[i];
        dfs(s1,1e18);
    }
    ll r=0;
    s1=t2;
    s2=t1;
    for(int i=t[t2];i!=0;i=a[i].q)
    {
        if(a[i].m==t1)
        {
            r+=a[i^1].r;
            a[i].r=a[i^1].r=0;
        }
    }
    while(bfs())
    {
        for(int i=1;i<=T;++i) t0[i]=t[i];
        r-=dfs(s1,1e18);
    }
    printf("%lld",r);
    return 0;
}