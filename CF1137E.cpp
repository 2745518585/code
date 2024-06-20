#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
ll n,q,w;
int m,R;
pair<ll,ll> Q[N];
ll cross(ll x1,ll y1,ll x2,ll y2)
{
    return x1*y2-x2*y1;
}
ll sum(pair<ll,ll> x)
{
    return q*(x.first-1)+x.second+w;
}
int main()
{
    scanf("%lld%d",&n,&m);
    Q[R=1]=make_pair(1,0);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            ll k;
            scanf("%lld",&k);
            Q[R=1]=make_pair(1,-w);
            n+=k;
        }
        else if(z==2)
        {
            ll k;
            scanf("%lld",&k);
            auto x=make_pair(n+1,-q*n-w);
            n+=k;
            if(sum(Q[R])>sum(x))
            {
                while(R>1&&cross(Q[R].first-Q[R-1].first,Q[R].second-Q[R-1].second,x.first-Q[R].first,x.second-Q[R].second)<=0) --R;
                Q[++R]=x;
            }
        }
        else if(z==3)
        {
            ll k1,k2;
            scanf("%lld%lld",&k2,&k1);
            q+=k1,w+=k2;
            while(R>1&&sum(Q[R-1])<=sum(Q[R])) --R;
        }
        printf("%d %lld\n",Q[R].first,sum(Q[R]));
    }
    return 0;
}