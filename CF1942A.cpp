#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,k;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        if(k==1)
        {
            for(int i=1;i<=n;++i) printf("%d ",(i!=1)+1);
            printf("\n");
        }
        else if(k==n)
        {
            for(int i=1;i<=n;++i) printf("%d ",1);
            printf("\n");
        }
        else printf("-1\n");
    }
    return 0;
}