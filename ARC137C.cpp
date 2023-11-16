#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    if(a[n]-a[n-1]>1||(a[n]-n)%2==0) printf("Alice");
    else printf("Bob");
    return 0;
}