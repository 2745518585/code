#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
int n,q,a[N],b[N],f[N][4],g[N][4];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            b[i]=a[i];
        }
        sort(b+1,b+n+1);
        q=unique(b+1,b+n+1)-b-1;
        for(int i=1;i<=n;++i)
        {
            a[i]=lower_bound(b+1,b+q+1,a[i])-b;
        }
        for(int i=1;i<=n;++i)
        {
            if(a[i]==a[g[i-1][3]])
            {
                g[i][0]=g[i-1][0];
                g[i][1]=g[i-1][1];
                g[i][2]=g[i-1][2];
                g[i][3]=i;
            }
            else if(a[i]==a[g[i-1][2]])
            {
                g[i][0]=g[i-1][0];
                g[i][1]=g[i-1][1];
                g[i][2]=g[i-1][3];
                g[i][3]=i;
            }
            else if(a[i]==a[g[i-1][1]])
            {
                g[i][0]=g[i-1][0];
                g[i][1]=g[i-1][2];
                g[i][2]=g[i-1][3];
                g[i][3]=i;
            }
            else
            {
                g[i][0]=g[i-1][1];
                g[i][1]=g[i-1][2];
                g[i][2]=g[i-1][3];
                g[i][3]=i;
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<=2;++j) f[i][j]=0;
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<=2;++j)
            {
                for(int k=0;k<=2;++k)
                {
                    if(a[g[g[i][j]][k]]!=a[i]) f[i][j]=max(f[i][j],f[g[i][j]][k]+1);
                }
            }
        }
        int s=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<=2;++j) s=max(s,f[i][j]);
        }
        printf("%d\n",s);
    }
    return 0;
}