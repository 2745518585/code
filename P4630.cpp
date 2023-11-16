#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,w,p=1,t[N],t2[N],tot,f[N],g[N];
ll s;
stack<int> S;
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int b,c;
}T[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void road2(int x,int y)
{
    a[++p].m=y;
    a[p].q=t2[x];
    t2[x]=p;
}
void dfs(int x)
{
    ++w;
    T[x].b=T[x].c=++tot;
    S.push(x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(T[a[i].m].b==0)
        {
            dfs(a[i].m);
            T[x].c=min(T[x].c,T[a[i].m].c);
            if(T[a[i].m].c==T[x].b)
            {
                ++q;
                while(S.top()!=a[i].m)
                {
                    ++f[q];
                    road2(q,S.top());
                    road2(S.top(),q);
                    S.pop();
                }
                ++f[q];
                road2(q,S.top());
                road2(S.top(),q);
                S.pop();
                ++f[q];
                road2(q,x);
                road2(x,q);
            }
        }
        T[x].c=min(T[x].c,T[a[i].m].b);
    }
}
void dfs2(int x,int fa)
{
    int u;
    if(x<=n) g[x]=1,u=-1;
    else g[x]=0,u=f[x];
    for(int i=t2[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs2(a[i].m,x);
        s+=(ll)u*g[x]*g[a[i].m];
        g[x]+=g[a[i].m];
    }
    s+=(ll)u*g[x]*(w-g[x]);
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
    q=n;
    for(int i=1;i<=n;++i)
    {
        if(T[i].b!=0) continue;
        w=0;
        dfs(i);
        dfs2(i,0);
    }
    printf("%lld",s*2);
    return 0;
}