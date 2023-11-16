#include<bits/stdc++.h>
using namespace std;
int n,s=2,a[20];
int main()
{
    scanf("%d",&n);
    if(n==1)
    {
        printf("0");
        return 0;
    }
    --n;
    for(int i=1;i<=n;++i)
    {
        int x=i,a[20],t=0;
        for(int j=2;j*j<=x;++j)
        {
            if(x%j==0) a[++t]=j;
            while(x%j==0) x/=j;
        }
        if(x!=1) a[++t]=x;
        int d=0;
        for(int j=0;j<=(1<<t)-1;++j)
        {
            int q=1,w=0;
            for(int k=1;k<=t;++k)
            {
                if((j&(1<<(k-1)))!=0)
                {
                    ++w;
                    q*=a[k];
                }
            }
            if(w%2==0) d+=(n/q);
            else d-=(n/q);
        }
        s+=d;
    }
    printf("%d",s);
    return 0;
}