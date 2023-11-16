#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,k;
int main()
{
    scanf("%d%d",&n,&k);
    if(k<=n/2)
    {
        for(int i=1;i<=k-1;++i) printf("LDRU");
        printf("L");
    }
    else
    {
        for(int i=1;i<=n-2-k;++i) printf("RDLU");
        for(int i=1;i<=n;++i) printf("LDLU");
        printf("RDL");
    }
    return 0;
}