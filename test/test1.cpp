#include<bits/stdc++.h>
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
        printf("%.12Lf %.12Lf\n",x,y);
    }
};
struct line
{
    point a,b;
    line(){}
    line(point a,point b):a(a),b(b){}
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
int n;
point a[N];
ld c,s;
point find(ld x)
{
    for(int i=1;i<=n;++i)
    {
        if(disPP(a[i],a[i+1])<=x) x-=disPP(a[i],a[i+1]);
        else return a[i]+(a[i+1]-a[i])/disPP(a[i],a[i+1])*x;
    }
    return a[1];
}
ld check(ld x)
{
    ld y=x+c/2,w=0;
    point z=point(1e9,1e9);
    for(int i=1;i<=n;++i)
    {
        if(disPP(a[i],a[i+1])<=x) x-=disPP(a[i],a[i+1]),w-=cross(a[i],a[i+1])/2;
        else
        {
            w-=cross(a[i],a[i]+(a[i+1]-a[i])/disPP(a[i],a[i+1])*x)/2;
            z=a[i]+(a[i+1]-a[i])/disPP(a[i],a[i+1])*x;
            break;
        }
    }
    if(z.x==1e9) z=a[1];
    for(int i=1;i<=n;++i)
    {
        if(disPP(a[i],a[i+1])<=y) y-=disPP(a[i],a[i+1]),w+=cross(a[i],a[i+1])/2;
        else
        {
            w+=cross(a[i],a[i]+(a[i+1]-a[i])/disPP(a[i],a[i+1])*y)/2;
            w+=cross(a[i]+(a[i+1]-a[i])/disPP(a[i],a[i+1])*y,z)/2;
            break;
        }
    }
    return s-fabs(w)*2;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) a[i].input();
    a[n+1]=a[1];
    for(int i=1;i<=n;++i)
    {
        s+=cross(a[i],a[i+1])/2;
        c+=disPP(a[i],a[i+1]);
    }
    s=fabs(s);
    // printf("%.12Lf\n",check(sqrt(2)));
    // return 0;
    ld l=0,r=c/2;
    if(dcmp(check(l))==0)
    {
        find(l).print();
        find(l+c/2).print();
    }
    if(dcmp(check(r))==0)
    {
        find(r).print();
        find(r+c/2).print();
    }
    while(r-l>1e-12)
    {
        ld z=(l+r)/2;
        ld p1=check(l),p2=check(z),p3=check(r);
        if(dcmp(p2)==0)
        {
            find(z).print();
            find(z+c/2).print();
            return 0;
        }
        if(p1*p2<0) r=z;
        else l=z;
    }
    find(l).print();
    find(l+c/2).print();
    return 0;
}
