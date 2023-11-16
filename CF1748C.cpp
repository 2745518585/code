#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=500001;
ll n,a[N],b[N];
bool h[N];
int main()
{
    ll T;
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld",&n);
        for(ll i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            if(a[i]==0) h[i]=true;
            else h[i]=false;
            a[i]+=a[i-1];
        }
        ll s=0,x=1;
        while(x<=n&&h[x]==false) s+=(a[x]==0),++x;
        for(ll i=x;i<=n;++i)
        {
            ll j=i+1;
            while(j<=n&&h[j]==false) ++j;
            ll q=0;
            for(ll k=i;k<=j-1;++k) b[++q]=a[k];
            sort(b+1,b+q+1);
            ll p=0,w=0;
            for(ll k=1;k<=q;++k)
            {
                if(b[k]==b[k-1]) ++p;
                else p=1;
                w=max(w,p);
            }
            s+=w;
            i=j-1;
        }
        printf("%lld\n",s);
    }
    return 0;
}