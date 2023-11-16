#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001;
int n,q,a[N],b[N];
struct tree
{
    int T[N];
    int lowbit(int x)
    {
        return x&-x;
    }
    void add(int x,int k)
    {
        T[x]+=k;
        while(x<=q)
        {
            x+=lowbit(x);
            T[x]+=k;
        }
    }
    int sum(int x)
    {
        int s=T[x];
        while(x!=0)
        {
            x-=lowbit(x);
            s+=T[x];
        }
        return s;
    }
}T1,T2;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    q=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
    }
    for(int i=1;i<=n;++i)
    {
        T2.add(a[i],1);
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(i>1) T1.add(a[i-1],1);
        T2.add(a[i],-1);
        int x=(i-1)-T1.sum(a[i]),y=(n-i)-T2.sum(a[i]);
        if(max(x,y)>min(x,y)*2) ++s;
    }
    printf("%d",s);
    return 0;
}