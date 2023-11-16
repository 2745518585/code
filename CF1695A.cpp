#include<cstdio>
#include<algorithm>
using namespace std;
int m,n,qx,qy,s;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        s=-2e9;
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                int x;
                scanf("%d",&x);
                if(x>s) s=x,qx=i,qy=j;
            }
        }
        printf("%d\n",max(qx,m-qx+1)*max(qy,n-qy+1));
    }
    return 0;
}