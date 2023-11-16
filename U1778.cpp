#include<bits/stdc++.h>
using namespace std;
const int N=100001;
const double eps=10e-8;
int n,m,a[N];
double b[N],c[N],d[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        a[i]+=a[i-1];
    }
    double l=0,r=100000000;
    while(r-l>eps)
    {
        double z=(l+r)/2;
        for(int i=1;i<=n;++i)
        {
            b[i]=a[i]-z*i;
        }
        c[0]=0;
        for(int i=1;i<=n;++i)
        {
            c[i]=min(b[i],c[i-1]);
        }
        d[n+1]=-1e18;
        for(int i=n;i>=1;--i)
        {
            d[i]=max(b[i],d[i+1]);
        }
        bool u=false;
        for(int i=0;i<=n-m;++i)
        {
            if(c[i]<=d[i+m])
            {
                u=true;
                break;
            }
        }
        if(u==true) l=z;
        else r=z;
    }
    printf("%d",(int)(l*1000+0.0001));
    return 0;
}