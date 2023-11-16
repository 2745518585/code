#include<bits/stdc++.h>
using namespace std;
const int N=5001;
int n,m,k,a[N],f[N][N],g[N][N];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int t=j%n+1,l=max(i-k,1);
            if(a[j]==a[t])
            {
                if(g[t][i-1]-g[t][l-1]==0) f[j][i]=0;
                else f[j][i]=1;
            }
            else
            {
                if(g[t][i-1]-g[t][l-1]!=i-l) f[j][i]=1;
                else f[j][i]=0;
            }
            g[j][i]=g[j][i-1]+f[j][i];
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d ",!(f[i][m]^a[i]));
    }
    return 0;
}