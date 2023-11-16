#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,b[N];
ll q;
struct str
{
    int x,t;
}a[N];
bool cmp(str a,str b)
{
    return a.x<b.x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].t);
        q+=a[i].t;
    }
    sort(a+1,a+n+1,cmp);
    b[0]=-1e9;
    for(int i=1;i<=n;++i) b[i]=max(b[i-1],a[i].x+a[i].t);
    int x=1;
    while(x<n)
    {
        if(a[x+1].x<=b[x]) ++x;
        else
        {
            q+=a[x+1].x-b[x];
            ++x;
        }
    }
    printf("%lld",q);
    return 0;
}