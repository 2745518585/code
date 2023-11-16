#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=100001,M=1000001;
int n,m,p=1,s=1e9,t[N],b[10],f[10][N];
bool h[N];
struct str
{
    int m,q,w;
}a[M];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void SPFA(int x,int f[])
{
    for(int i=1;i<=n;++i) f[i]=1e9,h[i]=false;
    f[x]=0;
    h[x]=true;
    queue<int> Q;
    Q.push(x);
    while(!Q.empty()) 
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                h[a[i].m]=true;
                Q.push(a[i].m);
            }
        }
    }
}
void dfs(int x,int k,int w)
{
    if(x==5)
    {
        s=min(s,w);
        return;
    }
    for(int i=1;i<=5;++i)
    {
        if(h[i]==true) continue;
        h[i]=true;
        dfs(x+1,i,w+f[k][b[i]]);
        h[i]=false;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=5;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    SPFA(1,f[0]);
    for(int i=1;i<=5;++i) SPFA(b[i],f[i]);
    dfs(0,0,0);
    printf("%d",s);
    return 0;
}