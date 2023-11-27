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
        x/=p,y/=p;
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
    }
    ld area()
    {
        ld s=0;
        a[n+1]=a[1];
        for(int i=1;i<=n;++i)
        {
            s+=(a[i]^a[i+1])/2;
        }
        return s;
    }
    ld len()
    {
        ld s=0;
        a[n+1]=a[1];
        for(int i=1;i<=n;++i)
        {
            s+=dis(a[i],a[i+1]);
        }
        return s;
    }
    ld maxdis()
    {
        if(n==2) return dis(a[1],a[2]);
        ld s=0;
        a[n+1]=a[1];
        for(int i=1,j=1;i<=n;++i)
        {
            while(dcmp((a[i+1]-a[i])^(a[j]-a[j+1]))<0) j=j%n+1;
            s=max(s,max(dis(a[i],a[j]),dis(a[i+1],a[j])));
            while(dcmp(angle(a[i+1]-a[i],a[j]-a[j+1]))==0)
            {
                j=j%n+1;
                s=max(s,max(dis(a[i],a[j]),dis(a[i+1],a[j])));
            }
        }
        return s;
    }
    squ minsquare()
    {
        squ s=squ(pt(0,0),pt(0,1e9),pt(1e9,0),pt(1e9,1e9));
        a[n+1]=a[1];
        for(int i=1,j1=2,j2=2,j3=2;i<=n;++i)
        {
            while(dcmp((a[i+1]-a[i])*(a[j2]-a[j2+1]))<0||dcmp((a[i+1]-a[i])^(a[j2]-a[j2+1]))<0) j2=j2%n+1;
            while(j1!=j2&&dcmp((a[j1+1]-a[j1])*(a[i+1]-a[i]))>0) j1=j1%n+1;
            while(j3!=i&&(dcmp((a[i+1]-a[i])^(a[j3]-a[j3+1]))<=0||dcmp((a[i+1]-a[i])*(a[j3+1]-a[j3]))<0)) j3=j3%n+1;
            lin p=lin(a[i],a[i+1]-a[i]),p1=lin(a[j1],p.t.turn(pi/2)),p2=lin(a[j2],p.t),p3=lin(a[j3],p.t.turn(pi/2));
            squ t=squ(inter(p,p1),inter(p1,p2),inter(p2,p3),inter(p3,p));
            s=min(s,t);
        }
        return s;
    }
};

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

