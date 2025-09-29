#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=5001;
int n,m,d[N],f[N][N*2];
vector<int> a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) a[i].clear(),d[i]=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
            ++d[x],++d[y];
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<=n*2;++j) f[i][j]=1e9;
        }
        f[1][0]=0;
        for(int i=0;i<=n*2;++i)
        {
            for(int j=1;j<=n;++j)
            {
                f[j][i+1]=min(f[j][i+1],f[j][i]+1);
                f[a[j][i%d[j]]][i+1]=min(f[a[j][i%d[j]]][i+1],f[j][i]);
            }
            if(f[n][i]<1e9)
            {
                printf("%d %d\n",i,f[n][i]);
                break;
            }
        }
    }
    return 0;
}