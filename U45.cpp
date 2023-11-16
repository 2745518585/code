#include<bits/stdc++.h>
using namespace std;
const int N=3001;
int n,m,f[N][N][2][2];
char a[N],b[N];
int main()
{
    scanf("%s%s",a+1,b+1);
    m=strlen(a+1),n=strlen(b+1);
    int s=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k1=0;k1<=1;++k1)
            {
                for(int k2=0;k2<=1;++k2)
                {
                    f[i][j][k1][k2]=-1e9;
                    for(int l1=0;l1<=1;++l1)
                    {
                        for(int l2=0;l2<=1;++l2)
                        {
                            f[i][j][k1][k2]=max(f[i][j][k1][k2],f[i-k1][j-k2][l1][l2]+(k1&&k2&&a[i]==b[j])*2-(!k1&&l1)-(!k2&&l2));
                        }
                    }
                    // printf("%d %d %d %d %d\n",i,j,k1,k2,f[i][j][k1][k2]);
                    if(i==m&&j==n)
                    {
                        s=max(s,f[i][j][k1][k2]);
                    }
                }
            }
        }
    }
    printf("%d",s);
    return 0;
}