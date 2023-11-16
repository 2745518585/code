#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001,M=1000001;
int n,m,tot=0,p=1,t[N];
ll d[N];
struct tree
{
    int b,c;
    ll s;
}T[N];
struct road
{
    int m,q;
}a[M];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa,int r)
{
    T[x].b=T[x].c=++tot;
    T[x].s=1;
    int s=0;
    ll w=1,q=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(T[a[i].m].b==0)
        {
            dfs(a[i].m,x,r);
            T[x].s+=T[a[i].m].s;
            T[x].c=min(T[x].c,T[a[i].m].c);
            ++s;
            w*=T[a[i].m].s;
            if(T[a[i].m].c>=T[x].b&&x!=r)
            {
                d[x]+=T[a[i].m].s*(n-T[a[i].m].s-1);
                q+=T[a[i].m].s;
            }
        }
        T[x].c=min(T[x].c,T[a[i].m].b);
    }
    d[x]+=q*(n-q-1);
    if(x==r&&s>=2) d[x]=w*2;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        if(T[i].b==0) dfs(i,0,i);
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld\n",d[i]+(n-1)*2);
    }
    return 0;
}