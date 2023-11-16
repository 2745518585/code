#include<cstdio>
using namespace std;
typedef long long ll;
const int N=1e6+1;
int n,p=1,t[N];
struct str
{
    int m,q;
}a[N*2];
struct tree
{
    int fa,s;
    ll q,w;
}T[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    T[x].s=1;
    T[x].q=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].fa) continue;
        T[a[i].m].fa=x;
        dfs(a[i].m);
        T[x].s+=T[a[i].m].s;
        T[x].q+=T[a[i].m].q+T[a[i].m].s;
    }
}
void dfs2(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].fa) continue;
        T[a[i].m].w=T[x].w+n-2*T[a[i].m].s;
        dfs2(a[i].m);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs(1);
    T[1].w=T[1].q;
    dfs2(1);
    int q=0;
    ll s=-1;
    for(int i=1;i<=n;++i)
    {
        if(T[i].w>s)
        {
            s=T[i].w;
            q=i;
        }
    }
    printf("%d",q);
    return 0;
}