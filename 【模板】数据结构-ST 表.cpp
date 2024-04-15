#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=200001,M=31;
int n,a[N];
namespace ST
{
    int b[N][M],lg[N];
    void init()
    {
        for(int i=1;i<=n;++i) b[i][0]=a[i];
        for(int i=1;i<=20;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+(1<<i)-1<=n) b[j][i]=min(b[j][i-1],b[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        if(x>y) swap(x,y);
        return min(b[x][lg[y-x]],b[y-(1<<lg[y-x])+1][lg[y-x]]);
    }
}
int main()
{

    return 0;
}