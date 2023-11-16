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
        if(n%2==1) printf("-1\n");
        else printf("1 %d\n",n/2);
    }
    return 0;
}