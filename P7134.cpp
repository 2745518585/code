#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
struct str
{
    ll w1,w2,s1,s2,s;
    str(){}
    str(ll w1,ll w2,ll s1,ll s2,ll s):w1(w1),w2(w2),s1(s1),s2(s2),s(s){}
};
map<ll,str> Map;
str solve(ll n)
{
    if(n==1) return str(1,1,0,0,0);
    if(Map.count(n)) return Map[n];
    str z1=solve((n+1)/2),z2=solve(n/2),z;
    z.w1=(z1.w1+z2.w1)%P;
    z.w2=(z2.w2+z1.w2)%P;
    z.s1=(z1.s1+(z2.s1+z2.w1))%P;
    z.s2=(z2.s2+(z1.s2+z1.w2))%P;
    z.s=(z1.s+z2.s+z1.s2*z2.w1%P+z2.s1*z1.w2%P)%P;
    return Map[n]=z;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll n;
        scanf("%lld",&n);
        str s=solve(n);
        printf("%lld\n",((s.s+s.s1+s.s2+1)%P+P)%P);
    }
    return 0;
}