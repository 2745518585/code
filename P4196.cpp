#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps=1e-12,pi=acos(-1.0);
const int N=100001;
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
    point(double x0,double y0) {x=x0,y=y0;}
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
    line(point a0,vector b0) {a=a0,b=b0;}
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
double disPP(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
bool inL(line a,point b)
{
    return dcmp(cross(a.a-b,b))==0;
}
bool inS(segment a,point b)
{
    return dcmp(cross(a.a-b,a.b-b))==0&&dcmp(dot(a.a-b,a.b-b))<=0;
}
bool intSS(segment a,segment b)
{
    return dcmp(max(a.a.x,a.b.x)-min(b.a.x,b.b.x))>=0&&dcmp(max(b.a.x,b.b.x)-min(a.a.x,a.b.x))>=0
    &&dcmp(max(a.a.y,a.b.y)-min(b.a.y,b.b.y))>=0&&dcmp(max(b.a.y,b.b.y)-min(a.a.y,a.b.y))>=0
    &&dcmp(cross(b.a-a.a,b.b-a.a)*cross(b.a-a.b,b.b-a.b))<=0&&dcmp(cross(a.a-b.a,a.b-b.a)*cross(a.a-b.b,a.b-b.b))<=0;
}
point intLL(line a,line b)
{
    if(cross(a.b,b.b)==0) return point(0,0);
    return a.a+a.b-(cross((a.a+a.b)-(b.a+b.b),b.b)/cross(a.b,b.b))*a.b;
}
double angle(vector a,vector b)
{
    return acos(dot(a,b)/length(a)/length(b));
}
vector turnV(vector a,double b)
{
    return vector(a.x*cos(b)-a.y*sin(b),a.y*cos(b)+a.x*sin(b));
}
point turnP(point a,point b,double c)
{
    return point((a.x-b.x)*cos(c)-(a.y-b.y)*sin(c)+b.y,(a.y-b.y)*cos(c)+(a.x-b.x)*sin(c)+b.x);
}
bool onleftPL(point a,line b)
{
    return dcmp(cross(a-b.a,b.b))<0;
}
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
    static bool halfplane_cmp(line a,line b)
    {
        return atan2(a.b.y,a.b.x)<atan2(b.b.y,b.b.x);
    }
    void solve()
    {
        sort(b+1,b+m+1,halfplane_cmp);
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
}Halfplane;
int m,n,k;
line a[N];
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&k);
        point x,y,z;
        x.input();
        z=x;
        for(int j=2;j<=k;++j)
        {
            y.input();
            a[++n]=line(x,y-x);
            x=y;
        }
        a[++n]=line(x,z-x);
    }
    Halfplane.init(n,a);
    printf("%.3lf",Halfplane.area());
    return 0;
}