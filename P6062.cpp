#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1001;
int m,n,q1,q2,p=1,t[N*N],c1[N][N],c2[N][N],g[N*N];
bool h[N*N];
char b[N][N];
vector<int> a[N*N];
bool dfs(int x)
{
    for(auto i:a[x])
    {
        if(h[i]) continue;
        h[i]=true;
        if(g[i]==0||dfs(g[i]))
        {
            g[i]=x;
            return true;
        }
    }
    return false;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",b[i]+1);
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(b[i][j]!='*') continue;
            if(b[i-1][j]=='*') c1[i][j]=c1[i-1][j];
            else c1[i][j]=++q1;
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(b[i][j]!='*') continue;
            if(b[i][j-1]=='*') c2[i][j]=c2[i][j-1];
            else c2[i][j]=++q2;
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j) a[c1[i][j]].push_back(c2[i][j]);
    }
    int s=0;
    for(int i=1;i<=q1;++i)
    {
        for(int j=1;j<=q2;++j) h[j]=false;
        s+=dfs(i);
    }
    printf("%d",s);
    return 0;
}