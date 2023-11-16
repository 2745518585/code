#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q1,q2,b1[N],b2[N];
ll T1[N],T2[N],T3[N],T4[N];
struct str
{
    int x,y;
}a[N];
void add(ll T[],int x,ll k)
{
    while(x<=n)
    {
        T[x]+=k;
        x+=(x&-x);
    }
}
ll sum(ll T[],int x)
{
    ll s=0;
    while(x>=1)
    {
        s+=T[x];
        x-=(x&-x);
    }
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i].x=x+y,a[i].y=x-y;
        b1[i]=a[i].x;
        b2[i]=a[i].y;
    }
    sort(b1+1,b1+n+1);
    sort(b2+1,b2+n+1);
    q1=unique(b1+1,b1+n+1)-b1-1;
    q2=unique(b2+1,b2+n+1)-b2-1;
    for(int i=1;i<=n;++i)
    {
        a[i].x=lower_bound(b1+1,b1+q1+1,a[i].x)-b1;
        a[i].y=lower_bound(b2+1,b2+q2+1,a[i].y)-b2;
        add(T1,a[i].x,1);
        add(T2,a[i].y,1);
        add(T3,a[i].x,b1[a[i].x]);
        add(T4,a[i].y,b2[a[i].y]);
    }
    ll s=1e18,p1=sum(T3,n),p2=sum(T4,n);
    for(int i=1;i<=n;++i)
    {
        ll z1=sum(T1,a[i].x),z2=sum(T2,a[i].y),z3=sum(T3,a[i].x),z4=sum(T4,a[i].y);
        s=min(s,(z1*b1[a[i].x]-z3)+((p1-z3)-(n-z1)*b1[a[i].x])+(z2*b2[a[i].y]-z4)+((p2-z4)-(n-z2)*b2[a[i].y]));
    }
    printf("%lld",s/2);
    return 0;
}