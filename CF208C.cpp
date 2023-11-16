#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1001,M=1000001;
int n,m,p=1,t[N],f[N],l[N];
ll g[N][N];
bool h[N];
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
void SPFA()
{
    for(int i=1;i<=n;++i) f[i]=1e9;
    f[1]=0;
    h[1]=true;
    queue<int> Q;
    Q.push(1);
    while(!Q.empty()) 
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+1<f[a[i].m])
            {
                f[a[i].m]=f[k]+1;
                h[a[i].m]=true;
                Q.push(a[i].m);
            }
        }
    }
}
void tpsort(int x,ll g[])
{
    g[x]=1;
    queue<int> Q;
    for(int i=1;i<=n;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]+1==f[k])
            {
                g[a[i].m]+=g[k];
                --l[a[i].m];
                if(l[a[i].m]==0) Q.push(a[i].m);
            }
        }
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
    SPFA();
    for(int r=1;r<=n;++r)
    {
        for(int i=1;i<=n;++i)
        {
            for(int j=t[i];j!=0;j=a[j].q)
            {
                if(f[i]+1==f[a[j].m]) ++l[i];
            }
        }
        tpsort(r,g[r]);
    }
    double s=0;
    for(int i=1;i<=n;++i)
    {
        if(i==1|i==n) s=max(s,(double)(g[i][1]*g[n][i])/g[n][1]);
        else s=max(s,(double)(2*g[i][1]*g[n][i])/g[n][1]);
    }
    printf("%.12lf",s);
    return 0;
}