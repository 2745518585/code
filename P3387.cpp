#include<cstdio>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
struct str
{
	int m,q;
}a[100001],a0[100001];
stack<int> S;
int n,m,p=0,q=0,s=0,t[10001],d[10001],
b[10001],c[10001],
r[10001],l[10001],f[10001],g[10001],
p0=0,t0[10001];
bool h[10001];
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
int tpsort()
{
    queue<int> Q;
    for(int i=1;i<=s;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t0[k];i!=0;i=a0[i].q)
        {
            f[a0[i].m]=max(f[a0[i].m],f[k]+g[a0[i].m]);
            --l[a0[i].m];
            if(l[a0[i].m]==0) Q.push(a0[i].m);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&d[i]);
    }
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
                a0[++p0].m=r[a[j].m];
                a0[p0].q=t0[r[i]];
                t0[r[i]]=p0;
			}
		}
	}
    for(int i=1;i<=n;++i)
    {
        g[r[i]]+=d[i];
    }
    for(int i=1;i<=s;++i)
    {
        f[i]=g[i];
    }
    tpsort();
    int w=0;
    for(int i=1;i<=n;++i)
    {
        w=max(w,f[r[i]]);
    }
    printf("%d",w);
    return 0;
}