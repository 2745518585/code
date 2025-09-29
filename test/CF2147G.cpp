#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=998244353;
int q;
ll m1,m2,m3,a[N];
map<ll,int> M;
set<ll> S;
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    return (x%P+P)%P;
}
int sum(int x)
{
    int s=0;
    while(x>0) s+=x&1,x>>=1;
    return s;
}
void solve1(ll x)
{
    ll z=x;
    for(ll i=2;i*i<=x;++i)
    {
        if(z%i==0)
        {
            ++M[i];
            while(z%i==0) z/=i;
        }
    }
    if(z>1) ++M[z];
}
void solve2(ll x)
{
    ll z=x;
    for(ll i=2;i*i<=x;++i)
    {
        if(z%i==0)
        {
            S.insert(i);
            while(z%i==0) z/=i;
        }
    }
    if(z>1) S.insert(z);
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%lld%lld%lld",&m1,&m2,&m3);
        M.clear(),S.clear();
        solve1(m1);
        solve1(m2);
        solve1(m3);
        for(auto i:M)
        {
            solve2(i.first-1);
            if(i.second>1) S.insert(i.first);
        }
        ll t=1;
        q=0;
        for(auto i:S) a[++q]=i,t*=i;
        for(int i=1;i<=q;++i) printf("%lld ",a[i]);printf("\n");
        ll s=0;
        for(int i=0;i<=(1<<q)-1;++i)
        {
            ll w=1;
            for(int j=1;j<=q;++j)
            {
                if(i&(1<<(j-1))) w*=a[j];
            }
            if(sum(i)%2==0) s+=t/w;
            else s-=t/w;
        }
        printf("%lld\n",(s*inv(t)%P+P)%P);
    }
    return 0;
}