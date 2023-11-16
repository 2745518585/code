#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,k,a[N];
ll f[N];
int main()
{
    scanf("%d",&k);
    for(int i=0;i<=5;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<=1000000;++i)
    {
        int x=i;
        for(int j=0;j<=5;++j)
        {
            if(x%10%3==0) f[i]+=(ll)a[j]*(x%10/3);
            x/=10;
        }
    }
    int w=3;
    for(int i=0;i<=5;++i)
    {
        int p=3*(k-1);
        for(int j=1;j<p;j<<=1)
        {
            p-=j;
            for(int l=1000000;l>=(ll)w*j;--l) f[l]=max(f[l],f[l-w*j]+(ll)a[i]*j);
        }
        for(int l=1000000;l>=(ll)w*p;--l) f[l]=max(f[l],f[l-w*p]+(ll)a[i]*p);
        w*=10;
    }
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        printf("%lld\n",f[x]);
    }
    return 0;
}