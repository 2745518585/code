#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,q1,q2,a[N],b[N],c1[N],c2[N],c[N],d1[N],d2[N],d[N],*S[N],T[N];
ll f[N],g[N];
namespace sgt
{
    ll T[N];
    void add(int x,ll k)
    {
        while(x<=q2) T[x]=max(T[x],k),x+=x&-x;
    }
    ll sum(int x)
    {
        ll s=0;
        while(x>=1) s=max(s,T[x]),x-=x&-x;
        return s;
    }
};
bool cmp(int x,int y)
{
    if(d1[x]!=d1[y]) return d1[x]<d1[y];
    return d2[x]<d2[y];
}
double abc(int x,int y)
{
    return (double)((g[x]+(ll)(x-1)*(x-1))-(g[y]+(ll)(y-1)*(y-1)))/((x-1)-(y-1));
}
void solve(int x)
{
    g[x]=sgt::sum(d2[x]);
    int *S=::S[d[x]],&T=::T[d[x]];
    while(T>1&&abc(S[T-1],S[T])<abc(S[T],x)) --T;
    S[++T]=x;
    int l=1,r=T;
    while(l<r)
    {
        int z=l+r>>1;
        if(abc(S[z],S[z+1])<2*x) r=z;
        else l=z+1;
    }
    f[x]=g[S[l]]+(ll)(x-S[l]+1)*(x-S[l]+1);
    sgt::add(d2[x],f[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i],&b[i]);
        c1[i]=b[i]-a[i];
        c2[i]=b[i]+a[i];
    }
    sort(c1+1,c1+n+1);
    q1=unique(c1+1,c1+n+1)-c1-1;
    sort(c2+1,c2+n+1);
    q2=unique(c2+1,c2+n+1)-c2-1;
    for(int i=1;i<=n;++i)
    {
        d1[i]=lower_bound(c1+1,c1+q1+1,b[i]-a[i])-c1;
        d2[i]=lower_bound(c2+1,c2+q2+1,b[i]+a[i])-c2;
    }
    for(int i=1;i<=n;++i)
    {
        int j=i;
        d[i]=++q;
        while(j+1<=n&&abs(a[j+1]-a[j])<=b[j+1]-b[j]) d[++j]=q;
        S[q]=new int[(j-i+1)+10];
        i=j;
    }
    for(int i=1;i<=n;++i) c[i]=i;
    sort(c+1,c+n+1,cmp);
    for(int i=1;i<=n;++i) solve(c[i]);
    ll s=0;
    for(int i=1;i<=n;++i) s=max(s,f[i]);
    printf("%lld",s);
    return 0;
}