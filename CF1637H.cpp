#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
ll T[N],f[N];
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
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        ll s=0;
        for(int i=1;i<=n;++i) T[i]=0;
        for(int i=1;i<=n;++i)
        {
            f[i]=(sum(n)-sum(a[i]))-sum(a[i]-1);
            s+=sum(n)-sum(a[i]);
            add(a[i],1);
        }
        for(int i=1;i<=n;++i) T[i]=0;
        for(int i=n;i>=1;--i)
        {
            f[i]-=sum(a[i])*2;
            add(a[i],1);
        }
        sort(f+1,f+n+1);
        printf("%lld ",s);
        for(int i=n;i>=1;--i)
        {
            s-=f[i]+(n-i);
            printf("%lld ",s);
        }
        printf("\n");
    }
}