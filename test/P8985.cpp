#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=51001,K=11001,Q=151001,M=14;
int n,m,q,c[Q],d[N],lg[1<<M];
short f1[K][N/M],f2[K][N/M],f3[K][N/M];
ll g1[1<<M],g2[1<<M],e1[N],e2[N];
vector<int> e[N/M];
struct str
{
    int x,y,z,a,b,t;
}a[N];
struct
{
    int x,y,z,t;
}b[N];
inline void add(short *a,int x)
{
    a[x/M]^=(1<<(x%M));
}
bool cmp(str a,str b)
{
    if((a.a<a.b)^(b.a<b.b)) return a.a<a.b;
    if(a.a<a.b) return a.a<b.a;
    else return a.b>b.b;
}
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        char z;
        scanf("%s",&z);
        if(z=='+')
        {
            ++n;
            scanf("%d%d%d%d%d",&a[n].x,&a[n].y,&a[n].z,&a[n].a,&a[n].b);
            a[n].t=n;
            c[i]=n;
        }
        else if(z=='-')
        {
            scanf("%d",&c[i]);
        }
        else if(z=='?')
        {
            ++q;
            scanf("%d%d%d",&b[q].x,&b[q].y,&b[q].z);
            b[q].t=i;
        }
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i) d[a[i].t]=i;
    for(int i=1;i<=m;++i)
    {
        if(c[i]>0) c[i]=d[c[i]];
    }
    for(int i=1;i<=n;++i)
    {
        add(f1[a[i].x],i);
        add(f2[a[i].y],i);
        add(f3[a[i].z],i);
    }
    for(int i=1;i<=10000;++i)
    {
        for(int j=0;j<=n/M;++j)
        {
            f1[i][j]^=f1[i-1][j];
            f2[i][j]^=f2[i-1][j];
            f3[i][j]^=f3[i-1][j];
        }
    }
    for(int i=0;i<=M-1;++i)
    {
        for(int j=(1<<i);j<=(1<<(i+1))-1;++j) lg[j]=i;
    }
    for(int i=1;i<=m;++i)
    {
        if(c[i]>0) e[c[i]/M].push_back(i);
    }
    for(int i=0;i<=n/M;++i)
    {
        for(int j=1;j<=(1<<M)-1;++j)
        {
            g1[j]=min(g1[j^(1<<lg[j])],g2[j^(1<<lg[j])]-a[i*M+lg[j]].a);
            g2[j]=g2[j^(1<<lg[j])]-a[i*M+lg[j]].a+a[i*M+lg[j]].b;
        }
        int x=0,p=e[i].size(),t=0;
        for(int j=1;j<=q;++j)
        {
            while(x<p&&e[i][x]<b[j].t) t^=(1<<(c[e[i][x]]%M)),++x;
            int p=f1[b[j].x][i]&f2[b[j].y][i]&f3[b[j].z][i]&t;
            e1[j]=min(e1[j],e2[j]+g1[p]);
            e2[j]+=g2[p];
        }
    }
    for(int i=1;i<=q;++i)
    {
        printf("%lld\n",-e1[i]);
    }
    return 0;
}