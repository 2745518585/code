#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N=100001;
int n,k,T,R,g[N];
ll m,a[N];
ld f[N];
char c[N][101];
bool h[N];
struct str
{
    int l,r,k;
}Q[N];
ld pow(ll x,int p)
{
    ld s=1;
    for(int i=1;i<=p;++i) s*=x;
    return s;
}
ld abc(int x,int y)
{
    return f[y]+pow(abs(a[x]-a[y]+x-y-1-m),k);
}
void dp()
{
    scanf("%d%lld%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",c[i]);
        a[i]=a[i-1]+strlen(c[i]);
    }
    T=0,R=-1;
    Q[++R]=(str){1,n,0};
    f[0]=0;
    for(int i=1;i<=n;++i)
    {
        while(T<=R&&Q[T].r<i) ++T;
        Q[T].l=i;
        f[i]=abc(i,Q[T].k);
        g[i]=Q[T].k;
        if(f[i]>1e18) continue;
        if(T<=R&&abc(n,i)>abc(n,Q[R].k)) continue;
        while(T<=R&&abc(Q[R].l,i)<=abc(Q[R].l,Q[R].k)) --R;
        if(T<=R)
        {
            int l=Q[R].l,r=Q[R].r+1;
            while(l<r)
            {
                int z=l+r>>1;
                if(abc(z,i)<=abc(z,Q[R].k)) r=z;
                else l=z+1;
            }
            Q[R].r=l-1;
            Q[++R]=(str){l,n,i};
        }
        else Q[++R]=(str){i+1,n,i};
    }
    if(f[n]>1e18)
    {
        printf("Too hard to arrange\n");
        return;
    }
    printf("%lld\n",(ll)f[n]);
    for(int i=1;i<=n;++i) h[i]=false;
    int x=n;
    while(x>=1)
    {
        h[x]=true;
        x=g[x];
    }
    for(int i=1;i<=n;++i)
    {
        printf("%s",c[i]);
        if(h[i]==true) printf("\n");
        else printf(" ");
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        dp();
        printf("--------------------\n");
    }
    return 0;
}