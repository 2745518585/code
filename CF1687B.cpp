#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,b[N];
struct str
{
    int x,s;
}a[N];
bool cmp(str a,str b)
{
    return a.s<b.s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        printf("? ");
        for(int j=1;j<=m;++j) printf("%d",i==j);
        printf("\n");
        fflush(stdout);
        scanf("%d",&a[i].s);
        a[i].x=i;
    }
    sort(a+1,a+m+1,cmp);
    ll s=0;
    for(int i=1;i<=m;++i)
    {
        printf("? ");
        b[a[i].x]=1;
        for(int j=1;j<=m;++j) printf("%d",b[j]);
        printf("\n");
        fflush(stdout);
        b[a[i].x]=0;
        ll x;
        scanf("%lld",&x);
        if(x-s==a[i].s) s=x,b[a[i].x]=1;
    }
    printf("! %lld",s);
    fflush(stdout);
    return 0;
}