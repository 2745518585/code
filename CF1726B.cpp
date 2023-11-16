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
        if((n%2==0&&m%2==1)||m<n)
        {
            printf("No\n");
            continue;
        }
        printf("Yes\n");
        if(n%2==0)
        {
            for(int i=1;i<=n-2;++i)
            {
                printf("1 ");
            }
            printf("%d %d\n",(m-n+2)/2,(m-n+2)/2);
        }
        else
        {
            for(int i=1;i<=n-1;++i)
            {
                printf("1 ");
            }
            printf("%d\n",m-n+1);
        }
    }
    return 0;
}