#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=1e9+7;
int n,m;
ll s,a[N],b1[N],b2[N];
ll sum1(ll q,ll l,ll r)
{
    return ((r-q)/(m-1)-(l-q-1)/(m-1))%P;
}
ll sum2(ll q,ll l,ll r)
{
    return ((q-l)/(m-1)-(q-r-1)/(m-1))%P;
}
void solve(int l,int r)
{
    if(l>r) return;
    if(l==r) return;
    int q=l+r>>1;
    b1[q]=a[q];
    b2[q+1]=a[q+1];
    for(int i=q-1;i>=l;--i) b1[i]=max(b1[i+1],a[i]);
    for(int i=q+2;i<=r;++i) b2[i]=max(b2[i-1],a[i]);
    int x=q;
    for(int i=q;i>=l;--i)
    {
        while(x+1<=r&&b2[x+1]<=b1[i]) ++x;
        s=(s+b1[i]*sum1(i,q+1,x)%P)%P;
    }
    x=q+1;
    for(int i=q+1;i<=r;++i)
    {
        while(x-1>=l&&b1[x-1]<b2[i]) --x;
        s=(s+b2[i]*sum2(i,x,q)%P)%P;
    }
    solve(l,q);
    solve(q+1,r);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    solve(1,n);
    printf("%lld",(s%P+P)%P);
    return 0;
}