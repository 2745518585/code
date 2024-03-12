#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,m,a[N],b1[N],b2[N],S[N],T;
ll jc[N],ivjc[N],f[N];
bool h[N];
struct str
{
    int l,r,t;
    str() {}
    str(int l,int r,int t):l(l),r(r),t(t) {}
}c[N];
vector<str> c1[N],c2[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd((a%P+P)%P,P,x,y);
    return (x%P+P)%P;
}
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P*ivjc[b]%P;
}
struct sgt
{
    struct tree
    {
        int l,r,s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,int k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=max(T[x].s,k);
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s=max(s,sum(x<<1,l,r));
        if(r>z) s=max(s,sum(x<<1|1,l,r));
        return s;
    }
}T1,T2;
ll sum(int x,int y)
{
    return C(x+y,x)-C(x+y,x-1);
}
int main()
{
    scanf("%d",&n);
    jc[0]=1;
    for(int i=1;i<=n*2;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n*2]=inv(jc[n*2]);
    for(int i=n*2;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        a[n+i]=a[i];
    }
    T1.build(1,1,n);
    for(int i=1;i<=n;++i) T1.add(1,i,a[i]);
    for(int i=1;i<=n;++i)
    {
        while(T>0&&a[i]>a[S[T]]) --T;
        b1[i]=S[T];
        S[++T]=i;
    }
    T=0;
    for(int i=n*2;i>=1;--i)
    {
        while(T>0&&a[i]<a[S[T]]) --T;
        if(i<=n) b2[i]=S[T];
        S[++T]=i;
    }
    for(int i=1;i<=n;++i)
    {
        if(b1[i]&&b2[i]) c1[b2[i]].push_back(str(b1[i],i,0));
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&c[i].l,&c[i].r);
        c[i].t=i;
        c2[c[i].l+n-1].push_back(c[i]);
    }
    T2.build(1,1,n);
    for(int i=1;i<=n*2;++i)
    {
        for(auto j:c1[i]) T2.add(1,j.r,j.l);
        for(auto j:c2[i])
        {
            h[j.t]=T2.sum(1,j.l,j.r)>=j.l;
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(h[i])
        {
            printf("0\n");
            continue;
        }
        int p=T1.sum(1,c[i].l,c[i].r)-(c[i].r-c[i].l+1),q=n-(c[i].r-c[i].l+1);
        printf("%lld\n",(sum(q-p,q)%P+P)%P);
    }
    return 0;
}