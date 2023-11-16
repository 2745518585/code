#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],f[N];
bool h[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        ++f[a[i]];
    }
    ll s=1;
    for(ll i=2;i<=200000;++i)
    {
        if(h[i]) continue;
        for(ll j=2;i*j<=200000;++j) h[i*j]=true;
        int w=n;
        for(ll j=1;i*j<=200000;++j) w-=f[i*j];
        if(w>=2) continue;
        for(ll j=i;j<=200000;j*=i)
        {
            for(ll k=1;j*k<=200000;++k)
            {
                if(k%i==0) continue;
                w+=f[j*k];
                if(w>=2)
                {
                    s*=j;
                    break;
                }
            }
            if(w>=2) break;
        }
    }
    printf("%lld",s);
    return 0;
}