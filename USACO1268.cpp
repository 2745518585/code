#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int n,m,a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        m+=a[i];
    }
    int x=0,d=1;
    for(int i=1;i<=m;++i)
    {
        if(d==1)
        {
            if(a[x+1]>0)
            {
                --a[x+1];
                ++x;
            }
            else
            {
                d^=1;
                --a[x];
                --x;
            }
        }
        else
        {
            if((a[x]==1&&a[x+1]>0)||a[x]==0)
            {
                d^=1;
                --a[x+1];
                ++x;
            }
            else
            {
                --a[x];
                --x;
            }
        }
        if(d==1) putchar('R');
        else putchar('L');
    }
    return 0;
}