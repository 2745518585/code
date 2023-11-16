#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10000001;
int n,m,q,rt[N],tot,p=1,t[N],b[N],c[N],d[N],T[N];
struct road
{
    int m,q;
}a[N];
void add(int x,int k)
{
    T[x]+=k;
    while(x<=n)
    {
        x+=(x&(-x));
        T[x]+=k;
    }
}
int sum(int x)
{
    int s=T[x];
    while(x!=0)
    {
        x-=(x&(-x));
        s+=T[x];
    }
    return s;
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    add(b[x],1);
    d[x]-=sum(q)-sum(b[x]);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs(a[i].m);
    }
    d[x]+=sum(q)-sum(b[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        c[i]=b[i];
    }
    sort(c+1,c+n+1);
    q=unique(c,c+n+1)-c-1;
    for(int i=1;i<=n;++i) rt[i]=++tot;
    for(int i=1;i<=n;++i)
    {
        b[i]=lower_bound(c+1,c+q+1,b[i])-c;
    }
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        road(x,i);
    }
    dfs(1);
    for(int i=1;i<=n;++i)
    {
        printf("%d\n",d[i]);
    }
    return 0;
}