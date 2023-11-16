#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,k;
        scanf("%d%d",&n,&k);
        bool u=false;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            if(x==k) u=true;
        }
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}