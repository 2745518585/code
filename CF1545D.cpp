#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001;
int n,m,t;
ll k,q,a[N][N],b[N];
ll check(int x)
{
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        s+=a[x-1][i]*a[x-1][i]+a[x+1][i]*a[x+1][i]-2*a[x][i]*a[x][i];
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%lld",&a[i][j]);
            b[i]+=a[i][j];
        }
    }
    if(b[2]-b[1]==(b[3]-b[1])/2) k=b[2]-b[1];
    else k=(b[4]-b[1])/3;
    for(int i=2;i<=m;++i)
    {
        if(b[i]-b[i-1]!=k)
        {
            t=i;
            break;
        }
    }
    if(t>3) q=check(2);
    else q=check(m-1);
    for(int i=1;i<=n;++i)
    {
        a[t][i]+=k-(b[t]-b[t-1]);
        if(check(t<m?t:t-1)==q)
        {
            printf("%d %lld\n",t-1,a[t][i]);
            return 0;
        }
        a[t][i]-=k-(b[t]-b[t-1]);
    }
    printf("%d %d\n",t-1,0);
    return 0;
}