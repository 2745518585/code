#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500001;
int T,n,m,fa[N],fa2[N],b[N];
struct road
{
    int x,y;
}a[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int find2(int x)
{
    if(fa2[x]==x) return x;
    return fa2[x]=find2(fa2[x]);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) fa[i]=fa2[i]=i;
        int t=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[i].x=x,a[i].y=y;
            if(find(x)!=find(y))
            {
                fa[find(x)]=find(y);
                b[i]=0;
            }
            else if(find2(x)!=find2(y))
            {
                fa2[find2(x)]=find2(y);
                b[i]=1;
            }
            else t=i,b[i]=1;
        }
        if(t!=0)
        {
            for(int i=1;i<=n;++i) fa[i]=i;
            for(int i=1;i<=m;++i)
            {
                if(b[i]==0)
                {
                    if((find(a[i].x)==find(a[t].x)&&find(a[i].y)==find(a[t].y))||(find(a[i].x)==find(a[t].y)&&find(a[i].y)==find(a[t].x)))
                    {
                        swap(b[i],b[t]);
                        break;
                    }
                    fa[find(a[i].x)]=find(a[i].y);
                }
            }
        }
        for(int i=1;i<=m;++i)
        {
            printf("%d",b[i]);
        }
        printf("\n");
    }
    return 0;
}