#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N];
int main()
{
    scanf("%d%d",&n,&m);
    m=m*8/n;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    a[0]=-1;
    if(m>30)
    {
        printf("0");
        return 0;
    }
    int x=0,w=0,s=0;
    for(int i=1;i<=n;++i)
    {
        while(x<=n&&w<=(1<<m))
        {
            ++x;
            w+=a[x]!=a[x-1];
        }
        s=max(s,x-i);
        w-=a[i]!=a[i+1];
    }
    printf("%d",n-s);
    return 0;
}