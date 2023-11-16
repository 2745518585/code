#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
struct point
{
    int x,y;
    point() {}
    point(int x,int y):x(x),y(y) {}
}a[N];
priority_queue<int> Q1;
priority_queue<int,vector<int>,greater<int>> Q2;
bool cmp(point a,point b)
{
    return a.x+a.y<b.x+b.y;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    sort(a+1,a+n+1,cmp);
    ll s=0;
    int w=0;
    Q1.push(a[1].x);
    Q2.push(a[1].x);
    for(int i=2;i<=n;++i)
    {
        w+=(a[i].x+a[i].y)-(a[i-1].x+a[i-1].y);
        if(a[i].x<Q1.top())
        {
            s+=Q1.top()-a[i].x;
            Q2.push(Q1.top()-w);
            Q1.pop();
            Q1.push(a[i].x);
            Q1.push(a[i].x);
        }
        else if(a[i].x>Q2.top()+w)
        {
            s+=a[i].x-(Q2.top()+w);
            Q1.push(Q2.top()+w);
            Q2.pop();
            Q2.push(a[i].x-w);
            Q2.push(a[i].x-w);
        }
        else
        {
            Q1.push(a[i].x);
            Q2.push(a[i].x-w);
        }
    }
    printf("%lld",s);
    return 0;
}