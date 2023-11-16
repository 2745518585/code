#include<bits/stdc++.h>
using namespace std;
const int N=5;
int n,b[N],c[N],f[N],g[N][N*N][N],s=1e9;
bool h[N*N];
struct str
{
    int a[N][N];
}a[N][N];
int sum(int x,int y,int x2,int y2,int t)
{
    if(t==0) return a[x][y].a[x2][y2];
    if(t==1) return a[x][y].a[y2][n-x2+1];
    if(t==2) return a[x][y].a[n-x2+1][n-y2+1];
    return a[x][y].a[n-y2+1][x2];
}
bool check1(int x)
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n*n;++j) h[j]=false;
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=n;++k)
            {
                if(h[sum(x,j,i,k,b[j])]==true) return false;
                h[sum(x,j,i,k,b[j])]=true;
            }
        }
    }
    return true;
}
bool check2()
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=n*n;++k) h[k]=false;
            for(int k=1;k<=n;++k)
            {
                for(int l=1;l<=n;++l)
                {
                    if(h[sum(i,k,j,l,g[i][b[i]][k])]==true) return false;
                    h[sum(i,k,j,l,g[i][b[i]][k])]=true;
                }
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=n*n;++k) h[k]=false;
            for(int k=1;k<=n;++k)
            {
                for(int l=1;l<=n;++l)
                {
                    if(h[sum(k,i,l,j,g[k][b[k]][i])]==true) return false;
                    h[sum(k,i,l,j,g[k][b[k]][i])]=true;
                }
            }
        }
    }
    return true;
}
int num()
{
    int s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            s+=g[i][b[i]][j];
        }
    }
    return s;
}
void dfs1(int x,int y)
{
    if(y==n+1)
    {
        if(check1(x))
        {
            ++f[x];
            for(int i=1;i<=n;++i) g[x][f[x]][i]=b[i];
        }
        return;
    }
    for(int i=0;i<4;++i)
    {
        b[y]=i;
        dfs1(x,y+1);
    }
}
void dfs2(int x)
{
    if(x==n+1)
    {
        if(check2())
        {
            int z=num();
            if(z<s)
            {
                s=z;
                for(int i=1;i<=n;++i) c[i]=b[i];
            }
        }
        return;
    }
    for(int i=1;i<=f[x];++i)
    {
        b[x]=i;
        dfs2(x+1);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n*n;++i)
    {
        char c[N*N];
        scanf("%s",c+1);
        for(int j=1;j<=n*n;++j)
        {
            if(c[j]<='9') a[(i-1)/n+1][(j-1)/n+1].a[(i-1)%n+1][(j-1)%n+1]=c[j]-'0'+1;
            else a[(i-1)/n+1][(j-1)/n+1].a[(i-1)%n+1][(j-1)%n+1]=c[j]-'A'+11;
        }
    }
    for(int i=1;i<=n;++i) dfs1(i,1);
    dfs2(1);
    if(s==1e9)
    {
        printf("-1");
        return 0;
    }
    printf("%d\n",s);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=g[i][c[i]][j];++k)
            {
                printf("%d %d\n",i,j);
            }
        }
    }
    return 0;
}