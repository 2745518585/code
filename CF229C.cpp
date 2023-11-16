#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N];
ll s;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) a[i]=n-1;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        --a[x],--a[y];
    }
    for(int i=1;i<=n;++i)
    {
        s+=a[i]*(n-a[i]-1);
    }
    printf("%lld",(ll)n*(n-1)*(n-2)/6-s/2);
    return 0;
}