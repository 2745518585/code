#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int n;
struct str
{
    int a,b,x;
    friend bool operator <(str a,str b)
    {
        if(a.a-a.b!=b.a-b.b&&(a.a-a.b)*(b.a-b.b)<=0) return a.a-a.b<b.a-b.b;
        if(a.a-a.b<0) return a.a<b.a;
        return a.b>b.b;
    }
}a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].a);
        a[i].x=i;
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].b);
    }
    sort(a+1,a+n+1);
    int t1=0,t2=0;
    for(int i=1;i<=n;++i)
    { 
        t1+=a[i].a;
        t2=max(t1,t2)+a[i].b;
    }
    printf("%d\n",t2);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",a[i].x);
    }
    return 0;
}