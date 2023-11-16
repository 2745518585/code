#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        int w=0;
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            s+=x;
            w=max(w,x);
        }
        if(w>s-w||s%2==1) printf("T\n");
        else printf("HL\n");
    }
    return 0;
}