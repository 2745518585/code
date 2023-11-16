#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
bool h[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,k,x;
        scanf("%d%d%d",&n,&k,&x);
        for(int i=1;i<=n;++i) h[i]=false;
        int w=0;
        for(int i=1;i<=n;++i) w^=i;
        if(!((k%2==0&&w==0)||(k%2==1&&w==x)))
        {
            printf("NO\n");
            continue;
        }
        int s=0;
        for(int i=1;i<=n;++i)
        {
            if(i==x)
            {
                ++s;
                h[x]=true;
            }
            else if((i^x)<=n&&h[i^x]==false)
            {
                ++s;
                h[i]=h[i^x]=true;
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(h[i]==false)
            {
                ++s;
                break;
            }
        }
        if(s<k)
        {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        for(int i=1;i<=n;++i) h[i]=false;
        s=0;
        for(int i=1;i<=n;++i)
        {
            if(s==k-1) break;
            if(i==x)
            {
                printf("1 %d\n",x);
                ++s;
                h[x]=true;
            }
            else if((i^x)<=n&&h[i^x]==false)
            {
                printf("2 %d %d\n",i,i^x);
                ++s;
                h[i]=h[i^x]=true;
            }
        }
        int z=0;
        for(int i=1;i<=n;++i) z+=(h[i]==false);
        printf("%d ",z);
        for(int i=1;i<=n;++i)
        {
            if(h[i]==false) printf("%d ",i);
        }
        printf("\n");
    }
    return 0;
}