struct dynamic_poly
{
    map<ld,ld> Map1,Map2;
    ld s=0;
    pt check(map<ld,ld>::iterator x)
    {
        return pt(x->first,x->second);
    }
    ld sum(const pt &x1,const pt &x2)
    {
        return (x1^x2)/2;
    }
    ld solve1(map<ld,ld>::iterator x)
    {
        ld s=0;
        if(x!=Map1.begin()&&next(x)!=Map1.end()) s-=sum(check(next(x)),check(prev(x)));
        if(x!=Map1.begin()) s+=sum(check(x),check(prev(x)));
        if(next(x)!=Map1.end()) s+=sum(check(next(x)),check(x));
        return s;
    }
    ld solve2(map<ld,ld>::iterator x)
    {
        ld s=0;
        if(x!=Map2.begin()&&next(x)!=Map2.end()) s-=sum(check(prev(x)),check(next(x)));
        if(x!=Map2.begin()) s+=sum(check(prev(x)),check(x));
        if(next(x)!=Map2.end()) s+=sum(check(x),check(next(x)));
        return s;
    }
    bool check1(pt x)
    {
        map<ld,ld>::iterator p1=Map1.lower_bound(x.x);
        if(p1==Map1.end()) return false;
        if(dcmp((p1->first)-x.x)==0) return dcmp(x.y-(p1->second))<=0;
        if(p1==Map1.begin()) return false;
        map<ld,ld>::iterator p2=p1;
        --p2;
        return dcmp((check(p1)-check(p2))^(x-check(p2)))<=0;
    }
    bool check2(pt x)
    {
        map<ld,ld>::iterator p1=Map2.lower_bound(x.x);
        if(p1==Map2.end()) return false;
        if(dcmp((p1->first)-x.x)==0) return dcmp(x.y-(p1->second))>=0;
        if(p1==Map2.begin()) return false;
        map<ld,ld>::iterator p2=p1;
        --p2;
        return dcmp((check(p1)-check(p2))^(x-check(p2)))>=0;
    }
    bool remove1(map<ld,ld>::iterator p1)
    {
        if(p1==Map1.begin()) return false;
        map<ld,ld>::iterator p2=p1,p3=p1;
        --p2;
        ++p3;
        if(p3==Map1.end()) return false;
        if(dcmp((check(p1)-check(p2))^(check(p3)-check(p2)))>=0)
        {
            s-=solve1(p1);
            Map1.erase(p1);
            return true;
        }
        return false;
    }
    bool remove2(map<ld,ld>::iterator p1)
    {
        if(p1==Map2.begin()) return false;
        map<ld,ld>::iterator p2=p1,p3=p1;
        --p2;
        ++p3;
        if(p3==Map2.end()) return false;
        if(dcmp((check(p1)-check(p2))^(check(p3)-check(p2)))<=0)
        {
            s-=solve2(p1);
            Map2.erase(p1);
            return true;
        }
        return false;
    }
    void add1(pt x)
    {
        if(check1(x)) return;
        if(Map1.count(x.x)) s-=solve1(Map1.find(x.x));
        Map1[x.x]=x.y;
        map<ld,ld>::iterator p1=Map1.find(x.x),p2=p1;
        s+=solve1(p1);
        if(p1!=Map1.begin())
        {
            --p2;
            while(remove1(p2++)) --p2;
        }
        if(++p2!=Map1.end())
        {
            while(remove1(p2--)) ++p2;
        }
    }
    void add2(pt x)
    {
        if(check2(x)) return;
        if(Map2.count(x.x)) s-=solve2(Map2.find(x.x));
        Map2[x.x]=x.y;
        map<ld,ld>::iterator p1=Map2.find(x.x),p2=p1;
        s+=solve2(p1);
        if(p1!=Map2.begin())
        {
            --p2;
            while(remove2(p2++)) --p2;
        }
        if(++p2!=Map2.end())
        {
            while(remove2(p2--)) ++p2;
        }
    }
    ld query()
    {
        return s+sum(check(Map1.begin()),check(Map2.begin()))+sum(check(prev(Map2.end())),check(prev(Map1.end())));
    }
};

struct cir
{
    pt o;
    ld r;
    cir(){}
    cir(const pt &o,const ld &r):o(o),r(r) {}
    cir(const pt &x,const pt &y)
    {
        o=pt((x+y)/2);
        r=dis(x,y)/2;
    }
    cir(const pt &x,const pt &y,const pt &z)
    {
        o=inter(lin(pt((x+y)/2),(y-x).turn(pi/2)),lin(pt((x+z)/2),(z-x).turn(pi/2)));
        r=dis(o,x);
    }
    void input()
    {
        o.input();
        scanf("%Lf",&r);
    }
    bool inc(const pt &a) const
    {
        return dcmp(r-dis(a,o))>=0;
    }
};
cir min_cir_coverage(int n,const pt *a)
{
    cir s=cir(pt(0,0),0);
    for(int i=1;i<=n;++i)
    {
        if(s.inc(a[i])) continue;
        s=cir(a[i],0);
        for(int j=1;j<=i-1;++j)
        {
            if(s.inc(a[j])) continue;
            s=cir(a[i],a[j]);
            for(int k=1;k<=j-1;++k)
            {
                if(s.inc(a[k])) continue;
                s=cir(a[i],a[j],a[k]);
            }
        }
    }
    return s;
}

int main()
{
    
    return 0;
}