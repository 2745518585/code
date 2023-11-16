#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
int n,m,p=1,t[N],b[N],f[N],g[N];
struct road
{
    int m,q;
}a[N<<1];
int cmp(int a,int b)
{
    return a>b;
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa)
{
    b[x]=fa;
    g[x]=f[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        f[a[i].m]=f[x]+1;
        dfs(a[i].m,x);
        g[x]=max(g[x],g[a[i].m]);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    f[1]=1;
    dfs(1,0);
    int q=0;
    for(int i=1;i<=n;++i)
    {
        if(f[i]>f[q]) q=i;
    }
    f[q]=1;
    dfs(q,0);
    q=0;
    for(int i=1;i<=n;++i)
    {
        if(f[i]>f[q]) q=i;
    }
    for(int i=f[q]/2;i>=1;--i) q=b[q];
    dfs(q,0);
    for(int i=1;i<=n;++i) g[i]-=f[i];
    sort(g+1,g+n+1,cmp);
    printf("%d\n",g[m+1]+1);
    return 0;
}