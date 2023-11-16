#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=m;++i)
        {
            int x;
            scanf("%d",&x);
            int q=1;
            for(int j=2;j<=n;++j) if(a[j]<a[q]) q=j;
            a[q]=x;
        }
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            s+=a[i];
        }
        printf("%lld\n",s);
    }
    return 0;
}