#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,k,sa[N],rk[N],he[N],f[N];
char a[N],b1[N],b2[N];
namespace SA
{
    int h[N],x1[N],x2[N];
    void init(char a[])
    {
        int m=128;
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
        for(int i=1;i<=n;++i) rk[sa[i]]=i;
        int p=0;
        for(int i=1;i<=n;++i)
        {
            if(rk[i]==1) continue;
            if(p>=1) --p;
            int j=sa[rk[i]-1];
            while(i+p<=n&&j+p<=n&&a[i+p]==a[j+p]) ++p;
            he[rk[i]]=p;
        }
    }
}
char *check(char *a,char *b)
{
    int l1=strlen(a+1),l2=strlen(b+1);
    if(l1!=l2) return l1<l2?a:b;
    for(int i=1;i<=l1;++i)
    {
        if(a[i]!=b[i]) return a[i]<b[i]?a:b;
    }
    return a;
}
int main()
{
    scanf("%d%d%s",&n,&k,a+1);
    {
        for(int i=1;i<=n;++i) b1[i]=a[i];
        int p=k,x=n;
        for(int i=1;i<=n;++i)
        {
            if(b1[i]=='0') continue;
            while(x>0&&b1[x]=='1') --x;
            if(i>x) break;
            swap(b1[i],b1[x]);
            --p;
            if(p==0) break;
        }
        x=0;
        while(b1[x+1]=='0') ++x;
        for(int i=1;i<=n-x;++i) b1[i]=b1[i+x];
        b1[n-x+1]='\0';
    }
    for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
    SA::init(a);
    --k;
    for(int i=1;i<=n;++i) f[i]=f[i-1]+(a[i]=='1');
    int x=0,l=n;
    for(int i=1;i<=n;++i)
    {
        while(x<=n&&(x<i+f[n]-1||f[x]-f[i-1]<f[n]-k)) ++x;
        if(x<=n) l=min(l,x-i+1);
    }
    for(int i=1;i<=n;++i)
    {
        if(sa[i]+l-1<=n&&f[sa[i]+l-1]-f[sa[i]-1]>=f[n]-k)
        {
            for(int j=1;j<=l;++j) b2[j]=a[sa[i]+j-1];
            break;
        }
    }
    int p=k;
    for(int i=l;i>=1;--i)
    {
        if(b2[i]=='0') b2[i]='1',--p;
        if(p==0) break;
    }
    // printf("%s\n",b1+1);
    // printf("%s\n",b2+1);
    char *z=check(b1,b2);
    ll s=0,w=1;
    for(int i=strlen(z+1);i>=1;--i)
    {
        if(z[i]=='1') s=(s+w)%P;
        w=w*2%P;
    }
    printf("%lld",s);
    return 0;
}