#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int n;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ll s=0;
        int w=0;
        for(int i=1;i<=n;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            s+=min(x,y);
            w=max(w,max(x,y));
        }
        printf("%lld\n",(s+w)*2);
    }
    return 0;
}