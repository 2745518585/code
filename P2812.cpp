#include<cstdio>
#include<algorithm>
using namespace std;
struct str
{
	int m,q;
}a[100001];
int n,m=0,q=0,s=0,b[1001],c[1001],d[1001],r[1001],l[1001],t[1001];
bool e[1001];
void dfs(int x)
{
	++m;
    b[x]=m;
    c[x]=m;
    ++q;
    d[q]=x;
    for(int i=t[x];i!=0;i=a[i].q)
    {
    	if(b[a[i].m]==0)
    	{
    		dfs(a[i].m);
    		c[x]=min(c[x],c[a[i].m]);
    	}
    	else if(e[a[i].m]==false)
    	{
    		c[x]=min(c[x],c[a[i].m]);
    	}
    }
    if(b[x]==c[x]) 
    {
    	++s; 
    	while(d[q]!=x)
    	{
    		e[d[q]]=true;
    		r[d[q]]=s;
    		--q;
    	}
    	e[x]=true;
    	r[x]=s;
    	--q;
    }
}
int main()
{
    scanf("%d",&n);
    int k=0;
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		while(x!=0)
		{
			++k;
			a[k].m=x;
			a[k].q=t[i];
			t[i]=k;
			scanf("%d",&x);
		}
	}
	for(int i=1;i<=n;++i)
	{
		if(b[i]==0)
		{
			dfs(i);
		}
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
	int w=0;
	for(int i=1;i<=s;++i)
	{
		if(l[i]==0)
		{
			++w;
		}
	}
	printf("%d\n%d",w,w);
    return 0;
}