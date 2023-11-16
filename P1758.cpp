#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001;
const ll P=1024523;
int m,n;
ll f[N][N],g[N][N];
char a[N],b[N];
bool check1(int x)
{
    return x>=1&&x<=m;
}
bool check2(int x)
{
    return x>=1&&x<=n;
}
int main()
{
    scanf("%d%d%s%s",&m,&n,a+1,b+1);
    for(int i=1;i<=m/2;++i) swap(a[i],a[m-i+1]);
    for(int i=1;i<=n/2;++i) swap(b[i],b[n-i+1]);
    f[0][0]=1;
    for(int i=1;i<=m+n;++i)
    {
        for(int j=0;j<=m;++j)
        {
            for(int k=0;k<=m;++k) g[j][k]=f[j][k]%P,f[j][k]=0;
        }
        for(int j=0;j<=m;++j)
        {
            for(int k=0;k<=m;++k)
            {
                if(g[j][k]==0) continue;
                if(check1(j+1)&&check1(k+1)&&a[j+1]==a[k+1]) f[j+1][k+1]+=g[j][k];
                if(check1(j+1)&&check2(i-k)&&a[j+1]==b[i-k]) f[j+1][k]+=g[j][k];
                if(check2(i-j)&&check1(k+1)&&b[i-j]==a[k+1]) f[j][k+1]+=g[j][k];
                if(check2(i-j)&&check2(i-k)&&b[i-j]==b[i-k]) f[j][k]+=g[j][k];
            }
        }
    }
    printf("%lld",(f[m][m]%P+P)%P);
    return 0;
}