#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=500001,M=31;
int m,n,f[N][M],g[M];
char a[N],b[N];
int main()
{
    scanf("%s%s",a+1,b+1);
    m=strlen(a+1),n=strlen(b+1);
    for(int i=1;i<=m;++i)
    {
        for(int j=0;j<=25;++j) f[i][j]=f[i-1][j];
        if(a[i]!='?') ++f[i][a[i]-'a'];
    }
    for(int i=1;i<=n;++i) ++g[b[i]-'a'];
    int s=0;
    for(int i=0;i<=m-n;++i)
    {
        bool u=true;
        for(int j=0;j<=25;++j)
        {
            if(f[i+n][j]-f[i][j]>g[j])
            {
                u=false;
                break;
            }
        }
        if(u) ++s;
    }
    printf("%d",s);
    return 0;
}