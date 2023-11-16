#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=100000;
int n,m,a[5],b[5];
ll f[M+1];
int main()
{
    scanf("%d%d%d%d%d",&a[1],&a[2],&a[3],&a[4],&n);
    f[0]=1;
    for(int i=1;i<=4;++i)
    {
        for(int j=a[i];j<=M;++j)
        {
            f[j]+=f[j-a[i]];
        }
    }
    while(n--)
    {
        scanf("%d%d%d%d%d",&b[1],&b[2],&b[3],&b[4],&m);
        ll s=0;
        for(int i=0;i<=15;++i)
        {
            int q=m,w=0;
            for(int j=1;j<=4;++j)
            {
                if((i&(1<<(j-1)))!=0)
                {
                    ++w;
                    q-=a[j]*(b[j]+1);
                }
            }
            if(q<0) continue;
            if(w%2==0) s+=f[q];
            else s-=f[q];
        }
        printf("%lld\n",s);
    }
    return 0;
}