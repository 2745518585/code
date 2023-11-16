#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001;
const ll P=2011;
int n;
ll f[N][N];
struct str
{
    int a,b;
}a[N];
bool cmp(str a,str b)
{
    if(a.a!=b.a) return a.a>b.a;
    return a.b<b.b;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].a,&a[i].b);
    }
    sort(a+1,a+n+1,cmp);
    int x=0;
    ll s=1;
    for(int i=2;i<=n;++i)
    {
        if(a[i].a==a[i-1].a) ++x;
        else x=0;
        s=s*min(a[i].b+x,i)%P;
    }
    printf("%lld ",s%P);
    s=1;
    for(int i=1;i<=n;++i)
    {
        int j=i;
        while(a[j+1].a==a[i].a) ++j;
        for(int k=1;k<=i;++k) f[i-1][k]=1;
        for(int k=i;k<=j;++k)
        {
            for(int l=1;l<=i;++l)
            {
                f[k][l]=f[k][l-1];
                if(l<=a[k].b) f[k][l]=(f[k][l]+f[k-1][l])%P;
            }
        }
        s=s*(f[j][min(i,a[j].b)])%P;
        i=j;
    }
    printf("%lld",s%P);
    return 0;
}