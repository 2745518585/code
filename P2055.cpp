#include<cstdio>
using namespace std;
int n,g[1001];
bool h[1001],h1[1001],h2[1001],a[1001][1001];
bool dfs(int x)
{
    for(int i=1;i<=n;++i)
    {
        if(a[x][i]==true&&h[i]==false&&h1[i]==true)
        {
            h[i]=true;
            if(g[i]==0||dfs(g[i]))
            {
                g[i]=x;
                return true;
            }
        }
    }
    return false;
}
void abc()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&h1[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&h2[i]);
        if(h1[i]==false) h2[i]=false;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
        }
        if(h1[i]==true) a[i][i]=true;
    }
    for(int i=1;i<=n;++i) g[i]=0;
    for(int i=1;i<=n;++i)
    {
        if(h1[i]==true&&h2[i]==true) continue;
        for(int j=1;j<=n;++j) h[j]=false;
        if(dfs(i)==false)
        {
            printf("T_T\n");
            return;
        }
    }
    printf("^_^\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        abc();
    }
    return 0;
}