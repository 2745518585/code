#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,fa[N],f[N];
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
        if(n%2==1)
        {
            for(int i=1;i<=m;++i) scanf("%*d%*d");
            if((n*(n-1)/2-m)%2==1) printf("First\n");
            else printf("Second\n");
            continue;
        }
        for(int i=1;i<=n;++i) fa[i]=i,f[i]=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            fa[find(x)]=find(y);
        }
        for(int i=1;i<=n;++i) ++f[find(i)];
        if(f[find(1)]%2!=f[find(n)]%2||(n*(n-1)/2-m)%2!=f[find(1)]%2) printf("First\n");
        else printf("Second\n");
    }
    return 0;
}