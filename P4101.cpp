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
        printf("%d\n",!((n-((n-1)/m+1))%2));
    }
    return 0;
}