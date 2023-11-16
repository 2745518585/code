#include<bits/stdc++.h>
using namespace std;
const int N=2000001;
int n,m,s,p=1,t[N],f[N][2],f2[N][2],fa[N],ga[N],b[N],Q[N];
bool g[N],h[N];
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
void check(int x,int y)
{
    while(y!=x)
    {
        g[ga[y]]=g[ga[y]^1]=true;
        y=fa[y];
    }
}
void solve(int x,int y)
{
    int n=0;
    b[++n]=x;
    while(y!=x)
    {
        b[++n]=y;
        y=fa[y];
    }
    int s1=0,s2=0;
    f2[n][0]=f[b[n]][0],f2[n][1]=0;
    for(int i=n-1;i>=1;--i)
    {
        f2[i][0]=f[b[i]][0]+max(f2[i+1][0],f2[i+1][1]);
        f2[i][1]=f[b[i]][1]+f2[i+1][0];
    }
    s1=max(s1,f2[1][0]),s2=max(s2,f2[1][1]);
    f2[n][0]=f[b[n]][0],f2[n][1]=f[b[n]][1];
    for(int i=n-1;i>=1;--i)
    {
        f2[i][0]=f[b[i]][0]+max(f2[i+1][0],f2[i+1][1]);
        f2[i][1]=f[b[i]][1]+f2[i+1][0];
    }
    s1=max(s1,f2[1][0]);
    f[x][0]=s1,f[x][1]=s2;
}
void dfs(int x)
{
    f[x][1]=1;
    h[x]=true;
    int u=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa[x]) continue;
        if(h[a[i].m])
        {
            if(g[i]==false)
            {
                g[i]=g[i^1]=true;
                check(a[i].m,x);
            }
            else solve(x,a[i].m);
            continue;
        }
        fa[a[i].m]=x;
        ga[a[i].m]=i;
        dfs(a[i].m);
        if(g[i]==false)
        {
            f[x][0]+=max(f[a[i].m][0],f[a[i].m][1]);
            f[x][1]+=f[a[i].m][0];
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs(1);
    printf("%d",max(f[1][0],f[1][1]));
    return 0;
}