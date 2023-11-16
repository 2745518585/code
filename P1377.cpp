#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,a[N],b[N],t;
struct tree
{
    int l,r;
}T[N];
void print(int x)
{
    if(x==0) return;
    printf("%d ",x);
    print(T[x].l);
    print(T[x].r);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a[x]=i;
    }
    for(int i=1;i<=n;++i)
    {
        int x=t;
        while(x!=0&&a[b[x]]>a[i]) --x;
        if(x!=0) T[b[x]].r=i;
        if(x<t) T[i].l=b[x+1];
        b[++x]=i;
        t=x;
    }
    print(b[1]);
    return 0;
}