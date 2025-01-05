#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
char b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        scanf("%s",b+1);
        multiset<int> Set;
        ll s=0;
        for(int i=n;i>=1;--i)
        {
            Set.insert(a[i]);
            if(b[i]=='1')
            {
                s+=*Set.begin();
                Set.erase(Set.begin());
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}