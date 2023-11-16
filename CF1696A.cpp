#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        int s=0;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            s=max(s,x|m);
        }
        printf("%d\n",s);
    }
    return 0;
}