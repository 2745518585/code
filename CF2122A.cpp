#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int m,n;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        if(m==1||n==1||(m==2&&n==2)) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}