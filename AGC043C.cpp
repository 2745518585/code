#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001,M=600;
const ll P=998244353;
int n,m1,m2,m3,f1[N],f2[N],f3[N];
ll g1[N],g2[N],g3[N];
bool h[N];
vector<int> a[N];
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
void solve(int &m,int *f,ll *g)
{
    scanf("%d",&m);
    for(int i=1;i<=n;++i) a[i].clear();
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[min(x,y)].push_back(max(x,y));
    }
    f[n]=0;
    for(int i=n;i>=1;--i)
    {
        for(int j=0;j<=M;++j) h[j]=false;
        for(int j=0;j<a[i].size();++j) h[f[a[i][j]]]=true;
        for(int j=0;j<=M;++j)
        {
            if(h[j]==false)
            {
                f[i]=j;
                break;
            }
        }
        g[f[i]]=(g[f[i]]+qpow(10,i*18))%P;
    }
}
int main()
{
    scanf("%d",&n);
    solve(m1,f1,g1);
    solve(m2,f2,g2);
    solve(m3,f3,g3);
    ll s=0;
    for(int i=0;i<=M;++i)
    {
        for(int j=0;j<=M;++j)
        {
            s=(s+g1[i]%P*g2[j]%P*g3[i^j]%P)%P;
        }
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}