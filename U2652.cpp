#pragma GCC optimize("O2")
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=200001;
int n,m,q,tot,p=1,p2=1,t[N],t2[N],b[N],c[N],f[N],f2[N],h[N],r[N],d[N];
bool g[N],g2[N];
struct str
{
    int m,q;
}a[N<<1],a2[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void road2(int x,int y)
{
    a2[++p2].m=y;
    a2[p2].q=t2[x];
    t2[x]=p2;
}
void dfs(int x,int fa)
{
    b[x]=c[x]=++tot;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(b[a[i].m]==0)
        {
            dfs(a[i].m,x);
            c[x]=min(c[x],c[a[i].m]);
            if(c[a[i].m]>b[x]) g[i/2]=true;
        }
        c[x]=min(c[x],b[a[i].m]);
    }
}
void dfs2(int x)
{
    g2[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[i/2]==true||g2[a[i].m]==true) continue;
        dfs2(a[i].m);
    }
}
int dfs3(int x)
{
    h[x]=true;
    int s=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g2[a[i].m]==true||h[a[i].m]==true) continue;
        s+=dfs3(a[i].m);
    }
    return s;
}
void SPFA()
{
    queue<int> Q;
    for(int i=1;i<=q;++i) f[d[i]]=1e9,h[d[i]]=false;
    f[1]=0;
    h[1]=true;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t2[k];i!=0;i=a2[i].q)
        {
            if(f[k]+1<f[a2[i].m])
            {
                f[a2[i].m]=f[k]+1;
                h[a2[i].m]=true;
                Q.push(a2[i].m);
            }
        }
    }
}
int SPFA2(int x)
{
    queue<int> Q;
    for(int i=1;i<=q;++i) f2[d[i]]=1e9,h[d[i]]=false;
    f2[x]=0;
    h[x]=true;
    Q.push(x);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t2[k];i!=0;i=a2[i].q)
        {
            if(f2[k]+1<f2[a2[i].m])
            {
                f2[a2[i].m]=f2[k]+1;
                h[a2[i].m]=true;
                Q.push(a2[i].m);
            }
        }
    }
    int s=0;
    for(int i=1;i<=q;++i)
    {
        if(f2[d[i]]<=f[d[i]]) s+=r[d[i]];
    }
    return s;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;++i)
    {
        int x=read(),y=read();
        road(x,y);
        road(y,x);
    }
    dfs(1,0);
    dfs2(1);
    for(int i=t[1];i!=0;i=a[i].q) g2[a[i].m]=true;
    for(int i=1;i<=n;++i)
    {
        if(g2[i]!=true) continue;
        d[++q]=i;
        r[i]=1;
    }
    for(int i=2;i<=p;++i)
    {
        if(g2[a[i].m]==true&&g2[a[i^1].m]==true) road2(a[i].m,a[i^1].m);
        else if(g2[a[i].m]==true&&g2[a[i^1].m]==false) r[a[i].m]+=dfs3(a[i^1].m);
    }
    SPFA();
    int s=0;
    for(int i=1;i<=q;++i)
    {
        if(d[i]!=1) s=max(s,SPFA2(d[i]));
    }
    printf("%d",n-s);
    return 0;
}