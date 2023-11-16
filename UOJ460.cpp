#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n;
int main()
{
    scanf("%d",&n);
    bool u=n%2;
    n/=2;
    printf("%d\n",n);
    for(int i=1;i<=n;++i)
    {
        printf("%d %d ",i,n+i);
        for(int j=1;j<=n-1;++j) printf("%d %d ",i,i+j);
        for(int j=1;j<=n-1;++j) printf("%d %d ",n+i,(n+i+j-1)%(n*2)+1);
        if(u) printf("%d %d ",i,n*2+1);
        printf("\n");
    }
    return 0;
}