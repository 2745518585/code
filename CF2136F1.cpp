#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n=100000,q,a[N];
int sum(int x)
{
    int s=1,w=x;
    for(int i=1;i<=q;++i)
    {
        if(w<a[i]) ++s,w=x;
        w-=a[i];
    }
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        printf("? %d ",n);
        for(int i=1;i<=n;++i) printf("1 ");
        printf("\n");
        fflush(stdout);
        int x;
        scanf("%d",&x);
        int l=(n-1)/x+1,r=(x>1?(n-1)/(x-1):n);
        if(l==r)
        {
            printf("! %d\n",l);
            fflush(stdout);
            continue;
        }
        q=0;
        for(int i=l+1;i<=r;++i)
        {
            a[++q]=l;
            a[++q]=i-l;
        }
        q=min(q,n);
        printf("? %d ",q);
        for(int i=1;i<=q;++i) printf("%d ",a[i]);
        printf("\n");
        fflush(stdout);
        scanf("%d",&x);
        if(x==0) return 1;
        while(l<r)
        {
            int z=l+r>>1;
            if(sum(z)<=x) r=z;
            else l=z+1;
        }
        printf("! %d\n",l);
        fflush(stdout);
    }
    return 0;
}