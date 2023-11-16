#include<cstdio>
#include<algorithm>
using namespace std;
int f[3000001][21],a[21][21],t[21];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
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
			for(int k=1;k<=n;++k)
			{
				if((i&(1<<(k-1)))!=0) continue;
				f[i+(1<<(k-1))][k]=min(f[i+(1<<(k-1))][k],f[i][j]+a[j][k]);
			}
		}
	}
	printf("%d",f[(1<<n)-1][n]);
	return 0;
}