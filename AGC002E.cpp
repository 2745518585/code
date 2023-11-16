#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int main()
{
    scanf("%d",&n);
    a[0]=1e9;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1,[&](int x,int y){return x>y;});
    int q=0;
    for(int i=1;i<=n;++i)
    {
        if(i<=a[i]&&i>=a[i+1]) q=i-1;
    }
    int t=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]==q+1) t=i-1;
    }
    if((a[q+1]-1-q)%2==1||(t-q)%2==1) printf("First\n");
    else printf("Second\n");
    return 0;
}