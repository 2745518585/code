#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=300001;
int n,m,k,tot,a1[N],a2[N],b[N],sa[N],rk[N],he[N],rt[N];
ll d[N];
char a[N];
namespace st
{
    int b[N][21],lg[N];
    void init(int n,int *a)
    {
        for(int i=0;i<=19;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
        for(int i=1;i<=n;++i) b[i][0]=a[i];
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+(1<<i)-1<=n) b[j][i]=min(b[j][i-1],b[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        ++x;
        return min(b[x][lg[y-x]],b[y-(1<<lg[y-x])+1][lg[y-x]]);
    }
}
struct tree
{
    int l,r,s;
}T[N<<4];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void add(int &x,int ls,int rs,int q,int k)
{
    T[++tot]=T[x];
    x=tot;
    if(ls==rs)
    {
        T[x].s=k;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
    pushup(x);
}
int sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return 0;
    if(ls>=l&&rs<=r) return T[x].s;
    int z=ls+rs>>1,s=0;
    if(l<=z) s+=sum(T[x].l,ls,z,l,r);
    if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
    return s;
}
void init(char *a)
{
    static int x1[N],x2[N],h[N];
    int n=strlen(a+1),m=128;
    for(int i=1;i<=n;++i)
    {
        int z=a[i];
        if(a[i]=='#') z=++m;
        ++h[z];
        x1[i]=z;
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
    for(int i=1;i<=n;++i) rk[sa[i]]=i;
    int p=0;
    for(int i=1;i<=n;++i)
    {
        if(rk[i]==1) continue;
        if(p>=1) --p;
        int j=sa[rk[i]-1];
        while(i+p<=n&&j+p<=n&&(a[i+p]==a[j+p]&&a[i+p]!='#')) ++p;
        he[rk[i]]=p;
    }
}
int find1(int x,int k)
{
    int l=1,r=x;
    while(l<r)
    {
        int z=l+r>>1;
        if(st::sum(z,x)>=k) r=z;
        else l=z+1;
    }
    return l;
}
int find2(int x,int k)
{
    int l=x,r=m;
    while(l<r)
    {
        int z=l+r+1>>1;
        if(st::sum(x,z)>=k) l=z;
        else r=z-1;
    }
    return l;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",a+m+1);
        int z=strlen(a+m+1);
        for(int j=m+1;j<=m+z;++j) a1[j]=i,a2[j]=(m+z)-j+1;
        m+=z;
        a[++m]='#';
    }
    init(a);
    st::init(m,he);
    for(int i=1;i<=m;++i)
    {
        if(a[sa[i]]=='#') continue;
        rt[i]=rt[i-1];
        add(rt[i],1,m,i,1);
        if(b[a1[sa[i]]]!=0) add(rt[i],1,m,b[a1[sa[i]]],0);
        b[a1[sa[i]]]=i;
    }
    for(int i=1;i<=m;++i)
    {
        if(a[sa[i]]=='#') continue;
        int l=0,r=a2[sa[i]];
        while(l<r)
        {
            int z=l+r+1>>1;
            int z1=find1(i,z),z2=find2(i,z);
            if(sum(rt[z2],1,m,z1,z2)>=k) l=z;
            else r=z-1;
        }
        d[a1[sa[i]]]+=l;
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld ",d[i]);
    }
    return 0;
}