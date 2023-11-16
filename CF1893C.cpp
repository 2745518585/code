#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
typedef long long ll;
const int N=100001;
int n;
ll g[N],d1[N],d2[N],z[N];
map<ll,vector<int>> Map;
map<ll,ll> f[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int w=0;
        ll p1=0,p2=0;
        Map.clear();
        for(int i=1;i<=n;++i)
        {
            int k;
            scanf("%d%lld%lld",&k,&d1[i],&d2[i]);
            w+=k;
            p1+=d1[i],p2+=d2[i];
            f[i].clear();
            g[i]=0;
            for(int j=1;j<=k;++j)
            {
                ll x;
                scanf("%lld",&z[j]);
                Map[z[j]].push_back(i);
            }
            for(int j=1;j<=k;++j)
            {
                ll x;
                scanf("%lld",&x);
                f[i][z[j]]=x;
                g[i]+=x;
            }
        }
        if(p2-p1+1>w)
        {
            printf("0\n");
            continue;
        }
        ll q=0;
        for(int i=1;i<=n;++i) q+=d2[i];
        ll s=1e18;
        for(ll i=p1;i<=p2;++i)
        {
            ll z1=q,z2=0;
            for(auto j:Map[i])
            {
                z1-=d2[j];
                if(g[j]-f[j][i]>=d1[j]) z1+=min(d2[j],g[j]-f[j][i]);
                else z1+=g[j]-f[j][i],z2+=d1[j]-(g[j]-f[j][i]);
            }
            if(z1+z2<i) z2+=i-(z1+z2);
            s=min(s,z2);
        }
        printf("%lld\n",s);
    }
    return 0;
}