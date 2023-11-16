#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=300001;
int n,m,Q[N*2],T=0,R=0;
ll a[N],b[N],f[N];
ll abc(int x,int y)
{
    if(b[x]==b[y]) return 1e18;
    return ((f[x]-m*b[x])-(f[y]-m*b[y]))/(b[x]-b[y]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i]=a[i-1]+x;
        b[i]=b[i-1]+y;
    }
    Q[++R]=0;
    for(int i=1;i<=n;++i)
    {
        int l=T,r=R;
        while(l<r)
        {
            int z=l+r>>1;
            if(abc(Q[z],Q[z+1])<a[i]) l=z+1;
            else if(abc(Q[z],Q[z+1])>a[i]) r=z;
            else
            {
                l=z;
                break;
            }
        }
        f[i]=f[Q[l]]+a[i]*(b[i]-b[Q[l]])+m*(b[n]-b[Q[l]]);
        while(T<R&&abc(Q[R],i)<abc(Q[R-1],Q[R])) --R;
        Q[++R]=i;
    }
    printf("%lld",f[n]);
    return 0;
}