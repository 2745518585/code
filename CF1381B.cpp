#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],b[N];
bool f[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n*2;++i) b[i]=0;
        int w=0;
        for(int i=1;i<=n*2;++i)
        {
            scanf("%d",&a[i]);
            w=max(w,a[i]);
            ++b[w];
        }
        for(int i=1;i<=n;++i) f[i]=false;
        f[0]=true;
        for(int i=1;i<=n*2;++i)
        {
            for(int j=n;j>=b[i];--j) f[j]|=f[j-b[i]];
        }
        if(f[n]) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}