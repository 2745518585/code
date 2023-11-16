#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=100001;
int n,m,p=1,s1,s2,t[N],t0[N],d[N][2];
char c[N];
bool h[N];
ll v,f[N];
struct road
{
    int m,q;
    ll r,w;
}a[N];
struct str
{
    int x,y;
    ll w;
}b[N];
void road(int x,int y,ll r,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
}
bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i)
    {
        f[i]=-1e18;
        h[i]=false;
    }
    f[s1]=0;
    h[s1]=true;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r>0&&f[k]+a[i].w>f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    return f[s2]!=-1e18;
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(h[a[i].m]==false&&a[i].r>0&&f[a[i].m]==f[x]+a[i].w)
        {
            h[a[i].m]=true;
            ll z=dfs(a[i].m,min(r,a[i].r));
            h[a[i].m]=false;
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
                v+=z*a[i].w;
            }
            else f[a[i].m]=0;
            if(r==0) return s;
        }
    }
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%lld",&b[i].x,&b[i].y,&b[i].w);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s%d%d",z,&d[i][0],&d[i][1]);
        c[i]=z[0];
    }
    ll s=0;
    for(int k=1;k<=n;++k)
    {
        s1=n*2+k*2+1,s2=n*2+k*2+2;
        p=1;
        for(int i=1;i<=s2;++i) t[i]=0;
        v=0;
        for(int i=1;i<=k;++i)
        {
            road(s1,n*2+i,1,0);
            road(n*2+i,s1,0,0);
        }
        for(int i=1;i<=k;++i)
        {
            int w1=0,w2=1e9;
            for(int j=1;j<=m;++j)
            {
                if(c[j]=='L'&&i>=d[j][1]+1) w1=max(w1,d[j][0]+1);
                if(c[j]=='R'&&i<=k-d[j][1]) w2=min(w2,d[j][0]-1);
            }
            for(int j=1;j<=n;++j)
            {
                if(b[j].x>=w1&&b[j].x<=w2)
                {
                    road(n*2+i,j,1,0);
                    road(j,n*2+i,0,0);
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            road(i,n+i,1,b[i].w);
            road(n+i,i,0,-b[i].w);
        }
        for(int i=1;i<=k;++i)
        {
            int w1=0,w2=1e9;
            for(int j=1;j<=m;++j)
            {
                if(c[j]=='D'&&i>=d[j][1]+1) w1=max(w1,d[j][0]+1);
                if(c[j]=='U'&&i<=k-d[j][1]) w2=min(w2,d[j][0]-1);
            }
            for(int j=1;j<=n;++j)
            {
                if(b[j].y>=w1&&b[j].y<=w2)
                {
                    road(n+j,n*2+k+i,1,0);
                    road(n*2+k+i,n+j,0,0);
                }
            }
        }
        for(int i=1;i<=k;++i)
        {
            road(n*2+k+i,s2,1,0);
            road(s2,n*2+k+i,0,0);
        }
        while(SPFA())
        {
            for(int i=1;i<=s2;++i) 
            {
                t0[i]=t[i];
                h[i]=false;
            }
            dfs(s1,1e18);
        }
        s=max(s,v);
    }
    printf("%lld",s);
    return 0;
}