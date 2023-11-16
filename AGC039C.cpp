#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,q,a[N],d[N];
ll f[N];
ll check(int x)
{
    ll s=0;
    for(int i=1;i<=x;++i) s=(s*2+a[i])%P;
    for(int i=1;i<=n/x-1;++i)
    {
        for(int j=1;j<=x;++j)
        {
            if((a[j]^(i%2))>a[i*x+j]) return s;
            if((a[j]^(i%2))<a[i*x+j]) return (s+1)%P;
        }
    }
    return (s+1)%P;
}
int main()
{
    scanf("%d\n",&n);
    for(int i=1;i<=n;++i) a[i]=getchar()-'0';
    for(int i=1;i<=n;++i)
    {
        if(n%i==0&&(n/i)%2==1) d[++q]=i;
    }
    ll s=0;
    for(int i=1;i<=q;++i)
    {
        f[i]=check(d[i]);
        for(int j=1;j<=i-1;++j)
        {
            if(d[i]%d[j]==0) f[i]=(f[i]-f[j])%P;
        }
        // printf("%d %lld\n",i,f[i]);
        s=(s+f[i]*(d[i]*2)%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}