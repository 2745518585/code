#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=1000001;
int n,m,q,d[N];
bool h[N];
vector<pair<int,int>> a[N];
vector<int> b[N],p1[N],p2[N];
void dfs(int x)
{
    while(!a[x].empty())
    {
        auto i=a[x].back();
        a[x].pop_back();
        if(h[i.second]) continue;
        h[i.second]=true;
        if(x>q) p1[x-q].push_back(i.first);
        else if(i.first>q) p2[i.first-q].push_back(x);
        dfs(i.first);
    }
}
void solve(int l,int r)
{
    if(l==r) return;
    int z=l+r>>1;
    for(int i=1;i<=n;++i)
    {
        a[q+i].clear();
        for(int j=l;j<=r;++j)
        {
            a[b[i][j]].clear();
            d[b[i][j]]=0;
        }
    }
    int p=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=l;j<=r;++j)
        {
            ++p;
            a[q+i].push_back(make_pair(b[i][j],p));
            a[b[i][j]].push_back(make_pair(q+i,p));
            ++d[b[i][j]];
        }
    }
    int x=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=l;j<=r;++j)
        {
            if(d[b[i][j]]%2==1)
            {
                ++d[b[i][j]];
                if(x==0) x=b[i][j];
                else
                {
                    ++p;
                    a[b[i][j]].push_back(make_pair(x,p));
                    a[x].push_back(make_pair(b[i][j],p));
                    x=0;
                }
            }
        }
    }
    for(int i=1;i<=p;++i) h[i]=false;
    for(int i=1;i<=n;++i) p1[i].clear(),p2[i].clear();
    for(int i=1;i<=n;++i)
    {
        dfs(q+i);
        for(int j=l;j<=r;++j) dfs(b[i][j]);
    }
    for(int i=1;i<=n;++i)
    {
        int p=l-1;
        for(auto j:p1[i]) b[i][++p]=j;
        for(auto j:p2[i]) b[i][++p]=j;
    }
    solve(l,z);
    solve(z+1,r);
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
    {
        b[i].resize(m+10);
        for(int j=1;j<=m;++j)
        {
            scanf("%d",&b[i][j]);
        }
    }
    solve(1,m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j) printf("%d ",b[i][j]);
        printf("\n");
    }
    return 0;
}