#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m;
ll a[N];
vector<int> b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) b[i].clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        for(int i=1;i<=n;++i)
        {
            ll x;
            scanf("%lld",&x);
            a[i]-=x;
        }
        for(int i=1;i<=n;++i) a[i]+=a[i-1];
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            b[x-1].push_back(y);
            b[y].push_back(x-1);
        }
        
    }
    return 0;
}