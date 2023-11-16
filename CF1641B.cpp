#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int n,m,q,w,a[N],c[N];
struct str
{
    int x,k;
    str(){}
    str(int x,int k):x(x),k(k){}
}b[N*N];
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
        }
        m=q=w=0;
        while(n)
        {
            int x=0;
            for(int i=2;i<=n;++i)
            {
                if(a[i]==a[1])
                {
                    x=i;
                    break;
                }
            }
            if(x==0)
            {
                printf("-1\n");
                break;
            }
            for(int i=1;i<=x;++i) ++m;
            for(int i=2;i<=x-1;++i)
            {
                b[++q]=str(m,a[i]);
                ++m;
            }
            c[++w]=m;
            for(int i=2;i<=x/2;++i) swap(a[i],a[x-i+1]);
            for(int i=2;i<=x-1;++i) a[i-1]=a[i];
            for(int i=x+1;i<=n;++i) a[i-2]=a[i];
            n-=2;
        }
        if(n!=0) continue;
        printf("%d\n",q);
        for(int i=1;i<=q;++i)
        {
            printf("%d %d\n",b[i].x,b[i].k);
        }
        printf("%d\n",w);
        for(int i=1;i<=w;++i)
        {
            printf("%d ",c[i]-c[i-1]);
        }
        printf("\n");
    }
    return 0;
}