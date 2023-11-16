#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=501;
bool begin;
struct num
{
    ll a[6];
    friend bool operator <(num a,num b)
    {
        if(a.a[0]!=b.a[0]) return a.a[0]<b.a[0];
        if(a.a[1]!=b.a[1]) return a.a[1]<b.a[1];
        if(a.a[2]!=b.a[2]) return a.a[2]<b.a[2];
        if(a.a[3]!=b.a[3]) return a.a[3]<b.a[3];
        if(a.a[4]!=b.a[4]) return a.a[4]<b.a[4];
        return a.a[5]>b.a[5];
    }
}f2[N][N],g2[N][N];
int m,n,f[N][N],g[N][N];
char a[N][N];
bool end;
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
    }
    for(int i=0;i<=n+1;++i)
    {
        for(int j=0;j<=m;++j)
        {
            f[i][j]=-1e9;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(a[m][i]=='M') f[i][0]=0;
    }
    int s=-1e9;
    num q;
    for(int i=m-1;i>=1;--i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=0;k<=m;++k)
            {
                if(a[i+1][j]!='*') g[j][k]=f[j][k],g2[j][k]=f2[j][k];
                else g[j][k]=-1e9;
            }
        }
        for(int j=0;j<=m;++j) g[0][j]=g[n+1][j]=-1e9;
        for(int j=1;j<=n;++j)
        {
            if(a[i][j]=='(')
            {
                for(int k=1;k<=m;++k)
                {
                    f[j][k]=g[j][k-1];
                    f2[j][k]=g2[j][k-1];
                    if(g[j-1][k-1]>f[j][k]||(g[j-1][k-1]==f[j][k]&&g2[j-1][k-1]<f2[j][k]))
                    {
                        f[j][k]=g[j-1][k-1];
                        f2[j][k]=g2[j-1][k-1];
                    }
                    if(g[j+1][k-1]>f[j][k]||(g[j+1][k-1]==f[j][k]&&g2[j+1][k-1]<f2[j][k]))
                    {
                        f[j][k]=g[j+1][k-1];
                        f2[j][k]=g2[j+1][k-1];
                    }
                    ++f[j][k];
                }
            }
            else if(a[i][j]==')')
            {
                for(int k=0;k<=m-1;++k)
                {
                    f[j][k]=g[j][k+1];
                    f2[j][k]=g2[j][k+1];
                    if(g[j-1][k+1]>f[j][k]||(g[j-1][k+1]==f[j][k]&&g2[j-1][k+1]<f2[j][k]))
                    {
                        f[j][k]=g[j-1][k+1];
                        f2[j][k]=g2[j-1][k+1];
                    }
                    if(g[j+1][k+1]>f[j][k]||(g[j+1][k+1]==f[j][k]&&g2[j+1][k+1]<f2[j][k]))
                    {
                        f[j][k]=g[j+1][k+1];
                        f2[j][k]=g2[j+1][k+1];
                    }
                    ++f[j][k];
                    if(f[j][k]>=0) f2[j][k].a[f[j][k]/60]|=(1ll<<(59-f[j][k]%60));
                }
            }
            else
            {
                for(int k=0;k<=m;++k)
                {
                    f[j][k]=g[j][k];
                    f2[j][k]=g2[j][k];
                    if(g[j-1][k]>f[j][k]||(g[j-1][k]==f[j][k]&&g2[j-1][k]<f2[j][k]))
                    {
                        f[j][k]=g[j-1][k];
                        f2[j][k]=g2[j-1][k];
                    }
                    if(g[j+1][k]>f[j][k]||(g[j+1][k]==f[j][k]&&g2[j+1][k]<f2[j][k]))
                    {
                        f[j][k]=g[j+1][k];
                        f2[j][k]=g2[j+1][k];
                    }
                }
            }
            if(a[i][j]=='*'&&(f[j][0]>s||(f[j][0]==s&&f2[j][0]<q)))
            {
                s=f[j][0];
                q=f2[j][0];
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(f[i][0]>s||(f[i][0]==s&&f2[i][0]<q))
        {
            s=f[i][0];
            q=f2[i][0];
        }
    }
    printf("%d\n",s);
    for(int i=1;i<=s;++i)
    {
        if((q.a[i/60]&(1ll<<(59-i%60)))==0) printf("(");
        else printf(")");
    }
    return 0;
}