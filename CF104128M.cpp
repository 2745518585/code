#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
struct point
{
    int x,y;
    point(){}
    point(int x,int y):x(x),y(y) {}
    friend point operator +(point a,point b)
    {
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator -(point a,point b)
    {
        return point(a.x-b.x,a.y-b.y);
    }
    friend int dot(point a,point b)
    {
        return a.x*b.x+a.y*b.y;
    }
    friend int cross(point a,point b)
    {
        return a.x*b.y-a.y*b.x;
    }
    void input()
    {
        scanf("%d%d",&x,&y);
    }
};
int n,m;
point a[N],b[N];
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i) b[i].input(),b[m+i]=b[i];
    b[0]=b[m];
    for(int i=1;i<=m;++i)
    {
        if(cross(b[i-1]-b[i],b[i]-b[i+1])!=0) a[++n]=b[i];
    }
    if(n==0)
    {
        printf("1\n");
        return 0;
    }
    for(int i=1;i<=n;++i) a[n+i]=a[i];
    a[0]=a[n];
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i+1].y-a[i].y==0)
        {
            if(a[i].x<=a[i+1].x&&a[i].y-a[i-1].y<0&&a[i+2].y-a[i+1].y>0) ++s;
        }
        else if(a[i+1].y-a[i].y>0)
        {
            if(a[i].y-a[i-1].y<0&&cross(a[i]-a[i-1],a[i+1]-a[i])>0) ++s;
        }
    }
    printf("%d",s);
    return 0;
}