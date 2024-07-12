#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
typedef __int128_t lll;
const int N=1000001;
const ll P=998244353;
int n,T;
ll a[N],b[N],c[N];
struct str
{
    ll x;
    lll w;
    str() {}
    str(ll x,lll w):x(x),w(w) {}
}S[N];
int main()
{
    int TOT;
    scanf("%*d%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&b[i]);
        }
        for(int i=1;i<=n-1;++i)
        {
            scanf("%lld",&c[i]);
        }
        c[n]=1;
        T=0;
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            ll x=b[i];
            while(T>0&&S[T].w<a[i]) x+=S[T].x,--T;
            S[++T]=str(x,a[i]);
            if(c[i]>1)
            {
                ll x=0;
                lll w=0;
                vector<str> p;
                for(int j=T;j>=1;--j)
                {
                    if(x+S[j].x<c[i])
                    {
                        x+=S[j].x,w+=S[j].x*S[j].w;
                        continue;
                    }
                    p.push_back(str(1,w+(c[i]-x)*S[j].w));
                    ll z=(S[j].x-(c[i]-x))/c[i];
                    if(z>0) p.push_back(str(z,c[i]*S[j].w));
                    x=S[j].x-(c[i]-x)-z*c[i];
                    w=x*S[j].w;
                }
                s=(s+w)%P;
                reverse(p.begin(),p.end());
                T=0;
                for(auto j:p) S[++T]=j;
            }
        }
        for(int i=1;i<=T;++i) s=(s+(S[i].x%P)*(S[i].w%P)%P)%P;
        printf("%lld\n",s);
    }
    return 0;
}