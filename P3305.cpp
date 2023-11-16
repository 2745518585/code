#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10001,M=1000001;
int n,m,p=1,s1,s2,t[N],t0[N],f[N];
double d,w;
struct road
{
    int m,q;
    double r;
}a[M];
struct road2
{
    int x,y;
    double r;
}b[M];
bool cmp(road2 a,road2 b)
{
    return a.r<b.r;
}
void road(int x,int y,double r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
bool bfs()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=n;++i) f[i]=0;
    f[s1]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]==0&&a[i].r!=0)
            {
                f[a[i].m]=f[k]+1;
                Q.push(a[i].m);
            }
        }
    }
    return f[s2]!=0;
}
double dfs(int x,double r)
{
    if(x==s2) return r;
    double s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[a[i].m]==f[x]+1&&a[i].r!=0)
        {
            double z=dfs(a[i].m,min(r,a[i].r));
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
            }
            else f[a[i].m]=0;
            if(r==0) return s;
        }
    }
    return s;
}
int main()
{
    scanf("%d%d%lf",&n,&m,&w);
    s1=1,s2=n;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        double r;
        scanf("%d%d%lf",&x,&y,&r);
        b[i]=(road2){x,y,r};
        road(x,y,r);
        road(y,x,0);
    }
    d=1e9;
    double r=0;
    while(bfs())
    {
        for(int i=1;i<=n;++i) t0[i]=t[i];
        r+=dfs(s1,1e9);
    }
    printf("%.0lf\n",r);
    double L=1,R=r;
    while(L<R-1e-5)
    {
        double d=(L+R)/2;
        p=1;
        for(int i=1;i<=n;++i) t[i]=0;
        for(int i=1;i<=m;++i)
        {
            road(b[i].x,b[i].y,min(b[i].r,d));
            road(b[i].y,b[i].x,0);
        }
        double r0=0;
        while(bfs())
        {
            for(int i=1;i<=n;++i) t0[i]=t[i];
            r0+=dfs(s1,1e9);
        }
        if(r0>=r) R=d;
        else L=d;
    }
    printf("%.4lf",double(L*w));
    return 0;
}