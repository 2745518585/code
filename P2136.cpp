#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int t[1000001],f[1000001],g[10000001],z[1000001];
bool h[1000001];
struct str
{
	int m,q,w;
}a[10000001];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int x;
		scanf("%d%d%d",&x,&a[i].m,&a[i].w);
		a[i].q=t[x];
		t[x]=i;
        a[i].w=-a[i].w;
	}
    for(int i=1;i<=n;++i) f[i]=1e9;
    f[1]=0;
    h[1]=true;
	queue<int> q;
	q.push(1);
    while(!q.empty()) 
    {
        int k=q.front();
        q.pop();
        ++z[k];
        if(z[k]>n)
        {
            printf("Forever love");
            return 0;
        }
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                h[a[i].m]=true;
                q.push(a[i].m);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        g[i]=1e9;
        h[i]=false;
        z[i]=0;
    }
    g[n]=0;
    h[n]=true;
	q.push(n);
    while(!q.empty()) 
    {
        int k=q.front();
        q.pop();
        ++z[k];
        if(z[k]>n)
        {
            printf("Forever love");
            return 0;
        }
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(g[k]+a[i].w<g[a[i].m])
            {
                g[a[i].m]=g[k]+a[i].w;
                h[a[i].m]=true;
                q.push(a[i].m);
            }
        }
    }
    int s=1e9;
    for(int i=1;i<=n;++i)
    {
        s=min(s,f[i]+g[i]);
    }
    printf("%d",s);
	return 0;
}