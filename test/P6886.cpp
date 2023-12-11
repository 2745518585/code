#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;

int dcmp(int x)
{
    if(x==0) return 0;
    if(x>0) return 1;
    else return -1;
}

struct pt;
struct vec;

struct pt
{
    int x=0,y=0;
    pt();
    pt(const int &_x,const int &_y);
    explicit pt(const vec &p);
};
struct vec
{
    int x=0,y=0;
    vec();
    vec(const int &_x,const int &_y);
    vec(const pt &p);
};

pt::pt() {}
pt::pt(const int &_x,const int &_y):x(_x),y(_y) {};
pt::pt(const vec &p):x(p.x),y(p.y) {}
vec::vec() {}
vec::vec(const int &_x,const int &_y):x(_x),y(_y) {};
vec::vec(const pt &p):x(p.x),y(p.y) {}

pt operator+(const pt &a,const vec &b) {return pt(a.x+b.x,a.y+b.y);}
vec operator+(const vec &a,const vec &b) {return vec(a.x+b.x,a.y+b.y);}
vec operator-(const pt &a,const pt &b) {return vec(a.x-b.x,a.y-b.y);}
pt operator-(const pt &a,const vec &b) {return pt(a.x-b.x,a.y-b.y);}
vec operator-(const vec &a,const vec &b) {return vec(a.x-b.x,a.y-b.y);}
vec operator*(const vec &a,int b) {return vec(a.x*b,a.y*b);}
vec operator*(int a,const vec &b) {return vec(b.x*a,b.y*a);}
vec operator/(const vec &a,int b) {return vec(a.x/b,a.y/b);}
bool operator==(const pt &a,const pt &b) {return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}
bool operator==(const vec &a,const vec &b) {return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}
int operator*(const vec &a,const vec &b) {return a.x*b.x+a.y*b.y;}
int operator^(const vec &a,const vec &b) {return a.x*b.y-a.y*b.x;}

struct seg
{
    pt a,b;
    seg() {}
    seg(const pt &_a,const pt &_b):a(_a),b(_b) {}
    seg(const pt &_a,const vec &_b):a(_a),b(_a+_b) {}
    bool inc(const pt &x) const
    {
        return dcmp((a-x)^(b-x))==0&&dcmp((a-x)*(b-x))<=0;
    }
};
struct lin
{
    pt a;
    vec t;
    lin() {}
    lin(const pt &_a,const vec &_t):a(_a),t(_t) {}
    lin(const pt &_a,const pt &_b):a(_a),t(_b-_a) {}
    lin(const seg &p):a(p.a),t(p.b-p.a) {}
};

