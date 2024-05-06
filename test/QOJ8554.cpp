#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=6001;
int n,f[N][N],g[N][N];
char a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a+1);
        n=strlen(a+1);
        for(int i=0;i<=n;++i)
        {
            for(int j=0;j<=n;++j) f[i][j]=g[i][j]=-1e9;
        }
        f[0][0]=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<=n;++j)
            {
                if(a[i]!='<')
                {
                    f[i][j+1]=max(f[i][j+1],max(f[i-1][j],g[i-1][j]));
                }
                if(a[i]!='>')
                {
                    if(j>0)
                    {
                        g[i][j]=max(g[i][j],f[i-1][j]);
                        g[i][j-1]=max(g[i][j-1],f[i-1][j]+1);
                        if(j>1) g[i][j-2]=max(g[i][j-2],f[i-1][j]+2);
                        g[i][j-1]=max(g[i][j-1],g[i-1][j]+2);
                    }
                    else
                    {
                        f[i][0]=max(f[i][0],max(f[i-1][0],g[i-1][0]));
                    }
                }
            }
        }
        int s=0;
        for(int i=0;i<=n;++i) s=max(s,max(f[n][i],g[n][i]));
        printf("%d\n",s);
    }
    return 0;
}