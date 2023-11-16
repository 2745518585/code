#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,a[N],b[N],c[N],g[N];
ll pow2[N];
bool h[N];
vector<int> d[N];
bool cmp(int x,int y)
{
    return a[x]>a[y];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        ++g[a[i]];
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;i*j<=n;++j)
        {
            d[i*j].push_back(i);
            if(a[i*j]>a[b[i]]) b[i]=i*j;
        }
    }
    pow2[0]=1;
    for(int i=1;i<=n;++i) pow2[i]=pow2[i-1]*2%P;
    for(int i=1;i<=n;++i) c[i]=i;
    sort(c+1,c+n+1,cmp);
    ll s=0;
    int w=n;
    for(int i=1;i<=n;++i)
    {
        int x=c[i];
        if(b[x]!=x||h[x]) continue;
        int z=0;
        for(auto j:d[x])
        {
            if(!h[j]) ++z;
        }
        s=(s+pow2[w-z]*(pow2[z]-1)%P*a[x]%P)%P;
        // printf("%d %d %lld %lld\n",x,z,w,s);
        for(auto j:d[x])
        {
            if(!h[j]) --w,h[j]=true;
        }
    }
    printf("%lld",s);
    return 0;
}