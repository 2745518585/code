#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,m,p=1,t[N];
ll q=1e18,b[N],f[N],f2[N],g[N],s,s2;
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa)
{
    if(b[x]>2)
    {
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==fa) continue;
            dfs(a[i].m,x);
        }
        return;
    }
    f[x]=f2[x]=g[x]=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        if(f[a[i].m]>=f[x])
        {
            f2[x]=f[x];
            f[x]=f[a[i].m];
        }
        else if(f[a[i].m]>f2[x])
        {
            f2[x]=f[a[i].m];
        }
        g[x]=max(g[x],g[a[i].m]);
    }
    if(b[x]==1)
    {
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==fa) continue;
            if(f[a[i].m]!=f[x])
            {
                s=max(s,f[x]+f[a[i].m]+1);
                s2=max(s2,f[x]+g[a[i].m]+1);
            }
            else
            {
                s=max(s,f2[x]+f[a[i].m]+1);
                s2=max(s2,f2[x]+g[a[i].m]+1);
            }
        }
        ++f[x];
        ++f2[x];
        ++g[x];
    }
    else
    {
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==fa) continue;
            if(f[a[i].m]!=f[x])
            {
                s2=max(s2,f[x]+f[a[i].m]+1);
            }
            else
            {
                s2=max(s2,f2[x]+f[a[i].m]+1);
            }
        }
        g[x]=f[x]+1;
        f[x]=f2[x]=0;
    }
}
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
        q=min(q,b[i]);
    }
    if(q>2)
    {
        printf("%lld/1",q);
        return 0;
    }
    dfs(1,0);
    if(s*2>=s2)
    {
        printf("1/%lld",s);
    }
    else
    {
        if(s2%2==0) printf("1/%lld",s2/2);
        else printf("2/%lld",s2);
    }
}