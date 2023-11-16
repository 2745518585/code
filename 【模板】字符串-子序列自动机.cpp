#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=2000001;
int n,m,k,a[N];
vector<int> f[N];
int main()
{
    scanf("%d%d%d%d",&n,&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        f[a[i]].push_back(i);
    }
    for(int i=1;i<=k;++i) f[i].push_back(1e9);
    for(int i=1;i<=m;++i)
    {
        int q,t=0;
        scanf("%d",&q);
        for(int j=1;j<=q;++j)
        {
            int x;
            scanf("%d",&x);
            if(t!=1e9) t=f[x][upper_bound(f[x].begin(),f[x].end(),t)-f[x].begin()];
        }
        if(t<1e9) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}