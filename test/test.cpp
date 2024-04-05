#pragma GCC optimize("Ofast","inline")
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+500,M=2e7+19260+817;

struct node
{
	int u,v,nxt;
}e[N];

int n,d,head[N],cnt,pri[N],cc,a[N],fir[N],f[N],mx[N],tot,tl[M],tr[M],sa[M],sb[M],ro[N],ans[N],sz[N],vis[N],dfn[N],ccc;ll sum[M];
vector<pair<int,int>>p[N];vector<int>in[N];int st[M],top;pair<int,int>g[N];

void init()
{
	for(int i=2;i<=n;i++)
	{
		if(!a[i])pri[++cc]=fir[i]=i;
		for(int j=1;j<=cc&&i*pri[j]<=n;j++)
		{
			a[i*pri[j]]=1;fir[i*pri[j]]=pri[j];
			if(i%pri[j]==0)break;
		}
	}
	p[1].push_back(make_pair(1,1));f[1]=1;
	vis[1]=1;
	for(int i=2;i<=n;i++)
	{
		int num=0,x=i;ll k=1;
		while(x%fir[i]==0)++num,x/=fir[i];
		mx[i]=max(mx[x],num);
		if(mx[i]<=d)f[i]=-f[i/fir[i]];
		else continue;
		for(int j=1;j<=d-num+1&&k<=n;j++)k*=fir[i];
		if(k==1)continue;
		int c=0;
		for(auto t:p[x])if(1ll*t.first*k<=n)t.first*=k,t.second*=-1,g[c++]=t,vis[t.first]=1;
		int pos1=0,pos2=0;
		for(int j=0;j<c+p[x].size();j++)
		{
			if(pos1==p[x].size())p[i].push_back(g[pos2++]);
			else if(pos2==c)p[i].push_back(p[x][pos1++]);
			else if(p[x][pos1]<g[pos2])p[i].push_back(p[x][pos1++]);
			else p[i].push_back(g[pos2++]);
		}
	}
	ccc=0;
	for(int i=1;i<=n;i++)if(vis[i])dfn[i]=++ccc;
	for(int i=1;i<=n;i++)for(auto&x:p[i])x.first=dfn[x.first];
	for(int i=1;i<=n;i++)if(vis[i]&&f[i]!=0)for(int j=i;j<=n;j+=i)in[j].push_back(dfn[i]);
	// cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n';
}

#define mid ((l+r)>>1)

void add(int&x)
{
	if(top)x=st[top--];
	else x=++tot;
}

void erase(int x)
{
	st[++top]=x;tl[x]=tr[x]=sum[x]=sa[x]=sb[x]=0;
}

void merge(int&a,int b,int l,int r)
{
	if(!a||!b)return void(a=a+b);
	if(l==r)
	{
		sa[a]+=sa[b];sb[a]+=sb[b];sum[a]=1ll*sa[a]*sb[a];
		return;
	}
	merge(tl[a],tl[b],l,mid);merge(tr[a],tr[b],mid+1,r);
	sum[a]=sum[tl[a]]+sum[tr[a]];erase(b);
}

int sta[N<<1],pos,da[N],db[N];

void insert(int&x,int l,int r)
{
	if(!x)add(x);
	if(l==r)
	{
		int t=pos;
		while(sta[pos]==sta[t])sa[x]+=da[pos],sb[x]+=db[pos],++pos;
		sum[x]=1ll*sa[x]*sb[x];
		return;
	}
	if(sta[pos]<=mid&&sta[pos]>=l)insert(tl[x],l,mid);
	if(sta[pos]>mid&&sta[pos]<=r)insert(tr[x],mid+1,r);
	sum[x]=sum[tl[x]]+sum[tr[x]];
}

void dfs(int x,int fa)
{
	add(ro[x]);sz[x]=(mx[a[x]]*2<=d?1:0);
	if(f[a[x]])
	{
		int top=0;pos=1;
		int p1=0,p2=0,w=a[x],n1=p[w].size(),n2=in[w].size();
		while(p1<n1||p2<n2)
		{
			if(p1==n1)sta[++top]=in[w][p2++],da[top]=0,db[top]=f[w];
			else if(p2==n2)sta[++top]=p[w][p1].first,da[top]=f[w]*p[w][p1].second,db[top]=0,++p1;
			else if(p[w][p1].first>in[w][p2])sta[++top]=in[w][p2++],da[top]=0,db[top]=f[w];
			else sta[++top]=p[w][p1].first,da[top]=f[w]*p[w][p1].second,db[top]=0,++p1;
		}
		sta[top+1]=-1;insert(ro[x],1,ccc);
	}
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dfs(v,x);sz[x]+=sz[v];
		merge(ro[x],ro[v],1,ccc);
	}
	ans[x]=sum[ro[x]]+sz[x];
}

namespace IO {
#define iL (1 << 20)
char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
#define gc() ((iS == iT) ? (iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), iS == iT ? EOF : *iS ++) : *iS ++)
template<class T> inline void read(T &x) {
  x = 0;int f = 0;char ch = gc();
  for (; !isdigit(ch); f |= ch == '-', ch = gc());
  for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc());
  x = (f == 1 ? ~ x + 1 : x);
}
template<class T, class... Args> inline void read(T &x, Args&... args) { read(x), read(args...); }
template<class T> inline void readch(T &x) { char ch = gc(); for (; !isalpha(ch); ch = gc()); x = ch; }
char Out[iL], *iter = Out;
#define flush() fwrite(Out, 1, iter - Out, stdout), iter = Out
template<class T> inline void write(T x, char ch = '\n') {
  T l, c[35];
  if (x < 0) *iter ++ = '-', x = ~ x + 1;
  for (l = 0; !l || x; c[l] = x % 10, l++, x /= 10);
  for (; l; -- l, *iter ++ = c[l] + '0');*iter ++ = ch;
  flush();
}
template<class T, class... Args> inline void write(T x, Args... args) { write(x, ' '), write(args...); }
} // IO
using namespace IO;

int main()
{
	// freopen("in","w",stdout);
	// n=2e5,d=20;
	// cout<<n<<' '<<d<<'\n';
	// for(int i=2;i<=n;i++)cout<<rand()%(i-1)+1<<' '<<i<<'\n';
	// for(int i=1;i<=n;i++)cout<<i<<' ';
	// return 0;
	// freopen("in","r",stdin);
	// freopen("out","w",stdout);
	read(n,d);
	// n=2e5;
	init();
	for(int i=1;i<n;i++)
	{
		int u,v;read(u,v);
		e[++cnt]=(node){u,v,head[u]};head[u]=cnt;
		e[++cnt]=(node){v,u,head[v]};head[v]=cnt;
	}
	for(int i=1;i<=n;i++)read(a[i]);
	dfs(1,0);
	for(int i=1;i<=n;i++)write(ans[i]/2);
	// cerr<<clock()*1.0/CLOCKS_PER_SEC;
}