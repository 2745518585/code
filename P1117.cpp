#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=100001,M=31;
int n,b1[N],b2[N];
char a[N];
struct ST
{
    int q,b[N][M],lg[N],pw[N];
    void init(int a[])
    {
        for(int i=1;i<=n;++i)
        {
            b[i][0]=a[i];
            lg[i]=log2(i);
        }
        q=log2(n);
        pw[0]=1;
        for(int i=1;i<=q;++i) pw[i]=pw[i-1]*2;
        for(int i=1;i<=q;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+pw[i]-1<=n) b[j][i]=min(b[j][i-1],b[j+pw[i-1]][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        return min(b[x][lg[y-x]],b[y-pw[lg[y-x]]+1][lg[y-x]]);
    }
}ST1,ST2;
struct SA
{
    int h[N],x1[N],x2[N],sa[N],rk[N],he[N];
    char a[N];
    void init()
    {
        int n=strlen(a+1),m=128;
        for(int i=1;i<=m;++i) h[i]=0;
        for(int i=1;i<=n*2;++i) x1[i]=x2[i]=sa[i]=rk[i]=0;
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
}SA1,SA2;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a+1);
        n=strlen(a+1);
        for(int i=1;i<=n;++i) SA1.a[i]=a[n-i+1];
        SA1.a[n+1]='\0';
        SA1.init();
        for(int i=1;i<=n;++i) SA2.a[i]=a[i];
        SA2.a[n+1]='\0';
        SA2.init();
        ST1.init(SA1.he);
        ST2.init(SA2.he);
        for(int i=1;i<=n;++i) b1[i]=b2[i]=0;
        for(int i=1;i<=n-1;++i)
        {
            int x=1;
            while(x+i<=n)
            {
                int y=x+i,z1=ST1.sum(min(SA1.rk[n-x+1],SA1.rk[n-y+1])+1,max(SA1.rk[n-x+1],SA1.rk[n-y+1])),z2=ST2.sum(min(SA2.rk[x],SA2.rk[y])+1,max(SA2.rk[x],SA2.rk[y]));
                z1=min(z1,i),z2=min(z2,i);
                if(z1+z2>=i+1)
                {
                    ++b1[x-z1+i*2],--b1[y+z2];
                    ++b2[x-z1+1],--b2[y+z2-i*2+1];
                }
                x+=i;
            }
        }
        for(int i=1;i<=n;++i) b1[i]+=b1[i-1],b2[i]+=b2[i-1];
        ll s=0;
        for(int i=1;i<=n-1;++i) s+=(ll)b1[i]*b2[i+1];
        printf("%lld\n",s);
    }
    return 0;
}