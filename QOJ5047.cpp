#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,k,a[N],b[N];
ll jc[N];
set<int> Set;
struct str
{
    int l,r,ls,rs;
}f[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            b[a[i]]=i;
        }
        jc[0]=1;
        for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
        Set.clear();
        Set.insert(0);
        for(int i=1;i<=n;++i) f[i].l=f[i].r=f[i].ls=f[i].rs=0;
        f[0].l=0,f[0].r=n+1,f[0].ls=f[0].rs=0;
        ll s=1;
        for(int i=1;i<=n;++i)
        {
            int t=b[i];
            auto p=Set.upper_bound(t);
            if(p==Set.begin()) continue;
            int x=*prev(p);
            if(f[x].r<=t) continue;
            if(t<=f[x].l+f[x].ls)
            {
                s=s*(f[x].ls-f[x].ls/k+1)%P;
                f[x].ls+=k;
            }
            else if(t>=f[x].r-f[x].rs)
            {
                s=s*(f[x].rs-f[x].rs/k+1)%P;
                f[x].rs+=k;
            }
            else
            {
                if(t+k<f[x].r)
                {
                    f[t].l=t,f[t].r=f[x].r,f[t].ls=k,f[t].rs=f[x].rs;
                    Set.insert(t);
                    if(f[t].ls+f[t].rs>=f[t].r-f[t].l)
                    {
                        s=s*jc[min(f[t].r,n)-max(f[t].l,1)+1-(f[t].ls+f[t].rs)/k]%P;
                        Set.erase(t);
                    }
                }
                if(t-k>f[x].l)
                {
                    f[x].r=t,f[x].rs=k;
                }
                else
                {
                    Set.erase(x);
                    continue;
                }
            }
            if(f[x].ls+f[x].rs>=f[x].r-f[x].l)
            {
                s=s*jc[min(f[x].r,n)-max(f[x].l,1)+1-(f[x].ls+f[x].rs)/k]%P;
                Set.erase(x);
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}