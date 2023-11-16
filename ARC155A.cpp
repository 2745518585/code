#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,fa[N];
ll m;
char a[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int num1(int x)
{
    if(x<=m) return n+x;
    return x-m;
}
int num2(int x)
{
    return x;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld%s",&n,&m,a+1);
        m%=(n*2);
        for(int i=1;i<=n+m;++i) fa[i]=i;
        for(int i=1;i<=(m+n)/2;++i)
        {
            int z1=num1(i),z2=num1((m+n)-i+1);
            if(z1>z2) swap(z1,z2);
            fa[find(z2)]=find(z1);
            z1=num2(i),z2=num2((m+n)-i+1);
            if(z1>z2) swap(z1,z2);
            fa[find(z2)]=find(z1);
        }
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            if(a[i]!=a[find(i)])
            {
                u=false;
                break;
            }
        }
        if(!u) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}