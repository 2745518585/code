#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],b[N];
int main()
{
    scanf("%d",&n);
    int x=1e9;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        x=min(x,a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        a[i]-=x-1;
        if(a[i]>n)
        {
            printf("NO");
            return 0;
        }
        ++b[a[i]];
    }
    int u=0;
    for(int i=1;i<=n;++i)
    {
        if(b[i]) u+=b[i];
        else if(u<n)
        {
            printf("NO");
            return 0;
        }
    }
    int w=0;
    for(int i=1;i<=n;++i)
    {
        if(b[i]==0) break;
        if(w>b[i]*2||(b[i-1]!=0&&w==0))
        {
            printf("NO");
            return 0;
        }
        if(w<=b[i])
        {
            w+=(b[i]-w)*2;
        }
        else
        {
            w-=(w-b[i])*2;
        }
    }
    if(w) printf("NO");
    else printf("YES");
    return 0;
}