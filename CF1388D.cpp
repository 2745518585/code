#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,q,k,t[N],b[N],c[N],l[N];
ll s,f[N];
struct road
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa)
{
    f[x]=b[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        if(f[a[i].m]>=0) f[x]+=f[a[i].m];
    }
}
void dfs2(int x,int fa)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(f[a[i].m]>=0) dfs2(a[i].m,x);
    }
    printf("%d ",x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(f[a[i].m]<0) dfs2(a[i].m,x);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&c[i]);
        if(c[i]!=-1) road(c[i],i),++l[i];
    }
    for(int i=1;i<=n;++i)
    {
        if(l[i]==0) dfs(i,0);
    }
    for(int i=1;i<=n;++i) s+=f[i];
    printf("%lld\n",s);
    for(int i=1;i<=n;++i)
    {
        if(l[i]==0) dfs2(i,0);
    }
    return 0;
}