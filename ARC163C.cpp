#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        if(n==2)
        {
            printf("No\n");
            continue;
        }
        printf("Yes\n");
        int z=sqrt(n);
        if(z*(z+1)==n)
        {
            printf("2 ");
            for(int i=1;i<=n-2;++i) printf("%d ",i*(i+1)*2);
            printf("%d\n",(n-1)*2);
        }
        else
        {
            for(int i=1;i<=n-1;++i) printf("%d ",i*(i+1));
            printf("%d\n",n);
        }
    }
    return 0;
}