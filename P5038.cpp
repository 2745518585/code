#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=101;
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
int m,n;
ll b[M][M],q;
int sum(int x,int y)
{
    return (x-1)*n+y;
}
bool check(ll x)
{
    p=1;
    for(int i=1;i<=s2;++i) t[i]=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if((i+j)%2==0)
            {
                road(s1,sum(i,j),x-b[i][j]);
                if(i>1) road(sum(i,j),sum(i-1,j),1e18);
                if(i<m) road(sum(i,j),sum(i+1,j),1e18);
                if(j>1) road(sum(i,j),sum(i,j-1),1e18);
                if(j<n) road(sum(i,j),sum(i,j+1),1e18);
            }
            else road(sum(i,j),s2,x-b[i][j]);
        }
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    for(int i=t[s1];i!=0;i=a[i].q)
    {
        if(a[i].r!=0) return false;
    }
    for(int i=t[s2];i!=0;i=a[i].q)
    {
        if(a[i^1].r!=0) return false;
    }
    return true;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        s1=m*n+1,s2=m*n+2;
        int p1=0,p2=0;
        ll q1=0,q2=0,w=0;
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                scanf("%lld",&b[i][j]);
                if((i+j)%2==0) q1+=b[i][j],++p1;
                else q2+=b[i][j],++p2;
                w=max(w,b[i][j]);
            }
        }
        if(m%2==1&&n%2==1)
        {
            ll z=(q1-q2)/(p1-p2);
            if(check(z)) printf("%lld\n",z*p1-q1);
            else printf("-1\n");
            continue;
        }
        if(q1!=q2)
        {
            printf("-1\n");
            continue;
        }
        q=q1+q2;
        ll l=w,r=2e9;
        while(l<r)
        {
            ll z=l+r>>1;
            if(check(z)) r=z;
            else l=z+1;
        }
        printf("%lld\n",(l*m*n-q)/2);
    }
    return 0;
}