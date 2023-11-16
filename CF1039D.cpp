#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
int n,m,tot,p=1,t[N],f[N],g[N],b[N],d[N];
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int b;
}T[N];
bool cmp(int a,int b)
{
    return T[a].b>T[b].b;
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa)
{
    T[x].b=++tot;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
    }
}
void solve(int x)
{
    f[x]=0,g[x]=1;
    int s1=0,s2=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(T[a[i].m].b<T[x].b) continue;
        f[x]+=f[a[i].m];
        if(g[a[i].m]>s1) s2=s1,s1=g[a[i].m];
        else if(g[a[i].m]>s2) s2=g[a[i].m];
    }
    if(s1+s2+1>=m) ++f[x],g[x]=0;
    else g[x]=s1+1;
}
int check(int x)
{
    m=x;
    for(int i=1;i<=n;++i) solve(b[i]);
    return f[1];
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
    dfs(1,0);
    for(int i=1;i<=n;++i) b[i]=i;
    sort(b+1,b+n+1,cmp);
    int q=min((int)(sqrt(n)*2),n);
    for(int i=1;i<=q;++i) d[i]=check(i);
    for(int i=q+1;i<=n;++i)
    {
        int x=i,t=1,w=check(i);
        while(t>=1)
        {
            if(x+t<=n&&check(x+t)==w) x+=t,t*=2;
            else t/=2;
        }
        for(int j=i;j<=x;++j) d[j]=w;
        i=x;
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d\n",d[i]);
    }
    return 0;
}