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
        int x=0;
        while(n>=10)
        {
            n/=10;
            ++x;
        }
        printf("%d\n",n%10+x*9);
    }
    return 0;
}