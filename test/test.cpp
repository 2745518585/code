// Problem: G. Modular Tetration
// Contest: Codeforces - Codeforces Global Round 29 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2147/problem/G
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
// #define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=1ll*t*t%p)
		if(y&1) res=1ll*res*t%p;
	return res;
}
int pr[1<<20],pc;
int inv[1<<20];
bool vis[1<<20];
int arr[1<<20];
// int a[1<<20];
vector<int> vec[1<<20];
int in[5];
int X[103],Y[103],cnt;
signed main()
{
	const int N=1e6;
	for(int i=2; i<=N; ++i) if(!vis[i])
	{
		pr[++pc]=i;
		for(int j=1; i*j<=N; ++j)
		{
			int Q=i*j;
			while(Q%i==0)
				Q/=i,
				vec[i*j].push_back(i);
			vis[i*j]=1;
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1; i<=N; ++i) inv[i]=qp(i,p-2);
	for(int T=read();T--;)
	{
		cnt=0;
		int ans=1,ans1=1,len=0;
		// for(int Q=3; Q--;)
		long long X=1;
		for(int i=1; i<=3; ++i)
		{
			
			in[i]=read();X*=in[i];
			ans=1ll*ans*inv[in[i]]%p;
			int x=in[i];
			// int x=read();
			for(int i=1; pr[i]*pr[i]<=x; ++i)
				if(x%pr[i]==0) 
				{
					while(x%pr[i]==0)
						arr[++len]=pr[i],x/=pr[i];
				}
			if(x>1) arr[++len]=x;
			ans1=1ll*ans1*inv[in[i]]%p;
		}
		sort(arr+1,arr+len+1);
		// for(int i=1; i<=len; ++i)
		// {
			// int q=arr[i];
			// if(arr[i]!=arr[i-1]) --q;
			// // printf("* %d\n",q);
			// for(int j:vec[q]) 
				// if(!vis[j]) vis[j]=1,ans=1ll*ans*inv[j]%p;
		// }
		// for(int i=1; i<=3; ++i)
		// {
			// for(int j:vec[in[i]])
				// if(!vis[j])
					// vis[j]=1,ans=1ll*ans*inv[j]%p;
		// }
		int prod=1;
		// for(int i=1; i<=len; ++i) prod*=arr[i];
		// int len1=0;
		map<int,int> mp;
		for(int i=1; i<=len; ++i)
		{
			int j=1;
			while(i<len&&arr[i]==arr[i+1]) ++i,++j;
			// for(int k=1; k<j; ++k)
				// a[++len1]=1;
			if(j>1) mp[arr[i]]+=j-1;
			for(int k:vec[arr[i]-1]) ++mp[k];
		}
		// for(int i=1; i<=len; ++i)
		for(auto [x,y]:mp)
		{
			// int j=1;
			// while(i<len&&a[i]==a[i+1]) ++i,++j;
			// X[++cnt]=a[i],
			// Y[cnt]=j;
			// printf("%lld %lld\n",X[cnt],Y[cnt]);
			// int Q=1;
			// printf("%d %d\n",x,y);
			int z=1ll*(x-1)*inv[x]%p,s=1;
			// printf("%lld %d\n",X,x);
			if(X%x==0) continue;
			for(int i=1; i<=y; ++i)
				s=(s+z)%p,z=1ll*z*x%p;
			// printf("%lld\n",2ll*s%p);
			ans=1ll*ans*s%p;
			// ans=ans*((a[i]-1)%p*inv[a[i]]%p*j%p+1)%p;
			// printf("%lld %lld\n",x,y);
			// int U=arr[i]-1;
			// for(int k=1; k<=j; ++k)
			// {
				
			// }
		}
		
		printf("%d\n",ans);
	}
	return 0;
}