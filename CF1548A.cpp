#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,a[N],s;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        s-=(a[x]>0)+(a[y]>0);
        a[x]+=y>x;
        a[y]+=x>y;
        s+=(a[x]>0)+(a[y]>0);
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            s-=(a[x]>0)+(a[y]>0);
            a[x]+=y>x;
            a[y]+=x>y;
            s+=(a[x]>0)+(a[y]>0);
        }
        else if(z==2)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            s-=(a[x]>0)+(a[y]>0);
            a[x]-=y>x;
            a[y]-=x>y;
            s+=(a[x]>0)+(a[y]>0);
        }
        else if(z==3)
        {
            printf("%d\n",n-s);
        }
    }
    return 0;
}