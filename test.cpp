#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#include<map>
using namespace std;
typedef long double ld;
const ld eps=1e-12,pi=acos(-1.0);
const int N=201;
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
    vec turn(ld b) const
    {
        return vec(x*cos(b)-y*sin(b),y*cos(b)+x*sin(b));
    }
    vec &resize(ld p)
    {
        p/=len();
        x*=p,y*=p;
        return *this;
    }
    ld angle()
    {
        return atan2(y,x);
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
pt sym(const pt &a,const lin &b)
{
    return pt(inter(lin(a,b.t.turn(pi/2)),b)*2-a);
}

int n,m,f[N],g[N][N],h[N];
pt a[N];
struct str
{
    int x,y;
};
bool cmp(const str &x,const str &y)
{
    return lin(seg(a[x.y],a[x.x])).t.angle()<lin(seg(a[y.y],a[y.x])).t.angle();
}
int main()
{
    scanf("%d%d",&m,&n);
    n+=m+1;
    for(int i=2;i<=m+1;++i) a[i].input(),h[i]=1;
    for(int i=m+2;i<=n;++i) a[i].input(),h[i]=-1;
    a[1]=pt(0,0);
    vector<str> p;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            for(int k=1;k<=n;++k)
            {
                if(j==1) {if(!lin(seg(pt(0,0),a[i])).onright(a[k])&&!lin(seg(a[i],a[j])).onright(a[k])) g[i][j]+=h[k];}
                else {if(!lin(seg(pt(0,0),a[i])).onright(a[k])&&!lin(seg(a[i],a[j])).onright(a[k])&&lin(seg(a[j],pt(0,0))).onleft(a[k])) g[i][j]+=h[k];}
            }
            // printf("%d %d %d\n",i,j,g[i][j]);
            p.push_back({i,j});
        }
    }
    sort(p.begin(),p.end(),cmp);
    for(int i=1;i<=n;++i) f[i]=-1e9;
    f[1]=0;
    for(auto i:p)
    {
        f[i.y]=max(f[i.y],f[i.x]+g[i.x][i.y]);
        // printf("%d %d %d\n",i.x,i.y,g[i.x][i.y]);
        // for(int j=1;j<=n;++j) printf("%d ",f[j]);printf("\n");
    }
    printf("%d",f[1]);
    return 0;
}