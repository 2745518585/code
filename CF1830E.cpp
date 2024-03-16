#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,a[N],p[N];
ll f[N],g[N];
struct str
{
    int a,b,c,t;
    str() {}
    str(int a,int b,int c,int t):a(a),b(b),c(c),t(t) {}
};
bool cmp(str a,str b)
{
    if(a.a!=b.a) return a.a<b.a;
    if(a.b!=b.b) return a.b<b.b;
    return a.c<b.c;
}
struct cdq
{
    int n,b[N],c[N];
    ll T[N];
    str a[N];
    void add(int x,ll k)
    {
        while(x<=q) T[x]+=k,x+=(x&-x);
    }
    ll sum(int x)
    {
        ll s=0;
        while(x>=1) s+=T[x],x-=(x&-x);
        return s;
    }
    void solve(int *b,int n)
    {
        if(n==1) return;
        int m=n>>1;
        solve(b,m);
        solve(b+m,n-m);
        for(int i=1;i<=n;++i) c[i]=b[i];
        int x=1,y=m+1;
        for(int i=1;i<=n;++i)
        {
            if(x<=m&&(y>n||a[c[x]].b<a[c[y]].b))
            {
                b[i]=c[x];
                add(a[c[x]].c,a[c[x]].t);
                ++x;
            }
            else
            {
                b[i]=c[y];
                f[a[c[y]].a]+=sum(a[c[y]].c-1)*a[c[y]].t;
                ++y;
            }
        }
        for(int i=1;i<=m;++i) add(a[c[i]].c,-a[c[i]].t);
    }
    void solve()
    {
        // for(int i=1;i<=n;++i)
        // {
        //     printf("%d %d %d %d\n",a[i].a,a[i].b,a[i].c,a[i].t);
        // }
        // printf("\n");
        sort(a+1,a+n+1,cmp);
        for(int i=1;i<=n;++i) b[i]=i;
        solve(b,n);
    }
    void add(str x)
    {
        a[++n]=x;
    }
}cdq1,cdq2;
void add(int x,int t)
{
    ++q;
    cdq1.add(str(q,n-x+1,a[x],t));
    cdq2.add(str(q,x,n-a[x]+1,t));
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        g[0]+=abs(a[i]-i);
        add(i,1);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[i]=g[i-1]-abs(x-a[x])-abs(y-a[y]);
        add(x,-1),add(y,-1);
        swap(a[x],a[y]);
        g[i]+=abs(x-a[x])+abs(y-a[y]);
        add(x,1),add(y,1);
        p[i]=q;
    }
    cdq1.solve();
    cdq2.solve();
    for(int i=1;i<=q;++i) f[i]+=f[i-1];
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",g[i]-f[p[i]]);
    }
    return 0;
}