#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,b[N];
ll a[N],s=0;
bool cmp(int x,int y)
{
    return ((-a[x])%x+x)%x<((-a[y])%y+y)%y;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        s=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            s+=a[i];
        }
        if(s%n!=0)
        {
            printf("-1\n");
            continue;
        }
        s/=n;
        printf("%d\n",(n-1)*3);
        for(int i=1;i<=n-1;++i) b[i]=i+1;
        sort(b+1,b+n,cmp);
        int x=1;
        for(int i=1;i<=n-1;++i)
        {
            printf("%d %d %lld\n",1,b[i],((-a[b[i]])%b[i]+b[i])%b[i]);
            a[b[i]]+=((-a[b[i]])%b[i]+b[i])%b[i];
            printf("%d %d %lld\n",b[i],1,a[b[i]]/b[i]);
        }
        for(int i=2;i<=n;++i)
        {
            printf("%d %d %lld\n",1,i,s);
        }
    }
    return 0;
}