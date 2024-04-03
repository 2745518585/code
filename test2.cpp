#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=1e9+7;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=1ll*t*t%p)
		if(y&1) res=1ll*res*t%p;
	return res;
}
int arr[300003];
bool b[300003];
int a[300003],sa[300003];
int ans[600003],pre[300003],tmp[300003];
int n=read(),m=read();
vector<int> vl[300003],vr[300003];
int tl[3][300003],tr[3][300003];
int lst[300003];
void solve(int l,int r)
{
	if(l==r) return ;
	int mid=(l+r)>>1,mx=0;
	solve(l,mid),solve(mid+1,r);
	for(int i=l; i<=r; ++i) mx=max(mx,a[i]);
	for(int i=1; i<=mx; ++i)
		lst[i]=1,vl[i].clear(),vr[i].clear();
	for(int i=mid,fir=0; i>=l; fir+=a[i--])
		for(int j=1; j<a[i]; ++j)
			for(int k=j+1; k<=a[i]; k+=j)
				vl[j].push_back(fir+k-lst[j]),lst[j]=fir+k;
	for(int i=1; i<=mx; ++i)
		vl[i].push_back(sa[mid]-sa[l-1]-lst[i]+1),lst[i]=1;
	for(int i=mid+1,fir=0; i<=r; fir+=a[i++])
		for(int j=1; j<a[i]; ++j)
			for(int k=j+1; k<=a[i]; k+=j)
				vr[j].push_back(fir+k-lst[j]),lst[j]=fir+k;
	for(int i=1; i<=mx; ++i)
		vr[i].push_back(sa[r]-sa[mid]-lst[i]+1);
	const int inv2=(p+1)>>1;
	for(int d=1; d<=mx; ++d){
	int all=0,nl=vl[d].size(),nr=vr[d].size();--nl,--nr;
	for(int i=0; i<=nl; ++i) tl[0][i]=vl[d][i];
	for(int i=0; i<=nl; ++i) tl[1][i]=1ll*vl[d][i]*i%p;
	for(int i=0; i<=nl; ++i) tl[2][i]=1ll*vl[d][i]*i%p*i%p;
	tr[0][nr+1]=tr[1][nr+1]=tr[2][nr+1]=0;
	for(int i=nr; i>=0; --i) tr[0][i]=(tr[0][i+1]+vr[d][i])%p;
	for(int i=nr; i>=0; --i) tr[1][i]=(tr[1][i+1]+1ll*vr[d][i]*i)%p;
	for(int i=nr; i>=0; --i) tr[2][i]=(tr[2][i+1]+1ll*vr[d][i]*i%p*i)%p;
	auto solve=[&](int lim,int ml,int mr,int coef)
	{
		int sum=0;
		for(int i=max(lim-nr,0); i<=nl; ++i)
			sum=(sum+1ll*tl[ml][i]*tr[mr][max(0,lim-i)])%p;
		all=(all+1ll*sum*coef)%p;
		return ;
	};
	solve(2,1,0,(m+1+inv2)%p),
	solve(2,0,1,(m+1+inv2)%p),
	solve(2,0,0,p-m-1),
	solve(2,2,0,p-inv2),
	solve(2,0,2,p-inv2),
	solve(2,1,1,p-1);
	if(nl+nr>=m+2)
		solve(m+2,2,0,inv2),
		solve(m+2,0,2,inv2),
		solve(m+2,1,1,1),
		solve(m+2,0,0,(1ll*m*m%p*inv2+3ll*inv2%p*m+1)%p),
		solve(m+2,1,0,(3ll*(p-inv2)+(p-m))%p),
		solve(m+2,0,1,(3ll*(p-inv2)+(p-m))%p);
	ans[d+1]=(ans[d+1]+all)%p;
	}
	return ;
}
void HaitangSuki()
{
	for(int i=1; i<=m; ++i)
		pre[i]=(pre[i-1]+m+1-i)%p;
	for(int i=1; i<=n; ++i) arr[i]=read();
	for(int i=1; i<n; ++i) b[i]=(arr[i]<arr[i+1]);
	int cur=1,L=0;
	for(int i=2; i<n; ++i,++cur)
		if(b[i]!=b[i-1]) a[++L]=cur,cur=0;
	a[++L]=cur;
	for(int i=1; i<=L; ++i)
	{
		int w=a[i];
		for(int j=1; j<=w; ++j)
			tmp[j]=(tmp[j-1]+w+1-j)%p;
		for(int j=1; j<=w; ++j)
			for(int l=j*2+1,r=j*3,x=1; l<=w; l+=j,r+=j,++x)
				r=min(r,w),ans[j+1]=(ans[j+1]
				+1ll*pre[min(x,m)]*(p+tmp[r]-tmp[l-1]))%p;
		sa[i]=sa[i-1]+a[i];
	}
	solve(1,L);
	return ;
}
signed main()
{
	int N=n+m;
	HaitangSuki(),swap(n,m),HaitangSuki(),
	ans[1]=250000002ll*n%p*(n+1)%p*m%p*(m+1)%p,
	printf("0 ");
	for(int i=1; i<N; ++i)
		printf("%d ",(ans[i]+p-ans[i+1])%p);
	return 0;
}