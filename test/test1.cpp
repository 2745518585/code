#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,k,a[N];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
int main()
{
    scanf("%d%d",&n,&k);
    int w=0;
    for(int i=1;i<=k;++i) w+=(a[i]=i);
    a[k+1]=n;
    int t=k;
    while(gcd(w,n)!=1)
    {
        while(a[t]+1>=a[t+1]) --t;
        ++a[t],++w;
    }
    int x=1;
    for(int i=1;i<=n-1;++i)
    {
        for(int j=1;j<=k;++j)
        {
            x=(x+a[j]-1)%n+1;
            printf("%d ",x);
        }
    }
    return 0;
}