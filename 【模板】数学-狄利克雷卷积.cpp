#pragma GCC optimize("Ofast","inline")
#pragma GCC optimize("O2")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,sp,p[N];
ll f[N],g[N];
bool h[N];
int main()
{
    for(int i=2;i<=1000000;++i)
    {
        if(h[i]==false) p[++sp]=i;
        for(int j=1;j<=sp&&i*p[j]<=1000000;++j)
        {
            h[i*p[j]]=true;
            if(i%p[j]==0) break;
        }
    }
    for(int i=1;i<=sp;++i)
    {
        for(int j=n/p[i];j>=1;--j)
        {
            if(f[j]==0) continue;
            int t=p[i];
            for(ll k=j*p[i];k<=n;k*=p[i])
            {
                f[k]=(f[k]+f[j]*g[t])%P;
                t*=p[i];
            }
        }
    }
    return 0;
}
