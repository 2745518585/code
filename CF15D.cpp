#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1201;
int m,n,k,q,t,a[N][N],b[N][N],c[N][N],Q2[N],T,R;
ll d[N][N];
bool h[N][N];
struct str
{
    int x,y;
    ll s;
    friend bool operator <(str a,str b)
    {
        if(a.s!=b.s) return a.s>b.s;
        if(a.x!=b.x) return a.x>b.x;
        return a.y>b.y;
    }
}e[N*N];
priority_queue<str> Q;
int main()
{
    scanf("%d%d%d%d",&m,&n,&k,&q);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=m;++i)
    {
        T=0,R=-1;
        for(int j=1;j<=n;++j)
        {
            while(T<=R&&Q2[T]<j-q+1) ++T;
            while(T<=R&&a[i][Q2[R]]>=a[i][j]) --R;
            Q2[++R]=j;
            b[i][j]=a[i][Q2[T]];
        }
    }
    for(int i=1;i<=n;++i)
    {
        T=0,R=-1;
        for(int j=1;j<=m;++j)
        {
            while(T<=R&&Q2[T]<j-k+1) ++T;
            while(T<=R&&b[Q2[R]][i]>=b[j][i]) --R;
            Q2[++R]=j;
            c[j][i]=b[Q2[T]][i];
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            d[i][j]=d[i-1][j]+d[i][j-1]-d[i-1][j-1]+a[i][j];
        }
    }
    for(int i=k;i<=m;++i)
    {
        for(int j=q;j<=n;++j)
        {
            Q.push((str){i,j,d[i][j]-d[i-k][j]-d[i][j-q]+d[i-k][j-q]-(ll)c[i][j]*k*q});
        }
    }
    while(!Q.empty())
    {
        str x=Q.top();
        Q.pop();
        if(h[x.x][x.y]) continue;
        e[++t]=x;
        for(int i=x.x-k+1;i<=x.x+k-1;++i)
        {
            for(int j=x.y-q+1;j<=x.y+q-1;++j)
            {
                h[i][j]=true;
            }
        }
    }
    printf("%d\n",t);
    for(int i=1;i<=t;++i)
    {
        printf("%d %d %lld\n",e[i].x-k+1,e[i].y-q+1,e[i].s);
    }
    return 0;
}