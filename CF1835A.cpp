#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int pw10[11];
int main()
{
    pw10[0]=1;
    for(int i=1;i<=7;++i) pw10[i]=pw10[i-1]*10;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int a,b,c;
        ll k;
        scanf("%d%d%d%lld",&a,&b,&c,&k);
        bool u=false;
        for(int i=pw10[a-1];i<=pw10[a]-1;++i)
        {
            int x1=max(i+pw10[b-1],pw10[c-1]),x2=min(i+pw10[b]-1,pw10[c]-1);
            if(x1>x2) continue;
            if(k<=x2-x1+1)
            {
                int z=x1+k-1;
                printf("%d + %d = %d\n",i,z-i,z);
                u=true;
                break;
            }
            k-=(x2-x1+1);
        }
        if(!u) printf("-1\n");
    }
    return 0;
}