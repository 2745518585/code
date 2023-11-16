#pragma GCC optimize("O2")
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long double ld;
const ld eps=1e-12,pi=acos(-1.0);
const int N=1000001;
ld s;
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
    point(ld x,ld y):x(x),y(y) {}
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
ld disPP(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
ld disPP2(point a,point b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
point intLL(line a,line b)
{
    if(dcmp(cross(a.b,b.b))==0) return point(0,0);
    return a.a+(cross(b.b,a.a-b.a)/cross(a.b,b.b))*a.b;
}
vector turnV(vector a,ld b)
{
    return vector(a.x*cos(b)-a.y*sin(b),a.y*cos(b)+a.x*sin(b));
}
point symPL(point a,line b)
{
    return intLL(line(a,turnV(b.b,pi/2)),b)*2-a;
}
int n,m;
ld x2,y2,r;
point a[N];
vector b[N];
ld solve(point a1,vector b1,point a2,vector b2,ld t)
{
    ld a=(b1.x-b2.x)*(b1.x-b2.x)+(b1.y-b2.y)*(b1.y-b2.y),b=2*(a1.x-a2.x)*(b1.x-b2.x)+2*(a1.y-a2.y)*(b1.y-b2.y);
    if(a==0||-b/(a*2)<0||-b/(a*2)>t) return min(disPP(a1,a2),disPP(a1+b1*t,a2+b2*t));
    return disPP(a1+b1*(-b/(a*2)),a2+b2*(-b/(a*2)));
}
ld check(int t1,int t2)
{
    point a1=a[t1],a2=a[t2];
    vector b1=b[t1],b2=b[t2];
    int q1=0,q2=0;
    ld s=1e9;
    while(q1<m&&q2<m)
    {
        point z1=intLL(line(a1,b1),line(point(0,0),turnV(b1,pi/2))),x1=z1+b1/length(b1)*sqrt(r*r-disPP2(point(0,0),z1));
        point z2=intLL(line(a2,b2),line(point(0,0),turnV(b2,pi/2))),x2=z2+b2/length(b2)*sqrt(r*r-disPP2(point(0,0),z2));
        if(disPP(a1,x1)/length(b1)<=disPP(a2,x2)/length(b2))
        {
            ld t=disPP(a1,x1)/length(b1);
            s=min(s,solve(a1,b1,a2,b2,t));
            b1=vector(0,0)-symPL(b1,line(point(0,0),x1));
            a1=x1;
            a2=a2+b2*t;
            ++q1;
        }
        else
        {
            ld t=disPP(a2,x2)/length(b2);
            s=min(s,solve(a1,b1,a2,b2,t));
            b2=vector(0,0)-symPL(b2,line(point(0,0),x2));
            a1=a1+b1*t;
            a2=x2;
            ++q2;
        }
    }
    return s;
}
int main()
{
    scanf("%Lf%Lf%Lf%d%d",&x2,&y2,&r,&n,&m);
    for(int i=1;i<=n;++i)
    {
        a[i].input(),b[i].input();
        a[i]=a[i]-point(x2,y2);
    }
    ld s=1e9;
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            s=min(s,check(i,j));
        }
    }
    printf("%.1Lf",s);
    return 0;
}