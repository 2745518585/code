#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=1001;
int m,n,k,p=1,s1,s2,t[N],t0[N],c1[M][M],c2[M][M];
ll v,f[N],b1[M][M],b2[M][M];
bool h[N];
struct road
{
    int m,q;
    ll r,w;
}a[N];
void road(int x,int y,ll r,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
    a[++p].m=x;
    a[p].q=t[y];
    t[y]=p;
    a[p].r=0;
    a[p].w=-w;
    // printf("%d -> %d: %lld %lld\n",x,y,r,w);
}
bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i)
    {
        f[i]=1e18;
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
            if(a[i].r>0&&f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    return f[s2]!=1e18;
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
int sum(int x,int y)
{
    return x*(n-1)+y;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&m,&n,&k);
        int t1=sum(m,n-1)+1,t2=sum(m,n-1)+2;
        s1=sum(m,n-1)+3,s2=sum(m,n-1)+4;
        p=1;
        for(int i=1;i<=s2;++i) t[i]=0;
        v=0;
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n-1;++j)
            {
                ll r;
                scanf("%lld",&r);
                b1[i][j]=r;
                road(sum(i-1,j),sum(i,j),r,0);
                road(sum(i,j),sum(i-1,j),r,0);
            }
        }
        for(int i=1;i<=m-1;++i)
        {
            for(int j=1;j<=n;++j)
            {
                ll r;
                scanf("%lld",&r);
                b2[i][j]=r;
                if(j==1||j==n) continue;
                road(sum(i,j-1),sum(i,j),r,0);
                road(sum(i,j),sum(i,j-1),r,0);
            }
        }
        road(s1,t1,1e18,0);
        road(t2,s2,1e18,0);
        for(int i=1;i<=n-1;++i)
        {
            road(t1,sum(0,i),1e18,0);
        }
        for(int i=1;i<=n-1;++i)
        {
            road(sum(m,i),t2,1e18,0);
        }
        ll r=0;
        while(SPFA())
        {
            for(int i=1;i<=s2;++i) 
            {
                t0[i]=t[i];
                h[i]=false;
            }
            r+=dfs(s1,1e18);
        }
        for(int i=t[s1];i!=0;i=a[i].q)
        {
            if(a[i].m==t1) a[i].r=k;
        }
        for(int i=t[t2];i!=0;i=a[i].q)
        {
            if(a[i].m==s2) a[i].r=k;
        }
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n-1;++j)
            {
                road(sum(i-1,j),sum(i,j),k,1);
                road(sum(i,j),sum(i-1,j),k,1);
                c1[i][j]=p;
            }
        }
        for(int i=1;i<=m-1;++i)
        {
            for(int j=2;j<=n-1;++j)
            {
                road(sum(i,j-1),sum(i,j),k,1);
                road(sum(i,j),sum(i,j-1),k,1);
                c2[i][j]=p;
            }
        }
        while(SPFA())
        {
            for(int i=1;i<=s2;++i) 
            {
                t0[i]=t[i];
                h[i]=false;
            }
            r+=dfs(s1,1e18);
        }
        printf("%lld\n",v);
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n-1;++j)
            {
                printf("%lld ",b1[i][j]+max(a[c1[i][j]-2].r,a[c1[i][j]].r));
            }
            printf("\n");
        }
        for(int i=1;i<=m-1;++i)
        {
            printf("%lld ",b2[i][1]);
            for(int j=2;j<=n-1;++j)
            {
                printf("%lld ",b2[i][j]+max(a[c2[i][j]-2].r,a[c2[i][j]].r));
            }
            printf("%lld ",b2[i][n]);
            printf("\n");
        }
    }
    return 0;
}