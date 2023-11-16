#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int sum(int x)
{
    if(x<1||x>n) return 1e9;
    if(a[x]!=0) return a[x];
    printf("? %d\n",x);
    fflush(stdout);
    scanf("%d",&a[x]);
    return a[x];
}
int main()
{
    scanf("%d",&n);
    int l=1,r=n;
    while(l<r)
    {
        int z=l+r>>1;
        if(sum(z)<sum(z+1)) r=z;
        else l=z+1;
    }
    printf("! %d\n",l);
    fflush(stdout);
    return 0;
}