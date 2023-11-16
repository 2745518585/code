#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int n,m,a[100001],T=0,R=-1;
ll b[100001],f[100001][2];
struct deque
{
    ll a;
    int x;
}Q[1000001];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=b[i-1]+a[i];
    }
    Q[++R]=(deque){0,0};
    for(int i=1;i<=n;++i)
    {
        f[i][0]=max(f[i-1][0],f[i-1][1]);
        while(T<=R&&i-Q[T].x>m) ++T;
        while(T<=R&&Q[R].a<=f[i][0]-b[i]) --R;
        f[i][1]=Q[T].a+b[i];
        Q[++R]=(deque){f[i][0]-b[i],i};
    }
    printf("%lld",max(f[n][0],f[n][1]));
    return 0;
}