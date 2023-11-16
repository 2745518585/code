#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char c[101];
int n,f[101][101];
int main()
{
    scanf("%s",c+1);
    n=strlen(c+1);
    for(int i=1;i<=n;++i)
    {
    	for(int j=1;j<=n;++j)
    	{
    		f[i][j]=1e9;
    	}
    }
    for(int i=1;i<=n;++i)
    {
        f[i][i]=1;
    }
    for(int l=2;l<=n;++l)
    {
        for(int i=1,j=l;j<=n;++i,++j)
        {
            if(c[i]==c[j])
            {
                f[i][j]=min(f[i][j-1],f[i+1][j]);
                continue;
            }
            for(int k=i;k<j;++k)
            {
                f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
            }
        }
    }
    printf("%d",f[1][n]);
    return 0;
}