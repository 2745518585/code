#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
int n,s,a[N];
bool h[N];
struct str
{
    int x,s;
}b[N];
bool cmp(str a,str b)
{
    return a.s<b.s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i].s);
        b[i].x=i;
    }
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
        a[b[i].x]=i;
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]==i||h[i]==true) continue;
        int x=a[i],k=b[i].s,q=b[i].s,w=1;
        while(x!=i)
        {
            k=min(k,b[x].s);
            q+=b[x].s;
            ++w;
            h[x]=true;
            x=a[x];
        }
        s+=min(q+(w-2)*k,q+k+(w+1)*b[1].s);
    }
    printf("%d",s);
    return 0;
}