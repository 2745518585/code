#include<cstdio>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
struct str
{
	int m,q;
}a[100001];
stack<int> S;
int n,m,u,p=0,q=0,s=0,t[10001],d[10001],
b[10001],c[10001],
r[10001],l[10001],g[10001];
bool h[10001],f[10001];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    b[x]=c[x]=++q;
    S.push(x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
    	if(b[a[i].m]==0)
    	{
    		dfs(a[i].m);
    		c[x]=min(c[x],c[a[i].m]);
    	}
    	else if(h[a[i].m]==false)
    	{
    		c[x]=min(c[x],c[a[i].m]);
    	}
    }
    if(b[x]==c[x])
    {
    	++s;
    	while(S.top()!=x)
    	{
    		h[S.top()]=true;
    		r[S.top()]=s;
            S.pop();
    	}
    	h[x]=true;
    	r[x]=s;
        S.pop();
    }
}
void dfs2(int x)
{
    f[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(f[a[i].m]==0)
        {
            dfs2(a[i].m);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&u);
    for(int i=1;i<=n;++i) d[i]=1e9;
    for(int i=1;i<=u;++i)
    {
        int x,w;
        scanf("%d%d",&x,&w);
        d[x]=w;
    }
    scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
	}
	for(int i=1;i<=n;++i)
	{
		if(b[i]==0) dfs(i);
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=t[i];j!=0;j=a[j].q)
		{
			if(r[i]!=r[a[j].m])
			{
                ++l[r[a[j].m]];
			}
		}
	}
    for(int i=1;i<=s;++i) g[i]=1e9;
    for(int i=1;i<=n;++i)
    {
        g[r[i]]=min(g[r[i]],d[i]);
    }
    int v=0;
    for(int i=1;i<=s;++i)
    {
        if(l[i]==0) v+=g[i];
    }
    if(v<1e9)
    {
        printf("YES\n%d",v);
        return 0;
    }
    for(int i=1;i<=n;++i)
    {
        if(d[i]!=1e9)
        {
            dfs2(i);
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(f[i]==false)
        {
            printf("NO\n%d",i);
            return 0;
        }
    }
    return 0;
}