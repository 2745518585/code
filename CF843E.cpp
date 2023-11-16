#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,s1,s2,s0,t1,t2,t[N],t0[N],f[N],b[N];
bool g[N];
struct road
{
    int m,q;
    ll r;
}a[N];
struct road2
{
    int x,y,t;
}a2[N];
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
    for(int i=1;i<=s0;++i) f[i]=0;
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
            ll z=dfs(a[i].m,min(r,a[i].r));
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
    scanf("%d%d%d%d",&n,&m,&s1,&s2);
    s0=n;
    for(int i=1;i<=m;++i)
    {
        int x,y,t;
        scanf("%d%d%d",&x,&y,&t);
        a2[i].x=x,a2[i].y=y,a2[i].t=t;
        if(t==0)
        {
            road(x,y,1e6);
            road(y,x,0);
        }
        else
        {
            road(x,y,1);
            road(y,x,1e6);
        }
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s0;++i) t0[i]=t[i];
        r+=dfs(s1,1e6);
    }
    printf("%lld\n",r);
    for(int i=1;i<=m;++i)
    {
        if(a2[i].t==0||a2[i].x!=s1) continue;
        for(int j=t[a2[i].x];j;j=a[j].q)
        {
            if(j%2==0&&a[j].m==a2[i].y)
            {
                if(a[j].r==0) g[i]=true;
                break;
            }
        }
    }
    p=1;
    for(int i=1;i<=s0;++i) t[i]=0;
    t1=s1,t2=s2,s1=n+1,s2=n+2,s0=n+2;
    for(int i=1;i<=m;++i)
    {
        if(a2[i].t==1)
        {
            ++b[a2[i].x];
            --b[a2[i].y];
            road(a2[i].x,a2[i].y,1e6);
            road(a2[i].y,a2[i].x,0);
        }
    }
    for(int i=1;i<=s0;++i)
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
    road(t2,t1,1e6);
    road(t1,t2,0);
    while(bfs())
    {
        for(int i=1;i<=s0;++i) t0[i]=t[i];
        dfs(s1,1e6);
    }
    for(int i=1;i<=m;++i)
    {
        if(a2[i].t==0)
        {
            printf("%d %d\n",0,1000000);
        }
        else
        {
            for(int j=t[a2[i].x];j;j=a[j].q)
            {
                if(j%2==0&&a[j].m==a2[i].y)
                {
                    if(!g[i]) printf("%d %d\n",a[j^1].r+1,1000000);
                    else printf("%d %d\n",a[j^1].r+1,a[j^1].r+1);
                }
            }
        }
    }
    return 0;
}