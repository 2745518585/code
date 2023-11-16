#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,T[N];
struct str
{
    int x,y;
}a[N];
bool check(int x)
{
    int w=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i].x>=w&&a[i].y>=x-w-1) ++w;
    }
    return w>=x;
}
int main()
{
    int TT;
    scanf("%d",&TT);
    while(TT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&a[i].y,&a[i].x);
        }
        int l=1,r=n;
        while(l<r)
        {
            int z=l+r+1>>1;
            if(check(z)) l=z;
            else r=z-1;
        }
        printf("%d\n",l);
    }
    return 0;
}