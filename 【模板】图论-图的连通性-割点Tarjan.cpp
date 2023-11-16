#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001,M=1000001;
int n,m,tot=0,p=1,t[N];
bool d[N];
struct tree
{
    int b,c;
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
void dfs(int x,int r)
{
    T[x].b=T[x].c=++tot;
    int s=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(T[a[i].m].b==0)
        {
            dfs(a[i].m,r);
            T[x].c=min(T[x].c,T[a[i].m].c);
            ++s;
            if(T[a[i].m].c>=T[x].b&&x!=r)
            {
                d[x]=true;
            }
        }
        T[x].c=min(T[x].c,T[a[i].m].b);
    }
    if(x==r&&s>=2) d[x]=true;
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
        if(T[i].b==0) dfs(i,i);
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(d[i]==true) ++s;
    }
    printf("%d\n",s);
    for(int i=1;i<=n;++i)
    {
        if(d[i]==true)
        {
            printf("%d ",i);
        }
    }
    return 0;
}