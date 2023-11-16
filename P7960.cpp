#include<cstdio>
#include<algorithm>
using namespace std;
const int N=20000001;
int n,a[N];
bool h[N];
bool check(int x)
{
    while(x)
    {
        if(x%10==7) return false;
        x/=10;
    }
    return true;
}
void init()
{
    for(int i=1;i<=11000000;++i)
    {
        if(!check(i)&&h[i]==false)
        {
            h[i]=true;
            for(int j=2;i*j<=11000000;++j) h[i*j]=true;
        }
        if(h[i]==false) a[++n]=i;
    }
}
int main()
{
    init();
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int x;
        scanf("%d",&x);
        int z=lower_bound(a+1,a+n+1,x)-a;
        if(a[z]!=x) printf("-1\n");
        else printf("%d\n",a[z+1]);
    }
    return 0;
}