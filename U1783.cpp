#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8,Q=1000;
double a1,a2,b1,b2,c1,c2,d1,d2,v1,v2,v3;
double dis(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double num(double x,double y)
{
    return dis(a1,a2,a1+b1*x,a2+b2*x)/v1+dis(a1+b1*x,a2+b2*x,d1+c1*y,d2+c2*y)/v3+dis(d1+c1*y,d2+c2*y,d1,d2)/v2;
}
double sum(double x)
{
    double l=0,r=Q;
    while(r-l>eps)
    {
        double z1=l+(r-l)/3,z2=l+(r-l)/3*2,p1=num(x,z1),p2=num(x,z2);
        if(p1<p2) r=z2;
        else l=z1;
    }
    return num(x,l);
}
int main()
{
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&c1,&c2,&d1,&d2,&v1,&v2,&v3);
    b1-=a1,b2-=a2,c1-=d1,c2-=d2;
    a1*=Q,a2*=Q,d1*=Q,d2*=Q;
    double l=0,r=Q;
    while(r-l>eps)
    {
        double z1=l+(r-l)/3,z2=l+(r-l)/3*2,p1=sum(z1),p2=sum(z2);
        if(p1<p2) r=z2;
        else l=z1;
    }
    printf("%.2lf",sum(l)/Q);
    return 0;
}