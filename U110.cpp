#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=50;
int n,m;
ll f[N][N];
int main()
{
    scanf("%d%d",&n,&m);
	f[1][1]=1;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			f[i][j]+=f[i-1][j-1]*(i-j+1)+f[i-1][j]*j;
		}
	}
	printf("%lld",f[n][m]);
    return 0;
}
