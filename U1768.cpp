#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int n,m;
double k;
struct str
{
    double a,b;
}a[N];
bool cmp(str a,str b)
{
    if(a.a!=b.a) return a.a<b.a;
    return a.b<b.b;
}
void abc()
{
    scanf("%d%d%lf",&n,&m,&k);
    k=(double)k/2;
    for(int i=1;i<=n;++i)
    {
        int x,r;
        scanf("%d%d",&x,&r);
        if(r<k)
        {
            a[i].a=a[i].b=x;
            continue;
        }
        a[i].a=x-sqrt(r*r-k*k);
        a[i].b=x+sqrt(r*r-k*k);
    }
    sort(a+1,a+n+1,cmp);
    int t=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i].a>0) break;
        if(a[i].b>a[t].b) t=i;
    }
    if(t==0)
    {
        printf("-1\n");
        return;
    }
    int s=0;
    while(true)
    {
        ++s;
        if(a[t].b>=m)
        {
            printf("%d\n",s);
            return;
        }
        int d=t;
        for(int i=t+1;i<=n;++i)
        {
            if(a[i].a>a[t].b) break;
            if(a[i].b>=a[d].b) d=i;
        }
        if(d==t) break;
        t=d;
    }
    printf("-1\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}