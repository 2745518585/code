#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const ll P=998244353;
const int N=1000001;
int n,q,a[N],d[N],e[N];
ll f[N],T[N];
vector<int> b[N];
void add(int x,ll k)
{
    while(x<=n) T[x]=(T[x]+k)%P,x+=(x&-x);
}
ll sum(int x)
{
    ll s=0;
    while(x>=1) s=(s+T[x])%P,x-=(x&-x);
    return s;
}
void insert(int x)
{
    if(e[x]==0) ++q;
    ++e[x];
}
void del(int x)
{
    --e[x];
    if(e[x]==0) --q;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    int t=n;
    for(int i=n;i>=1;--i)
    {
        if(a[i]==a[i+1])
        {
            for(int j=i+1;j<=t;++j) d[j]=i;
            t=i;
        }
    }
    f[1]=1;
    add(1,1);
    int x=1;
    insert(a[1]);
    for(int i=2;i<=n;++i)
    {
        insert(a[i]);
        while(q>2) del(a[x]),++x;
        if(d[i]<=x-1) f[i]=sum(x-1)-sum(d[i]);
        f[i]+=f[i-1];
        if(a[i-2]==a[i]&&a[i-1]!=a[i]) f[i]+=f[i-2];
        f[i]=(f[i]%P+P)%P;
        add(i,f[i]);
    }
    printf("%lld\n",f[n]);
    return 0;
}