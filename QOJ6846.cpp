#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1001,M=1000001;
int n,m,a[N][N],a1[N],a2[N];
ll f[N*N*3],g[N*N*3],d[M];
vector<pair<int,ll>> b1[N*N*3],b2[N*N*3];
struct str
{
    int l1,r1,l2,r2,t;
};
inline int sum(int x,int y,int t)
{
    return (x-1)*(n+1)*3+(y-1)*3+t+1;
}
pair<int,int> num(int x)
{
    return make_pair((x-1)/((n+1)*3)+1,(x-1)/3%(n+1)+1);
}
void road(int x,int y,ll w)
{
    auto [x1,x2]=num(x);
    auto [y1,y2]=num(y);
    b1[x].push_back(make_pair(y,w));
    b2[y].push_back(make_pair(x,w));
}
void check(int x,int l1,int r1,int l2,int r2)
{
    for(int i=l1;i<=r1;++i)
    {
        for(int j=l2;j<=r2;++j)
        {
            f[sum(i,j,0)]=f[sum(i,j,1)]=f[sum(i,j,2)]=-1e18;
            g[sum(i,j,0)]=g[sum(i,j,1)]=g[sum(i,j,2)]=-1e18;
        }
    }
    f[x]=g[x]=0;
    auto [x1,x2]=num(x);
    for(int i=x1;i>=l1;--i)
    {
        for(int j=x2;j>=l2;--j)
        {
            for(int k=2;k>=0;--k)
            {
                int x=sum(i,j,k);
                for(auto l:b2[x]) f[l.first]=max(f[l.first],f[x]+l.second);
            }
        }
    }
    for(int i=x1;i<=r1;++i)
    {
        for(int j=x2;j<=r2;++j)
        {
            for(int k=0;k<=2;++k)
            {
                int x=sum(i,j,k);
                for(auto l:b1[x]) g[l.first]=max(g[l.first],g[x]+l.second);
            }
        }
    }
}
void solve(int l1,int r1,int l2,int r2,const vector<str> &x)
{
    if(l1>r1&&l2>r2) return;
    if(r1-l1>=r2-l2)
    {
        int z=l1+r1>>1;
        vector<str> p,p1,p2;
        for(auto i:x)
        {
            if(i.r1<z) p1.push_back(i);
            else if(i.l1>z) p2.push_back(i);
            else p.push_back(i);
        }
        for(int i=l2;i<=r2;++i)
        {
            check(sum(z,i,2),l1,r1,l2,r2);
            for(auto j:p)
            {
                d[j.t]=max(d[j.t],f[sum(j.l1,j.l2,0)]+g[sum(j.r1,j.r2,0)]);
            }
        }
        solve(l1,z-1,l2,r2,p1);
        solve(z+1,r1,l2,r2,p2);
    }
    else
    {
        int z=l2+r2>>1;
        vector<str> p,p1,p2;
        for(auto i:x)
        {
            if(i.r2<z) p1.push_back(i);
            else if(i.l2>z) p2.push_back(i);
            else p.push_back(i);
        }
        for(int i=l1;i<=r1;++i)
        {
            check(sum(i,z,1),l1,r1,l2,r2);
            for(auto j:p)
            {
                d[j.t]=max(d[j.t],f[sum(j.l1,j.l2,0)]+g[sum(j.r1,j.r2,0)]);
            }
        }
        solve(l1,r1,l2,z-1,p1);
        solve(l1,r1,z+1,r2,p2);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a1[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a2[i]);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n+1;++i)
    {
        for(int j=1;j<=n+1;++j)
        {
            int x=sum(i,j,0);
            if(i>1) road(sum(i-1,j,0),x,0),road(sum(i-1,j,1),x,0);
            if(j>1) road(sum(i,j-1,0),x,0),road(sum(i,j-1,2),x,0);
            x=sum(i,j,1);
            road(sum(i,j,0),x,-a1[i]);
            if(j>1) road(sum(i,j-1,1),x,max(a[i][j-1]-a2[j-1],0)),road(sum(i,j-1,2),x,a[i][j-1]-a1[i]);
            x=sum(i,j,2);
            road(sum(i,j,0),x,-a2[j]);
            if(i>1) road(sum(i-1,j,2),x,max(a[i-1][j]-a1[i-1],0)),road(sum(i-1,j,1),x,a[i-1][j]-a2[j]);
        }
    }
    vector<str> p;
    for(int i=1;i<=m;++i)
    {
        str x;
        scanf("%d%d%d%d",&x.l1,&x.r1,&x.l2,&x.r2);
        ++x.r1,++x.r2;
        x.t=i;
        p.push_back(x);
    }
    solve(1,n+1,1,n+1,p);
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",d[i]);
    }
    return 0;
}