#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,a[N];
ll pw2[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if(x!=-1) ++a[x];
    }
    pw2[0]=1;
    for(int i=1;i<=n;++i) pw2[i]=pw2[i-1]*2%P;
    ll s=pw2[n-1]-1;
    for(int i=1;i<=n;++i)
    {
        s=(s-(pw2[a[i]]-1))%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}