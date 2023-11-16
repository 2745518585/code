#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int n,m,fa[N],ga[N],a[N],b[N],f[N];
int find(int x)
{
    if(fa[x]==x) return x;
    int z=find(fa[x]);
    ga[x]*=ga[fa[x]];
    return fa[x]=z;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=1000000;++i) fa[i]=i,ga[i]=1;
    int l=1,r=1000000,ls=1,rs=1000000;
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        if(ls>0) ls-=x,rs-=x;
        else ls+=x,rs+=x;
        if(ls>0||rs<0) continue;
        int z=l-ls;
        f[z]=i;
        if(abs(ls)>=abs(rs))
        {
            for(int i=z+1;i<=r;++i) fa[i]=z*2-i,ga[i]=-1;
            r=z-1;
            rs=-1;
        }
        else
        {
            for(int i=l;i<=z-1;++i) fa[i]=z*2-i,ga[i]=-1;
            l=z+1;
            ls=1;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(f[find(b[i])]==0) printf("No %d\n",ga[b[i]]*(find(b[i])-l+ls));
        else printf("Yes %d\n",f[find(b[i])]);
    }
    return 0;
}