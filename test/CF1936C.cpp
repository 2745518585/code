#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],b[N],c[N];
ll f[N];
bool h[N];
vector<pair<int,int>> d[N];
inline int sum(int x,int y)
{
    return (x-1)*(m+1)+y+1;
}
void road(int x,int y,int w)
{
    d[x].push_back(make_pair(y,w));
    // printf("%d -> %d: %d\n",x,y,w);
}
struct str
{
    int x;
    ll s;
    str(){}
    str(int x,ll s):x(x),s(s){}
    friend bool operator<(const str &a,const str &b)
    {
        return a.s>b.s;
    }
};
void SPFA()
{
    priority_queue<str> Q;
    Q.push(str(1,0));
    for(int i=1;i<=sum(n,m);++i) f[i]=1e18,h[i]=false;
    f[1]=0;
    while(!Q.empty())
    {
        int k=Q.top().x;
        Q.pop();
        if(h[k]==true) continue;
        h[k]=true;
        for(auto i:d[k])
        {
            if(h[i.first]==false&&f[k]+i.second<f[i.first])
            {
                f[i.first]=f[k]+i.second;
                Q.push(str(i.first,f[i.first]));
            }
        }
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=sum(n,m);++i) d[i].clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&c[i]);
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&a[sum(i,j)]);
            }
        }
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j) b[j]=j;
            sort(b+1,b+n+1,[&](int x,int y)
            {
                return a[sum(x,i)]>a[sum(y,i)];
            });
            for(int j=1;j<=n;++j)
            {
                road(sum(j,i),sum(j,0),c[j]);
                road(sum(j,0),sum(j,i),0);
            }
            for(int j=1;j<=n-1;++j)
            {
                road(sum(b[j],i),sum(b[j+1],i),a[sum(b[j],i)]-a[sum(b[j+1],i)]);
                road(sum(b[j+1],i),sum(b[j],i),0);
            }
        }
        SPFA();
        printf("%lld\n",f[sum(n,0)]);
    }
    return 0;
}