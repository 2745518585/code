#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
const int N=101;
int n,k;
ll a[N];
map<ll,int> Map,lg;
ll dfs(ll x)
{
    if(x==0) return 0;
    if(Map.count(x)) return Map[x];
    ll z=lg[x&-x];
    return Map[x]=max(dfs(x^(1ll<<(z-1))),dfs(x&a[z])+1);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x;
            scanf("%d",&x);
            a[i]|=(ll)x<<(j-1);
        }
    }
    for(int i=1;i<=n;++i) lg[1ll<<(i-1)]=i;
    int x=dfs((1ll<<n)-1);
    printf("%.12lf",(double)k*k/x*(x-1)/2);
    return 0;
}