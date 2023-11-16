#include<cstdio>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
struct str
{
	int m,q;
}a[10000001],a0[10000001];
stack<int> S;
int n,m,s1,n0,p=0,q=0,s=0,t[1000001],d[1000001],
b[1000001],c[1000001],
r[1000001],l[1000001],f[1000001],g[0100001],
p0=0,t0[1000001];
bool h[1000001],h0[1000001];
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
    Q.push(r[s1]);
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
	for(int i=1;i<=m;++i)
	{
		int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
	}
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&d[i]);
    }
    scanf("%d%d",&s1,&n0);
    for(int i=1;i<=n0;++i)
    {
        int x;
        scanf("%d",&x);
        h0[x]=true;
    }
    dfs(s1);
	for(int i=1;i<=n;++i)
	{
        if(r[i]==0) continue;
		for(int j=t[i];j!=0;j=a[j].q)
		{
            if(r[a[j].m]==0) continue;
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
    f[r[s1]]=g[r[s1]];
    tpsort();
    int w=0;
    for(int i=1;i<=n;++i)
    {
        if(h0[i]==true) w=max(w,f[r[i]]);
    }
    printf("%d",w);
    return 0;
}