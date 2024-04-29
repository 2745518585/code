#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=5001;
int n,m,a0[N],a1[N],a2[N],f[N][N],g[N][N];
char a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        {
            a0[0]=a1[0]=a2[0]=0;
            static char z[N];
            scanf("%s",z+1);
            for(int i=1;i<=m;++i)
            {
                if(z[i]=='W') ++a0[0];
                else if(z[i]=='Q') ++a1[0];
                else if(z[i]=='B') ++a2[0];
            }
            --m;
        }
        scanf("%s",a+1);
        for(int i=1;i<=n;++i)
        {
            a0[i]=a0[i-1],a1[i]=a1[i-1],a2[i]=a2[i-1];
            if(a[i]=='W') ++a0[i];
            else if(a[i]=='Q') ++a1[i];
            else if(a[i]=='B') ++a2[i];
        }
        for(int i=0;i<=n+2;++i)
        {
            for(int j=0;j<=a2[n]+1;++j) f[i][j]=-1e9;
        }
        f[0][a2[0]]=a1[0];
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<=a2[n];++j)
            {
                if(f[i-1][j-(a[i]=='B')]>0) f[i][j]=max(f[i][j],f[i-1][j-(a[i]=='B')]-1+(a[i]=='Q'));
                if(i>1&&j-(a[i-1]=='B')-(a[i]=='B')+1>0) f[i][j]=max(f[i][j],f[i-2][j-(a[i-1]=='B')-(a[i]=='B')+1]+(a[i-1]=='Q')+(a[i]=='Q'));
            }
        }
        for(int i=0;i<=n+1;++i)
        {
            for(int j=a2[n]-1;j>=0;--j) f[i][j]=max(f[i][j],f[i][j+1]);
        }
        for(int i=0;i<=n+2;++i)
        {
            for(int j=0;j<=a2[n]+1;++j) g[i][j]=1e9;
        }
        for(int i=0;i<=a2[n];++i) g[n+1][i]=g[n+2][i]=0;
        for(int i=n;i>=1;--i)
        {
            for(int j=0;j<=a2[n];++j)
            {
                g[i][j]=min(g[i][j],max(g[i+1][j+(a[i]=='B')]-(a[i]=='Q'),0)+1);
                if(j>0) g[i][j]=min(g[i][j],g[i+2][j-1+(a[i]=='B')]-(a[i]=='Q'));
            }
        }
        for(int i=0;i<=n+1;++i)
        {
            for(int j=1;j<=a2[n];++j) g[i][j]=min(g[i][j],g[i][j-1]);
        }
        int s=1e9;
        for(int i=0;i<=n;++i)
        {
            for(int j=m;j<=m+n;++j)
            {
                int w1=a1[i]-(i-(j-m)*2),w2=a2[i]-(j-m);
                if(w2>=0&&w2<=a2[n]&&f[i][w2]>=w1&&g[i+1][w2]<=w1) s=min(s,j);
            }
        }
        if(s==1e9) printf("IMPOSSIBLE\n");
        else printf("%d\n",s+1);
    }
    return 0;
}