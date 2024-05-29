#pragma GCC optimize("Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+50,M=560;

struct node
{
    int x,l,r,y;
}Q[N];

struct ask
{
    int x,y;
}t[N];

int n,q,S=500,a[N],m,c,ans[N],vis[N],L[M],D[N],U[N],R[M],pre[M],s[N],f[N],tmp[N];
vector<pair<int,int>>in[N];

void solve(int l,int r)
{
    int w=r-l,h=0;
    for(int i=l;i<=r;i++)D[i-l]=a[i];
    s[0]=1;
    for(int i=1;i<=m;i++)if(Q[i].l<=l&&Q[i].r>=r)s[i]=1;
    for(int i=1,now=0;i<=m;i++)
    {
        if(Q[i].l<=l-1&&Q[i].r>l-1)now^=pre[i-1];
        if(s[i])L[++h]=now,now=0;
    }
    for(auto&x:in[r])while(!s[x.second])x.second--;
    for(int i=0;i<=h*2;i++)f[i]=0;
    for(int i=0;i<=w;i++)f[i]=D[w-i];
    for(int i=0;(1<<i)<=h;i++)for(int j=0;j<=h;j++)if((j>>i)&1)f[j]^=f[j^(1<<i)];
    for(int i=0;i<=h;i++)R[i]=f[i];
    for(int i=0;i<=h*2;i++)f[i]=0;
    for(int i=0;i<=h;i++)f[h-i]=L[i];
    for(int i=0;(1<<i)<=h;i++)for(int j=0;j<=h;j++)if(!((j>>i)&1))f[j]^=f[j^(1<<i)];
    for(int i=0;i<=min(h,w);i++)U[i]=f[i];
    for(int i=0;i<=w;i++)f[i]=D[i];
    for(int i=0;(1<<i)<=w;i++)if((h>>i)&1)
    for(int j=w-(1<<i);j>=0;j--)f[j+(1<<i)]^=f[j];
    for(int i=0;i<=w;i++)U[i]^=f[i];
    for(int i=0;i<=h;i++)f[i]=0;
    for(int i=0;i+w<=h;i++)f[i+w]=L[i];
    for(int i=0;(1<<i)<=h;i++)if(!((w>>i)&1))
    for(int j=h-(1<<i);j>=0;j--)f[j+(1<<i)]^=f[j];
    for(int i=0;i<=h;i++)R[i]^=f[i];
    for(int i=0,now=-1;i<=m;i++)pre[i]=R[now+=s[i]];
    for(int i=0;i<=w;i++)a[i+l]=U[i];
    for(auto x:in[r])ans[x.first]=pre[x.second];
    for(int i=0;i<=h;i++)L[i]=R[i]=0;
    for(int i=0;i<=w;i++)U[i]=D[i]=0;
    for(int i=1;i<=m;i++)s[i]=0;
    if(r==n)for(int i=0;i<=m;i++)pre[i]=0;
}

void solve()
{
    vis[n]=1;
    for(int i=1;i<=m;i++)vis[Q[i].l-1]=vis[Q[i].r]=1;
    for(int i=1;i<=c;i++)vis[t[i].y]=1,in[t[i].y].push_back(make_pair(i,t[i].x));
    for(int i=1,la=1;i<=n;i++)if(vis[i])solve(la,i),la=i+1;
    for(int i=1;i<=c;i++)cout<<ans[i]<<'\n';
    for(int i=1;i<=n;i++)vis[i]=0,in[i].clear();
    m=c=0;
}

main()
{
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    cin>>n>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    while(q--)
    {
        int opt;cin>>opt;
        if(opt==1)
        {
            m++;Q[m].x=m;
            cin>>Q[m].l>>Q[m].r;
        }
        else cin>>t[++c].y,t[c].x=m;
        if(!q||m==S)solve();
    }
    for(int i=1;i<=n;i++)cout<<a[i]<<'\n';
}