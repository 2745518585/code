#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
int n;
ll a[N][N],P;
int main()
{
    scanf("%d%d",&n,&P);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%lld",&a[i][j]);
        }
    }
    ll s=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            while(a[i][i]!=0)
            {
                ll z=a[j][i]/a[i][i];
                for(int k=i;k<=n;++k)
                {
                    a[j][k]=(a[j][k]-z*a[i][k]%P+P)%P;
                }
                swap(a[i],a[j]);
                s=-s;
            }
            swap(a[i],a[j]);
            s=-s;
        }
    }
    for(int i=1;i<=n;++i) s=(s*a[i][i])%P;
    printf("%lld",(s%P+P)%P);
    return 0;
}