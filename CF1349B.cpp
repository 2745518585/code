#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,k,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        bool v=false;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            if(a[i]==k) v=true;
        }
        a[n+1]=0;
        bool u=false;
        for(int i=1;i<=n-1;++i)
        {
            if(a[i]>=k&&(a[i+1]>=k||a[i+2]>=k)) u=true;
        }
        if(n==1) u=true;
        if(u&&v) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}