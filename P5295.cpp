#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10001;
int n,m;
struct road
{
    int x,y;
}a[N];
namespace mf
{
    int p=1,s1,s2,t[N],t0[N],f[N];
    struct road
    {
        int m,q;
        ll r;
    }a[N];
    void road(int x,int y,ll r)
    {
        a[++p].m=y;
        a[p].q=t[x];
        t[x]=p;
        a[p].r=r;
        a[++p].m=x;
        a[p].q=t[y];
        t[y]=p;
        a[p].r=0;
    }
    bool bfs()
    {
        queue<int> Q;
        Q.push(s1);
        for(int i=1;i<=s2;++i) f[i]=0;
        f[s1]=1;
        while(!Q.empty())
        {
            int k=Q.front();
            Q.pop();
            for(int i=t[k];i!=0;i=a[i].q)
            {
                if(f[a[i].m]==0&&a[i].r!=0)
                {
                    f[a[i].m]=f[k]+1;
                    Q.push(a[i].m);
                }
            }
        }
        return f[s2]!=0;
    }
    ll dfs(int x,ll r)
    {
        if(x==s2) return r;
        ll s=0;
        for(int i=t0[x];i!=0;i=a[i].q)
        {
            t0[x]=i;
            if(f[a[i].m]==f[x]+1&&a[i].r!=0)
            {
                ll z=dfs(a[i].m,min(r,a[i].r));
                if(z!=0)
                {
                    a[i].r-=z;
                    a[i^1].r+=z;
                    r-=z;
                    s+=z;
                }
                else f[a[i].m]=0;
                if(r==0) return s;
            }
        }
        return s;
    }
    ll solve()
    {
        ll r=0;
        while(bfs())
        {
            for(int i=1;i<=s2;++i) t0[i]=t[i];
            r+=dfs(s1,1e18);
        }
        return r;
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&a[i].x,&a[i].y);
        }
        mf::s1=n+m+1,mf::s2=n+m+2;
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            mf::p=1;
            for(int j=1;j<=mf::s2;++j) mf::t[j]=0;
            for(int j=1;j<=n;++j)
            {
                if(i==j) mf::road(mf::s1,j,1e18);
                mf::road(j,mf::s2,2);
            }
            for(int j=1;j<=m;++j)
            {
                mf::road(mf::s1,n+j,1);
                mf::road(n+j,a[j].x,1e18);
                mf::road(n+j,a[j].y,1e18);
            }
            ll r=mf::solve();
            if(m-r>-2)
            {
                u=false;
                break;
            }
        }
        if(u) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}