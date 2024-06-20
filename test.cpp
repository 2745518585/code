#include <bits/stdc++.h>

#define N 100005
#define hs(x,y,z) ((x)+1ll*(y)*N+1ll*(z)*N*N)

typedef long long ll;

using namespace std;

ll nw;
int s,n,a[N*3],vis[N];
struct edge{int v,w,nxt;};
unordered_map<ll,int>mp;
void updt(int,int,int,int);
struct tRee
{
	edge e[N*2];
	int id,en,cnt,c[N],d[N],fm[N],dfn[N],sz[N],sn[N],head[N];
	void adde(int u,int v,int w){e[++en]={v,w,head[u]};head[u]=en;}
	void read()
	{
		int i,u,v,w;
		for(i=1;i<n;++i)
		{
			scanf("%d %d %d",&u,&v,&w);
			adde(u,v,w);adde(v,u,w);
		}
	}
	void dfs(int u,int fa)
	{
		int i,v;
		fm[dfn[u]=++cnt]=u;sz[u]=1;
		for(i=head[u];i;i=e[i].nxt)
			if((v=e[i].v)!=fa)
			{
				d[v]=d[u]+e[i].w;
				dfs(v,u);sz[u]+=sz[v];
				if(sz[sn[u]]<sz[v])sn[u]=v;
			}
	}
	void add(int u)
	{
		int i;vis[u]|=1<<id;
		if(!sn[u]){updt(id,u,u,1);return;}
		updt(id,u,c[sn[u]],1);
		for(i=dfn[u]+1;i<dfn[sn[u]];++i)updt(id,fm[i],c[sn[u]],0);
		for(i=dfn[sn[u]]+sz[sn[u]];i<dfn[u]+sz[u];++i)updt(id,fm[i],c[sn[u]],0);
	}
}A[3];
void updt(int p,int k,int x,int fl)
{
	if(!fl)if(vis[k]==s)nw-=--mp[hs(A[0].c[k],A[1].c[k],A[2].c[k])];
	A[p].c[k]=x;if(vis[k]==s)nw+=mp[hs(A[0].c[k],A[1].c[k],A[2].c[k])]++;
}

vector<pair<int,int>>g[N*3];

int main()
{
	ll ans=0;
	int i,k,tl=0;
	scanf("%d",&n);
	for(i=0;i<3;++i){A[i].read();A[i].id=i;A[i].dfs(1,0);}
	for(k=0;k<3;++k)for(i=1;i<=n;++i)a[++tl]=A[k].d[i];
	sort(a+1,a+tl+1);tl=unique(a+1,a+tl+1)-a-1;
	for(k=0;k<3;++k)for(i=1;i<=n;++i)g[lower_bound(a+1,a+tl+1,A[k].d[i])-a].push_back({k,i});
	for(s=1;s<8;++s)
	{
		mp.clear();nw=0;
		memset(vis,0,sizeof(vis));
        ll w=0;
		for(i=tl;i;--i)
		{
			for(auto t:g[i])if(s&(1<<t.first))A[t.first].add(t.second);
			w+=(a[i]-a[i-1])*nw;
		}
        printf("%d %lld\n",s,w);
        ans+=(__builtin_popcount(s)&1?1ll:-1ll)*w;
	}
	printf("%lld\n",ans);
	return 0;
}

