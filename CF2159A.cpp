#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
bool h[N];
int query(int l,int r)
{
    int s=0;
    for(int i=l;i<=r;++i) if(!h[i]) ++s;
    if(s==0) return 0;
    printf("? %d ",s);
    for(int i=l;i<=r;++i) if(!h[i]) printf("%d ",i);
    printf("\n");
    fflush(stdout);
    int x;
    scanf("%d",&x);
    return x;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n*2;++i) a[i]=0,h[i]=false;
        for(int i=1;i<=n*2;++i)
        {
            int x=query(1,i);
            if(x!=0) a[i]=x,h[i]=true;
        }
        for(int i=1;i<=n*2;++i) h[i]=false;
        for(int i=n*2;i>=1;--i)
        {
            if(a[i]) continue;
            int x=query(i,n*2);
            if(x!=0) a[i]=x,h[i]=true;
        }
        printf("! ");
        for(int i=1;i<=n*2;++i) printf("%d ",a[i]);
        printf("\n");
        fflush(stdout);
    }
    return 0;
}