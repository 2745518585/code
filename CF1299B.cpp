#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const ll N=1000001;
struct point
{
    ll x,y;
    point(){}
    point(ll x,ll y):x(x),y(y) {}
    friend point operator +(point a,point b)
    {
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator -(point a,point b)
    {
        return point(a.x-b.x,a.y-b.y);
    }
    friend point operator *(point a,ll b)
    {
        return point(a.x*b,a.y*b);
    }
    friend point operator *(ll b,point a)
    {
        return point(a.x*b,a.y*b);
    }
    friend point operator /(point a,ll b)
    {
        return point(a.x/b,a.y/b);
    }
    friend bool operator ==(point a,point b)
    {
        return a.x==b.x&&a.y==b.y;
    }
    friend ll dot(point a,point b)
    {
        return a.x*b.x+a.y*b.y;
    }
    friend ll cross(point a,point b)
    {
        return a.x*b.y-a.y*b.x;
    }
    void input()
    {
        scanf("%lld%lld",&x,&y);
    }
};
int n;
point a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) a[i].input(); 
    if(n%2!=0)
    {
        printf("NO\n");
        return 0;
    }
    point x=(a[1]+a[n/2+1]);
    for(int i=1;i<=n/2;++i)
    {
        if(!((a[i]+a[n/2+i])==x))
        {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}