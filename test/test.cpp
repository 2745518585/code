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
    ld len2() const {return x*x+y*y;}
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
ld dis2(const pt &a,const pt &b)
{
    return (a-b).len2();
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

ld x,y,z,a,b,c;
ld solve(const ld &a,const ld &b,const ld &c)
{
    printf("%.6Lf %.6Lf %.6Lf\n",a,b,c);
    return b*(a*a+b*b-c*c)/(a*b*2);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%Lf%Lf%Lf%Lf%Lf%Lf",&x,&y,&z,&a,&b,&c);
        ld p=acos((a*a+b*b-c*c)/(a*b*2));
        pt A(b*cos(p),b*sin(p)),B(a,0),C(0,0);
        printf("%.6Lf %.6Lf %.6Lf %.6Lf %.6Lf %.6Lf\n",A.x,A.y,B.x,B.y,C.x,C.y);
        ld t1=x*((x*x+c*c-y*y)/(x*c*2)),t2=x*((x*x+b*b-z*z)/(x*b*2));
        printf("%.6Lf %.6Lf\n",t1,t2);
        pt O=inter(lin(A+(B-A).tolen(t1),(B-A).turn(pi/2)),lin(A+(C-A).tolen(t2),(C-A).turn(pi/2)));
        printf("%.6Lf %.6Lf\n",O.x,O.y);
        pt S=inter(seg(B,pt((A+C)/2)),seg(C,pt((A+B)/2)));
        printf("%.6Lf %.6Lf\n",S.x,S.y);
        ld d=sqrtl(x*x-dis2(O,A)+dis2(O,S));
        printf("%.6Lf\n",d);
        if(dis(A,S)>x||dis(B,S)>y||dis(C,S)>z)
        {
            if(x<=y&&x<=z)
            {
                if(x*x+c*c>y*y&&x*x+b*b>z*z)
                {
                    printf("%.12Lf %.12Lf %.12Lf\n",-x,-solve(dis(A,S),c,dis(B,S))-x,-solve(dis(A,S),b,dis(C,S))-x);
                    continue;
                }
                else if(x*x+b*b>z*z)
                {
                    printf("%.12Lf %.12Lf %.12Lf\n",-x,-y,-dis(C,S));
                }
            }
        }
        printf("%.12Lf %.12Lf %.12Lf\n",-solve(d,x,dis(A,S)),-solve(d,y,dis(B,S)),-solve(d,z,dis(C,S)));
    }
    return 0;
}