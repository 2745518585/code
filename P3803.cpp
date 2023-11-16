#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=3000001;
const double pi=acos(-1);
struct complex
{
    double x,y;
    friend complex operator + (complex a,complex b)
    {
        return (complex){a.x+b.x,a.y+b.y};
    }
    friend complex operator - (complex a,complex b)
    {
        return (complex){a.x-b.x,a.y-b.y};
    }
    friend complex operator * (complex a,complex b)
    {
        return (complex){a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};
    }
}a[N],b[N];
int n,m;
void FFT(int x,complex a[],int u)
{
    if(x==1) return;
    complex a1[x],a2[x];
    for(int i=0;i<=x/2;++i)
    {
        a1[i]=a[i*2];
        a2[i]=a[i*2+1];
    }
    FFT(x/2,a1,u);
    FFT(x/2,a2,u);
    complex r=(complex){cos(2.0*pi/x),u*sin(2.0*pi/x)},k=(complex){1,0};
    for(int i=0;i<x/2;++i,k=k*r)
    {
        a[i]=a1[i]+k*a2[i];
        a[i+x/2]=a1[i]-k*a2[i];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;++i) scanf("%lf",&a[i].x);
    for(int i=0;i<=m;++i) scanf("%lf",&b[i].x);
    int x=1;
    while(x<=n+m) x*=2;
    FFT(x,a,1);
    FFT(x,b,1);
    for(int i=0;i<=x;++i) a[i]=a[i]*b[i];
    FFT(x,a,-1);
    for(int i=0;i<=n+m;++i)
    {
        printf("%d ",(int)(a[i].x/x+0.5));
    }
    return 0;
}
