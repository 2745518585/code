#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int m,n,k,a[N],b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&m,&n,&k);
        for(int i=1;i<=k;++i)
        {
            scanf("%d",&a[i]);
            b[a[i]]=i;
        }
        int t=0,w=0;
        bool u=true;
        for(int i=k;i>=1;--i)
        {
            if(b[i]>t)
            {
                w+=b[i]-t;
                t=b[i];
            }
            if(w>=m*n-2)
            {
                u=false;
                break;
            }
            --w;
        }
        if(u) printf("YA\n");
        else printf("TIDAK\n");
    }
    return 0;
}