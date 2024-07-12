#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll m,k,a[N];
struct str
{
    ll l,r;
}b[N];
bool cmp(str a,str b)
{
    if(a.l!=b.l) return a.l<b.l;
    return a.r>b.r;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%lld%d%lld",&m,&n,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        a[++n]=m;
        for(int i=n;i>=1;--i) a[i]-=a[i-1];
        ll l=1,r=1e18;
        while(l<r)
        {
            auto check=[&](ll x)
            {
                ll s=0;
                for(int i=1;i<=n;++i) s+=a[i]/x-1;
                return s;
            };
            ll z=l+r+1>>1;
            if(check(z)>=k) l=z;
            else r=z-1;
        }
        ll L=l;
        l=1,r=1e18;
        while(l<r)
        {
            auto check=[&](ll x)
            {
                ll s=0;
                for(int i=1;i<=n;++i) s+=(a[i]-1)/x;
                return s;
            };
            ll z=l+r>>1;
            if(check(z)<=k) r=z;
            else l=z+1;
        }
        ll R=l;
        if(L>=R)
        {
            printf("0\n");
            continue;
        }
        for(int i=1;i<=n;++i)
        {
            if((a[i]-1)/R==a[i]/L)
            {
                b[i].l=a[i]/((a[i]-1)/R+1);
                if(a[i]/L==0) b[i].r=1e18;
                else b[i].r=(a[i]-1)/(a[i]/L)+1;
            }
            else b[i].l=L,b[i].r=R;
        }
        sort(b+1,b+n+1,cmp);
        ll s=1e18,p=R;
        for(int i=1;i<=n;++i)
        {
            s=min(s,p-b[i].l);
            p=max(p,b[i].r);
        }
        printf("%lld\n",s);
    }
    return 0;
}