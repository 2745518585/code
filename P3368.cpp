#include<cstdio>
using namespace std;
typedef long long ll;
int n,m,a[1000001];
ll T[1000001];
int sum(int x)
{
    return x&(-x);
}
void add(int x,int k)
{
    while(x<=n)
    {
        T[x]+=k;
        x+=sum(x);
    }
}
ll find(int x)
{
    ll s=0;
    while(x!=0)
    {
        s+=T[x];
        x-=sum(x);
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    int p=0;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        add(i,x-p);
        p=x;
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            add(x,k);
            add(y+1,-k);
        }
        else
        {
            int x;
            scanf("%d",&x);
            printf("%lld\n",find(x));
        }
    }
    return 0;
}