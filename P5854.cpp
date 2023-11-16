#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=10000001;
int n,a[N],b[N],t;
struct tree
{
    int l,r;
}T[N];
int main()
{
    n=read();
    for(int i=1;i<=n;++i)
    {
        a[i]=read();
        int x=t;
        while(x!=0&&a[b[x]]>a[i]) --x;
        if(x!=0) T[b[x]].r=i;
        if(x<t)T[i].l=b[x+1];
        b[++x]=i;
        t=x;
    }
    ll s1=0,s2=0;
    for(int i=1;i<=n;++i)
    {
        s1^=(ll)i*(T[i].l+1);
        s2^=(ll)i*(T[i].r+1);
    }
    printf("%lld %lld",s1,s2);
    return 0;
}