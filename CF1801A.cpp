#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int m,n;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        printf("%d\n",m*n);
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                printf("%d ",(i<<15)+j);
            }
            printf("\n");
        }
    }
    return 0;
}