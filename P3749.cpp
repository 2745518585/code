#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k,b[N];
struct Maxflow
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
}a;
int sum(int x,int y)
{
    return (x-1)*n+y;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        m=max(m,b[i]);
    }
    a.s1=n*n+m+1,a.s2=n*n+m+2;
    ll q=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j<=n;++j)
        {
            ll x;
            scanf("%lld",&x);
            if(i==j) x-=b[i];
            if(x>=0)
            {
                a.road(a.s1,sum(i,j),x);
                a.road(sum(i,j),a.s2,0);
                q+=x;
            }
            else
            {
                a.road(a.s1,sum(i,j),0);
                a.road(sum(i,j),a.s2,-x);
            }
            if(i!=j)
            {
                a.road(sum(i,j),sum(i+1,j),1e18);
                a.road(sum(i,j),sum(i,j-1),1e18);
            }
            else
            {
                a.road(sum(i,j),n*n+b[i],1e18);
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        a.road(a.s1,n*n+i,0);
        a.road(n*n+i,a.s2,k*i*i);
    }
    printf("%lld",q-a.solve());
    return 0;
}