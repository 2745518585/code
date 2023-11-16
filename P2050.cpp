#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=100001,M=10000001;
int n,m,p=1,v,s1,s2,t[N],t0[N];
ll f[N],b[N],c[101][101],q,g[N];
bool h[N];
struct str
{
    int m,q;
    ll r,w;
}a[M];
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
    if(f[s2]!=1e18) return true;
    return false;
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
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
        q+=b[i];
    }
    s1=n+q*m+1;
    s2=n+q*m+2;
    for(int i=1;i<=n;++i)
    {
        road(s1,i,b[i],0);
        road(i,s1,0,0);
    }
    for(int i=1;i<=m;++i)
    {
        road(n+(i-1)*q+1,s2,1,0);
        road(s2,n+(i-1)*q+1,0,0);
        g[i]=1;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            scanf("%lld",&c[i][j]);
            road(i,n+(j-1)*q+1,1,c[i][j]);
            road(n+(j-1)*q+1,i,0,-c[i][j]);
        }
    }
    ll r=0;
    while(r<q)
    {
        SPFA();
        for(int i=1;i<=s2;++i) 
        {
            t0[i]=t[i];
            h[i]=false;
        }
        r+=dfs(s1,1e18);
        for(int i=1;i<=m;++i)
        {
            int x=n+(i-1)*q+g[i];
            for(int j=t[x];j!=0;j=a[j].q)
            {
                if(a[j].m==s2)
                {
                    if(a[j].r==0)
                    {
                        ++g[i];
                        if(g[i]==q+1) break;
                        for(int k=1;k<=n;++k)
                        {
                            road(k,x+1,1,c[k][i]*g[i]);
                            road(x+1,k,0,-c[k][i]*g[i]);
                        }
                        road(x+1,s2,1,0);
                        road(s2,x+1,0,0);
                    }
                    break;
                }
            }
        }
    }
    printf("%lld",v);
    return 0;
}