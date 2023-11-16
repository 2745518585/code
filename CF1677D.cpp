#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,k,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        bool u=false;
        for(int i=1;i<=n-k;++i)
        {
            if(a[i]>=i)
            {
                u=true;
                break;
            }
        }
        for(int i=n-k+1;i<=n;++i)
        {
            if(a[i]!=0&&a[i]!=-1)
            {
                u=true;
                break;
            }
        }
        if(u)
        {
            printf("0\n");
            continue;
        }
        ll s=1;
        for(int i=1;i<=k;++i) s=s*i%P;
        for(int i=1;i<=n-k;++i)
        {
            if(a[i]==-1) s=s*(i+k)%P;
            if(a[i]==0) s=s*(k+1)%P;
        }
        printf("%lld\n",s);
    }
    return 0;
}