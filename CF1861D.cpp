#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],f1[N],f2[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        f1[1]=0;
        for(int i=2;i<=n;++i)
        {
            f1[i]=f1[i-1];
            if(a[i-1]<=a[i]) ++f1[i];
        }
        f2[n]=0;
        for(int i=n-1;i>=1;--i)
        {
            f2[i]=f2[i+1];
            if(a[i]>=a[i+1]) ++f2[i];
        }
        int s=min(f1[n]+1,f2[1]);
        for(int i=1;i<=n-1;++i)
        {
            s=min(s,f1[i]+f2[i+1]+1);
        }
        printf("%d\n",s);
    }
    return 0;
}