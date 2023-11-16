#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,fa[N];
bool h[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) fa[i]=i;
        int s=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            if(x!=y) ++s;
            else fa[x]=0;
            fa[find(x)]=find(y);
        }
        for(int i=1;i<=n;++i)
        {
            if(find(i)==i) ++s;
        }
        printf("%d\n",s-(n-m));
    }
    return 0;
}