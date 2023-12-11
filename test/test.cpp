#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
typedef long double ld;
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
        scanf("%Lf%Lf",&x,&y);
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
        scanf("%Lf%Lf",&x,&y);
    }
    ld len() const {return sqrtl(x*x+y*y);}
    vec turn(const ld &b) const
    {
        return vec(x*cos(b)-y*sin(b),y*cos(b)+x*sin(b));
    }
    vec tolen(const ld &p) const
    {
        return vec(x/len()*p,y/len()*p);
    }
    vec resize(ld p)
    {
        p/=len();
        x*=p,y*=p;
        return *this;
    }
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

ld angle(const vec &a,const vec &b)
{
    return acos((a*b)/a.len()/b.len());
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
ld dis(const pt &a,const pt &b)
{
    return (a-b).len();
}
ld dis(const pt &a,const lin &b)
{
    if(a==b.a||b.t==pt(0,0)) return 0;
    return dis(a,b.a)*fabs(sin(angle(a-b.a,b.t)));
}
ld dis(const pt &a,const seg &b)
{
    if(b.inc(inter(lin(a,(b.b-b.a).turn(pi/2)),b))) return dis(a,lin(b));
    else return min(dis(a,b.a),dis(a,b.b));
}
pt hangf(const pt &a,const lin &b)
{
    return inter(lin(a,b.t.turn(pi/2)),b);
}
pt sym(const pt &a,const lin &b)
{
    return pt(hangf(a,b)*2-a);
}

struct squ
{
    pt a;
    vec b1,b2;
    squ(pt a1,pt a2,pt a3,pt a4)
    {
        if(dcmp(a2.y-a1.y)<0||(dcmp(a2.y-a1.y)==0&&dcmp(a2.x-a1.x)<0)) swap(a1,a2);
        if(dcmp(a3.y-a1.y)<0||(dcmp(a3.y-a1.y)==0&&dcmp(a3.x-a1.x)<0)) swap(a1,a3);
        if(dcmp(a4.y-a1.y)<0||(dcmp(a4.y-a1.y)==0&&dcmp(a4.x-a1.x)<0)) swap(a1,a4);
        if(a1+a2==a3+a4) a=a1,b1=a3-a1,b2=a4-a1;
        else if(a1+a3==a2+a4) a=a1,b1=a2-a1,b2=a4-a1;
        else if(a1+a4==a2+a3) a=a1,b1=a2-a1,b2=a3-a1;
        if(dcmp(b1^b2)<0) swap(b1,b2);
    }
    ld area() const
    {
        return b1^b2;
    }
    ld len() const
    {
        return (b1.len()+b2.len())*2;
    }
};
bool operator<(const squ &a,const squ &b)
{
    return dcmp(a.area()-b.area())<0;
}

struct hp
{
    int n;
    lin *a=NULL;
    hp() {}
    hp(int _n):n(_n)
    {
        if(a!=NULL) delete[] a;
        a=new lin[n+3];
    }
    hp(int _n,lin *_a):n(_n)
    {
        if(a!=NULL) delete[] a;
        a=new lin[n+3];
        for(int i=1;i<=n;++i) a[i]=_a[i];
    }
    hp(const hp &p):n(p.n)
    {
        if(a!=NULL) delete[] a;
        a=new lin[n+3];
        for(int i=1;i<=n;++i) a[i]=p[i];
    }
    hp(const hp &&p):n(p.n),a(p.a) {}
    ~hp() {if(a!=NULL) delete[] a,a=NULL;}
    lin &operator[](const size_t pos) {return a[pos];}
    lin operator[](const size_t pos) const {return a[pos];}
    void input()
    {
        scanf("%d",&n);
        if(a!=NULL) delete[] a;
        a=new lin[n+3];
        for(int i=1;i<=n;++i) a[i].input();
    }
    void solve()
    {
        lin *b=new lin[n+1];
        for(int i=1;i<=n;++i) b[i]=a[i];
        int m=n;
        sort(b+1,b+m+1,[](lin a,lin b)
        {
            return atan2(a.t.y,a.t.x)<atan2(b.t.y,b.t.x);
        });
        int T=1,R=0;
        a[++R]=b[1];
        for(int i=2;i<=m;++i)
        {
            while(T<=R-1&&!b[i].onleft(inter(a[R-1],a[R]))) --R;
            while(T<=R-1&&!b[i].onleft(inter(a[T],a[T+1]))) ++T;
            a[++R]=b[i];
            if(T<=R-1&&dcmp(a[R].t^a[R-1].t)==0)
            {
                if(dcmp((a[R-1].a-a[R].a)^a[R].t)>=0&&dcmp(a[R-1].t*a[R].t)<0)
                {
                    n=0;
                    return;
                }
                if(dcmp(a[R-1].t*a[R].t)>0)
                {
                    if(dcmp((a[R-1].a-a[R].a)^a[R].t)>0) swap(a[R],a[R-1]);
                    --R;
                }
            }
        }
        while(T<=R-1&&!a[T].onleft(inter(a[R-1],a[R]))) --R;
        n=R-T+1;
        if(n<=2) n=0;
        for(int i=1;i<=n;++i)
        {
            a[i]=a[T+i-1];
        }
        a[n+1]=a[1];
        a[n+2]=a[2];
        delete[] b;
    }
    ld area()
    {
        ld s=0;
        a[n+1]=a[1];
        a[n+2]=a[2];
        for(int i=1;i<=n;++i)
        {
            s+=(inter(a[i],a[i+1])^inter(a[i+1],a[i+2]))/2;
        }
        return s;
    }
};

int n;
ld k;
pt a[N];
int main()
{
    while(~scanf("%d%Lf",&n,&k))
    {
        for(int i=1;i<=n;++i) a[i].input();
        a[n+1]=a[1];
        ld s=0;
        for(int i=1;i<=n;++i) s+=(a[i]^a[i+1])/2;
        ld l=0,r=k;
        while(r-l>1e-6)
        {
            ld z=(l+r)/2;
            hp p(n);
            for(int i=1;i<=n;++i) p[i]=lin(a[i]+(a[i+1]-a[i]).turn(pi/2).tolen(z),a[i+1]-a[i]);
            p.solve();
            if(p.area()<s/2) r=z;
            else l=z;
        }
        printf("%.3Lf\n",l);
    }
    return 0;
}