#include<bits/stdc++.h> 
#define ll long long
using namespace std; 

ll n,pp,a[500005],fa[500005],dep[500005],u,v,sc,ans,gcdd;
vector <ll> e[500005],ss;

void dfs(int x,int fat)
{
	for(auto i:e[x])
	{
		if(i==fat) continue; fa[i]=x; dep[i]=dep[x]+1; dfs(i,x);
	}
}
ll gcd(ll x,ll y)
{
	return !y?x:gcd(y,x%y);
}

signed main(int argc,char *argv[]) 
{ 
    FILE *f_stdin=fopen(argv[1],"r");
    FILE *f_out=fopen(argv[3],"r");
    FILE *f_stdout=fopen(argv[2],"r");
    
	sc=atoi(argv[4]);
    fscanf(f_stdin,"%lld",&n);
    fscanf(f_stdin,"%lld",&pp);
    for(int i=1;i<=n;i++) fscanf(f_stdin,"%lld",&a[i]);
    for(int i=1;i<=n;i++) 
	{
		fscanf(f_stdin,"%lld%lld",&u,&v);
		e[u].push_back(v); e[v].push_back(u);
	}
	dep[1]=1; dfs(1,1);
    fscanf(f_stdout,"%lld",&ans);
    ll xx;
    while (fscanf(f_out,"%lld",&xx)!=EOF) ss.push_back(xx);
    if(ss.size()!=4)
    {
    	printf("Invalid output");return 1;
	}
	else
	{
		ll nans=ss[0];
		if(nans!=ans)
		{
			printf("Wrong answer");return 1;
		}
		ll uu=ss[1],vv=ss[2],ww=ss[3];
		if(uu<1||uu>n||vv<1||vv>n||ww<0||ww>1000000000000000000)
		{
			printf("Invalid operation");return 1;
		}
		while(uu!=vv)
		{
			if(dep[uu]>dep[vv]) a[uu]+=ww,uu=fa[uu];
			else a[vv]+=ww,vv=fa[vv];	
		}
		a[uu]+=ww; gcdd=ans;
		for(int i=1;i<=n;i++) gcdd=gcd(gcdd,a[i]);
		if(gcdd==ans)
		{
			return 0;
		}
		else
		{
			printf("Wrong answer: wrong operation");return 1;
		}
	}
    return 0;
}
