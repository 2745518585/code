#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N=3000001;
int n;
struct num
{
    ll a,b;
    num(){}
    num(ll a,ll b):a(a),b(b){}
    friend num operator +(num a,num b)
    {
        return num(a.a+b.a,a.b+b.b);
    }
    friend num operator -(num a,num b)
    {
        return num(a.a-b.a,a.b-b.b);
    }
    friend bool operator !=(num a,num b)
    {
        return a.a!=b.a||a.b!=b.b;
    }
    num check(num a)
    {
        return num(2*a.a*a.a,2*a.a*a.b);
    }
}a[N];
void abc()
{
    scanf("%d",&n);
    a[1]=num(1,0);
    for(int i=1;i<=n;++i)
    {
        ll x;
        scanf("%lld",&x);
        a[i+1]=num(0,x)-a[i];
    }
    if(a[1]!=a[n+1])
    {
        num t=a[1]-a[n+1];
        if(t.a==0&&t.b!=0)
        {
            printf("Painfully lose rank#1\n");
            return;
        }
        if(t.b!=0)
        {
            double r=(double)-t.b/t.a,s=0;
            for(int i=1;i<=n;++i)
            {
                if(a[i].a*r+a[i].b<0)
                {
                    printf("Painfully lose rank#1\n");
                    return;
                }
                s+=(a[i].a*r+a[i].b)*(a[i].a*r+a[i].b);
            }
            printf("%.3lf\n",s);
            return;
        }
    }
    double r1=-1e9,r2=1e9;
    for(int i=1;i<=n;++i)
    {
        if(a[i].a>0) r1=max(r1,(double)-a[i].b/a[i].a);
        else r2=min(r2,(double)-a[i].b/a[i].a);
    }
    if(r2<r1)
    {
        printf("Painfully lose rank#1\n");
        return;
    }
    double s1=0,s2=0;
    for(int i=1;i<=n;++i)
    {
        s1+=(a[i].a*r1+a[i].b)*(a[i].a*r1+a[i].b);
        s2+=(a[i].a*r2+a[i].b)*(a[i].a*r2+a[i].b);
    }
    num t=num(0,0);
    for(int i=1;i<=n;++i)
    {
        t=t+a[i].check(a[i]);
    }
    if(t.b==0)
    {
        printf("%.3lf\n",min(s1,s2));
        return;
    }
    double r=(double)-t.b/t.a;
    ld s=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i].a*r+a[i].b<0)
        {
            printf("%.3lf\n",min(s1,s2));
            return;
        }
        s+=(a[i].a*r+a[i].b)*(a[i].a*r+a[i].b);
    }
    printf("%.3Lf\n",s);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}