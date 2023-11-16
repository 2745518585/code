#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N=1000001;
int n,m;
ll a[N],b[N];
ld s1=-1e20,s2=1e20;
void check(ld x,ld y,ld z)
{
    s1=max(s1,(x+y+z)/(x*y*z));
    s2=min(s2,(x+y+z)/(x*y*z));
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    sort(a+1,a+n+1);
    int x=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]>=0)
        {
            x=i;
            break;
        }
    }
    b[++m]=1;
    b[++m]=2;
    b[++m]=3;
    b[++m]=n;
    b[++m]=n-1;
    b[++m]=n-2;
    b[++m]=x-4;
    b[++m]=x-3;
    b[++m]=x-2;
    b[++m]=x-1;
    b[++m]=x;
    b[++m]=x+1;
    b[++m]=x+2;
    b[++m]=x+3;
    b[++m]=x+4;
    for(int i=1;i<=m;++i)
    {
        if(b[i]<1||b[i]>n) b[i]=1;
    }
    sort(b+1,b+m+1);
    m=unique(b+1,b+m+1)-b-1;
    for(int i=1;i<=m;++i)
    {
        for(int j=i+1;j<=m;++j)
        {
            for(int k=j+1;k<=m;++k)
            {
                check(a[b[i]],a[b[j]],a[b[k]]);
            }
        }
    }
    printf("%.15Lf\n%.15Lf",s2,s1);
    return 0;
}