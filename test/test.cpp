//minamoto
#include<bits/stdc++.h>
#define R register
#define fp(i,a,b) for(R int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(R int i=(a),I=(b)-1;i>I;--i)
#define go(u) for(int i=head[u],v=e[i].v;i;i=e[i].nx,v=e[i].v)
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
int read(){
    R int res,f=1;R char ch;
    while((ch=getchar())>'9'||ch<'0')(ch=='-')&&(f=-1);
    for(res=ch-'0';(ch=getchar())>='0'&&ch<='9';res=res*10+ch-'0');
    return res*f;
}
inline int get(){R char ch;while((ch=getchar())>'1'||ch<'0');return ch-'0';}
const int N=1e5+5;
struct eg{int v,nx;}e[N<<1];int head[N],tot;
inline void add(R int u,R int v){e[++tot]={v,head[u]},head[u]=tot;}
inline bool query(R int u,R int v){printf("? %d %d\n",u,v),fflush(stdout);return read();}
int vis[N],ins[N],deg[N];vector<int>to[N],now;
int n,m;
void tarjan(int u){
	vis[u]=ins[u]=1;
	go(u){
		if(!ins[v])to[u].push_back(v),++deg[v];
		if(!vis[v])tarjan(v);
	}
	ins[u]=0;
}
int main(){
	n=read(),m=read();
	for(R int i=1,u,v;i<=m;++i)u=read(),v=read(),add(u,v);
	fp(i,1,n)if(!vis[i])tarjan(i);
	fp(i,1,n)if(!deg[i])now.push_back(i);
	while(now.size()>1){
        for(auto i:now) printf("%d ",i);printf("\n");
		int u=now.back();now.pop_back();
		int v=now.back();now.pop_back();
		if(!query(u,v))swap(u,v);now.push_back(u);
		fp(i,0,to[v].size()-1)if(!--deg[to[v][i]])now.push_back(to[v][i]);
	}
	printf("! %d\n",now.front());
	return 0;
}
