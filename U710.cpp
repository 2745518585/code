#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3000001;
int n,q,p=1,t[N],b[N];
ll f[N][2];
bool h[N];
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
void dfs0(int x,int fa)
{
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(h[a[i].m]==true)
        {
            q=i/2;
            continue;
        }
        dfs0(a[i].m,x);
    }
}
void dfs(int x,int fa,int p)
{
    f[x][0]=0;
    f[x][1]=b[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||i/2==p) continue;
        dfs(a[i].m,x,p);
        f[x][0]+=max(f[a[i].m][0],f[a[i].m][1]);
        f[x][1]+=f[a[i].m][0];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d%d",&b[i],&x);
        road(x,i);
        road(i,x);
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        if(h[i]==false)
        {
            dfs0(i,0);
            dfs(a[q*2].m,0,q);
            ll w1=f[a[q*2].m][0];
            dfs(a[q*2+1].m,0,q);
            ll w2=f[a[q*2+1].m][0];
            s+=max(w1,w2);
        }
    }
    printf("%lld",s);
    return 0;
}