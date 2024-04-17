#include<bits/stdc++.h>
using namespace std;
const int N=1e7+500,mod=998244353;

int n,m,l,r,ans,mi=1,X,num,tot;
char s[N];

int C(int n)
{
    return (1ll*n*(n-1)/2)%mod;
}

int S(int l,int r)
{
    return (1ll*(l+r)*(r-l+1)/2)%mod;
}

int solve(int n,int m,int k)
{
    if(!k)return 0;
    long long ans=(1ll*(k-1)*(n-k+1)%mod+C(k))%mod;
    if(!m)return ans;
    int p=n/k;
    if(!p)return (ans+S(k,k-1+m))%mod;
    if(m<=2*k)return (ans+S(k,k+m/2-1)+S(k,k+(m-m/2)-1))%mod;
    ans=(ans+2*S(k,2*k-2))%mod;m-=2*k-2;
    int len=m/(p+1),b=2*k-1;m%=(p+1);
    ans=(ans+1ll*(p+1)*S(b,b+len-1)%mod+1ll*m*(b+len)%mod)%mod;
    return ans;
}

int main()
{
    cin>>m>>l>>r>>X;getchar();n=X*m;
    for(int i=0;i<m;i++)s[i]=getchar(),n+=(s[i]=='1');
    tot=C(n+1);
    for(int i=0;i<=m;i++)
    {
        if(l<=i&&r>=i)ans^=1ll*(tot+mod-solve(num,n,i))%mod*mi%mod;
        printf("%d %lld\n",i,solve(num,n,i));
        n-=s[i]-'0'+X;num+=s[i]-'0'+X;mi=1ll*mi*233%mod;
    }
    cout<<ans;
}