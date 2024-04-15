#include<cstdio>
#include<algorithm>
#include<vector>
#include<bitset>
using namespace std;
const int N=6001;
int n,g[N];
bitset<N> a[N],h;
struct str
{
    int l,r;
}b[N];
bool dfs(int x)
{
    bitset<N> z=a[x]&h;
    for(int i=z._Find_first();i<=n;i=z._Find_next(i))
    {
        if(h[i]==0) continue;
        h[i]=0;
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
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&b[i].l,&b[i].r);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(b[i].l<b[j].l&&b[j].l<b[i].r&&b[i].r<b[j].r) a[i][j]=1;
        }
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) h[j]=1;
        if(dfs(i)) ++s;
    }
    printf("%d",n*2-s);
    return 0;
}