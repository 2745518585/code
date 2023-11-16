#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
const int N=1000001;
typedef long long ll;
int n;
ll k,a[N];
map<ll,int> Map;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld",&n,&k);
        Map.clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            ++Map[a[i]];
        }
        sort(a+1,a+n+1);
        int s=0;
        for(int i=1;i<=n;++i)
        {
            if(Map[a[i]]==0) continue;
            --Map[a[i]];
            if(Map.count(a[i]*k)&&Map[a[i]*k]>0)
            {
                --Map[a[i]*k];
            }
            else ++s;
        }
        printf("%d\n",s);
    }
    return 0;
}