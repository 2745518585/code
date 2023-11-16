#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,Q[N],R;
ll a[N],b[N],d;
double abc(int x,int y)
{
    return (double)(a[y-1]-a[x-1])/(y*d-x*d);
}
int main()
{
    scanf("%d%lld",&n,&d);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&a[i],&b[i]);
        a[i]+=a[i-1];
    }
    double s=0;
    for(int i=1;i<=n;++i)
    {
        while(R>=2&&abc(Q[R-1],Q[R])>=abc(Q[R],i)) --R;
        Q[++R]=i;
        int l=1,r=R;
        while(l<r)
        {
            int z=l+r>>1;
            if(abc(Q[z],Q[z+1])>(double)(a[i]-a[Q[z]-1])/(b[i]+(i-Q[z])*d)) r=z;
            else l=z+1;
        }
        s+=(double)(a[i]-a[Q[l]-1])/(b[i]+(i-Q[l])*d);
    }
    printf("%.0lf",s);
    return 0;
}