#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5000001,M=20;
const ll P=1e9+7;
int n,a[N],f[N];
ll pow2[N];
int sum(int x)
{
    int s=0;
    while(x) x-=x&-x,++s;
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        ++f[a[i]];
    }
    for(int i=0;i<=M;++i)
    {
        for(int j=0;j<=(1<<M)-1;++j)
        {
            if((j&(1<<i))==0) f[j]+=f[j^(1<<i)];
        }
    }
    pow2[0]=1;
    for(int i=1;i<=n;++i) pow2[i]=pow2[i-1]*2%P;
    ll s=0;
    for(int i=0;i<=(1<<M)-1;++i)
    {
        if(sum(i)%2==0) s+=pow2[f[i]];
        else s-=pow2[f[i]];
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}