#include<bits/stdc++.h>
using namespace std;
const int N=2000001;
int n,a[N];
void solve()
{
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=1;j<=(1<<n)-1;j<<=1)
        {
            for(int k=j<<1;k<=(1<<n)-1;k<<=1)
            {
                if(a[i|j]+a[i|k]<a[i]+a[i|j|k])
                {
                    printf("%d %d\n",i|j,i|k);
                    return;
                }
            }
        }
    }
    printf("-1\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<=(1<<n)-1;++i)
        {
            scanf("%d",&a[i]);
        }
        solve();
    }
    return 0;
}