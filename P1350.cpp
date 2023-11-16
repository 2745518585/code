#include<cstdio>
using namespace std;
const int p=1e5+3;
typedef long long ll;
int a,b,c,d,m;
void mod(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else mod(b,a%b,y,x),y-=a/b*x;
}
ll C(int x,int y)
{
    if(x<y) return 0;
    ll s=1;
    for(int i=x-y+1;i<=x;++i)
    {
        s=(s*i)%p;
    }
    for(int i=1;i<=y;++i)
    {
        ll f,g;
        mod(i,p,f,g);
        f=(f%p+p)%p;
        s=(s*f)%p;
    }
    return s;
}
ll A(int x,int y)
{
    if(x<y) return 0;
    ll s=1;
    for(int i=x-y+1;i<=x;++i)
    {
        s=(s*i)%p;
    }
    return s;
}
int main()
{
    scanf("%d%d%d%d%d",&a,&b,&c,&d,&m);
    ll s=0;
    for(int i=0;i<=m;++i)
    {
        ll w=1;
        w=(w*C(b,i))%p;
        w=(w*A(a,i))%p;
        w=(w*C(d,m-i))%p;
        w=(w*A(a+c-i,m-i))%p;
        s=(s+w)%p;
    }
    printf("%lld",s);
    return 0;
}