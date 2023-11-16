#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[101],f[101][101],g[101][101];
void print(int l,int r)
{
    if(l>r) return;
    if(l==r)
    {
        printf("%d ",l);
        return;
    }
    printf("%d ",g[l][r]);
    print(l,g[l][r]-1);
    print(g[l][r]+1,r);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        f[i][i]=a[i];
    }
    for(int i=2;i<=n;++i)
    {
        for(int j=1;j<=n-i+1;++j)
        {
            int l=j,r=i+j-1;
            if(f[l+1][r]+a[l]>f[l][r])
            {
                f[l][r]=f[l+1][r]+a[l];
                g[l][r]=l;
            }
            else if(f[l][r-1]+a[r]>f[l][r])
            {
                f[l][r]=f[l][r-1]+a[r];
                g[l][r]=r;
            }
            for(int k=l+1;k<=r-1;++k)
            {
                if(f[l][k-1]*f[k+1][r]+a[k]>f[l][r])
                {
                    f[l][r]=f[l][k-1]*f[k+1][r]+a[k];
                    g[l][r]=k;
                }
            }
        }
    }
    printf("%d\n",f[1][n]);
    print(1,n);
    return 0;
}