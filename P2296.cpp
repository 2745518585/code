#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=10001,M=2000001;
int n,m,s1,s2,p=1,t[N],f[N];
bool g[N],h[N];
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
void dfs(int x)
{
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]==false) dfs(a[i].m);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(y,x);
    }
    scanf("%d%d",&s1,&s2);
    dfs(s2);
    for(int i=1;i<=n;++i) g[i]=true;
    for(int i=1;i<=n;++i)
    {
        if(h[i]==true) continue;
        g[i]=false;
        for(int j=t[i];j!=0;j=a[j].q)
        {
            g[a[j].m]=false;
        }
    }
    queue<int> Q;
    for(int i=1;i<=n;++i) f[i]=1e9,h[i]=false;
    f[s2]=0,h[s2]=true;
    Q.push(s2);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+1<f[a[i].m]&&g[a[i].m]==true)
            {
                f[a[i].m]=f[k]+1;
                h[a[i].m]=true;
                Q.push(a[i].m);
            }
        }
    }
    printf("%d",f[s1]==1e9?-1:f[s1]);
    return 0;
}