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
        int s=0,u=0;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            if(u==0&&x!=0) ++s;
            if(x!=0) u=1;
            else u=0;
        }
        printf("%d\n",min(s,2));
    }
    return 0;
}