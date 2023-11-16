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
    point(long double x0,long double y0) {x=x0,y=y0;}
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
        printf("%.5Lf %.5Lf",x,y);
    }
};
typedef point vector;
struct line
{
    point a;
    vector b;
    line(){}
    line(point a0,vector b0) {a=a0,b=b0;}
};
struct segment
{
    point a,b;
    segment(){}
    segment(point a,point b):a(a),b(b){}
};
long double disPP(point a,point b)
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
    return a.a+a.b-(cross((a.a+a.b)-(b.a+b.b),b.b)/cross(a.b,b.b))*a.b;
}
long double angle(vector a,vector b)
{
    return acos(dot(a,b)/length(a)/length(b));
}
vector turnV(vector a,long double b)
{
    return vector(a.x*cos(b)-a.y*sin(b),a.y*cos(b)+a.x*sin(b));
}
point turnP(point a,point b,long double c)
{
    return point((a.x-b.x)*cos(c)-(a.y-b.y)*sin(c)+b.y,(a.y-b.y)*cos(c)+(a.x-b.x)*sin(c)+b.x);
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
        if(dcmp(length(a.b1)*length(a.b2)-length(b.b1)*length(b.b2))<=0) return a;
        return b;
    }
};
bool polygon_cmp(point a,point b);
struct polygon
{
    int n;
    point a[N];
    void init(int n0,point a0[])
    {
        n=n0;
        for(int i=1;i<=n;++i) a[i]=a0[i];
        solve();
    }
    void input()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) a[i].input();
        solve();
    }
    void solve()
    {
        for(int i=2;i<=n;++i)
        {
            if(a[i].y<a[1].y||(a[i].y==a[1].y&&a[i].x<a[1].x))
            {
                swap(a[1],a[i]);
            }
        }
        sort(a+2,a+n+1,polygon_cmp);
        a[n+1]=a[1];
    }
}Polygon;
bool polygon_cmp(point x,point y)
{
    int z=dcmp(cross(x-Polygon.a[1],y-Polygon.a[1]));
    return z>0||(z==0&&dcmp(disPP(x,Polygon.a[1])-disPP(y,Polygon.a[1]))<0);
}
long double areaPo(polygon a)
{
    long double s=0;
    a.a[a.n+1]=a.a[1];
    for(int i=1;i<=a.n;++i)
    {
        s+=cross(a.a[i]-point(0,0),a.a[i+1]-point(0,0))/2;
    }
    return s;
}
struct convex
{
    int n,k;
    point a[N],b[N];
    long double solve(polygon a0)
    {
        n=a0.n;
        for(int i=1;i<=n;++i) a[i]=a0.a[i];
        k=0;
        b[++k]=a[1];
        for(int i=2;i<=n;++i)
        {
            while(k>1&&dcmp(cross(b[k]-b[k-1],a[i]-b[k]))<=0) --k;
            b[++k]=a[i];
        }
        b[k+1]=a[1];
        long double s=0;
        for(int i=1;i<=k;++i)
        {
            s+=disPP(b[i],b[i+1]);
        }
        return s;
    }
    long double maxdis()
    {
        if(k==2) return disPP(b[1],b[2]);
        long double s=0;
        for(int i=1,j=1;i<=k;++i)
        {
            while(dcmp(dot(b[i+1]-b[i],b[j]-b[j+1]))<0||dcmp(cross(b[i+1]-b[i],b[j]-b[j+1]))<0) j=j%k+1;
            s=max(s,max(disPP(b[i],b[j]),disPP(b[i+1],b[j])));
            while(dcmp(angle(b[i+1]-b[i],b[j]-b[j+1]))==0)
            {
                j=j%k+1;
                s=max(s,max(disPP(b[i],b[j]),disPP(b[i+1],b[j])));
            }
        }
        return s;
    }
    square minsquare()
    {
        square s=square(point(0,0),point(0,1e9),point(1e9,0),point(1e9,1e9));
        for(int i=1,j1=1,j2=1,j3=1;i<=k;++i)
        {
            while(dcmp(dot(b[j1+1]-b[j1],b[i+1]-b[i]))>0) j1=j1%k+1;
            while(dcmp(dot(b[i+1]-b[i],b[j2]-b[j2+1]))<0||dcmp(cross(b[i+1]-b[i],b[j2]-b[j2+1]))<0) j2=j2%k+1;
            while(dcmp(cross(b[i+1]-b[i],b[j3]-b[j3+1]))<=0||dcmp(dot(b[i+1]-b[i],b[j3+1]-b[j3]))<0) j3=j3%k+1;
            line p=line(b[i],b[i+1]-b[i]),p1=line(b[j1],turnV(p.b,pi/2)),p2=line(b[j2],p.b),p3=line(b[j3],turnV(p.b,pi/2));
            square t=square(intLL(p,p1),intLL(p1,p2),intLL(p2,p3),intLL(p3,p));
            s=min(s,t);
        }
        return s;
    }
}Convex;
int main()
{
    Polygon.input();
    Convex.solve(Polygon);
    square t=Convex.minsquare();
    printf("%.5Lf\n",length(t.b1)*length(t.b2));
    t.a.print();
    printf("\n");
    (t.a+t.b1).print();
    printf("\n");
    (t.a+t.b1+t.b2).print();
    printf("\n");
    (t.a+t.b2).print();
    return 0;
}