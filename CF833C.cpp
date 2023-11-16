#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=101;
int a[N],b[N],c[N],l[N],r[N];
ll s=0;
bool check1(int x)
{
    for(int i=0;i<=9;++i) c[i]=b[i];
    for(int i=9;i>=0;--i)
    {
        while(c[i]>0&&i==l[x]) --c[i],--x;
        if(c[i]>0&&l[x]>i) return false;
        if(c[i]>0&&l[x]<i) return true;
    }
    return true;
}
bool check2(int x)
{
    for(int i=0;i<=9;++i) c[i]=b[i];
    for(int i=0;i<=9;++i)
    {
        while(c[i]>0&&i==r[x]) --c[i],--x;
        if(c[i]>0&&r[x]<i) return false;
        if(c[i]>0&&r[x]>i) return true;
    }
    return true;
}
bool check()
{
    for(int i=0;i<=9;++i) b[i]=a[i];
    for(int i=19;i>=1;--i)
    {
        for(int j=l[i]+1;j<=r[i]-1;++j)
        {
            if(b[j]>0) return true;
        }
        if(l[i]==r[i]&&b[l[i]]>0)
        {
            --b[l[i]];
            continue;
        }
        if(b[l[i]]>0)
        {
            --b[l[i]];
            if(check1(i-1)) return true;
            ++b[l[i]];
        }
        if(b[r[i]]>0)
        {
            --b[r[i]];
            if(check2(i-1)) return true;
            ++b[r[i]];
        }
        return false;
    }
    return true;
}
void dfs(int x,int t)
{
    if(x==20)
    {
        if(check()) ++s;
        return;
    }
    for(int i=t;i<=9;++i)
    {
        ++a[i];
        dfs(x+1,i);
        --a[i];
    }
}
int main()
{
    ll x,y;
    scanf("%lld%lld",&x,&y);
    for(int i=1;i<=19;++i) l[i]=x%10,x/=10;
    for(int i=1;i<=19;++i) r[i]=y%10,y/=10;
    dfs(1,0);
    printf("%lld",s);
    return 0;
}