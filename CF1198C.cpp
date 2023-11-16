#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,h[N],g[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n*3;++i) h[i]=false;
        for(int i=1;i<=m;++i) g[i]=false;
        int w=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            if(w<n&&!h[x]&&!h[y]) h[x]=true,h[y]=true,g[i]=true,++w;
        }
        if(w>=n)
        {
            printf("Matching\n");
            int s=n;
            for(int i=1;i<=m;++i)
            {
                if(s&&g[i]) printf("%d ",i),--s;
            }
            printf("\n");
        }
        else
        {
            printf("IndSet\n");
            int s=n;
            for(int i=1;i<=n*3;++i)
            {
                if(s&&!h[i]) printf("%d ",i),--s;
            }
            printf("\n");
        }
    }
    return 0;
}