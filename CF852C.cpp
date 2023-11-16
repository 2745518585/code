#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
int n,a[N],c[N];
struct str
{
    int x,t;
}b[N];
bool cmp(str a,str b)
{
    return a.x>b.x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        b[i].x=(n+1-a[i]-a[i%n+1]);
        b[i].t=i;
    }
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n;++i) c[b[i].t]=i;
    for(int i=1;i<=n;++i)
    {
        printf("%d ",c[i]-1);
    }
    return 0;
}