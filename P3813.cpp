#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=1e9+7;
int n,m,m1,m2,q1,q2,b1[N],b2[N],f[N][N];
struct str
{
    int x1,y1,x2,y2,w;
}a[N];
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
int sum(int x)
{
    int s=0;
    while(x) x-=x&-x,++s;
    return s;
}
ll solve(int x)
{
    for(int i=1;i<=q1;++i)
    {
        for(int j=1;j<=q2;++j) f[i][j]=m;
    }
    for(int i=1;i<=n;++i)
    {
        int z;
        if((x&(1<<(i-1)))==0) z=a[i].w;
        else z=a[i].w-1;
        for(int j=a[i].x1+1;j<=a[i].x2;++j)
        {
            for(int k=a[i].y1+1;k<=a[i].y2;++k) f[j][k]=min(f[j][k],z);
        }
    }
    ll s=1;
    for(int i=1;i<=q1;++i)
    {
        for(int j=1;j<=q2;++j)
        {
            s=(s*qpow(f[i][j],(b1[i]-b1[i-1])*(b2[j]-b2[j-1])))%P;
        }
    }
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&m1,&m2,&m,&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d%d%d",&a[i].x1,&a[i].y1,&a[i].x2,&a[i].y2,&a[i].w);
            --a[i].x1,--a[i].y1;
            b1[++q1]=a[i].x1;
            b1[++q1]=a[i].x2;
            b2[++q2]=a[i].y1;
            b2[++q2]=a[i].y2;
        }
        b1[++q1]=0,b1[++q1]=m1;
        b2[++q2]=0,b2[++q2]=m2;
        sort(b1+1,b1+q1+1);
        q1=unique(b1+1,b1+q1+1)-b1-1;
        sort(b2+1,b2+q2+1);
        q2=unique(b2+1,b2+q2+1)-b2-1;
        for(int i=1;i<=n;++i)
        {
            a[i].x1=lower_bound(b1+1,b1+q1+1,a[i].x1)-b1;
            a[i].x2=lower_bound(b1+1,b1+q1+1,a[i].x2)-b1;
            a[i].y1=lower_bound(b2+1,b2+q2+1,a[i].y1)-b2;
            a[i].y2=lower_bound(b2+1,b2+q2+1,a[i].y2)-b2;
        }
        ll s=0;
        for(int i=0;i<=(1<<n)-1;++i)
        {
            if(sum(i)%2==0) s=(s+solve(i))%P;
            else s=(s-solve(i))%P;
        }
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}