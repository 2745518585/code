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
    return -1;
}
struct point
{
    ld x,y;
    point(){}
    point(ld x0,ld y0) {x=x0,y=y0;}
    friend point operator +(point a,point b)
    {
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator -(point a,point b)
    {
        return point(a.x-b.x,a.y-b.y);
    }
    friend point operator *(point a,ld b)
    {
        return point(a.x*b,a.y*b);
    }
    friend point operator *(ld b,point a)
    {
        return point(a.x*b,a.y*b);
    }
    friend point operator /(point a,ld b)
    {
        return point(a.x/b,a.y/b);
    }
    friend bool operator == (point a,point b)
    {
        return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
    }
    friend ld dot(point a,point b)
    {
        return a.x*b.x+a.y*b.y;
    }
    friend ld cross(point a,point b)
    {
        return a.x*b.y-a.y*b.x;
    }
    friend ld length(point a)
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
ld angle(vector a,vector b)
{
    return acos(dot(a,b)/length(a)/length(b));
}
ld disPP(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
ld disPL(point a,line b)
{
    return disPP(a,b.a)*fabs(sin(angle(a-b.a,b.b)));
}
bool inL(line a,point b)
{
    return dcmp(cross(a.a-b,b))==0;
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
vector turnV(vector a,ld b)
{
    return vector(a.x*cos(b)-a.y*sin(b),a.y*cos(b)+a.x*sin(b));
}
point turnP(point a,point b,ld c)
{
    return point((a.x-b.x)*cos(c)-(a.y-b.y)*sin(c)+b.y,(a.y-b.y)*cos(c)+(a.x-b.x)*sin(c)+b.x);
}
int n;
point a[N];
int main()
{
    while(~scanf("%Lf%Lf",&a[0].x,&a[0].y))
    {
        scanf("%d",&n);
        for(int i=1;i<=n+1;++i) a[i].input();
        ld s=1e9;
        point q;
        for(int i=1;i<=n;++i)
        {
            if(dcmp(dot(a[0]-a[i],a[i+1]-a[i]))<=0)
            {
                if(disPP(a[0],a[i])<s) s=disPP(a[0],a[i]),q=a[i];
            }
            else if(dcmp(dot(a[0]-a[i+1],a[i]-a[i+1]))<=0)
            {
                if(disPP(a[0],a[i+1])<s) s=disPP(a[0],a[i+1]),q=a[i+1];
            }
            else
            {
                if(disPL(a[0],line(a[i],a[i+1]-a[i]))<s) s=disPL(a[0],line(a[i],a[i+1]-a[i])),q=intLL(line(a[0],turnV(a[i+1]-a[i],pi/2)),line(a[i],a[i+1]-a[i]));
            }
        }
        printf("%.4Lf\n%.4Lf\n",q.x,q.y);
    }
    return 0;
}