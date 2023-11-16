#include<cstdio>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,r,g[N];
bool h[N];
struct str
{
    int x,y,r,t;
}a[N];
unordered_map<ll,vector<int>> Map;
ll mp(ll x,ll y)
{
    return ((x+1000000000)<<32)+(y+1000000000);
}
bool cmp(str a,str b)
{
    if(a.r!=b.r) return a.r>b.r;
    return a.t<b.t;
}
void build()
{
    Map.clear();
    r=0;
    for(int i=1;i<=n;++i)
    {
        if(!h[i]) r=max(r,a[i].r);
    }
    for(int i=1;i<=n;++i)
    {
        if(!h[i]) Map[mp(a[i].x/r,a[i].y/r)].push_back(i);
    }
}
bool check(str a,str b)
{
    return (ll)(a.x-b.x)*(a.x-b.x)+(ll)(a.y-b.y)*(a.y-b.y)<=(ll)(a.r+b.r)*(a.r+b.r);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].r);
        a[i].t=i;
    }
    sort(a+1,a+n+1,cmp);
    build();
    for(int i=1;i<=n;++i)
    {
        if(h[i]) continue;
        if(a[i].r*2<r) build();
        for(int j=a[i].x/r-2;j<=a[i].x/r+2;++j)
        {
            for(int k=a[i].y/r-2;k<=a[i].y/r+2;++k)
            {
                if(!Map.count(mp(j,k))) continue;
                auto p=Map[mp(j,k)];
                vector<int> q;
                for(auto l:p)
                {
                    if(h[l]) continue;
                    if(check(a[i],a[l])) g[a[l].t]=a[i].t,h[l]=true;
                    else q.push_back(l);
                }
                Map[mp(j,k)]=q;
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d ",g[i]);
    }
    return 0;
}