#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll qpow(ll a,ll b,ll P)
{
	__int128_t x=1,y=a;
	while(b!=0)
	{
		if(b&1) x=x*y%P;
		y=y*y%P;
		b>>=1;
	}
	return x%P;
}
bool check(ll n)
{
	if(n==2) return true;
	if(n<3||n%2==0) return false;
	ll a=n-1,b=0;
	while(a%2==0) a/=2,++b;
	for(int i=1,j;i<=8;++i)
	{
		ll x=rand()%(n-2)+2,t=qpow(x,a,n);
		if(t==1) continue;
		for(j=0;j<b;++j)
		{
			if(t==n-1) break;
			t=(__int128_t)t*t%n;
		}
		if(j>=b) return false;
	}
	return true;
}
int main()
{
    scanf("%d",&n);
	srand(time(NULL));
    int s=0;
    for(int i=1;i<=n;++i)
    {
    	ll x;
    	scanf("%lld",&x);
    	if(check(x)) ++s;
	}
	printf("%d",s);
    return 0;
}
