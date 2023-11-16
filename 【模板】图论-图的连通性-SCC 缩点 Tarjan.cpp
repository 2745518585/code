#include<cstdio>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
const int N=10001,M=100001;
int n,m,p=1,tot,s,t[N],d[N],r[N],l[N],f[N],g[N],p0=1,t0[N];
bool h[N];
struct tree
{
    int b,c;
}T[N];
struct str
{
	int m,q;
}a[M],a0[M];
stack<int> S;
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void road0(int x,int y)
{
    a0[++p0].m=y;
    a0[p].q=t0[x];
    t0[x]=p0;
}
void dfs(int x)
{
    T[x].b=T[x].c=++tot;
    S.push(x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
    	if(T[a[i].m].b==0)
    	{
    		dfs(a[i].m);
    		T[x].c=min(T[x].c,T[a[i].m].c);
    	}
    	else if(h[a[i].m]==false)
    	{
    		T[x].c=min(T[x].c,T[a[i].m].c);
    	}
    }
    if(T[x].b==T[x].c)
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
void tpsort()
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
		if(T[i].b==0) dfs(i);
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=t[i];j!=0;j=a[j].q)
		{
			if(r[i]!=r[a[j].m])
			{
				++l[r[a[j].m]];
                road0(r[i],r[a[j].m]);
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
