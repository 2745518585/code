#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=1e9+7;
int n,m,k;
ll C[N][N];
ll sum(int k)
{
    return C[n+m][n]-C[n+m][k-1];
}
int main()
{
    int T;
    scanf("%d",&T);
    C[0][0]=1;
    for(int i=1;i<=4000;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        if(n<k||m<k)
        {
            printf("0\n");
            continue;
        }
        ll s=sum(k);
        if(n>=k+1&&m>=k+1) s=(s-sum(k+1));
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}