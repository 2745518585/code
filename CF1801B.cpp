#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,b[N];
set<int> Set;
struct str
{
    int a,b;
}a[N];
bool cmp(str a,str b)
{
    return a.a<b.a;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&a[i].a,&a[i].b);
        }
        sort(a+1,a+n+1,cmp);
        b[n+1]=-1e9;
        for(int i=n;i>=1;--i) b[i]=max(b[i+1],a[i].b);
        Set.clear();
        int s=1e9;
        for(int i=1;i<=n;++i)
        {
            if(i<n) s=min(s,abs(a[i].a-b[i+1]));
            set<int>::iterator p=Set.lower_bound(a[i].a);
            if(p!=Set.end()&&(*p)>b[i+1]) s=min(s,abs(a[i].a-(*p)));
            if(p!=Set.begin()&&(*prev(p))>b[i+1]) s=min(s,abs(a[i].a-(*prev(p))));
            Set.insert(a[i].b);
        }
        printf("%d\n",s);
    }
    return 0;
}