#include<bits/stdc++.h>
using namespace std;
const int N=1001,M=101;
int n,m,p,a[N][3],f[N][M][6];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][1]=y-x;
        p+=y;
    }
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][2]=y-x;
        p+=y;
    }
    for(int i=0;i<=m;++i)
    {
        f[0][i][1]=0;
        f[0][i][2]=f[0][i][3]=f[0][i][4]=f[0][i][5]=-1e9;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=m;++j)
        {
            for(int k=1;k<=5;++k)
            {
                f[i][j][k]=-1e9;
                for(int l=1;l<=5;++l)
                {
                    if(k==1) f[i][j][k]=max(f[i][j][k],f[i-1][j][l]);
                    else if(k==2)
                    {
                        if(l==2||l==4) f[i][j][k]=max(f[i][j][k],f[i-1][j][l]+a[i][1]);
                        else if(j>=1) f[i][j][k]=max(f[i][j][k],f[i-1][j-1][l]+a[i][1]);
                    }
                    else if(k==3)
                    {
                        if(l==3||l==4) f[i][j][k]=max(f[i][j][k],f[i-1][j][l]+a[i][2]);
                        else if(j>=1) f[i][j][k]=max(f[i][j][k],f[i-1][j-1][l]+a[i][2]);
                    }
                    else if(k==4)
                    {
                        if(l==4) f[i][j][k]=max(f[i][j][k],f[i-1][j][l]+a[i][1]+a[i][2]);
                        else if((l==2||l==3)&&j>=1) f[i][j][k]=max(f[i][j][k],f[i-1][j-1][l]+a[i][1]+a[i][2]);
                        else if(j>=2) f[i][j][k]=max(f[i][j][k],f[i-1][j-2][l]+a[i][1]+a[i][2]);
                    }
                    else if(k==5)
                    {
                        if(l==5) f[i][j][k]=max(f[i][j][k],f[i-1][j][l]+a[i][1]+a[i][2]);
                        else if(j>=1) f[i][j][k]=max(f[i][j][k],f[i-1][j-1][l]+a[i][1]+a[i][2]);
                    }
                }
            }
        }
    }
    int s=-1e9;
    for(int i=0;i<=m;++i)
    {
        for(int j=1;j<=5;++j)
        {
            s=max(s,f[n][i][j]);
        }
    }
    printf("%d",p-s);
    return 0;
}