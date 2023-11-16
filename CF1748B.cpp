#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001,M=12;
int n,f[N][M],g[M],b[N][M];
char a[N];
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,a+1);
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<=9;++j) f[i][j]=f[i-1][j];
            ++f[i][a[i]-'0'];
            b[f[i][a[i]-'0']][a[i]-'0']=i;
            for(int j=0;j<=9;++j) g[j+1]=b[f[i][j]][j];
            sort(g+1,g+10+1,cmp);
            for(int j=1;j<=10;++j)
            {
                int x=0;
                for(int k=0;k<=9;++k)
                {
                    x=max(x,b[max(f[i][k]-j,0)][k]);
                }
                s+=max(g[j]-max(x+1,g[j+1]+1)+1,0);
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}