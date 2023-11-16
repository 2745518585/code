#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const long double eps=1e-12,pi=acos(-1.0);
const int N=100001;
int dcmp(long double x)
{
    if(fabs(x)<eps) return 0;
    if(x>0) return 1;
    return -1;
}
struct point
{
    long double x,y;
    point(){}
    point(long double x,long double y):x(x),y(y) {}
    friend point operator +(point a,point b)
    {
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator -(point a,point b)
    {
        return point(a.x-b.x,a.y-b.y);
    }
    friend point operator *(point a,long double b)
    {
        return point(a.x*b,a.y*b);
    }
    friend point operator *(long double b,point a)
    {
        return point(a.x*b,a.y*b);
    }
    friend point operator /(point a,long double b)
    {
        return point(a.x/b,a.y/b);
    }
    friend bool operator == (point a,point b)
    {
        return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
    }
    friend long double dot(point a,point b)
    {
        return a.x*b.x+a.y*b.y;
    }
    friend long double cross(point a,point b)
    {
        return a.x*b.y-a.y*b.x;
    }
    friend long double length(point a)
    {
        return sqrt(a.x*a.x+a.y*a.y);
    }
    void input()
    {
        scanf("%Lf%Lf",&x,&y);
    }
    void print()
    {
        if(dcmp(x)==0) x=0;
        if(dcmp(y)==0) y=0;
        printf("%.2Lf %.2Lf",x,y);
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
long double angle(vector a,vector b)
{
    return acos(dot(a,b)/length(a)/length(b));
}
long double disPP(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
long double disPL(point a,line b)
{
    return disPP(a,b.a)*fabs(sin(angle(a-b.a,b.b)));
}
bool inL(line a,point b)
{
    return dcmp(cross(a.a-b,a.b))==0;
}
bool inS(segment a,point b)
{
    return dcmp(cross(a.a-b,a.b-b))==0&&dcmp(dot(a.a-b,a.b-b))<=0;
}
bool onleftPL(point a,line b)
{
    return dcmp(cross(a-b.a,b.b))<0;
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
    return a.a+(cross(b.b,a.a-b.a)/cross(a.b,b.b))*a.b;
}
vector turnV(vector a,long double b)
{
    return vector(a.x*cos(b)-a.y*sin(b),a.y*cos(b)+a.x*sin(b));
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
    static bool cmp(point x,point y)
    {
        int z=dcmp(cross(x,y));
        return z>0||(z==0&&dcmp(disPP(x,point(0,0))-disPP(y,point(0,0)))<0);
    }
    void solve()
    {
        for(int i=2;i<=n;++i)
        {
            if(a[i].y<a[1].y||(a[i].y==a[1].y&&a[i].x<a[1].x)) swap(a[1],a[i]);
        }
        for(int i=2;i<=n;++i) a[i]=a[i]-a[1];
        sort(a+2,a+n+1,cmp);
        for(int i=2;i<=n;++i) a[i]=a[i]+a[1];
        a[n+1]=a[1];
        int z=n;
        n=1;
        for(int i=2;i<=z;++i)
        {
            while(n>1&&dcmp(cross(a[n]-a[n-1],a[i]-a[n]))<=0) --n;
            a[++n]=a[i];
        }
        a[n+1]=a[1];
    }
    long double area()
    {
        long double s=0;
        a[n+1]=a[1];
        for(int i=1;i<=n;++i)
        {
            s+=cross(a[i],a[i+1])/2;
        }
        return s;
    }
    long double length()
    {
        a[n+1]=a[1];
        long double s=0;
        for(int i=1;i<=n;++i)
        {
            s+=disPP(a[i],a[i+1]);
        }
        return s;
    }
    long double maxdis()
    {
        if(n==2) return disPP(a[1],a[2]);
        long double s=0;
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
polygon a;
int main()
{
    a.input();
    a.solve();
    bool u=true;
    for(int i=3;i<=a.n;++i)
    {
        if(!inL(line(a.a[1],a.a[2]-a.a[1]),a.a[i]))
        {
            u=false;
            break;
        }
    }
    if(u)
    {
        printf("0");
        return 0;
    }
    printf("%d\n",a.n);
    for(int i=1;i<=a.n;++i)
    {
        printf("%.0Lf %.0Lf\n",a.a[i].x,a.a[i].y);
    }
    return 0;
}