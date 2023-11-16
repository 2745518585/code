#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps=1e-5,pi=acos(-1.0);
const int N=10;
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
    if(cross(a.b,b.b)==0) return point(1e9,1e9);
    return a.a+(cross(b.b,a.a-b.a)/cross(a.b,b.b))*a.b;
}
vector turnV(vector a,double b)
{
    return vector(a.x*cos(b)-a.y*sin(b),a.y*cos(b)+a.x*sin(b));
}
point turnP(point a,point b,double c)
{
    return point((a.x-b.x)*cos(c)-(a.y-b.y)*sin(c)+b.y,(a.y-b.y)*cos(c)+(a.x-b.x)*sin(c)+b.x);
}
int q;
double m,n,f[1<<N];
point a[N],b[N];
void check(line a,line b,point &q1,point &q2)
{
    point x=intLL(a,b);
    if(dcmp(x.x-m)>0||dcmp(x.x)<0||dcmp(x.y-n)>0||dcmp(x.y)<0) return;
    if(dcmp(dot(x-a.a,a.b))<=0)
    {
        if(disPP(a.a,x)<disPP(a.a,q1)) q1=x;
    }
    else
    {
        if(disPP(a.a,x)<disPP(a.a,q2)) q2=x;
    }
}
int main()
{
    scanf("%lf%lf%d",&m,&n,&q);
    for(int i=1;i<=q;++i) a[i].input();
    a[q+1]=a[1];
    b[1]=b[5]=point(0,0);
    b[2]=point(m,0);
    b[3]=point(m,n);
    b[4]=point(0,n);
    for(int i=0;i<=(1<<q)-1;++i) f[i]=1e9;
    f[0]=0;
    for(int i=0;i<=(1<<q)-1;++i)
    {
        for(int j=1;j<=q;++j)
        {
            if((i&(1<<(j-1)))!=0) continue;
            point q1(1e9,1e9),q2(1e9,1e9);
            for(int k=1;k<=q;++k)
            {
                if((i&(1<<(k-1)))!=0) check(line(a[j],a[j+1]-a[j]),line(a[k],a[k+1]-a[k]),q1,q2);
            }
            for(int k=1;k<=4;++k)
            {
                check(line(a[j],a[j+1]-a[j]),line(b[k],b[k+1]-b[k]),q1,q2);
            }
            f[i|(1<<(j-1))]=min(f[i|(1<<(j-1))],f[i]+disPP(q1,q2));
        }
    }
    printf("%.3lf",f[(1<<q)-1]);
    return 0;
}