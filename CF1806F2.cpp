#include<cstdio>
#include<algorithm>
using namespace std;
typedef __int128_t ll;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T>
inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
const int N=1000001;
int n,q,k;
ll m,a[N],a2[N],b[N],c[N];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        read(n),read(m),read(k);
        ++k;
        ll w=0;
        q=0;
        for(int i=1;i<=n;++i)
        {
            read(a[i]);
            w+=a[i];
        }
        sort(a+1,a+n+1);
        for(int i=1;i<=n;++i)
        {
            if(a[i]==a[i-1]) b[++q]=a[i];
        }
        q=unique(a+1,a+n+1)-a-1;
        for(int i=1;i<=q;++i) a2[i]=a2[i-1]+a[i];
        for(int i=1;i<=n-q;++i) b[i]+=b[i-1];
        ll s=0;
        if(k-1<=n-q) s=max(s,w-b[k-1]);
        for(int i=1;i<=q;++i)
        {
            c[i]=gcd(c[i-1],a[i]);
            if(k-i<=n-q&&k>=i) s=max(s,w+c[i]-a2[i]-b[k-i]);
        }
        for(int i=1;i<=q;++i)
        {
            int j=i;
            while(j+1<=q&&c[i]==c[j+1]) ++j;
            ll z=-1e36;
            for(int l=j+1;l<=q;++l)
            {
                z=max(z,gcd(c[i],a[l])-a[l]);
            }
            for(int l=i;l<=j;++l)
            {
                if(k-l-1<=n-q) s=max(s,w+z-a2[l]-b[k-l-1]);
            }
            i=j;
        }
        print(s);
        putchar('\n');
    }
    return 0;
}