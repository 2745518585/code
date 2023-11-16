#include<cstdio>
#include<algorithm>
using namespace std;
const int N=101;
int n;
void abc()
{
    scanf("%d",&n);
    if(n&1)
    {
        printf("1 ");
        for(int i=n-2;i>=2;--i) printf("%d ",i);
    }
    else for(int i=n-2;i;--i) printf("%d ",i);
    printf("%d %d\n",n-1,n);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}