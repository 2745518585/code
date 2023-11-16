#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001;
int n,m,a[N],Q[N],T=0,R=-1;
ll b[N],f[N][2];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=b[i-1]+a[i];
    }
    Q[++R]=0;
    for(int i=1;i<=n;++i)
    {
        f[i][0]=max(f[i-1][0],f[i-1][1]);
        while(T<=R&&i-Q[T]>m) ++T;
        while(T<=R&&f[Q[R]][0]-b[Q[R]]<=f[i][0]-b[i]) --R;
        f[i][1]=f[Q[T]][0]+b[i]-b[Q[T]];
        Q[++R]=i;
    }
    printf("%lld",max(f[n][0],f[n][1]));
    return 0;
}