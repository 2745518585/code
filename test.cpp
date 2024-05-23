#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=8e6;

int n,m,k,mod,cm[N],icm[N],ans;

int ksm(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1)ans=ans*a%mod;
        b>>=1;a=a*a%mod;
    }
    return ans;
}

int binom(int n,int m)
{
    if(m>n)return 0;
    return cm[n]*icm[m]%mod*icm[n-m]%mod;
}

signed main()
{
    // freopen("in.txt","r",stdin);
    cin>>n>>m>>k>>mod;
    cm[0]=1;
    for(int i=1;i<N;i++)cm[i]=cm[i-1]*i%mod;
    icm[N-1]=ksm(cm[N-1],mod-2);
    for(int i=N-1;i;i--)icm[i-1]=icm[i]*i%mod;
    if(k==n+m-1)
    {
        cout<<binom(n+m,n);
        return 0;
    }
    for(int i=0;i<=k;i++)ans=(ans+binom(k,i)*binom(n+m-1-k+i,n)%mod*binom(n+m-1-i,m)%mod)%mod;
    ans=2*(k+1)*ksm(n+m-1-k,mod-2)%mod*ans%mod;
    cout<<ans;
}
