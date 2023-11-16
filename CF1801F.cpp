#include<cstdio>
#include<algorithm>
using namespace std;
typedef long double ld;
const int N=201,M=100001;
int n,k,q,a[N],d[M],h[11000001];
ld f[N][M];
void solve(int x,int y)
{
    for(int i=1;i<=d[y];++i)
    {
        int j=d[y]/(d[y]/i);
        f[x][h[d[y]/i]]=max(f[x][h[d[y]/i]],(ld)(a[x]/i)/a[x]*f[x-1][y]);
        i=j;
    }
    f[x][q]=max(f[x][q],(ld)(a[x]/(d[y]+1))/a[x]*f[x-1][y]);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=k-1;++i)
    {
        int j=(k-1)/((k-1)/i);
        d[++q]=(k-1)/i;
        i=j;
    }
    d[++q]=0;
    for(int i=1;i<=q;++i) h[d[i]]=i;
    f[0][1]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=q;++j)
        {
            if(f[i-1][j]) solve(i,j);
        }
    }
    printf("%.9Lf",f[n][q]*k);
    return 0;
}