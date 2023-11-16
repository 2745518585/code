#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int m,n,*a[N];
ll solve(int *a)
{
    sort(a+1,a+n+1);
    ll s=0,w=0;
    for(int i=1;i<=n;++i)
    {
        w+=a[i];
        s+=(ll)i*a[i]-w;
    }
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;++i) a[i]=new int[n+10];
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&a[j][i]);
            }
        }
        ll s=0;
        for(int i=1;i<=m;++i)
        {
            s+=solve(a[i]);
            delete[] a[i];
        }
        printf("%lld\n",s);
    }
    return 0;
}