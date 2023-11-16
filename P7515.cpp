#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=4000001,M=2001;
int n,m,p=1,t[N],g[N],b[M][M];
ll f[N];
bool h[N];
struct road
{
    int m,q,w;
}a[N<<1];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
bool SPFA(int x)
{
    queue<int> Q;
    for(int i=1;i<=m+n;++i) f[i]=1e18,h[i]=false;
    f[1]=0;
    h[1]=true;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        ++g[k];
        if(g[k]>m+n) return false;
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
    return true;
}
void abc()
{
    scanf("%d%d",&m,&n);
    p=1;
    for(int i=1;i<=m+n;++i) t[i]=0;
    for(int i=2;i<=m;++i)
    {
        for(int j=2;j<=n;++j)
        {
            scanf("%d",&b[i][j]);
            b[i][j]-=b[i-1][j]+b[i][j-1]+b[i-1][j-1];
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if((i+j)%2==0)
            {
                road(m+j,i,b[i][j]);
                road(i,m+j,1e6-b[i][j]);
            }
            else
            {
                road(i,m+j,b[i][j]);
                road(m+j,i,1e6-b[i][j]);
            }
        }
    }
    for(int i=1;i<=m+n;++i) g[i]=0;
    if(!SPFA(1))
    {
        printf("NO\n");
        return;
    }
    printf("YES\n");
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if((i+j)%2==0) b[i][j]-=f[i]-f[m+j];
            else b[i][j]+=f[i]-f[m+j];
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}