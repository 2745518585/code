#pragma GCC optimize("Ofast","inline")
#include<bits/stdc++.h>
//#define int long long
//#define id(x,y) ((y-1)*n+x)
using namespace std;
const int N=5e5;

struct node
{
    int u,v,nxt;
}e[N];

int n,head[N],cnt,ro,mx,fa[N],T;

void dfs(int x,int f,int dep)
{
    fa[x]=f;
    if(mx<dep)mx=dep,ro=x;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v==f)continue;
        dfs(v,x,dep+1);
    }
}

void sol()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        e[++cnt]=(node){u,v,head[u]};head[u]=cnt;
        e[++cnt]=(node){v,u,head[v]};head[v]=cnt;
    }
    ro=1;mx=0;
    dfs(ro,0,1);
    int t=ro;ro=1;mx=0;
    dfs(t,0,1);
    if(mx%4==0)
    {
        cout<<mx/2<<'\n';
        int w=mx/2+1,u=ro,v,p=mx;
        while(mx>w)u=fa[u],mx--;
        v=fa[u];
        for(int i=1;i<p/2;i+=2)cout<<u<<' '<<i<<'\n'<<v<<' '<<i<<'\n';
        return;
    }
    cout<<(mx/2+1)<<'\n';
    int w=(mx+1)/2,x=ro,p=mx;
    while(mx>w)x=fa[x],mx--;
    for(int i=0;i<=max(p-w,w-1);i++)cout<<x<<' '<<i<<'\n';    
}

void clear()
{
    cnt=0;
    for(int i=1;i<=n;i++)head[i]=0;
}

main()
{
    cin>>T;
    while(T--)sol(),clear();
}