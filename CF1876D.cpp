#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,a[N],b[N],c[N],fa[N];
bool h[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
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
    x=(x%P+P)%P;
    return x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        h[a[i]]=true;
        if(b[a[i]]==0) b[a[i]]=i;
        else c[i]=b[a[i]],b[a[i]]=0;
    }
    ll q=1,w=1;
    int x1=0,x2=0;
    for(int i=1;i<=200000;++i)
    {
        if(h[i])
        {
            if(b[i]!=0) w=0;
            q=q*2%P,fa[i]=i;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(c[i]==0) continue;
        if(c[i]<x1)
        {
            w=0;
            break;
        }
        if(c[i]<=x2) fa[find(a[x2])]=find(a[i]);
        x1=c[i],x2=i;
    }
    for(int i=1;i<=200000;++i)
    {
        if(find(i)==i) w=w*2%P;
    }
    // printf("%lld %lld\n",q,w);
    printf("%lld\n",((q-w)*inv(2)%P+P)%P);
    return 0;
}