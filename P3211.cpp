#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long double ld;
const int N=2001;
int n,m,q,l[N];
ld a[N][N],b[N];
struct road
{
    int x,y,w;
}c[N*N];
void solve()
{
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j<=n;++j)
        {
            if(fabs(a[j][i])>1e-6)
            {
                swap(a[i],a[j]);
                swap(b[i],b[j]);
                break;
            }
        }
        if(fabs(a[i][i])<=1e-6) continue;
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            ld z=a[j][i]/a[i][i];
            b[j]-=b[i]*z;
            for(int l=i+1;l<=n;++l) a[j][l]-=a[i][l]*z;
        }
    }
}
void add(int x,int y,int w)
{
    if(x==n) return;
    c[++q]={x,y,w};
    ++l[x];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        add(x,y,w);
        if(x!=y) add(y,x,w);
    }
    ld s=0;
    for(int i=0;i<=30;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=n;++k) a[j][k]=0;
            b[j]=0;
            a[j][j]=-l[j];
        }
        for(int j=1;j<=q;++j)
        {
            if(!(c[j].w&(1<<i)))
            {
                a[c[j].x][c[j].y]+=1;
            }
            else
            {
                a[c[j].x][c[j].y]-=1;
                b[c[j].x]-=1;
            }
        }
        solve();
        s+=(b[1]/a[1][1])*(1<<i);
    }
    printf("%.3Lf",s);
    return 0;
}