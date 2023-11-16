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
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            printf("%d ",i+10000000);
        }
        printf("\n");
    }
    return 0;
}