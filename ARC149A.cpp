#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll m;
int main()
{
    scanf("%d%d",&n,&m);
    ll s=0;
    int x=0,y=0;
    for(int i=1;i<=9;++i)
    {
        ll s=0;
        for(int j=1;j<=n;++j)
        {
            s=(s*10+i)%m;
            if(s==0)
            {
                if(j>x||(j==x&&i>y)) x=j,y=i;
            }
        }
    }
    if(x!=0)
    {
        for(int i=1;i<=x;++i) printf("%d",y);
    }
    else printf("-1");
    return 0;
}