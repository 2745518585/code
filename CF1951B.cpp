#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,k,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        swap(a[1],a[k]);
        int s=0;
        for(int i=2;i<=n;++i)
        {
            if(a[i]<a[1]) ++s;
            else break;
        }
        swap(a[1],a[k]);
        int x=0;
        for(int i=1;i<=k-1;++i)
        {
            if(a[i]>a[k])
            {
                x=i;
                break;
            }
        }
        if(x!=0)
        {
            swap(a[x],a[k]);
            int w=0;
            if(x>1) ++w;
            for(int i=x+1;i<=n;++i)
            {
                if(a[i]<a[x]) ++w;
                else break;
            }
            s=max(s,w);
        }
        printf("%d\n",s);
    }
    return 0;
}