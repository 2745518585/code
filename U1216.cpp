#include<bits/stdc++.h>
using namespace std;
const int N=1001;
int m,n,d,t,q,s,a[N][N],b[N],f[N][N],g[N][N],h[N];
int main()
{
    scanf("%d%d%d%d",&m,&n,&d,&t);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=2;i<=n;++i)
    {
        for(int j=0;j<=t;++j) f[i][j]=-1e9;
    }
    for(int i=1;i<=min(d+1,m);++i)
    {
        for(int j=1;j<=min(d+1,n);++j)
        {
            for(int k=t;k>=1;--k) f[1][k]=max(f[1][k],f[1][k-1]+a[i][j]);
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i+j-2>t) continue;
            if(i>1&&i+d<=m)
            {
                for(int k=0;k<=t;++k) h[k]=-1e9;
                for(int k=i+j-2;k<=t;++k)
                {
                    h[k]=max(h[k],g[j][k-1]);
                }
                for(int k=max(j-d,1);k<=min(j+d,n);++k)
                {
                    for(int l=t;l>=i+j-2;--l)
                    {
                        h[l]=max(h[l],h[l-1]+a[i+d][k]);
                    }
                }
                for(int k=0;k<=t;++k) f[j][k]=max(f[j][k],h[k]);
            }
            if(j>1&&j+d<=n)
            {
                for(int k=0;k<=t;++k) h[k]=-1e9;
                for(int k=i+j-2;k<=t;++k)
                {
                    h[k]=max(h[k],f[j-1][k-1]);
                }
                for(int k=max(i-d,1);k<=min(i+d,m);++k)
                {
                    for(int l=t;l>=i+j-2;--l)
                    {
                        h[l]=max(h[l],h[l-1]+a[k][j+d]);
                    }
                }
                for(int k=0;k<=t;++k) f[j][k]=max(f[j][k],h[k]);
            }
            s=max(s,f[j][t]);
        }
        for(int j=1;j<=n;++j)
        {
            for(int k=0;k<=t;++k) g[j][k]=f[j][k],f[j][k]=-1e9;
        }
    }
    printf("%d",s);
    return 0;
}