#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N=1000001;
int dcmp(ll x)
{
    if(x==0) return 0;
    if(x>0) return 1;
    else return -1;
}

struct pt;
struct vec;

struct pt
{
    ll x=0,y=0;
    pt();
    pt(const ll &_x,const ll &_y);
    explicit pt(const vec &p);
    void input()
    {
        scanf("%lld%lld",&x,&y);
    }
};
struct vec
{
    ll x=0,y=0;
    vec();
    vec(const ll &_x,const ll &_y);
    vec(const pt &p);
    void input()
    {
        scanf("%lld%lld",&x,&y);
    }
    ld len() const {return sqrtl(x*x+y*y);}
    vec turn(const ll &b) const
    {
        return vec(x*cos(b)-y*sin(b),y*cos(b)+x*sin(b));
    }
    vec tolen(const ll &p) const
    {
        return vec(x/len()*p,y/len()*p);
    }
    vec resize(ll p)
    {
        p/=len();
        x*=p,y*=p;
        return *this;
    }
};

pt::pt() {}
pt::pt(const ll &_x,const ll &_y):x(_x),y(_y) {};
pt::pt(const vec &p):x(p.x),y(p.y) {}
vec::vec() {}
vec::vec(const ll &_x,const ll &_y):x(_x),y(_y) {};
vec::vec(const pt &p):x(p.x),y(p.y) {}

pt operator+(const pt &a,const vec &b) {return pt(a.x+b.x,a.y+b.y);}
vec operator+(const vec &a,const vec &b) {return vec(a.x+b.x,a.y+b.y);}
vec operator-(const pt &a,const pt &b) {return vec(a.x-b.x,a.y-b.y);}
pt operator-(const pt &a,const vec &b) {return pt(a.x-b.x,a.y-b.y);}
vec operator-(const vec &a,const vec &b) {return vec(a.x-b.x,a.y-b.y);}
vec operator*(const vec &a,ll b) {return vec(a.x*b,a.y*b);}
vec operator*(ll a,const vec &b) {return vec(b.x*a,b.y*a);}
vec operator/(const vec &a,ll b) {return vec(a.x/b,a.y/b);}
bool operator==(const pt &a,const pt &b) {return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}
bool operator==(const vec &a,const vec &b) {return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}
ll operator*(const vec &a,const vec &b) {return a.x*b.x+a.y*b.y;}
ll operator^(const vec &a,const vec &b) {return a.x*b.y-a.y*b.x;}

struct seg
{
    pt a,b;
    seg() {}
    seg(const pt &_a,const pt &_b):a(_a),b(_b) {}
    seg(const pt &_a,const vec &_b):a(_a),b(_a+_b) {}
    void input() {a.input(),b.input();}
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
    void input() {a.input(),t.input();}
    void input_seg() {a.input(),t.input();t=t-a;}
    bool inc(const pt &x) const
    {
        return dcmp((a-x)^t)==0;
    }
    bool onleft(const pt &x) const
    {
        return dcmp((x-a)^t)<0;
    }
    bool onright(const pt &x) const
    {
        return dcmp((x-a)^t)>0;
    }
};

ld dis(const pt &a,const pt &b)
{
    return (a-b).len();
}

struct poly
{
    int n;
    pt *a=NULL;
    poly() {}
    poly(int _n):n(_n)
    {
        if(a!=NULL) delete[] a;
        a=new pt[n+2];
    }
    poly(int _n,pt *_a):n(_n)
    {
        if(a!=NULL) delete[] a;
        a=new pt[n+2];
        for(int i=1;i<=n;++i) a[i]=_a[i];
    }
    poly(const poly &p):n(p.n)
    {
        if(a!=NULL) delete[] a;
        a=new pt[n+2];
        for(int i=1;i<=n;++i) a[i]=p[i];
    }
    poly(const poly &&p):n(p.n),a(p.a) {}
    ~poly() {if(a!=NULL) delete[] a,a=NULL;}
    pt &operator[](const size_t pos) {return a[pos];}
    pt operator[](const size_t pos) const {return a[pos];}
    void input()
    {
        scanf("%d",&n);
        if(a!=NULL) delete[] a;
        a=new pt[n+2];
        for(int i=1;i<=n;++i) a[i].input();
    }
    void solve()
    {
        if(n<=2) return;
        pt *b=new pt[n+1];
        for(int i=1;i<=n;++i) b[i]=a[i];
        sort(b+1,b+n+1,[](const pt &a,const pt &b)
        {
            if(a.x!=b.x) return a.x<b.x;
            return a.y<b.y;
        });
        int m=n;
        delete[] a;
        a=new pt[n*2+1];
        a[0]=b[1],a[1]=b[2];
        n=1;
        for(int i=3;i<=m;++i)
        {
            while(n>=1&&dcmp((a[n]-a[n-1])^(b[i]-a[n]))<0) --n;
            a[++n]=b[i];
        }
        a[++n]=b[m-1];
        for(int i=m-2;i>=1;--i)
        {
            while(n>=1&&dcmp((a[n]-a[n-1])^(b[i]-a[n]))<0) --n;
            a[++n]=b[i];
        }
        a[n+1]=a[1];
    }
};

ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        poly a;
        a.input();
        int n=a.n;
        a.solve();
        if(a.n==1)
        {
            printf("1\n");
            continue;
        }
        if(a.n==2)
        {
            if(gcd(abs(a[1].x-a[2].x),abs(a[1].y-a[2].y))==n-1) printf("1\n");
            else printf("0\n");
            continue;
        }
        ll s=2;
        for(int i=1;i<=a.n;++i)
        {
            s+=(a[i]^a[i+1]);
        }
        for(int i=1;i<=a.n;++i)
        {
            s-=gcd(abs(a[i].x-a[i+1].x),abs(a[i].y-a[i+1].y));
        }
        if(s==(n-a.n)*2) printf("1\n");
        else printf("0\n");
    }
    return 0;
}