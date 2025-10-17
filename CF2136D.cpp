#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll K=1e9;
int n;
struct str
{
    ll x,y;
    str() {}
    str(ll x,ll y):x(x),y(y) {}
}a[N];
ll move(char c,ll k)
{
    printf("? %c %lld\n",c,k);
    fflush(stdout);
    ll x;
    scanf("%lld",&x);
    return x;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int p1=1,p2=1;
        for(int i=1;i<=n;++i)
        {
            scanf("%lld%lld",&a[i].x,&a[i].y);
            if(a[i].x+a[i].y>a[p1].x+a[p1].y) p1=i;
            if(a[i].x-a[i].y>a[p2].x-a[p2].y) p2=i;
        }
        move('U',K);
        move('U',K);
        move('R',K);
        ll x1=move('R',K);
        move('D',K);
        move('D',K);
        move('D',K);
        ll x2=move('D',K);
        ll x=a[p1].x+(x1+x2+(a[p1].y-a[p2].y)-(a[p1].x-a[p2].x)-K*4)/2,y=a[p1].y+(x1-(x-a[p1].x));
        printf("! %lld %lld\n",x-K*2,y-K*2);
        fflush(stdout);
    }
    return 0;
}