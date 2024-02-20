#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353;
int n,m;
ll f[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=i;++j)
        {
            f[i][j]=(f[i-1][j-1]+f[i-j][j])%P;
            if(j>=m+1) f[i][j]=(f[i][j]-f[i-j][j-(m+1)])%P;
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld\n",(f[n][i]%P+P)%P);
    }
    return 0;
}