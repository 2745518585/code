#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=10000001;
char a[N],b[N];
ll n,m,p,k;
ll qpow(ll a,ll b,ll P)
{
	ll x=1,y=a;
	while(b)
	{
		if(b&1) x=x*y%P;
		y=y*y%P;
		b>>=1;
	}
	return x;
}
int main()
{
	scanf("%s%s%lld",a+1,b+1,&p);
	ll x=p;
	k=p;
	for(ll i=2;i*i<=p;++i)
	{
		if(x%i==0)
		{
			k=k-k/i;
			while(x%i==0) x/=i;
		}
	}
	if(x>1) k=k-k/x;
	int z1=strlen(a+1),z2=strlen(b+1);
	for(int i=1;i<=z1;++i) n=(n*10+a[i]-'0')%p;
	--b[z2];
	for(int i=z2;i>=1;--i)
	{
		if(b[i]<'0') --b[i-1],b[i]+=10;
		else break;
	}
	bool u=false;
	for(int i=1;i<=z2;++i)
	{
		m=m*10+b[i]-'0';
		if(m>=k) u=true;
		m%=k;
	}
	if(u) m+=k;
	printf("%lld",(qpow(n,m,p)%p*(n-1)+p-1)%p+1);
	return 0;
}
