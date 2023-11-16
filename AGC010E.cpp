#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=3001;
int n,a[N],l[N];
bool g[N],h[N][N];
vector<int> b[N];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void dfs(int x)
{
    g[x]=true;
    for(int i=1;i<=n;++i)
    {
        if(g[i]||!h[x][i]) continue;
        dfs(i);
        b[x].push_back(i);
        ++l[i];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            h[i][j]=gcd(a[i],a[j])!=1;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(!g[i]) dfs(i);
    }
    priority_queue<int> Q;
    for(int i=1;i<=n;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.top();
        Q.pop();
        printf("%d ",a[k]);
        for(auto i:b[k])
        {
            --l[i];
            if(l[i]==0) Q.push(i);
        }
    }
    printf("\n");
    return 0;
}