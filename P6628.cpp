#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5001,M=10000001;
int n,m,s,l[N],fa[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
namespace Solve
{
    int q,l[N],fa[N];
    struct str
    {
        int x,y,w;
    }a[M];
    bool cmp(str a,str b)
    {
        return a.w<b.w;
    }
    int find(int x)
    {
        if(fa[x]==x) return x;
        return fa[x]=find(fa[x]);
    }
    int solve(int k)
    {
        ++l[k],++l[s];
        fa[find(k)]=find(s);
        int x=0,w=0;
        for(int i=1;i<=n;++i)
        {
            if(x!=0)
            {
                fa[find(x)]=find(i);
                w+=abs(x-i);
                if(l[i]%2==1) x=0;
                else x=i;
            }
            else if(l[i]%2==1) x=i;
        }
        q=0;
        x=0;
        for(int i=1;i<=n;++i)
        {
            if(l[i]==0) continue;
            if(x!=0) a[++q]=(str){x,i,abs(x-i)};
            x=i;
        }
        x=0;
        for(int i=n;i>=1;--i)
        {
            if(l[i]==0) continue;
            if(x!=0) a[++q]=(str){x,i,abs(x-i)};
            x=i;
        }
        sort(a+1,a+q+1,cmp);
        for(int i=1;i<=q;++i)
        {
            if(find(a[i].x)!=find(a[i].y))
            {
                w+=a[i].w*2;
                fa[find(a[i].x)]=find(a[i].y);
            }
        }
        return w;
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&s);
    int w=0;
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ++l[x],++l[y];
        fa[find(x)]=find(y);
        w+=abs(y-x);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) Solve::l[j]=l[j],Solve::fa[j]=fa[j];
        printf("%d ",Solve::solve(i)+w);
    }
    return 0;
}