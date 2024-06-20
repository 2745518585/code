#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=501,M=10001;
const ll P=1e9+7;
int n,m,q,a1[N],a2[N],b[N<<1],d[N][N];
ll f[M][N],jc[N];
vector<int> c[M];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    return (x%P+P)%P;
}
void init(int l,int r)
{
    if(d[l][r]||l>r) return;
    d[l][r]=++m;
    for(int i=l;i<=r;++i)
    {
        if(abs((i-l)-(r-i))<=2)
        {
            c[d[l][r]].push_back(i);
            init(l,i-1);
            init(i+1,r);
        }
    }
}
void solve(int l,int r)
{
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=min(r-l,n+1);++j) f[i][j]=0;
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=i;j<=n;++j)
        {
            if(!d[i][j]) continue;
            for(auto k:c[d[i][j]])
            {
                if(!(l>=a1[k]&&l<a2[k])) continue;
                for(int p=1;p<=min(r-l,n+1);++p)
                {
                    f[d[i][j]][p]+=f[d[i][k-1]][p]*f[d[k+1][j]][p-1]%P;
                }
            }
            for(int k=1;k<=min(r-l,n+1);++k)
            {
                f[d[i][j]][k]=(f[d[i][j]][k]%P+f[d[i][j]][k-1])%P;
            }
        }
    }
    if(r-l<=n+1)
    {
        for(int i=1;i<=m;++i) f[i][0]=f[i][r-l];
        return;
    }
    ll w=1;
    for(int i=1;i<=n+1;++i) w=w*((r-l)-i)%P;
    for(int i=1;i<=m;++i) f[i][0]=0;
    for(int i=1;i<=n+1;++i)
    {
        ll w1=w*inv((r-l)-i)%P,w2=jc[i-1]*jc[n+1-i]%P*((n+1-i)%2?-1:1)%P;
        ll w=w1*inv(w2)%P;
        for(int j=1;j<=m;++j)
        {
            f[j][0]+=f[j][i]*w%P;
        }
    }
    for(int i=1;i<=m;++i) f[i][0]%=P;
}
int main()
{
    scanf("%d",&n);
    jc[0]=1;
    for(int i=1;i<=n+1;++i) jc[i]=jc[i-1]*i%P;
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a1[i],&a2[i]);
        ++a2[i];
        b[++q]=a1[i],b[++q]=a2[i];
    }
    init(1,n);
    sort(b+1,b+q+1);
    q=unique(b+1,b+q+1)-b-1;
    for(int i=0;i<=n+1;++i) f[0][i]=1;
    for(int i=1;i<=q-1;++i)
    {
        solve(b[i],b[i+1]);
    }
    printf("%lld",(f[d[1][n]][0]%P+P)%P);
    return 0;
}