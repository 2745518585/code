#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=100;++i) a[i]=1;
        int x=n;
        for(int i=2;i*i<=n;++i)
        {
            int z=0;
            while(x%i==0)
            {
                a[++z]*=i;
                x/=i;
            }
        }
        if(x!=1) a[1]*=x;
        int s=0;
        for(int i=1;i<=100;++i) if(a[i]>1) s+=a[i];
        printf("%d\n",s);
    }
    return 0;
}