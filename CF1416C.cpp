#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
struct str
{
    int x,t;
    str(){}
    str(int x,int t):x(x),t(t){}
}b[N];
bool cmp(str a,str b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.t<b.t;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    ll s=0;
    int x=0;
    for(int i=30;i>=0;--i)
    {
        for(int j=1;j<=n;++j) b[j]=str(a[j]>>(i+1),j);
        sort(b+1,b+n+1,cmp);
        ll w1=0,w2=0;
        int q1=0,q2=0;
        for(int j=1;j<=n;++j)
        {
            if((a[b[j].t]>>(i+1))!=(a[b[j-1].t]>>(i+1))) q1=q2=0;
            if((a[b[j].t]&(1<<i))==0)
            {
                ++q1;
                w1+=q2;
            }
            else
            {
                ++q2;
                w2+=q1;
            }
        }
        if(w1>w2) x|=(1<<i);
        s+=min(w1,w2);
    }
    printf("%lld %d",s,x);
    return 0;
}