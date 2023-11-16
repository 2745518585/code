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
    if(b.b==point(0,0)) return a==b.a;
    return dcmp(cross(a-b.a,b.b))<=0;
}
bool onleftPL2(point a,line b)
{
    if(b.b==point(0,0)) return false;
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
int n,n1,m,f[N],g[N];
point a[N];
struct str
{
    int x,y,w;
}b[N];
bool cmp(str x,str y)
{
    return atan2(a[x.y].y-a[x.x].y,a[x.y].x-a[x.x].x)<atan2(a[y.y].y-a[y.x].y,a[y.y].x-a[y.x].x);
}
int main()
{
    scanf("%d%d",&n1,&n);
    n+=n1+1;
    a[1]=point(0,0);
    for(int i=2;i<=n;++i) a[i].input();
    for(int i=2;i<=n1+1;++i) g[i]=1;
    for(int i=n1+2;i<=n;++i) g[i]=-1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            int w=0;
            for(int k=1;k<=n;++k)
            {
                if(onleftPL(a[k],line(point(0,0),a[i]))&&!onleftPL(a[k],line(point(0,0),a[j]))&&onleftPL(a[k],line(a[i],a[j]-a[i]))) w+=g[k];
                if(!onleftPL2(a[k],line(point(0,0),a[i]))&&onleftPL2(a[j],line(point(0,0),a[j]))&&onleftPL2(a[k],line(a[j],a[i]-a[j]))) w-=g[k];
            }
            b[++m]=(str){i,j,w};
        }
    }
    sort(b+1,b+m+1,cmp);
    int s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) f[j]=-1e9;
        f[i]=0;
        for(int j=1;j<=m;++j) f[b[j].y]=max(f[b[j].y],f[b[j].x]+b[j].w);
        s=max(s,f[i]);
    }
    printf("%d",s);
    return 0;
}