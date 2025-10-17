#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=100;++i) a[i]=0;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            ++a[x];
        }
        int s=0;
        for(int i=1;i<=100;++i)
        {
            if(a[i]>0) ++s;
        }
        printf("%d\n",s*2-1);
    }
    return 0;
}