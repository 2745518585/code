#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,a[N],c[N];
vector<int> b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) a[i]=(m+1)/2;
        for(int i=1;i<=m;++i)
        {
            b[i].clear();
            c[i]=0;
            int k;
            scanf("%d",&k);
            for(int j=1;j<=k;++j)
            {
                int x;
                scanf("%d",&x);
                b[i].push_back(x);
            }
            if(k==1)
            {
                --a[b[i][0]];
                c[i]=b[i][0];
            }
        }
        bool u=false;
        for(int i=1;i<=m;++i)
        {
            if(c[i]) continue;
            for(auto j:b[i])
            {
                if(a[j]>=1)
                {
                    --a[j];
                    c[i]=j;
                    break;
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(a[i]<0) u=true;
        }
        if(u) printf("NO\n");
        else
        {
            printf("YES\n");
            for(int i=1;i<=m;++i) printf("%d ",c[i]);
            printf("\n");
        }
    }
    return 0;
}