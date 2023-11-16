#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1001,inf=1e9;
int n,m,a[N][N],f[N][N];
ll s;
ll min(int t,int x,int y)
{
	ll w=0;
	int S[N],T=0,c[N];
	S[0]=x-1;
	c[x-1]=0;
	for(int i=x;i<=y;++i)
	{
		while(T>=1&&f[t][S[T]]>f[t][i]) --T;
		c[i]=(i-S[T])*f[t][i]+c[S[T]];
		w+=c[i];
		S[++T]=i;
	}
	return w;
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<=n;++j)
		{
			scanf("%d",&a[i][j]);
			if(a[i][j]==a[i-1][j]) f[i][j]=f[i-1][j]+1;
			else f[i][j]=1;
		}
	}
	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<=n;++j)
		{
			int k=j;
			while(k+1<=n&&a[i][k+1]==a[i][j]) ++k;
			s+=min(i,j,k);
			j=k;
		}
	}
	printf("%lld",s);
	return 0;
}
