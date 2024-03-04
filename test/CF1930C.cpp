#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            a[i]+=i;
        }
        sort(a+1,a+n+1,[](int x,int y){return x>y;});
        int x=2e9,w=0;
        for(int i=1;i<=n;++i)
        {
            while(x>a[i]&&w>0) printf("%d ",x),--x,--w;
            ++w;
            x=a[i];
        }
        while(w>0) printf("%d ",x),--x,--w;
        printf("\n");
    }
    return 0;
}