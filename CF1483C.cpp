#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],S[N],Top;
ll b[N],f[N][2][2];
struct tree
{
    int l,r;
}T[N];
void dfs(int x)
{
    if(x==0) return;
    dfs(T[x].l);
    dfs(T[x].r);
    f[x][0][0]=0;
    f[x][0][1]=f[x][1][0]=f[x][1][1]=-1e18;
    for(int i=0;i<=1;++i)
    {
        for(int j=0;j<=1;++j)
        {
            f[x][i][0]=max(f[x][i][0],f[T[x].l][i][j]);
        }
    }
    for(int i=0;i<=1;++i)
    {
        for(int j=0;j<=1;++j)
        {
            f[x][0][j]=max(f[x][0][j],f[T[x].r][i][j]);
        }
    }
    for(int i1=0;i1<=1;++i1)
    {
        for(int j1=0;j1<=1;++j1)
        {
            for(int i2=0;i2<=1;++i2)
            {
                for(int j2=0;j2<=1;++j2)
                {
                    f[x][i1][j2]=max(f[x][i1][j2],b[x]+f[T[x].l][i1][j1]+f[T[x].r][i2][j2]);
                }
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        int z=Top;
        while(Top>0&&a[S[Top]]>a[i]) --Top;
        if(Top!=0) T[S[Top]].r=i;
        if(Top<z) T[i].l=S[Top+1];
        S[++Top]=i;
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    dfs(S[1]);
    printf("%lld",f[S[1]][1][1]);
    return 0;
}