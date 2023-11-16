#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=5000001;
int n,tot=1,a[N][2];
ll b[N],g[N],h[N];
ll sum(ll x,ll k,ll q)
{
    for(ll i=q;i>=0;--i)
    {
        ll z=(x&(1<<(i-1)))!=0;
        if(a[k][z]!=0) k=a[k][z];
        else k=a[k][z^1];
    }
    return h[k];
}
void add(ll x)
{
    ll k=1;
    for(ll i=30;i>=0;--i)
    {
        ll z=(x&(1<<(i-1)))!=0;
        if(a[k][z]==0) a[k][z]=++tot;
        if(a[k][z^1]!=0)
        {
            if(g[k]==0) g[k]=1e9;
            g[k]=min(g[k],x^sum(x,a[k][z^1],i-1));
        }
        k=a[k][z];
    }
    h[k]=x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
        add(b[i]);
    }
    ll s=0;
    for(int i=1;i<=tot;++i) s+=g[i];
    printf("%lld",s);
    return 0;
}