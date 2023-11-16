#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N];
ll f[N];
vector<int> b[N];
struct str
{
    ll a,b;
    str() {}
    str(ll a,ll b):a(a),b(b) {}
    friend str operator+(str a,str b)
    {
        return str(a.a+b.a,a.b+b.b);
    }
    friend bool operator<(str a,str b)
    {
        if(a.b!=b.b) return a.b<b.b;
        return a.a<b.a;
    }
};
ll check(str a,str b)
{
    if(a.a==b.a) return 1e18;
    if(((a.b-b.b)>0)^((a.a-b.a)>0)) return (b.b-a.b)/(a.a-b.a);
    else return 1e18;
}
struct tree
{
    int l,r;
    ll t,k;
    str s;
}T[N<<2];
void pushup(tree &T,tree T1,tree T2)
{
    T.t=min(T1.t,T2.t);
    T.s=max(T1.s,T2.s);
    T.t=min(T.t,check(T1.s,T2.s));
}
void pushdown(int x);
void maketag(int x,ll k)
{
    if(k<=T[x].t)
    {
        T[x].k+=k;
        T[x].t-=k;
        T[x].s.b+=T[x].s.a*k;
    }
    else
    {
        T[x].k+=k;
        pushdown(x);
        pushup(T[x],T[x<<1],T[x<<1|1]);
    }
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    maketag(x<<1,T[x].k);
    maketag(x<<1|1,T[x].k);
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    T[x].t=T[x].k=0;
    if(l==r)
    {
        T[x].s=str(a[l],0);
        T[x].t=1e18;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
void add(int x,int l,int r,ll k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        maketag(x,k);
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
void add2(int x,int q,ll k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s.b=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add2(x<<1,q,k);
    else add2(x<<1|1,q,k);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&m,&n);
        for(int i=1;i<=n;++i) b[i].clear();
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            b[y].push_back(x);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        build(1,1,n);
        for(int i=1;i<=n;++i)
        {
            f[i]=T[1].s.b;
            add2(1,i,f[i]);
            for(auto j:b[i])
            {
                add(1,j,i,1);
            }
        }
        printf("%lld\n",T[1].s.b);
    }
    return 0;
}