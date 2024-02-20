#include<cstdio>
#include<algorithm>
using namespace std;
typedef long double ld;
const int N=1001;
int n,f[N];
char a[N][N];
bool h[N];
void dfs(int x)
{
    h[x]=true;
    for(int i=1;i<=n;++i)
    {
        if(a[i][x]=='1'&&!h[i]) dfs(i);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",a[i]+1);
    }
    ld s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) h[j]=false;
        dfs(i);
        int w=0;
        for(int j=1;j<=n;++j) w+=h[j];
        s+=(ld)1/w;
    }
    printf("%.18Lf",s);
    return 0;
}