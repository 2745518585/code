#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,q,b[N],f[N];
bool g[N],h[N];
vector<pair<int,int>> d[N];
struct str
{
    int l,r;
}a[N];
void dfs(int x)
{
    for(auto i:d[x])
    {
        if(g[i.second]) continue;
        g[i.second]=true;
        h[i.second]=x<i.first;
        dfs(i.first);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].l,&a[i].r);
        ++a[i].r;
        b[++q]=a[i].l;
        b[++q]=a[i].r;
    }
    sort(b+1,b+q+1);
    q=unique(b+1,b+q+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i].l=lower_bound(b+1,b+q+1,a[i].l)-b;
        a[i].r=lower_bound(b+1,b+q+1,a[i].r)-b;
        ++f[a[i].l],--f[a[i].r];
    }
    for(int i=1;i<=q;++i) f[i]+=f[i-1];
    for(int i=1;i<=q-1;++i)
    {
        if(f[i]%2==1)
        {
            d[i].push_back(make_pair(i+1,n+i));
            d[i+1].push_back(make_pair(i,n+i));
        }
    }
    for(int i=1;i<=n;++i)
    {
        d[a[i].l].push_back(make_pair(a[i].r,i));
        d[a[i].r].push_back(make_pair(a[i].l,i));
    }
    for(int i=1;i<=q;++i) dfs(i);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",h[i]);
    }
    return 0;
}