#include <bits/stdc++.h>

#define N 16
#define lowbit(x) ((x)&-(x))
#define mod 1000000007

typedef long long ll;

using namespace std;

ll ft[N*2],c[N*2][N*2],h[1<<15];
int n,K,d[N],g[1<<15][N],f[1<<15][N];

bitset<32768>w[32768];

ll qpow(ll,int);

int main()
{
// freopen("timeline.in","r",stdin);
// freopen("timeline.out","w",stdout);

	ll o=0;
	int i,j,k,s,t,T,u,v,m;
	scanf("%d %d %d",&n,&T,&K);
	if(T==0)return puts("1"),0;
	ft[0]=c[0][0]=1;for(i=1;i<N*2;++i){ft[i]=ft[i-1]*i%mod;c[i][0]=1;for(j=1;j<=i;++j)c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;}
	while(T--){scanf("%d %d",&u,&v);d[u]|=1<<v-1;}
	for(k=1;k<=n;++k)
		for(i=1;i<=n;++i)
			if(d[i]&(1<<k-1))
				d[i]|=d[k];
    for(int i=1;i<=n;++i) printf("%d ",d[i]);printf("\n");
	for(i=1;i<=n;++i)if(d[i]&(1<<i-1))return puts("0"),0;
	for(s=0;s<(1<<n);++s)
		for(t=(s-1)&s;t;t=(t-1)&s)
		{
			u=__lg(lowbit(t))+1;
			w[t][s^t]=w[t^(1<<u-1)][s^t]|((d[u]&(s^t))!=0);
		}
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=0;j<=(1<<n)-1;++j)
        {
            printf("%d ",(int)w[i][j]);
        }
        printf("\n");
    }
	h[0]=1;
	for(s=1;s<(1<<n);++s)
		for(i=1;i<=n;++i)
			if((s&(1<<i-1))&&!w[s^(1<<i-1)][1<<i-1])
				(h[s]+=h[s^(1<<i-1)])%=mod;
	for(int i=0;i<=(1<<n)-1;++i) printf("%lld ",h[i]);printf("\n");
	g[0][0]=1;
	for(s=1;s<(1<<n);++s)
		for(t=s;t;t=(t-1)&s)
			if((t&lowbit(s))&&!w[t][s^t]&&!w[s^t][t])
				for(i=1;i<=n;++i)
					(g[s][i]+=g[s^t][i-1]*h[t])%=mod;
	f[0][0]=1;
	for(s=0;s<(1<<n);++s)
		for(t=s;t;t=(t-1)&s)
			if(!w[t][s^t])
				for(i=1;i<=n;++i)
					for(j=0;j<=i;++j)
						(f[s][i]+=f[s^t][i-j]*g[t][j]*((j&1)?1:-1))%=mod;
	for(m=1;m<=K+1;++m)
		(o+=ft[m]*c[K+1][m]%mod*qpow(c[n+K][n]*ft[n]%mod,mod-2)%mod*f[(1<<n)-1][m])%=mod;
	printf("%lld\n",(o+mod)%mod);
	return 0;
}
ll qpow(ll a,int b)
{
	ll ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;b>>=1;
	}
	return ans;
}
