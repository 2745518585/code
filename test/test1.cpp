#include "bits/stdc++.h"
#define int long long
using namespace std;
int T,x,m,f[2000005],n=1e6+3,ans[2000005],mod=998244353;
signed main(){
    int tot=0,now=0;ans[2]=1;
    for(int i=3;i<=n;i++){
        f[n-i+1]++;tot+=i-1;now++;//f[i][1]++
        f[n-i]=tot;now+=tot;
        tot+=f[n-i]*(i+1)%mod;
        tot%=mod;now%=mod;
        /*for(int j=0;j<=i;j++){
            f[i+1][j+1]+=f[i][j];
            f[i+1][0]+=f[i][j]*(i-j);
            ans+=f[i][j];
        }*/
        ans[i]=(now+1-f[n-i]+mod)%mod;
    }
    cin>>T;
    while(T--){
        cin>>n;
        cout<<ans[n]<<'\n';
    }
    return 0;
}