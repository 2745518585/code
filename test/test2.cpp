#include<bits/stdc++.h>
typedef std::pair<int,int> pii;
const int N=1e5+3;
int n,m,M,vis[N],ord[N],dfc,p[N],siz[N],dp[N],dpc[N],ans,ansc;
std::vector<int>g[N],g1[N];
std::set<pii>t;
void Dfs1(int u){
	vis[u]=1;
	for(int v:g[u])if(!vis[v])Dfs1(v);
	ord[++dfc]=u;
}
void Dfs2(int u,int r){
	p[u]=r,++siz[r],++dp[r];
	for(int v:g1[u])if(!p[v])Dfs2(v,r);
}
int main(){
	int u,v;
	scanf("%d%d%d",&n,&m,&M);
	for(;m--;)scanf("%d%d",&u,&v),g[u].push_back(v),g1[v].push_back(u);
	for(u=1;u<=n;u++)if(!vis[u])Dfs1(u);
	for(int i=n;i;i--)if(!p[u=ord[i]])Dfs2(u,u);
	for(u=1;u<=n;u++)dpc[u]=1;
	for(int i=1;i<=n;i++){
		u=ord[i];
		for(int v:g[u])if(p[u]!=p[v]&&!t.count(pii(p[u],p[v]))){
			t.insert(pii(p[u],p[v]));
			if(dp[p[v]]+siz[p[u]]==dp[p[u]])
				dpc[p[u]]=(dpc[p[u]]+dpc[p[v]])%M;
			if(dp[p[v]]+siz[p[u]]>dp[p[u]])
				dp[p[u]]=dp[p[v]]+siz[p[u]],dpc[p[u]]=dpc[p[v]];
		}
	}
	for(u=1;u<=n;u++)if(u==p[u]){
		if(dp[p[u]]==ans)
			ansc=(ansc+dpc[p[u]])%M;
		if(dp[p[u]]>ans)
			ans=dp[p[u]],ansc=dpc[p[u]];
	}
	printf("%d\n%d\n",ans,ansc);
	return 0;
}
