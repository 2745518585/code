#include<cstdio>
#include<algorithm>
using namespace std;
int sum(int x)
{
    int s1=10,s2=-1;
    while(x)
    {
        s1=min(s1,x%10);
        s2=max(s2,x%10);
        x/=10;
    }
    return s2-s1;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        if(r-l>=200)
        {
            printf("%d\n",(l/100+1)*100+90);
            continue;
        }
        int s=-1,q=0;
        for(int i=l;i<=r;++i)
        {
            int z=sum(i);
            if(z>s) s=z,q=i;
        }
        printf("%d\n",q);
    }
    return 0;
}