#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=13,M=500;
int a[N+1],n,m,q;
ll f[1<<N][N+1][M+1];
int sum(int x)
{
    int s=0;
    while(x!=0)
    {
        ++s;
        x-=(x&-x);
    }
    return s;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
        if(a[i]>a[q]) q=i;
	}
    for(int i=1;i<=n;++i)
    {
        for(int j=n*max(a[q]-a[i]+(q<i),0);j<=m;++j)
        {
            f[1<<(i-1)][i][j]=1;
        }
    }
	for(int i=0;i<=(1<<n)-1;++i)
	{
		for(int j=1;j<=n;++j)
        {
            if((i&(1<<(j-1)))==0) continue;
            for(int k=1;k<=n;++k)
            {
                if((i&(1<<(k-1)))!=0) continue;
                int p=max(a[j]-a[k]+(j<k),0)*(n-sum(i));
                for(int l=0;l+p<=m;++l)
                {
                    f[i+(1<<(k-1))][k][l+p]+=f[i][j][l];
                }
            }
        }
	}
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        s+=f[(1<<n)-1][i][m];
    }
    printf("%lld",s);
	return 0;
}