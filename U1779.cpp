#include<bits/stdc++.h>
using namespace std;
const int N=100001;
const double eps=1e-10;
int n;
struct str
{
     int a,b,c;
}f[N];
double num(double x)
{
    double s=-1e9;
    for(int i=1;i<=n;++i)
    {
        s=max(s,f[i].a*x*x+f[i].b*x+f[i].c);
    }
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d",&f[i].a,&f[i].b,&f[i].c);
        }
        double l=0,r=1000;
        while(r-l>eps)
        {
            double z1=l+(r-l)/3,z2=l+(r-l)/3*2;
            if(num(l)>=num(z1)&&num(z1)>=num(z2)) l=z1;
            else if(num(r)>=num(z2)&&num(z2)>=num(z1)) r=z2;
        }
        printf("%.4lf\n",num(l));
    }
    return 0;
}