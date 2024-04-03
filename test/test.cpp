#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N],b[N];
int solve(int n,int *a)
{
    for(int i=1;i<=n;++i) a[n+i]=a[i];
    int p=1e9;
    for(int i=1;i<=n;++i) p=min(p,a[i]);
    if(n%2==1&&p>0) return n;
    int x=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]==p)
        {
            x=i;
            break;
        }
    }
    int s=0;
    while(x<=n)
    {
        int y=x+1;
        while(a[y]!=p) ++y;
        if((y-x)%2==0) s+=y-x;
        else s+=(y-x)/2;
        x=y;
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            a[x]=k;
        }
        else if(z==2)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            for(int j=1;j<=r-l+1;++j) b[j]=a[l+j-1];
            printf("%d\n",solve(r-l+1,b));
        }
    }
    return 0;
}