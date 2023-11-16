#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
const int N=2000001;
int n,m,p=1,q,t[N],tot,r[N];
bool h[N];
stack<int> S;
struct tree
{
    int b,c;
}T[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    T[x].b=T[x].c=++tot;
    S.push(x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(T[a[i].m].b==0)
        {
            dfs(a[i].m);
            T[x].c=min(T[x].c,T[a[i].m].c);
        }
        if(h[a[i].m]==false)
        {
            T[x].c=min(T[x].c,T[a[i].m].c);
        }
    }
    if(T[x].b==T[x].c)
    {
        ++q;
        while(S.top()!=x)
        {
            r[S.top()]=q;
            h[S.top()]=true;
            S.pop();
        }
        r[x]=q;
        h[x]=true;
        S.pop();
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,x2,y,y2;
        scanf("%d%d%d%d",&x,&x2,&y,&y2);
        road(x+(1-x2)*n,y+y2*n);
        road(y+(1-y2)*n,x+x2*n);
    }
    for(int i=1;i<=n*2;++i)
    {
        if(T[i].b==0) dfs(i);
    }
    for(int i=1;i<=n;++i)
    {
        if(r[i]==r[n+i])
        {
            printf("IMPOSSIBLE");
            return 0;
        }
    }
    printf("POSSIBLE\n");
    for(int i=1;i<=n;++i)
    {
        if(r[i]<r[n+i]) printf("0 ");
        else printf("1 ");
    }
    return 0;
}