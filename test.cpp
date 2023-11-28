#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef double ld;
const ld eps=1e-12,pi=acos(-1.0);
const int N=1000001;
int dcmp(ld x)
{
    if(fabs(x)<eps) return 0;
    if(x>0) return 1;
    else return -1;
}

struct pt;
struct vec;

struct pt
{
    ld x=0,y=0;
    pt();
    pt(const ld &_x,const ld &_y);
    explicit pt(const vec &p);
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
};
struct vec
{
    ld x=0,y=0;
    vec();
    vec(const ld &_x,const ld &_y);
    vec(const pt &p);
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    ld len() const {return sqrt(x*x+y*y);}
};

pt::pt() {}
pt::pt(const ld &_x,const ld &_y):x(_x),y(_y) {};
pt::pt(const vec &p):x(p.x),y(p.y) {}
vec::vec() {}
vec::vec(const ld &_x,const ld &_y):x(_x),y(_y) {};
vec::vec(const pt &p):x(p.x),y(p.y) {}

pt operator+(const pt &a,const vec &b) {return pt(a.x+b.x,a.y+b.y);}
vec operator+(const vec &a,const vec &b) {return vec(a.x+b.x,a.y+b.y);}
vec operator-(const pt &a,const pt &b) {return vec(a.x-b.x,a.y-b.y);}
pt operator-(const pt &a,const vec &b) {return pt(a.x-b.x,a.y-b.y);}
vec operator-(const vec &a,const vec &b) {return vec(a.x-b.x,a.y-b.y);}
vec operator*(const vec &a,ld b) {return vec(a.x*b,a.y*b);}
vec operator*(ld a,const vec &b) {return vec(b.x*a,b.y*a);}
vec operator/(const vec &a,ld b) {return vec(a.x/b,a.y/b);}
bool operator==(const pt &a,const pt &b) {return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}
bool operator==(const vec &a,const vec &b) {return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}
ld operator*(const vec &a,const vec &b) {return a.x*b.x+a.y*b.y;}
ld operator^(const vec &a,const vec &b) {return a.x*b.y-a.y*b.x;}

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
    bool inc(const pt &x) const
    {
        return dcmp((x-a)^t)==0;
    }
    bool onleft(const pt &x) const
    {
        return dcmp((x-a)^t)<0;
    }
};

ld angle(const vec &a,const vec &b)
{
    return acos((a*b)/a.len()/b.len());
}
ld dis(const pt &a,const pt &b)
{
    return (a-b).len();
}
ld dis(const pt &a,const lin &b)
{
    if(a==b.a||b.t==pt(0,0)) return 0;
    return dis(a,b.a)*fabs(sin(angle(a-b.a,b.t)));
}
bool ifinter(const seg &a,const seg &b)
{
    if(dcmp((a.b-a.a)^(b.b-b.a))==0) return false;
    return dcmp(max(a.a.x,a.b.x)-min(b.a.x,b.b.x))>=0&&dcmp(max(b.a.x,b.b.x)-min(a.a.x,a.b.x))>=0
    &&dcmp(max(a.a.y,a.b.y)-min(b.a.y,b.b.y))>=0&&dcmp(max(b.a.y,b.b.y)-min(a.a.y,a.b.y))>=0
    &&dcmp(((b.a-a.a)^(b.b-a.a))*((b.a-a.b)^(b.b-a.b)))<=0&&dcmp(((a.a-b.a)^(a.b-b.a))*((a.a-b.b)^(a.b-b.b)))<=0;
}
pt inter(const lin &a,const lin &b)
{
    if(dcmp(a.t^b.t)==0) return pt(0,0);
    return a.a+((b.t^(a.a-b.a))/(a.t^b.t))*a.t;
}
vec turn(const vec &a,ld b)
{
    return vec(a.x*cos(b)-a.y*sin(b),a.y*cos(b)+a.x*sin(b));
}
pt sym(const pt &a,const lin &b)
{
    return pt(inter(lin(a,turn(b.t,pi/2)),b)*2-a);
}

struct poly
{
    int n;
    pt *a=NULL;
    poly() {}
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
        int m=n;
        n=0;
        for(int i=2;i<=m;++i)
        {
            if(a[i].y<a[1].y||(a[i].y==a[1].y&&a[i].x<a[1].x)) swap(a[1],a[i]);
        }
        sort(a+2,a+m+1,[&](const pt &x,const pt &y)
        {
            int z=dcmp((x-a[1])^(y-a[1]));
            return z>0||(z==0&&dcmp(dis(x,a[1])-dis(y,a[1]))<0);
        });
        pt *b=new pt[m+2];
        b[++n]=a[1];
        for(int i=2;i<=m;++i)
        {
            while(n>1&&dcmp((b[n]-b[n-1])^(a[i]-b[n]))<=0) --n;
            b[++n]=a[i];
        }
        b[n+1]=a[1];
        swap(a,b);
        delete[] b;
        if(n<=2) n=0;
    }
};

pt a[N];
int main()
{
    poly p;
    p.input();
    p.solve();
    int n=p.n;
    for(int i=1;i<=n;++i) a[i]=a[n+i]=p[i];
    ld s=0;
    for(int i=1;i<=n;++i)
    {
        int x=i;
        for(int j=i+1;j<=n;++j)
        {
            while(x+1<=j&&dcmp((a[j]-a[i])^(a[x+1]-a[x]))<0) x=x%n+1;
            s=max(s,((a[x]-a[j])^(a[x]-a[i]))/2);
        }
    }
    printf("%.2lf\n",s);
    return 0;
}