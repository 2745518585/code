#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
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
        if(n%2==1)
        {
            printf("Second\n");
            continue;
        }
        sort(a+1,a+n+1);
        int w=0;
        bool u=false;
        for(int i=1;i<=n;++i)
        {
            if(a[i]==a[i-1]) ++w;
            else
            {
                if(w%2==1) u=true;
                w=1;
            }
        }
        if(w%2==1) u=true;
        if(u) printf("First\n");
        else printf("Second\n");
    }
    return 0;
}