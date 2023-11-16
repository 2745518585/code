#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m;
struct str
{
    int a,b;
}a[N];
bool cmp(str a,str b)
{
    if(max(a.a,a.b)!=max(b.a,b.b)) return max(a.a,a.b)<max(b.a,b.b);
    return a.b<b.b;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].b,&a[i].a);
    }
    sort(a+1,a+n+1,cmp);
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i].b>=m)
        {
            m=max(m,a[i].a);
            ++s;
        }
    }
    printf("%d",s);
    return 0;
}