#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=21;
const ll P=998244353;
int n,q1,q2,d1[1<<N],d2[1<<N];
ll a[N],b[1<<N],f[1<<N],g[1<<N];
void check(int x,int y,int u)
{
    for(int i=0;i<=(1<<q1)-1;++i)
    {
        f[d1[i]|d2[x]]=(f[d1[i]|d2[x]]+f[d1[i]|d2[y]]*u)%P;
        g[d1[i]|d2[x]]=(g[d1[i]|d2[x]]+g[d1[i]|d2[y]]*u)%P;
    }
}
void FWT(int u)
{
    for(int k=1;k*2<=(1<<q2);k<<=1)
    {
        for(int i=0;i<(1<<q2);i+=k*2)
        {
            for(int j=0;j<k;++j) check(i+j,i+j+k,u);
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<=n-1;++i)
    {
        scanf("%lld",&a[i]);
    }
    {
        static char z[1<<N];
        scanf("%s",z);
        for(int i=0;i<=(1<<n)-1;++i) b[i]=z[i]=='1';
    }
    f[(1<<n)-1]=1;
    for(int i=60;i>=0;--i)
    {
        q1=q2=0;
        d1[0]=d2[0]=0;
        int w=0;
        for(int j=0;j<=n-1;++j)
        {
            if((a[j]&(1ll<<i))==0)
            {
                for(int k=0;k<=(1<<q1)-1;++k) d1[k|(1<<q1)]=d1[k]|(1<<j);
                ++q1;
                w|=(1<<j);
            }
            else
            {
                for(int k=0;k<=(1<<q2)-1;++k) d2[k|(1<<q2)]=d2[k]|(1<<j);
                ++q2;
            }
        }
        for(int j=0;j<=(1<<n)-1;++j) g[j]=b[j^w];
        for(int j=0;j<=q1-1;++j)
        {
            for(int k=0;k<=(1<<n)-1;++k)
            {
                if(k&d1[1<<j]) g[k^d1[1<<j]]=(g[k^d1[1<<j]]+g[k])%P;
            }
        }
        FWT(1);
        for(int j=0;j<=(1<<n)-1;++j) f[j]=f[j]*g[j]%P;
        FWT(-1);
    }
    ll s=0;
    for(int i=0;i<=(1<<n)-1;++i) s=(s+f[i])%P;
    printf("%lld",s);
    return 0;
}