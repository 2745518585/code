#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,m,b[N],fa[N];
vector<int> a[N];
ll jc[N],f[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
ll C(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]*jc[b]%P))%P;
}
void dfs(int x)
{
    b[x]=1;
    for(auto i:a[x])
    {
        if(i==fa[x]) continue;
        fa[i]=x;
        dfs(i);
        b[x]+=b[i];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=(jc[i-1]*i)%P;
    for(int i=1;i<=n;++i)
    {
        f[i]=(f[i-1]+C(i-1,m/2)*C(n-i,(m-1)/2)%P)%P;
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(1);
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        ll w=0;
        for(auto j:a[i])
        {
            int z;
            if(j!=fa[i]) z=b[j];
            else z=n-b[i];
            w=(w+f[z])%P;
        }
        s=(s+C(n,m)-w)%P;
    }
    printf("%lld",(s*inv(C(n,m))%P+P)%P);
    return 0;
}