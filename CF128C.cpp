#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001;
const ll P=1e9+7;
int m1,m2,n,k;
ll g[N][N];
int main()
{
    scanf("%d%d%d",&m1,&m2,&k);
    n=max(m1,m2);
    for(int i=3;i<=n;++i) g[i][1]=((ll)(i-1)*(i-2)/2)%P;
    for(int i=2;i<=k;++i)
    {
        ll q=0,w=0;
        for(int j=i*2+1;j<=n;++j)
        {
            q=(q+g[j-2][i-1])%P;
            w=(w+q)%P;
            g[j][i]=w;
        }
    }
    printf("%lld",(g[m1][k]*g[m2][k]%P+P)%P);
    return 0;
}