#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
int n,m,a[N],T[N];
void add(int x,int k)
{
    T[x]+=k;
    while(x<=n)
    {
        x+=(x&(-x));
        T[x]+=k;
    }
}
int sum(int x)
{
    int s=T[x];
    while(x!=0)
    {
        x-=(x&(-x));
        s+=T[x];
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        add(i,x);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,z;
        scanf("%d%d%d",&z,&x,&y);
        if(z==1)
        {
            add(x,y);
        }
        else
        {
            printf("%d\n",sum(y)-sum(x-1));
        }
    }
    return 0;
}