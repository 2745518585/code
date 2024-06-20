#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=20000001;
const ll P=998244353;
int n,m,q;
ll jc[N],ivjc[N];
struct str
{
    ll a,b,c;
    str() {}
    str(ll a,ll b,ll c):a(a),b(b),c(c) {}
    friend str operator+(const str &a,const str &b)
    {
        return str(a.a+b.a,a.b+b.b,a.c+b.c);
    }
};
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
ll A(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P;
}
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P*ivjc[b]%P;
}
str check(str x,int k)
{
    str s(0,0,0);
    s.a=(s.a+x.a*(C(n-1,k-1)-2*C(n-2,k-1)+C(n-3,k-1))%P)%P;
    s.b=(s.b+x.a*(3*C(n-2,k-1)-3*C(n-3,k-1))%P+x.b*(C(n-1,k-1)-C(n-2,k-1))%P)%P;
    s.c=(s.c+x.a*(C(n-2,k-1)-2*C(n-3,k-1))%P+x.b*C(n-2,k-1)%P+x.c*C(n-1,k-1)%P)%P;
    return s;
}
int main()
{
    int p;
    scanf("%d%d%d",&n,&m,&p);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n]=inv(jc[n]);
    for(int i=n;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    str s;
    if(p==1) s=str(0,1,0);
    else s=str(1,0,0);
    ll w=1;
    for(int i=1;i<=m;++i)
    {
        int l;
        scanf("%d",&l);
        s=check(s,l)+check(str(s.a,(2*s.a*l%P+s.b)%P,(s.a*l%P*l%P+s.b*l%P+s.c)),n-l);
        w=w*C(n,l)%P;
    }
    w=inv(w);
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        int x;
        scanf("%d",&x);
        printf("%lld\n",((s.a*x%P*x%P+s.b*x%P+s.c)*w%P+P)%P);
    }
    return 0;
}