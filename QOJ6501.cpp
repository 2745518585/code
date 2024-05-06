#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,fa[N];
bool h[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n*2-2;++i) fa[i]=i;
    for(int i=1;i<=n*2-2;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x==y)
        {
            printf("0");
            return 0;
        }
        if(x>y) swap(x,y);
        y+=n-2;
        x=find(x),y=find(y);
        if(x!=y)
        {
            h[x]|=h[y];
            fa[y]=x;
        }
        else h[x]=true;
    }
    ll s=1;
    for(int i=1;i<=n*2-2;++i)
    {
        if(find(i)!=i) continue;
        if(h[i]==false) s=0;
        s=s*2%P;
    }
    printf("%lld",s);
    return 0;
}