pt inter(const lin &a,const lin &b)
{
    if(dcmp(a.t^b.t)==0) return pt(0,0);
    return a.a+((b.t^(a.a-b.a))/(a.t^b.t))*a.t;
}
bool ifinter(const seg &a,const seg &b)
{
    if(dcmp((a.b-a.a)^(b.b-b.a))==0) return false;
    return dcmp(max(a.a.x,a.b.x)-min(b.a.x,b.b.x))>=0&&dcmp(max(b.a.x,b.b.x)-min(a.a.x,a.b.x))>=0
    &&dcmp(max(a.a.y,a.b.y)-min(b.a.y,b.b.y))>=0&&dcmp(max(b.a.y,b.b.y)-min(a.a.y,a.b.y))>=0
    &&dcmp(((b.a-a.a)^(b.b-a.a))*((b.a-a.b)^(b.b-a.b)))<=0&&dcmp(((a.a-b.a)^(a.b-b.a))*((a.a-b.b)^(a.b-b.b)))<=0;
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
    return (x%P+P)%P;
}
ll qpow(ll x,ll y)
{
    ll a=1,b=x;
    while(y!=0)
    {
        if(y&1) a=a*b%P;
        b=b*b%P;
        y>>=1;
    }
    return a;
}
struct poly
{
    int n=-1;
    ll *a=NULL;
    poly resize(int _n)
    {
        ll *_a=new ll[_n+1];
        for(int i=0;i<=min(n,_n);++i) _a[i]=a[i];
        for(int i=min(n,_n)+1;i<=_n;++i) _a[i]=0;
        n=_n;
        if(a!=NULL) delete[] a;
        a=_a;
        return *this;
    }
    poly(){}
    poly(int x)
    {
        resize(0);
        a[0]=x;
    }
    ll &operator[](size_t x) {return a[x];}
    const ll &operator[](size_t x) const {return a[x];}
    void print()
    {
        for(int i=0;i<=n;++i) printf("%lld ",a[i]);
        printf("\n");
    }
    friend poly operator+(const poly &a,const poly &b)
    {
        poly c;
        c.resize(max(a.n,b.n));
        for(int i=0;i<=c.n;++i) c[i]=(a[i]+b[i])%P;
        return c;
    }
    friend poly operator-(const poly &a,const poly &b)
    {
        poly c;
        c.resize(max(a.n,b.n));
        for(int i=0;i<=c.n;++i) c[i]=(a[i]-b[i]+P)%P;
        return c;
    }
    friend poly NTT(int n,poly a,int u)
    {
        a.resize(n);
        int p=0;
        while((1<<p)<n) ++p;
        static int d[N];
        for(int i=0;i<n;++i)
        {
            d[i]=(d[i>>1]>>1)|((i&1)<<(p-1));
        }
        for(int i=0;i<n;++i)
        {
            if(i<d[i]) swap(a[i],a[d[i]]);
        }
        for(int i=1;i<n;i<<=1)
        {
            int t=qpow(3,(P-1)/(i*2));
            if(u==-1) t=inv(t);
            for(int j=0;j<n;j+=i*2)
            {
                ll w=1;
                for(int k=j;k<i+j;++k)
                {
                    ll q=w*a[k+i]%P;
                    a[k+i]=(a[k]-q)%P;
                    a[k]=(a[k]+q)%P;
                    w=w*t%P;
                }
            }
        }
        return a;
    }
    friend poly operator*(poly a,poly b)
    {
        int p=1;
        while(p<=a.n+b.n) p<<=1;
        a=NTT(p,a,1);
        b=NTT(p,b,1);
        poly c;
        c.resize(p);
        for(int i=0;i<=p;++i) c[i]=a[i]*b[i]%P;
        c=NTT(p,c,-1);
        c.resize(a.n+b.n);
        for(int i=0;i<=c.n;++i) c[i]=c[i]*inv(p)%P;
        return c;
    }
};

int m1,m2,n,q;
pt p[N];
int sum(int x,int y)
{
    return x*(m2+1)+y;
}
int main()
{
    scanf("%d%d%d",&m1,&m2,&n);
    poly a,b;
    a.resize(sum(m1,m2));
    b.resize(sum(m1,m2));
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        b[sum(m1,m2)-sum(x,y)]=1;
    }
    scanf("%d",&q);
    int x1=1e9,x2=-1e9,y1=1e9,y2=-1e9;
    for(int i=1;i<=q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        p[i]=pt(x,y);
        x1=min(x1,x);
        x2=max(x2,x);
        y1=min(y1,y);
        y2=max(y2,y);
    }
    for(int i=1;i<=q;++i) p[i].x-=x1;
    x2-=x1;
    x1=0;
    for(int i=1;i<=q;++i) p[i].y-=y1;
    y2-=y1;
    y1=0;
    if(x2>m1||y2>m2)
    {
        printf("0");
        return 0;
    }
    p[q+1]=p[1];
    for(int i=0;i<=x1;++i)
    {
        for(int j=0;j<=x2;++j)
        {
            int u=0;
            for(int k=1;k<=q;++k)
            {
                if(ifinter(seg(pt(i,j),pt(i,m2+1)),seg(p[k],p[k+1]))&&!seg(pt(i,j),pt(i,m2+1)).inc(p[k].x<p[k+1].x?p[k]:p[k+1])) ++u;
                if(seg(p[k],p[k+1]).inc(pt(i,j)))
                {
                    u=1;
                    break;
                }
            }
            if(u%2==1) a[sum(i,j)]=1;
        }
    }
    poly c=a*b;
    int s=0;
    for(int i=0;i<=m1-x2;++i)
    {
        for(int j=0;j<=m2-y2;++j)
        {
            if(c[sum(m1,m2)-sum(i,j)]==0) ++s;
        }
    }
    printf("%d",s);
    return 0;
}