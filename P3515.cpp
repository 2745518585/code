#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N=1000001;
int n,k,T,R,a[N];
ld f[N],g[N];
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
    return a[y]+sqrt(x-y);
}
void dp()
{
    T=0,R=-1;
    Q[++R]=(str){1,n,1};
    f[1]=abc(1,1);
    for(int i=2;i<=n;++i)
    {
        while(T<=R&&Q[T].r<i) ++T;
        Q[T].l=i;
        f[i]=abc(i,Q[T].k);
        if(f[i]>1e18) continue;
        if(T<=R&&abc(n,i)<abc(n,Q[R].k)) continue;
        while(T<=R&&abc(Q[R].l,i)>=abc(Q[R].l,Q[R].k)) --R;
        if(T<=R)
        {
            int l=Q[R].l,r=Q[R].r+1;
            while(l<r)
            {
                int z=l+r>>1;
                if(abc(z,i)>=abc(z,Q[R].k)) r=z;
                else l=z+1;
            }
            Q[R].r=l-1;
            Q[++R]=(str){l,n,i};
        }
        else Q[++R]=(str){i+1,n,i};
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    dp();
    for(int i=1;i<=n;++i) g[i]=f[i];
    for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
    dp();
    for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]),swap(f[i],f[n-i+1]);
    for(int i=1;i<=n;++i)
    {
        printf("%d\n",max(int(ceil(max(f[i],g[i])-a[i])),0));
    }
    return 0;
}