#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m;
struct road
{
    int x,y,w;
    road(){}
    road(int x,int y,int w):x(x),y(y),w(w){}
}a[N];
void solve(int k)
{
    int z=k/2;
    while(z) ++n,z/=2;
    for(int i=0;i<=n-1;++i)
    {
        a[++m]=road(1,i+2,1);
        for(int j=i+1;j<=n-1;++j)
        {
            a[++m]=road(i+2,j+2,1<<i);
        }
        a[++m]=road(i+2,n+3,1<<i);
    }
    a[++m]=road(1,n+3,1);
    for(int i=0;i<=n-1;++i)
    {
        if(k&(1<<i)) a[++m]=road(i+2,n+2,((k>>(i+1))<<(i+1))-1);
    }
    a[++m]=road(n+2,n+3,1);
}
int main()
{
    int l,r;
    scanf("%d%d",&l,&r);
    printf("YES\n");
    solve(r-l+1);
    if(l>1) a[++m]=road(n+3,n+4,l-1);
    printf("%d %d\n",n+3+(l>1),m);
    for(int i=1;i<=m;++i)
    {
        printf("%d %d %d\n",a[i].x,a[i].y,a[i].w);
    }
    return 0;
}