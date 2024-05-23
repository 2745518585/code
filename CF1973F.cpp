#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001,M=1001;
int n,m,sp1,sp2,q1,q2,q,a1[N],a2[N],b[N],pr1[N],pr2[N],p1[N],p2[N],f[M][M],h[N];
ll g1[M][M],g2[M][M];
pair<ll,int> d[N];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void solve1(int x,auto p)
{
    for(int i=1;i*i<=x;++i)
    {
        if(x%i==0)
        {
            p(i);
            if(x/i!=i) p(x/i);
        }
    }
}
void solve2(int x,auto p)
{
    for(int i=2;i*i<=x;++i)
    {
        if(x%i==0)
        {
            p(i);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) p(x);
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
        scanf("%d",&b[i]);
    }
    solve1(a1[1],[&](int x){p1[++q1]=x;});
    solve1(a2[1],[&](int x){p2[++q2]=x;});
    sort(p1+1,p1+q1+1);
    sort(p2+1,p2+q2+1);
    solve2(a1[1],[&](int x){pr1[++sp1]=x;});
    solve2(a2[1],[&](int x){pr2[++sp2]=x;});
    sort(pr1+1,pr1+sp1+1);
    sort(pr2+1,pr2+sp2+1);
    g2[q1][q2]+=b[1];
    for(int i=2;i<=n;++i)
    {
        {
            int x=lower_bound(p1+1,p1+q1+1,gcd(a1[1],a1[i]))-p1,y=lower_bound(p2+1,p2+q2+1,gcd(a2[1],a2[i]))-p2;
            ++f[x][y],g2[x][y]+=b[i];
        }
        {
            int x=lower_bound(p1+1,p1+q1+1,gcd(a1[1],a2[i]))-p1,y=lower_bound(p2+1,p2+q2+1,gcd(a2[1],a1[i]))-p2;
            ++f[x][y],g1[x][y]+=b[i];
        }
        {
            int x=lower_bound(p1+1,p1+q1+1,gcd(a1[1],gcd(a1[i],a2[i])))-p1,y=lower_bound(p2+1,p2+q2+1,gcd(a2[1],gcd(a1[i],a2[i])))-p2;
            --f[x][y],g1[x][y]-=b[i],g2[x][y]-=b[i];
        }
    }
    for(int i=1;i<=sp1;++i)
    {
        for(int j=q1;j>=1;--j)
        {
            int x=lower_bound(p1+1,p1+q1+1,(ll)p1[j]*pr1[i])-p1;
            if(p1[x]!=p1[j]*pr1[i]) continue;
            for(int k=1;k<=q2;++k)
            {
                f[j][k]+=f[x][k];
                g1[j][k]+=g1[x][k];
                g2[j][k]+=g2[x][k];
            }
        }
    }
    for(int i=1;i<=sp2;++i)
    {
        for(int j=q2;j>=1;--j)
        {
            int x=lower_bound(p2+1,p2+q2+1,(ll)p2[j]*pr2[i])-p2;
            if(p2[x]!=p2[j]*pr2[i]) continue;
            for(int k=1;k<=q1;++k)
            {
                f[k][j]+=f[k][x];
                g1[k][j]+=g1[k][x];
                g2[k][j]+=g2[k][x];
            }
        }
    }
    // for(int i=1;i<=q1;++i)
    // {
    //     for(int j=1;j<=q2;++j)
    //     {
    //         if(f[i][j]==n-1) printf("%d %d: %d %lld %lld\n",p1[i],p2[j],f[i][j],g1[i][j],g2[i][j]);
    //     }
    // }
    for(int i=1;i<=q1;++i)
    {
        for(int j=1;j<=q2;++j)
        {
            if(f[i][j]==n-1)
            {
                d[++q]=make_pair(min(g1[i][j],g2[i][j]),p1[i]+p2[j]);
            }
        }
    }
    sort(d+1,d+q+1);
    for(int i=1;i<=q;++i)
    {
        h[i]=max(h[i-1],d[i].second);
    }
    for(int i=1;i<=m;++i)
    {
        ll x;
        scanf("%lld",&x);
        int p=upper_bound(d+1,d+q+1,make_pair(x,(int)1e9))-d-1;
        printf("%lld ",h[p]);
    }
    return 0;
}