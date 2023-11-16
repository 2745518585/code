#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,q,l[N],b[N];
vector<int> a[N];
void dfs(int x,int fa)
{
    if(q>=n) return;
    b[++q]=x;
    int u=0;
    for(auto i:a[x])
    {
        if(l[i]>=2&&i!=fa) u=i;
    }
    if(u==0)
    {
        for(auto i:a[x])
        {
            if(l[i]<=1) b[++q]=i;
        }
        dfs(fa,x);
        return;
    }
    for(auto i:a[u])
    {
        if(l[i]<=1) b[++q]=i;
    }
    int v=0;
    for(auto i:a[u])
    {
        if(l[i]>=2&&i!=x) v=i;
    }
    if(v==0) dfs(u,0);
    else dfs(v,u);
}
int main()
{
    scanf("%d",&n);
    if(n<=2)
    {
        printf("Yes\n1 2");
        return 0;
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
        ++l[x],++l[y];
    }
    int x=0;
    for(int i=1;i<=n;++i)
    {
        int u=0;
        for(auto j:a[i]) if(l[j]>=2) ++u;
        if(u>=3)
        {
            printf("No\n");
            return 0;
        }
        if(l[i]>=2&&u<=1) x=i;
    }
    dfs(x,0);
    printf("Yes\n");
    for(int i=1;i<=q;++i)
    {
        printf("%d ",b[i]);
    }
    return 0;
}