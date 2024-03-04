#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            if(i%2) printf("%d ",i/2+1);
            else printf("%d ",n-i/2+1);
        }
        printf("\n");
    }
    return 0;
}