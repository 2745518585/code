#include<cstdio>
#include<algorithm>
#include<cmath>
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
};

pt::pt() {}
pt::pt(const ld &_x,const ld &_y):x(_x),y(_y) {}
pt::pt(const vec &p):x(p.x),y(p.y) {}
vec::vec() {}
vec::vec(const ld &_x,const ld &_y):x(_x),y(_y) {}
vec::vec(const pt &p):x(p.x),y(p.y) {}

pt operator+(const pt &a,const vec &b) {return pt(a.x+b.x,a.y+b.y);}
vec operator+(const vec &a,const vec &b) {return vec(a.x+b.x,a.y+b.y);}
vec operator-(const pt &a,const pt &b) {return vec(a.x-b.x,a.y-b.y);}
pt operator-(const pt &a,const vec &b) {return pt(a.x-b.x,a.y-b.y);}
vec operator-(const vec &a,const vec &b) {return vec(a.x-b.x,a.y-b.y);}
vec operator*(const vec &a,const ld &b) {return vec(a.x*b,a.y*b);}
vec operator*(const ld &b,const vec &a) {return vec(a.x*b,a.y*b);}
ld operator*(const vec &a,const vec &b) {return a.x*b.x+a.y*b.y;}
ld operator^(const vec &a,const vec &b) {return a.x*b.y-a.y*b.x;}

struct lin
{
    pt a;
    vec t;
    lin() {}
    lin(const pt &_a,const vec _t):a(_a),t(_t) {}
    void input()
    {
        a.input(),t.input();
    }
    bool inc(const pt &x)
    {
        return dcmp((x-a)^t)==0;
    }
    bool onleft(const pt &x)
    {
        return dcmp((x-a)^t)<0;
    }
    bool onright(const pt &x)
    {
        return dcmp((x-a)^t)>0;
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
pt inter(const lin &a,const lin &b)
{
    if(dcmp(a.t^b.t)==0) return pt(0,0);
    return a.a+((b.t^(a.a-b.a))/(a.t^b.t))*a.t;
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
    hp(int _n,const lin *_a):n(_n)
    {
        if(a!=NULL) delete[] a;
        a=new lin[n+3];
        for(int i=1;i<=n;++i) a[i]=_a[i];
    }
    void input()
    {
        scanf("%d",&n);
        if(a!=NULL) delete[] a;
        a=new lin[n+3];
        for(int i=1;i<=n;++i) a[i].input();
    }
    lin &operator[](size_t pos) {return a[pos];}
    lin operator[](size_t pos) const {return a[pos];}
    void solve()
    {
        lin *b=new lin[n+3];
        for(int i=1;i<=n;++i) b[i]=a[i];
        int m=n;
        sort(b+1,b+m+1,[](const lin &a,const lin &b)
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
                    if(dcmp((a[R-1].a-a[R].a)^a[R].t)>0) swap(a[R-1],a[R]);
                    --R;
                }
            }
        }
        while(T<=R-1&&!a[T].onleft(inter(a[R-1],a[R]))) --R;
        n=R-T+1;
        if(n<=2) n=0;
        for(int i=1;i<=n;++i) a[i]=a[i+T-1];
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

int m,n;
lin a[N];
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int k;
        scanf("%d",&k);
        pt x,y,z;
        x.input();
        z=x;
        for(int j=2;j<=k;++j)
        {
            y.input();
            a[++n]=lin(x,y-x);
            x=y;
        }
        a[++n]=lin(x,z-x);
    }
    hp x(n,a);
    x.solve();
    printf("%.3Lf",x.area());
    return 0;
}