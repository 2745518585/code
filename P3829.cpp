#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps=1e-8,pi=acos(-1.0);
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
    point(double x,double y):x(x),y(y){}
    friend point operator +(point a,point b)
    {
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator -(point a,point b)
    {
        return point(a.x-b.x,a.y-b.y);
    }
    friend point operator *(point a,int b)
    {
        return point(a.x*b,a.y*b);
    }
    friend point operator /(point a,int b)
    {
        return point(a.x/b,a.y/b);
    }
    friend bool operator == (point a,point b)
    {
        return dcmp(a.x-b.x)&&dcmp(a.y-b.y);
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
};
typedef point vector;
struct line
{
    point a,b;
    line(){}
    line(point a,point b):a(a),b(b){}
};
double PPdis(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
bool inL(line a,point b)
{
    return dcmp(cross(a.a-b,a.b-b))==0;
}
bool inS(line a,point b)
{
    return dcmp(cross(a.a-b,a.b-b))==0&&dcmp(dot(a.a-b,a.b-b))<=0;
}
bool intS(line a,line b)
{
    return dcmp(max(a.a.x,a.b.x)-min(b.a.x,b.b.x))>=0&&dcmp(max(b.a.x,b.b.x)-min(a.a.x,a.b.x))>=0
    &&dcmp(max(a.a.y,a.b.y)-min(b.a.y,b.b.y))>=0&&dcmp(max(b.a.y,b.b.y)-min(a.a.y,a.b.y))>=0
    &&dcmp(cross(b.a-a.a,b.b-a.a)*cross(b.a-a.b,b.b-a.b))<=0&&dcmp(cross(a.a-b.a,a.b-b.a)*cross(a.a-b.b,a.b-b.b))<=0;
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
bool convex_cmp(point a,point b);
struct convex
{
    int n,k;
    point a[N],b[N];
    double solve(int n0,point a0[])
    {
        n=n0;
        for(int i=1;i<=n;++i) a[i]=a0[i];
        k=0;
        for(int i=2;i<=n;++i)
        {
            if(a[i].y<a[1].y||(a[i].y==a[1].y&&a[i].x<a[1].x))
            {
                swap(a[1],a[i]);
            }
        }
        sort(a+2,a+n+1,convex_cmp);
        b[++k]=a[1];
        for(int i=2;i<=n;++i)
        {
            while(k>1&&dcmp(cross(b[k]-b[k-1],a[i]-b[k]))<=0) --k;
            b[++k]=a[i];
        }
        b[k+1]=a[1];
        double s=0;
        for(int i=1;i<=k;++i)
        {
            s+=PPdis(b[i],b[i+1]);
        }
        return s;
    }
    double maxdis()
    {
        if(k==2) return PPdis(b[1],b[2]);
        double s=0;
        for(int i=1,j=1;i<=k;++i)
        {
            while(dcmp(cross(b[i+1]-b[i],b[j]-b[j+1]))<0) j=j%k+1;
            s=max(s,max(PPdis(b[i],b[j]),PPdis(b[i+1],b[j])));
            while(dcmp(angle(b[i+1]-b[i],b[j]-b[j+1]))==0)
            {
                j=j%k+1;
                s=max(s,max(PPdis(b[i],b[j]),PPdis(b[i+1],b[j])));
            }
        }
        return s;
    }
}convex;
bool convex_cmp(point x,point y)
{
    int z=dcmp(cross(x-convex.a[1],y-convex.a[1]));
    return z>0||(z==0&&dcmp(PPdis(x,convex.a[1])-PPdis(y,convex.a[1]))<0);
}
int n;
double k1,k2,r;
point a[N];
int main()
{
    scanf("%d%lf%lf%lf",&n,&k2,&k1,&r);
    k1=k1/2-r,k2=k2/2-r;
    for(int i=1;i<=n;++i)
    {
        point x;
        double p;
        scanf("%lf%lf%lf",&x.x,&x.y,&p);
        a[i*4-3]=x+turnV(vector(k1,k2),p);
        a[i*4-2]=x+turnV(vector(k1,-k2),p);
        a[i*4-1]=x+turnV(vector(-k1,k2),p);
        a[i*4]=x+turnV(vector(-k1,-k2),p);
    }
    printf("%.2lf",convex.solve(n*4,a)+2*pi*r);
    return 0;
}