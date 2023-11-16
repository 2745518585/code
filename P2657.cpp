#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;
int n,a[21];
ll f[21][10];
ll dfs(int x,int k,bool u,bool v)
{
	if(x==n+1) return 1;
	ll s=0;
	if(u)
	{
		for(int i=0;i<=a[n-x+1]-1;++i)
		{
			if(v)
			{
				s+=dfs(x+1,i,false,i==0);
				continue;
			}
			if(abs(i-k)<=1) continue;
			if(f[x][i]==-1)
			{
				f[x][i]=dfs(x+1,i,false,false);
			}
			s+=f[x][i];
		}
		if(v||abs(a[n-x+1]-k)>1)
		{
			s+=dfs(x+1,a[n-x+1],true,false);
		}
	}
	else
	{
		for(int i=0;i<=9;++i)
		{
			if(v)
			{
				s+=dfs(x+1,i,false,i==0);
				continue;
			}
			if(!v&&abs(i-k)<=1) continue;
			if(f[x][i]==-1)
			{
				f[x][i]=dfs(x+1,i,false,v&&i==0);
			}
			s+=f[x][i];
		}
	}
	return s;
}
int main()
{
	ll x,y;
	scanf("%lld%lld",&x,&y);
	--x;
	n=0;
	while(x!=0)
	{
		a[++n]=x%10;
		x/=10;
	}
	if(n==0)
	{
		n=1;
		a[1]=0;
	}
	for(int i=1;i<=n;++i)
        for(int j=0;j<=9;++j) f[i][j]=-1;
	ll s1=dfs(1,-3,true,true);
	n=0;
	while(y!=0)
	{
		a[++n]=y%10;
		y/=10;
	}
	for(int i=1;i<=n;++i)
        for(int j=0;j<=9;++j) f[i][j]=-1;
	ll s2=dfs(1,-3,true,true);
	printf("%lld\n",s2-s1);
	return 0;
}
