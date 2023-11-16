#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2000001;
int n,b[N],c[N],d[N],sa[N];
char a[N];
namespace SA
{
    int h[N],x1[N],x2[N];
    void init(char a[])
    {
        int n=strlen(a+1),m=128;
        for(int i=1;i<=n;++i)
        {
            ++h[a[i]];
            x1[i]=a[i];
        }
        for(int i=1;i<=m;++i) h[i]+=h[i-1];
        for(int i=n;i>=1;--i) sa[h[x1[i]]--]=i;
        for(int r=1;r<=n;r<<=1)
        {
            int p=0;
            for(int i=n-r+1;i<=n;++i) x2[++p]=i;
            for(int i=1;i<=n;++i) if(sa[i]>r) x2[++p]=sa[i]-r;
            for(int i=1;i<=m;++i) h[i]=0;
            for(int i=1;i<=n;++i) ++h[x1[i]];
            for(int i=1;i<=m;++i) h[i]+=h[i-1];
            for(int i=n;i>=1;--i) sa[h[x1[x2[i]]]--]=x2[i],x2[i]=0;
            swap(x1,x2);
            p=0;
            x1[sa[1]]=++p;
            for(int i=2;i<=n;++i)
            {
                if(x2[sa[i]]==x2[sa[i-1]]&&x2[sa[i]+r]==x2[sa[i-1]+r]) x1[sa[i]]=p;
                else x1[sa[i]]=++p;
            }
            if(p==n) break;
            m=p;
        }
    }
}
struct tree
{
    int l,r,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=min(T[x<<1].s,T[x<<1|1].s);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=b[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
int sum1(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1,s=1e9;
    if(l<=z) s=min(s,sum1(x<<1,l,r));
    if(r>z) s=min(s,sum1(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=1;i<=n;++i) a[n+i]=a[i];
    for(int i=1;i<=n*2;++i)
    {
        if(a[i]=='(') b[i]=1;
        else b[i]=-1;
        b[i]+=b[i-1];
    }
    for(int i=n*2;i>=1;--i)
    {
        if(a[i]=='(') c[i]=c[i+1]+1;
        else c[i]=0;
    }
    build(1,1,n*2);
    int s=1e9;
    for(int i=1;i<=n;++i)
    {
        d[i]=max(max(b[i-1]-sum1(1,i,n+i-1),0),-b[n]);
        s=min(s,d[i]);
    }
    SA::init(a);
    for(int i=1;i<=n*2;++i)
    {
        if(sa[i]<=n&&d[sa[i]]==s)
        {
            for(int j=1;j<=s;++j) printf("(");
            for(int j=1;j<=n;++j) printf("%c",a[sa[i]+j-1]);
            for(int j=1;j<=s+b[n];++j) printf(")");
            return 0;
        }
    }
    return 0;
}