#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        int s=0,q=0;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            if(x>s) s=x,q=i;
        }
        printf("%d\n",q);
    }
    return 0;
}