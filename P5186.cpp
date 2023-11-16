#include<cstdio>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],b[N],c[N],Q[N],T,R;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    T=0,R=-1;
    for(int i=1;i<=n;++i)
    {
        while(T<=R&&Q[T]<=i-m) ++T;
        while(T<=R&&a[Q[R]]>a[i]) --R;
        Q[++R]=i;
        if(i>=m) b[i-m+1]=a[Q[T]];
    }
    T=0,R=-1;
    for(int i=1;i<=n;++i)
    {
        while(T<=R&&Q[T]<=i-m) ++T;
        while(T<=R&&b[Q[R]]<b[i]) --R;
        Q[++R]=i;
        c[i]=b[Q[T]];
    }
    int q=0,t=0;
    ll s=0,w=0;
    for(int i=1;i<=n;++i)
    {
        if(q>0&&c[i]==t) --q;
        else
        {
            ++s;
            q=m-1;
            t=c[i];
        }
        w+=a[i]-t;
    }
    printf("%lld\n%lld",w,s);
    return 0;
}