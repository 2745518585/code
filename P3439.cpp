#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q1,q2,b1[N],b2[N];
ll c1[N],c2[N];
struct str
{
    int x,y,t;
}a[N];
ll check(int x,int y)
{
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        s+=(ll)max(abs(a[i].x-x),abs(a[i].y-y))*a[i].t;
    }
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].t);
        b1[i]=a[i].x+a[i].y;
        b2[i]=a[i].x-a[i].y;
    }
    sort(b1+1,b1+n+1);
    sort(b2+1,b2+n+1);
    q1=unique(b1+1,b1+n+1)-b1-1;
    q2=unique(b2+1,b2+n+1)-b2-1;
    for(int i=1;i<=n;++i)
    {
        c1[lower_bound(b1+1,b1+q1+1,a[i].x+a[i].y)-b1]+=a[i].t;
        c2[lower_bound(b2+1,b2+q2+1,a[i].x-a[i].y)-b2]+=a[i].t;
    }
    for(int i=1;i<=q1;++i) c1[i]+=c1[i-1];
    for(int i=1;i<=q2;++i) c2[i]+=c2[i-1];
    int z1,z2;
    for(int i=1;i<=q1;++i)
    {
        if(c1[i]>=c1[q1]/2+1)
        {
            z1=b1[i];
            break;
        }
    }
    for(int i=1;i<=q2;++i)
    {
        if(c2[i]>=c2[q2]/2+1)
        {
            z2=b2[i];
            break;
        }
    }
    int x=(z1+z2)/2,y=(z1-z2)/2,qx=x,qy=y;
    ll s=check(x,y),z;
    if((z=check(x+1,y))<s) s=z,qx=x+1,qy=y;
    if((z=check(x,y+1))<s) s=z,qx=x,qy=y+1;
    if((z=check(x+1,y+1))<s) s=z,qx=x+1,qy=y+1;
    printf("%d %d",qx,qy);
    return 0;
}