#include<cstdio>
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
ll a,b;
const ll p=19260817;
inline ll read()
{
    char c=getchar();ll x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=((x<<1)+(x<<3)+(c^48))%p;
    if(f)x=-x;return x;
}
void abc(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else abc(b,a%b,y,x),y-=a/b*x;
}
int main()
{
    a=read();
    b=read();
    if(b==0)
    {
        printf("Angry!");
        return 0;
    }
    ll x,y;
    abc(b,p,x,y);
    x=(x%p+p)%p;
    printf("%lld",a*x%p);
    return 0;
}