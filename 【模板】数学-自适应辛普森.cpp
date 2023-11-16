#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
double a,b,c,d,l,r;
double num(double x)
{
    return (c*x+d)/(a*x+b);
}
double sum(double x,double y)
{
    return (y-x)*(num(x)+num(y)+4*num((x+y)/2))/6;
}
double solve(double x,double y,double eps,double s)
{
    double z1=sum(x,(x+y)/2),z2=sum((x+y)/2,y);
    if(fabs(z1+z2-s)<=15*eps) return z1+z2+(z1+z2-s)/15;
    return solve(x,(x+y)/2,eps/2,z1)+solve((x+y)/2,y,eps/2,z2);
}
int main()
{
    scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&l,&r);
    printf("%.6lf",solve(l,r,1e-6,sum(l,r)));
    return 0;
}