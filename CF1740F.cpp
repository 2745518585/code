#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353;
int n,a[N],b[N];
ll f[N][N],g[N][N];
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++a[x];
    }
    sort(a+1,a+n+1,cmp);
    int q=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=a[i];++j) b[++q]=i;
    }
    f[0][n]=1;
    for(int i=0;i<=n;++i) g[0][i]=(g[0][i-1]+f[0][i])%P;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=i;++j)
        {
            f[i][j]=(f[i][j]+(g[i-j][n]-g[i-j][max(a[b[i-j+1]],j)-1]))%P;
        }
        for(int j=0;j<=n;++j) g[i][j]=(g[i][j-1]+f[i][j])%P;
    }
    printf("%lld",(g[n][n]%P+P)%P);
    return 0;
}