#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        int s=0,w=0;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            s^=x;
            if(x>1) w=1;
        }
        if((s!=0)^(w!=0)) printf("Brother\n");
        else printf("John\n");
    }
    return 0;
}