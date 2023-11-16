#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%*s%*s%*s",&n);
        printf("1");
        for(int i=1;i<=n;++i) printf("0");
        for(int i=1;i<=n;++i) printf("1");
        printf("\n");
    }
    return 0;
}