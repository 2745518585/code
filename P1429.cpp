#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
int n;
struct point
{
    int x,y;
    point(){}
    point(int x,int y):x(x),y(y){}
}a[N],p[N];
bool cmp(point a,point b)
{
    return a.y<b.y;
}
double dis(point a,point b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}
double solve(int l,int r,int ml,int mr)
{
    if(l>=r||ml>mr) return 1e9;
    if(ml==mr)
    {
        double s=1e9;
        for(int i=l;i<=r-1;++i)
        {
            s=min(s,dis(a[i],a[i+1]));
        }
        return s;
    }
    int z=ml+mr>>1,p1=l-1,p2=r+1;
    for(int i=l;i<=r;++i)
    {
        if(a[i].x<=z) p[++p1]=a[i];
        else p[--p2]=a[i];
    }
    for(int i=l;i<=r;++i) a[i]=p[i];
    double s=min(solve(l,p1,ml,z),solve(p2,r,z+1,mr));
    int t=0;
    for(int i=p2;i<=r;++i)
    {
        if(a[i].x-z<=s) p[++t]=a[i];
    }
    p[t+1]=p[t+2]=point(1e9,1e9);
    int x=1;
    for(int i=l;i<=p1;++i)
    {
        if(a[i].x-z>s) continue;
        while(x<=t&&p[x].y<a[i].y-s) ++x;
        for(int j=x;j<=t&&p[j].y<=a[i].y+s;++j) s=min(s,dis(a[i],p[j]));
    }
    int x1=l,x2=p2;
    for(int i=l;i<=r;++i)
    {
        if(x1<=p1&&(x2>r||a[x1].y<a[x2].y)) p[i]=a[x1++];
        else p[i]=a[x2++];
    }
    for(int i=l;i<=r;++i) a[i]=p[i];
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    sort(a+1,a+n+1,cmp);
    printf("%.4lf",solve(1,n,0,1e9));
    return 0;
}