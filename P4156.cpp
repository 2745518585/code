#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,q,t,b[N],h[N],Q[N],o[N],T,R;
ll m,f[N],g[N];
char a[N];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void KMP()
{
    o[1]=0;
    for(int i=2,j=0;i<=n;++i)
    {
        while(j!=0&&a[i]!=a[j+1]) j=o[j];
        if(a[i]==a[j+1]) ++j;
        o[i]=j;
    }
    int x=o[n];
    while(x!=0) h[++q]=n-x,x=o[x];
    h[++q]=n;
}
void check(int x1,int x2)
{
    for(int i=0;i<=x2-1;++i) g[i]=f[i];
    for(int i=0;i<=n-1;++i) f[i]=1e18;
    for(int i=0;i<=x2-1;++i)
    {
        f[g[i]%x1]=min(f[g[i]%x1],g[i]);
    }
    int z=gcd(x1,x2);
    for(int i=0;i<=z-1;++i)
    {
        f[(i+x2)%x1]=min(f[(i+x2)%x1],f[i]+x2);
        int x=(i+x2)%x1;
        while(x!=i)
        {
            f[(x+x2)%x1]=min(f[(x+x2)%x1],f[x]+x2);
            x=(x+x2)%x1;
        }
        f[(i+x2)%x1]=min(f[(i+x2)%x1],f[i]+x2);
        x=(i+x2)%x1;
        while(x!=i)
        {
            f[(x+x2)%x1]=min(f[(x+x2)%x1],f[x]+x2);
            x=(x+x2)%x1;
        }
    }
}
void solve(int x,int x2,ll d,int l)
{
    check(x,x2);
    int z=gcd(x,d);
    if(d<0) return;
    for(int i=0;i<=z-1;++i)
    {
        b[t=1]=i;
        while((b[t]+d)%x!=i) ++t,b[t]=(b[t-1]+d)%x;
        int p=b[1];
        for(int j=2;j<=t;++j)
        {
            if(f[b[j]]<f[p]) p=b[j];
        }
        b[t=1]=p;
        while((b[t]+d)%x!=p) ++t,b[t]=(b[t-1]+d)%x;
        T=1,R=0;
        for(int j=1;j<=t;++j)
        {
            while(T<=R&&Q[T]+l<j) ++T;
            while(T<=R&&f[b[Q[R]]]-Q[R]*d>f[b[j]]-j*d) --R;
            Q[++R]=j;
            if(T<=R) f[b[j]]=min(f[b[j]],f[b[Q[T]]]+(j-Q[T])*d+x);
        }
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld%s",&n,&m,a+1);
        q=0;
        m-=n;
        KMP();
        sort(h+1,h+q+1);
        for(int i=1;i<=n;++i) f[i]=1e18;
        f[0]=0;
        int z=n;
        for(int i=1;i<=q;++i)
        {
            int j=i;
            while(j<=n&&h[j+1]-h[j]==h[i+1]-h[i]) ++j;
            --j;
            solve(h[i],z,h[i+1]-h[i],j-i);
            z=h[i];
            i=j;
        }
        ll s=0;
        for(int i=0;i<=z-1;++i)
        {
            if(f[i]<=m) s+=(m-f[i])/z+1;
        }
        printf("%lld\n",s);
    }
    return 0;
}