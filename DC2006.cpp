#include<cstdio>
#include<algorithm>
using namespace std;
int n,p=0,f[2000001][21],t[21];
struct str
{
	int m,q,w;
}a[10001];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
int main()
{
	scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int w;
            scanf("%d",&w);
            road(i,j,w);
            road(j,i,w);
        }
    }
	for(int i=1;i<=(1<<n)-1;++i)
	{
		for(int j=1;j<=n;++j)
		{
			f[i][j]=1e9;
		}
	}
	f[1][1]=0;
	for(int i=0;i<=(1<<n)-1;++i)
	{
		for(int j=1;j<=n;++j)
		{
			if((i&(1<<(j-1)))==0) continue;
			for(int k=t[j];k!=0;k=a[k].q)
			{
				if((i&(1<<(a[k].m-1)))!=0||(i==(1<<(n-1))&&k==n)) continue;
				f[i+(1<<(a[k].m-1))][a[k].m]=min(f[i+(1<<(a[k].m-1))][a[k].m],f[i][j]+a[k].w);
			}
		}
	}
	printf("%d",f[(1<<n)-1][n]);
	return 0;
}
