#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001;
const ll P=998244353;
int n,k,a[N],b[N];
bool h[N];
struct str
{
    int x,w;
    str() {}
    str(int x,int w):x(x),w(w) {}
    friend bool operator<(str a,str b)
    {
        return a.w>b.w;
    }
};
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=2;i<=10000;++i)
    {
        for(int j=2;i*j<=10000;++j) h[i*j]=true;
    }
    ll s=1;
    for(int i=2;i<=10000;++i)
    {
        if(h[i]) continue;
        for(int j=0;j<=10000;++j) b[j]=0;
        for(int j=1;j<=n;++j)
        {
            int x=0;
            while(a[j]%i==0) ++x,a[j]/=i;
            ++b[x];
        }
        int x=0;
        while(k%i==0) ++x,k/=i;
        for(int j=0;j<=10000&&x>0;++j)
        {
            while(b[j]>0&&x>0)
            {
                --b[j];
                ++b[j+1];
                --x;
            }
        }
        for(int j=0;j<=10000;++j)
        {
            while(b[j]>0) s=s*(j+1)%P,--b[j];
        }
    }
    printf("%lld",s);
    return 0;
}