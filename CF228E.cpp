#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
const int N=2000001;
int n,m,fa[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n*2;++i) fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        if(w==0)
        {
            if(find(x)==find(y))
            {
                printf("Impossible");
                return 0;
            }
            if(find(x)!=find(n+y)) fa[find(x)]=find(n+y);
            if(find(n+x)!=find(y)) fa[find(n+x)]=find(y);
        }
        else
        {
            if(find(x)==find(n+y))
            {
                printf("Impossible");
                return 0;
            }
            if(find(x)!=find(y)) fa[find(x)]=find(y);
            if(find(n+x)!=find(n+y)) fa[find(n+x)]=find(n+y);
        }
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(find(i)<find(n+i)) ++s;
    }
    printf("%d\n",s);
    for(int i=1;i<=n;++i)
    {
        if(find(i)<find(n+i)) printf("%d ",i);
    }
    return 0;
}