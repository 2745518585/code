#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=500001,P=10007;
int n,p=1,t[N];
ll s=0,k=0,b[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    for(int i=1;i<=n;++i)
    {
        ll w=0,m1=0,m2=0;
        for(int j=t[i];j!=0;j=a[j].q)
        {
            w=(w+b[a[j].m])%P;
            if(b[a[j].m]>=m1) m2=m1,m1=b[a[j].m];
            else if(b[a[j].m]>m2) m2=b[a[j].m];
        }
        for(int j=t[i];j!=0;j=a[j].q)
        {
            if(b[a[j].m]==m1) k=max(k,b[a[j].m]*m2);
            else k=max(k,b[a[j].m]*m1);
            s=(s+b[a[j].m]*(w-b[a[j].m])%P)%P;
        }
    }
    printf("%lld %lld",k,(s%P+P)%P);
    return 0;
}