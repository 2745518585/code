#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],b[N],f1[N],f2[N],g[N],Q[N],T,R;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ++b[x],++b[y];
    }
    for(int i=1;i<=n;++i) ++a[b[i]-1];
    for(int i=1;i<=n*2;++i) f1[i]=1e9,f2[i]=-1e9;
    f1[0]=0,f2[0]=a[0];
    for(int i=1;i<=n;++i)
    {
        if(a[i]==0) continue;
        for(int j=0;j<=n*2;++j) g[j]=f1[j],f1[j]=1e9;
        for(int j=0;j<=i-1;++j)
        {
            T=1,R=0;
            for(int k=j;k<=n*2;k+=i)
            {
                while(T<=R&&k-Q[T]>a[i]*i) ++T;
                while(T<=R&&g[Q[R]]-Q[R]/i>=g[k]-k/i) --R;
                Q[++R]=k;
                f1[k]=g[Q[T]]+(k-Q[T])/i;
            }
        }
        for(int j=0;j<=n*2;++j) g[j]=f2[j],f2[j]=-1e9;
        for(int j=0;j<=i-1;++j)
        {
            T=1,R=0;
            for(int k=j;k<=n*2;k+=i)
            {
                while(T<=R&&k-Q[T]>a[i]*i) ++T;
                while(T<=R&&g[Q[R]]-Q[R]/i<=g[k]-k/i) --R;
                Q[++R]=k;
                f2[k]=g[Q[T]]+(k-Q[T])/i;
            }
        }
    }
    ll s=0;
    for(int i=0;i<=n*2;++i)
    {
        s+=max(f2[i]-f1[i]+1,0);
    }
    printf("%lld",s);
    return 0;
}