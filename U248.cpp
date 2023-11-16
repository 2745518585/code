#include<bits/stdc++.h>
using namespace std;
const int N=301;
int n,m,a[N][N],f[2][N][N],g[N][N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=i;++j)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=0;i<=m;++i) g[n&1][i]=-1e18;
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<=m;++j)
		{
			f[n&1][i][j]=-1e18;
		}
	}
	for(int i=n;i>=1;--i)
	{
		int t=i&1;
		for(int j=1;j<=i;++j)
		{
			for(int k=0;k<=m;++k)
			{
				f[t][j][k]=max(f[t^1][j][k]+a[i][j],f[t^1][j+1][k]+a[i][j]);
				if(k!=0) f[t][j][k]=max(f[t][j][k],g[t^1][k-1]+a[i][j]);
				g[t][k]=max(g[t][k],f[t][j][k]);
			}
		}
	}
	printf("%d",f[1][1][m]);
	return 0;
}
