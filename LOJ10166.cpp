#include<cstdio>
#include<cmath>
using namespace std;
int n,m,a[21],f[21][201];
int dfs(int x,int k,bool u)
{
	if(x==n+1)
    {
        if(k==0) return 1;
        return 0;
    }
	int s=0;
	if(u)
	{
		for(int i=0;i<=a[n-x+1]-1;++i)
		{
			if(f[x][(k+i)%m]==-1)
			{
				f[x][(k+i)%m]=dfs(x+1,(k+i)%m,false);
			}
			s+=f[x][(k+i)%m];
		}
		s+=dfs(x+1,(k+a[n-x+1])%m,true);
	}
	else
	{
		for(int i=0;i<=9;++i)
		{
			if(f[x][(k+i)%m]==-1)
			{
				f[x][(k+i)%m]=dfs(x+1,(k+i)%m,false);
			}
			s+=f[x][(k+i)%m];
		}
	}
	return s;
}
int main()
{
	int x,y;
	while(~scanf("%d%d%d",&x,&y,&m))
	{
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
			for(int j=0;j<=m;++j) f[i][j]=-1;
		int s1=dfs(1,0,true);
		n=0;
		while(y!=0)
		{
			a[++n]=y%10;
			y/=10;
		}
		for(int i=1;i<=n;++i)
			for(int j=0;j<=m;++j) f[i][j]=-1;
		int s2=dfs(1,0,true);
		printf("%d\n",s2-s1);
	}
	return 0;
}