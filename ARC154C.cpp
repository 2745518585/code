#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N],b[N];
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
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
            if(a[i]!=b[i]) u=false;
        }
        if(u)
        {
            printf("Yes\n");
            continue;
        }
        m=1;
        for(int i=2;i<=n;++i)
        {
            if(b[i]!=b[m]) b[++m]=b[i];
        }
        while(m>1&&b[m]==b[1]) --m;
        if(m==n)
        {
            printf("No\n");
            continue;
        }
        for(int i=1;i<=n;++i) a[n+i]=a[i];
        u=false;
        for(int i=1;i<=n;++i)
        {
            int x=1;
            for(int j=i;j<=i+n-1;++j)
            {
                if(x<=m&&a[j]==b[x]) ++x;
            }
            if(x==m+1)
            {
                u=true;
                break;
            }
        }
        if(u) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}