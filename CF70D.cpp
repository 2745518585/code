#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
const double eps=1e-12,pi=acos(-1.0);
const int N=1000001;
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    if(x>0) return 1;
    return -1;
}
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y) {}
    friend point operator +(point a,point b)
    {
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator -(point a,point b)
    {
        return point(a.x-b.x,a.y-b.y);
    }
    friend point operator *(point a,double b)
    {
        return point(a.x*b,a.y*b);
    }
    friend point operator *(double b,point a)
    {
        return point(a.x*b,a.y*b);
    }
    friend point operator /(point a,double b)
    {
        return point(a.x/b,a.y/b);
    }
    friend bool operator == (point a,point b)
    {
        return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
    }
    friend double dot(point a,point b)
    {
        return a.x*b.x+a.y*b.y;
    }
    friend double cross(point a,point b)
    {
        return a.x*b.y-a.y*b.x;
    }
    friend double length(point a)
    {
        return sqrt(a.x*a.x+a.y*a.y);
    }
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    void print()
    {
        if(dcmp(x)==0) x=0;
        if(dcmp(y)==0) y=0;
        printf("%.2lf %.2lf",x,y);
    }
};
typedef point vector;
struct line
{
    point a;
    vector b;
    line(){}
    line(point a,vector b):a(a),b(b){}
    void input()
    {
        a.input(),b.input();
        b=b-a;
    }
    void print()
    {
        a.print();
        printf(" ");
        (a+b).print();
    }
};
struct segment
{
    point a,b;
    segment(){}
    segment(point a,point b):a(a),b(b){}
};
double angle(vector a,vector b)
{
    return acos(dot(a,b)/length(a)/length(b));
}
double disPP(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double disPL(point a,line b)
{
    return disPP(a,b.a)*fabs(sin(angle(a-b.a,b.b)));
}
bool inL(point a,line b)
{
    return dcmp(cross(b.a-a,b.b))==0;
}
bool inS(point a,segment b)
{
    return dcmp(cross(b.a-a,b.b-a))==0&&dcmp(dot(b.a-a,b.b-a))<=0;
}
bool onleftPL(point a,line b)
{
    return dcmp(cross(a-b.a,b.b))<0;
}
bool intSS(segment a,segment b)
{
    if(dcmp(cross(a.b-a.a,b.b-b.a))==0) return false;
    return dcmp(max(a.a.x,a.b.x)-min(b.a.x,b.b.x))>=0&&dcmp(max(b.a.x,b.b.x)-min(a.a.x,a.b.x))>=0
    &&dcmp(max(a.a.y,a.b.y)-min(b.a.y,b.b.y))>=0&&dcmp(max(b.a.y,b.b.y)-min(a.a.y,a.b.y))>=0
    &&dcmp(cross(b.a-a.a,b.b-a.a)*cross(b.a-a.b,b.b-a.b))<=0&&dcmp(cross(a.a-b.a,a.b-b.a)*cross(a.a-b.b,a.b-b.b))<=0;
}
point intLL(line a,line b)
{
    if(dcmp(cross(a.b,b.b))==0) return point(0,0);
    return a.a+(cross(b.b,a.a-b.a)/cross(a.b,b.b))*a.b;
}
vector turnV(vector a,double b)
{
    return vector(a.x*cos(b)-a.y*sin(b),a.y*cos(b)+a.x*sin(b));
}
point symPL(point a,line b)
{
    return intLL(line(a,turnV(b.b,pi/2)),b)*2-a;
}
struct square
{
    point a;
    vector b1,b2;
    square(point a1,point a2,point a3,point a4)
    {
        if(dcmp(a2.y-a1.y)<0||(dcmp(a2.y-a1.y)==0&&dcmp(a2.x-a1.x)<0)) swap(a1,a2);
        if(dcmp(a3.y-a1.y)<0||(dcmp(a3.y-a1.y)==0&&dcmp(a3.x-a1.x)<0)) swap(a1,a3);
        if(dcmp(a4.y-a1.y)<0||(dcmp(a4.y-a1.y)==0&&dcmp(a4.x-a1.x)<0)) swap(a1,a4);
        if(a1+a2==a3+a4) a=a1,b1=a3-a1,b2=a4-a1;
        else if(a1+a3==a2+a4) a=a1,b1=a2-a1,b2=a4-a1;
        else if(a1+a4==a2+a3) a=a1,b1=a2-a1,b2=a3-a1;
        if(dcmp(cross(b1,b2))<0) swap(b1,b2);
    }
    friend square min(square a,square b)
    {
        if(dcmp(cross(a.b1,a.b2)-cross(b.b1,b.b2))<=0) return a;
        return b;
    }
};
struct polygon
{
    int n;
    point a[N];
    void init(int m,point b[])
    {
        n=m;
        for(int i=1;i<=n;++i) a[i]=b[i];
    }
    void input()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) a[i].input();
    }
    static bool cmp(point a,point b)
    {
        if(a.x!=b.x) return a.x<b.x;
        return a.y<b.y;
    }
    void solve()
    {
        if(n<=2) return;
        point b[N];
        for(int i=1;i<=n;++i) b[i]=a[i];
        sort(b+1,b+n+1,cmp);
        int m=n;
        a[0]=b[1],a[1]=b[2];
        n=1;
        for(int i=3;i<=m;++i)
        {
            while(n>=1&&dcmp(cross(a[n]-a[n-1],b[i]-a[n]))<0) --n;
            a[++n]=b[i];
        }
        a[++n]=b[m-1];
        for(int i=m-2;i>=1;--i)
        {
            while(n>=1&&dcmp(cross(a[n]-a[n-1],b[i]-a[n]))<0) --n;
            a[++n]=b[i];
        }
        a[n+1]=a[1];
    }
    double area()
    {
        double s=0;
        a[n+1]=a[1];
        for(int i=1;i<=n;++i)
        {
            s+=cross(a[i],a[i+1])/2;
        }
        return s;
    }
    double length()
    {
        a[n+1]=a[1];
        double s=0;
        for(int i=1;i<=n;++i)
        {
            s+=disPP(a[i],a[i+1]);
        }
        return s;
    }
    map<int,int> Map1,Map2;
    bool check1(point x)
    {
        map<int,int>::iterator p1=Map1.lower_bound(x.x);
        if(p1==Map1.end()) return false;
        if(dcmp((p1->first)-x.x)==0) return dcmp(x.y-(p1->second))<=0;
        if(p1==Map1.begin()) return false;
        map<int,int>::iterator p2=p1;
        --p2;
        return dcmp(cross(point(p1->first,p1->second)-point(p2->first,p2->second),x-point(p2->first,p2->second)))<=0;
    }
    bool check2(point x)
    {
        map<int,int>::iterator p1=Map2.lower_bound(x.x);
        if(p1==Map2.end()) return false;
        if(dcmp((p1->first)-x.x)==0) return dcmp(x.y-(p1->second))>=0;
        if(p1==Map2.begin()) return false;
        map<int,int>::iterator p2=p1;
        --p2;
        return dcmp(cross(point(p1->first,p1->second)-point(p2->first,p2->second),x-point(p2->first,p2->second)))>=0;
    }
    bool remove1(map<int,int>::iterator p1)
    {
        if(p1==Map1.begin()) return false;
        map<int,int>::iterator p2=p1,p3=p1;
        --p2;
        ++p3;
        if(p3==Map1.end()) return false;
        if(dcmp(cross(point(p1->first,p1->second)-point(p2->first,p2->second),point(p3->first,p3->second)-point(p2->first,p2->second)))>=0)
        {
            Map1.erase(p1);
            return true;
        }
        return false;
    }
    bool remove2(map<int,int>::iterator p1)
    {
        if(p1==Map2.begin()) return false;
        map<int,int>::iterator p2=p1,p3=p1;
        --p2;
        ++p3;
        if(p3==Map2.end()) return false;
        if(dcmp(cross(point(p1->first,p1->second)-point(p2->first,p2->second),point(p3->first,p3->second)-point(p2->first,p2->second)))<=0)
        {
            Map2.erase(p1);
            return true;
        }
        return false;
    }
    void add1(point x)
    {
        if(check1(x)) return;
        Map1[x.x]=x.y;
        map<int,int>::iterator p1=Map1.find(x.x),p2=p1;
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
    void add2(point x)
    {
        if(check2(x)) return;
        Map2[x.x]=x.y;
        map<int,int>::iterator p1=Map2.find(x.x),p2=p1;
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
    double maxdis()
    {
        if(n==2) return disPP(a[1],a[2]);
        double s=0;
        for(int i=1,j=1;i<=n;++i)
        {
            while(dcmp(dot(a[i+1]-a[i],a[j]-a[j+1]))<0||dcmp(cross(a[i+1]-a[i],a[j]-a[j+1]))<0) j=j%n+1;
            s=max(s,max(disPP(a[i],a[j]),disPP(a[i+1],a[j])));
            while(dcmp(angle(a[i+1]-a[i],a[j]-a[j+1]))==0)
            {
                j=j%n+1;
                s=max(s,max(disPP(a[i],a[j]),disPP(a[i+1],a[j])));
            }
        }
        return s;
    }
    square minsquare()
    {
        square s=square(point(0,0),point(0,1e9),point(1e9,0),point(1e9,1e9));
        for(int i=1,j1=1,j2=1,j3=1;i<=n;++i)
        {
            while(dcmp(dot(a[j1+1]-a[j1],a[i+1]-a[i]))>0) j1=j1%n+1;
            while(dcmp(dot(a[i+1]-a[i],a[j2]-a[j2+1]))<0||dcmp(cross(a[i+1]-a[i],a[j2]-a[j2+1]))<0) j2=j2%n+1;
            while(dcmp(cross(a[i+1]-a[i],a[j3]-a[j3+1]))<=0||dcmp(dot(a[i+1]-a[i],a[j3+1]-a[j3]))<0) j3=j3%n+1;
            line p=line(a[i],a[i+1]-a[i]),p1=line(a[j1],turnV(p.b,pi/2)),p2=line(a[j2],p.b),p3=line(a[j3],turnV(p.b,pi/2));
            square t=square(intLL(p,p1),intLL(p1,p2),intLL(p2,p3),intLL(p3,p));
            s=min(s,t);
        }
        return s;
    }
};
struct halfplane
{
    int m,n;
    line a[N],b[N];
    void init(int n0,line a0[])
    {
        m=n0;
        for(int i=1;i<=m;++i) b[i]=a0[i];
        solve();
    }
    void input()
    {
        scanf("%d",&m);
        for(int i=1;i<=m;++i) b[i].input();
        solve();
    }
    static bool cmp(line a,line b)
    {
        return atan2(a.b.y,a.b.x)<atan2(b.b.y,b.b.x);
    }
    void solve()
    {
        sort(b+1,b+m+1,cmp);
        int T=1,R=0;
        a[++R]=b[1];
        for(int i=2;i<=m;++i)
        {
            while(T<=R-1&&!onleftPL(intLL(a[R-1],a[R]),b[i])) --R;
            while(T<=R-1&&!onleftPL(intLL(a[T],a[T+1]),b[i])) ++T;
            a[++R]=b[i];
            if(T<=R-1&&dcmp(cross(a[R].b,a[R-1].b))==0)
            {
                if(dcmp(cross(a[R-1].a-a[R].a,a[R].b))>=0&&dcmp(dot(a[R-1].b,a[R].b))<0)
                {
                    n=0;
                    return;
                }
                if(dcmp(dot(a[R-1].b,a[R].b))>0)
                {
                    if(dcmp(cross(a[R-1].a-a[R].a,a[R].b))>0) swap(a[R],a[R-1]);
                    --R;
                }
            }
        }
        while(T<=R-1&&!onleftPL(intLL(a[R-1],a[R]),a[T])) --R;
        n=R-T+1;
        if(n<=2) n=0;
        for(int i=1;i<=n;++i)
        {
            a[i]=a[T+i-1];
        }
        a[n+1]=a[1];
        a[n+2]=a[2];
    }
    double area()
    {
        double s=0;
        a[n+1]=a[1];
        a[n+2]=a[2];
        for(int i=1;i<=n;++i)
        {
            s+=cross(intLL(a[i],a[i+1]),intLL(a[i+1],a[i+2]))/2;
        }
        return s;
    }
};
struct circle
{
    point o;
    double r;
    circle(){}
    circle(point o,double r):o(o),r(r) {}
    void init(point x,point y)
    {
        o=(x+y)/2;
        r=disPP(x,y)/2;
    }
    void init(point x,point y,point z)
    {
        o=intLL(line((x+y)/2,turnV(y-x,pi/2)),line((x+z)/2,turnV(z-x,pi/2)));
        r=disPP(o,x);
    }
};
bool inC(point a,circle b)
{
    return dcmp(b.r-disPP(a,b.o))>=0;
}
circle min_circle_coverage(int n,point a[])
{
    circle s=circle(point(0,0),0);
    for(int i=1;i<=n;++i)
    {
        if(inC(a[i],s)) continue;
        s=circle(a[i],0);
        for(int j=1;j<=i-1;++j)
        {
            if(inC(a[j],s)) continue;
            s.init(a[i],a[j]);
            for(int k=1;k<=j-1;++k)
            {
                if(inC(a[k],s)) continue;
                s.init(a[i],a[j],a[k]);
            }
        }
    }
    return s;
}
int m;
polygon a;
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int z;
        point x;
        scanf("%d",&z);
        x.input();
        if(z==1) a.add1(x),a.add2(x);
        else
        {
            if(a.check1(x)&&a.check2(x)) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}