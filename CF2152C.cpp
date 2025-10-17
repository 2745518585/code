#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],b[N],c[N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            b[i]=b[i-1]+(a[i]!=a[i-1]);
            c[i]=c[i-1]+a[i];
        }
        for(int i=1;i<=m;++i)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            if((r-l+1)%3!=0||(c[r]-c[l-1])%3!=0) printf("-1\n");
            else if(b[r]-b[l]==r-l) printf("%d\n",(r-l+1)/3+1);
            else printf("%d\n",(r-l+1)/3);
        }
    }
    return 0;
}