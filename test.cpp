#pragma GCC optimize("Ofast","inline")
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+500,mod=998244353;

struct edge
{
    int u,v,nxt;
}e[N];

struct node
{
    int a,b;

    node operator+(node x)
    {
        return (node){(x.a+a)%mod,(x.b+b)%mod};
    }

    void mul(int x)
    {
        a=a*x%mod;b=b*x%mod;
    }
}f[N][3],s[N][3],las[N][2],w[N],lw[N];

node merge(node a,node b)
{
    return (node){(a.a*b.b%mod+a.b*b.a%mod)%mod,a.b*b.b%mod};
}

int n,k,head[N],cnt,in[N],inv1,inv2,ans,ro,vis[N],st[N],top,C;

int ksm(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1)ans=ans*a%mod;
        b>>=1;a=a*a%mod;
    }
    return ans;
}

void merge(node*f,node*h)
{
    node g[3];for(int i=0;i<3;i++)g[i]=f[i];
    for(int j=0;j<3;j++)
    for(int p=0;p<3;p++)
    {
        node re=merge(g[j],h[p]);
        if(j==1)re.mul(inv1);if(p==1)re.mul(inv1);
        int to=min(j+1,2ll);
        f[to]=f[to]+re;
    }
}

void dfs(int x,int fa)
{
    f[x][0]=(node){k*inv2%mod,k*inv2%mod};
    for(int i=head[x];i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(in[v]==2||v==fa)continue;
        dfs(v,x);merge(f[x],f[v]);
    }
    if(in[x]!=2)for(int i=0;i<3;i++)ans+=f[x][i].a;
}

void find(int x)
{
    vis[x]=1;st[++top]=x;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(in[v]==2&&!vis[v])return find(v);
    }
}

main()
{
    cin>>n>>k;
    inv1=ksm(k,mod-2),inv2=ksm(1-k,mod-2);C=ksm(1-k,n);
    for(int i=1;i<=n;i++)
    {
        int u,v;cin>>u>>v;++in[u],++in[v];
        e[++cnt]=(edge){u,v,head[u]};head[u]=cnt;
        e[++cnt]=(edge){v,u,head[v]};head[v]=cnt;
    }
    queue<int>q;
    for(int i=1;i<=n;i++)if(in[i]==1)q.push(i);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=e[i].nxt)
        {
            int v=e[i].v;--in[v];
            if(in[v]==1)q.push(v);
        }
    }
    for(int i=1;i<=n;i++)if(in[i]==2)dfs(i,0),ro=i;
    find(ro);
    for(int i=1;i<=top;i++)for(int j=0;j<3;j++)s[i][j]=f[st[i]][j];
    for(int i=1;i<=top;i++)for(int j=0;j<3;j++)f[i][j]=s[i][j];
    for(int i=top;i>=1;i--)
    {
        if(i!=top)merge(s[i],s[i+1]);
        int val=0;
        for(int j=0;j<3;j++)val+=s[i][j].a;
        ans+=val;
    }
    node tmp;
    for(int i=1;i<=top;i++)
    {
        w[i]=f[i][0]+f[i][1];w[i].mul(inv1);
        w[i]=w[i]+f[i][2];
        if(i==1)tmp=w[i];else tmp=merge(tmp,w[i]);
    }
    ans=ans+tmp.a;
    for(int i=top;i>=1;i--)
    {
        las[i][0]=f[i][0];
        las[i][1]=f[i][1];las[i][1].mul(inv1);
        las[i][1]=las[i][1]+f[i][2];
        if(i==top)continue;
        node a=las[i][0],b=las[i][1];
        las[i][0]=merge(a,las[i+1][0]);las[i][0].mul(inv1);las[i][0]=las[i][0]+merge(a,las[i+1][1]);
        las[i][1]=merge(b,las[i+1][0]);las[i][1].mul(inv1);las[i][1]=las[i][1]+merge(b,las[i+1][1]);
    }
    for(int i=top;i>=1;i--)lw[i]=lw[i+1]+las[i][0]+las[i][1];
    for(int i=1;i<top;i++)
    {
        int val=lw[i+1].a;
        node now;
        now=f[i][1];now.mul(inv1);
        now=now+f[i][0]+f[i][2];
        if(i==1)
        {
            now=merge(now,lw[i+1]);
            ans+=now.a;
        }
        else
        {
            now=merge(now,tmp);
            now=merge(now,lw[i+1]);
            ans+=now.a;
        }
        if(i==1)tmp=w[i];
        else tmp=merge(tmp,w[i]);
    }
    cout<<(ans%mod*C%mod+mod)%mod;
}
