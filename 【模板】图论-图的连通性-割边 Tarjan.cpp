#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001,M=1000001;
int n,m,tot=0,p=1,p2=1,t[N];
struct tree
{
    int b,c;
}T[N];
struct road
{
    int m,q;
}a[M];
struct road2
{
    int x,y;
}a2[M];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
bool cmp(road2 a,road2 b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}
void dfs(int x,int fa)
{
    T[x].b=T[x].c=++tot;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(T[a[i].m].b==0)
        {
            dfs(a[i].m,x);
            T[x].c=min(T[x].c,T[a[i].m].c);
            if(T[a[i].m].c>T[x].b)
            {
                ++p2;
                a2[p2].x=min(x,a[i].m);
                a2[p2].y=max(x,a[i].m);
            }
        }
        T[x].c=min(T[x].c,T[a[i].m].b);
    }
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
        if(T[i].b==0) dfs(i,0);
    }
    printf("%d\n",p2);
    sort(a2+1,a2+p2+1,cmp);
    for(int i=1;i<=p2;++i)
    {
        printf("%d %d\n",a2[i].x,a2[i].y);
    }
    return 0;
}