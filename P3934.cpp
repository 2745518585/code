#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001,M=2e7;
int n,m,a[N],sp,p[M+1],phi[M+1];
ll T[N];
bool ip[M+1];
void add(int x,ll k)
{
    while(x<=n) T[x]+=k,x+=x&-x;
}
ll sum(int x)
{
    ll s=0;
    while(x>=1) s+=T[x],x-=x&-x;
    return s;
}
struct str
{
    ll x;
    bool u;
    str(){}
    str(ll x,bool u):x(x),u(u){}
};
str qpow(ll a,ll b,ll P)
{
    bool u=false,v=false;
    if(a>=P)
    {
        u=true;
        a%=P;
    }
    ll x=1,y=a;
    while(b)
    {
        if(b&1)
        {
            u|=v;
            if(x*y>=P) u=true;
            x=x*y%P;
        }
        if(y*y>=P) v=true;
        y=y*y%P;
        b>>=1;
    }
    return str(x,u);
}
str solve(int x,int r,ll P)
{
    if(P==1) return str(0,true);
    if(x==r) return str(sum(r)%P,sum(r)>=P);
    str z=solve(x+1,r,phi[P]);
    return qpow(sum(x),z.x+(z.u?phi[P]:0),P);
}
int main()
{
    phi[1]=1;
    for(int i=2;i<=M;++i)
    {
        if(ip[i]==false) p[++sp]=i,phi[i]=i-1;
        for(int j=1;j<=sp&&i*p[j]<=M;++j)
        {
            ip[i*p[j]]=true;
            if(i%p[j]==0)
            {
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            phi[i*p[j]]=phi[i]*phi[p[j]];
        }
    }
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        add(i,a[i]-a[i-1]);
    }
    for(int i=1;i<=m;++i)
    {
        int z,x,y,k;
        scanf("%d%d%d%d",&z,&x,&y,&k);
        if(z==1)
        {
            add(x,k);
            add(y+1,-k);
        }
        else if(z==2)
        {
            printf("%lld\n",solve(x,y,k).x%k);
        }
    }
    return 0;
}