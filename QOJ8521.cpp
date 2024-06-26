#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001,M=31;
int n,s=1e9,f1[M][N],f2[M][N],g1[M][N],g2[M][N],l[N];
char a[N];
void solve(int x)
{
    for(int i=1;i<=n;++i)
    {
        f1[x][i]=f1[x-2][f1[x-1][i]];
        if(f1[x][i]==n+1) g1[x][i]=g1[x-1][i]+g1[x-2][f1[x-1][i]];
    }
    for(int i=1;i<=n;++i)
    {
        f2[x][i]=f2[x-1][f2[x-2][i]];
        if(f2[x][i]==0) g2[x][i]=g2[x-1][f2[x-2][i]]+g2[x-2][i];
    }
    for(int i=1;i<=n-1;++i)
    {
        if(f2[x-1][i]==0&&f1[x-2][i+1]==n+1) s=min(s,g2[x-1][i]+g1[x-2][i+1]);
    }
}
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    if(n==1)
    {
        printf("1");
        return 0;
    }
    for(int i=1;i<=n;++i)
    {
        int z=a[i]-'a';
        f1[z^1][i]=i+1,f2[z^1][i]=i-1;
        f1[z][i]=f2[z][i]=i;
    }
    l[0]=l[1]=1;
    for(int i=2;i<=n;++i) l[i]=l[i-1]+l[i-2];
    for(int i=0;i<=30;++i)
    {
        for(int j=0;j<=n+1;++j) g1[i][j]=g2[i][j]=l[i];
        f1[i][n+1]=n+1,f2[i][0]=0;
        g1[i][n+1]=g2[i][0]=0;
    }
    for(int i=2;i<=30;++i) solve(i);
    printf("%d\n",s);
    return 0;
}