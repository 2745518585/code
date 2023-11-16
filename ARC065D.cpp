#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=1e9+7;
int n,m,b[N][2],a1[N],a2[N];
ll f[N][N];
char a[N];
int main()
{
    scanf("%d%d%s",&n,&m,a+1);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&b[i][0],&b[i][1]);
    }
    for(int i=1;i<=n;++i) a1[i]=a[i]-'0';
    for(int i=1;i<=m;++i)
    {
        int x=b[i][0],y=b[i][1],w=0;
        for(int j=x;j<=y;++j) w+=(a1[j]==0);
        for(int j=x;j<=x+w-1;++j) a1[j]=0;
        for(int j=x+w;j<=y;++j) a1[j]=1;
    }
    for(int i=1;i<=n;++i) a1[i]+=a1[i-1];
    for(int i=1;i<=n;++i) a2[i]=a[i]-'0';
    for(int i=1;i<=m;++i)
    {
        int x=b[i][0],y=b[i][1],w=0;
        for(int j=x;j<=y;++j) w+=(a2[j]==0);
        for(int j=y;j>=y-w+1;--j) a2[j]=0;
        for(int j=y-w;j>=x;--j) a2[j]=1;
    }
    for(int i=1;i<=n;++i) a2[i]+=a2[i-1];
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=a1[i];j<=a2[i];++j)
        {
            f[i][j]=f[i-1][j];
            if(j>0) f[i][j]=(f[i][j]+f[i-1][j-1])%P;
        }
    }
    printf("%lld",f[n][a1[n]]);
    return 0;
}