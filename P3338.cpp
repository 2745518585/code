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
}a[N],a2[N],b[N],c[N],c2[N];
int n,d[N];
double q[N];
void FFT(int x,complex a[],int u)
{
    for(int i=0;i<x;++i)
    {
        if(i<d[i]) swap(a[i],a[d[i]]);
    }
    for(int i=1;i<x;i*=2)
    {
        complex r=(complex){cos(pi/i),u*sin(pi/i)};
        for(int j=0;j<x;j+=i*2)
        {
            complex t=(complex){1,0};
            for(int k=0;k<i;++k,t=t*r)
            {
                complex x1=a[j+k],x2=t*a[i+j+k];
                a[j+k]=x1+x2;
                a[i+j+k]=x1-x2;
            }
        }
    }   
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lf",&a[i].x);
    }
    a[0].x=b[0].x=0;
    for(int i=0;i<=n;++i) a2[i].x=a[n-i].x;
    for(int i=1;i<=n;++i) b[i].x=(double)(1)/i/i;
    int x=0;
    while((1<<x)<=n*2) ++x;
    for(int i=0;i<(1<<x);++i)
    {
        d[i]=(d[i>>1]>>1)|((i&1)<<(x-1));
    }
    x=(1<<x);
    FFT(x,a,1);
    FFT(x,a2,1);
    FFT(x,b,1);
    for(int i=0;i<=x;++i) c[i]=a[i]*b[i],c2[i]=a2[i]*b[i];
    FFT(x,c,-1);
    FFT(x,c2,-1);
    for(int i=1;i<=n;++i)
    {
        printf("%.3lf\n",c[i].x/x-c2[n-i].x/x);
    }
    return 0;
}