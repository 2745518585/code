#include<bits/stdc++.h>
using namespace std;
const int N=2001;
int n,m,k,q,C[N<<1][N<<1],a[N<<1][N<<1];
int main()
{
    scanf("%d%d",&q,&k);
    C[0][0]=1;
    for(int i=1;i<=N;++i)
    {
        C[i][0]=C[i-1][0];
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%k;
            a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1]+(C[i][j]==0);
        }
        for(int j=i+1;j<=N;++j)
        {
            a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
        }
    }
    for(int i=1;i<=q;++i)
    {
        scanf("%d%d",&n,&m);
        printf("%d\n",a[n][m]);
    }
    return 0;
}