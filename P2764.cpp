#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=100001,M=10000001;
int n,m,p=1,T,s1,s2,t1,t2,t[N],t0[N],f[N];
ll b[N];
struct str
{
    int m,q;
    ll r;
}a[M];
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
    scanf("%d%d",&n,&m);
    t1=n*2+1,t2=n*2+2,s1=n*2+3,s2=n*2+4,T=n*2+4;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(n+x,y,1e18);
        road(y,n+x,0);
    }
    for(int i=1;i<=n;++i)
    {
        road(t1,i,1e18);
        road(i,t1,0);
        road(n+i,t2,1e18);
        road(t2,n+i,0);
        ++b[i];
        --b[n+i];
    }
    for(int i=1;i<=n*2;++i)
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
    s1=t2,s2=t1;
    ll r=0;
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
    for(int i=1;i<=r;++i)
    {
        int x=t1-n;
        while(true)
        {
            for(int i=t[x+n];i!=0;i=a[i].q)
            {
                if(a[i^1].r>0&&a[i].m!=x)
                {
                    --a[i^1].r;
                    x=a[i].m;
                    break;
                }
            }
            if(x==t2) break;
            printf("%d ",x);
        }
        printf("\n");
    }
    printf("%lld",r);
    return 0;
}