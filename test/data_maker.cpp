#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_all(argc,argv);
    int n=rnd(1,10),m=rnd(1,2e5);
    printf("%d\n",n);
    for(int i=1;i<=n;++i)
    {
        if(i>1)
        {
            int k=rnd(1,2);
            printf("%d ",k);
            for(int j=1;j<=k;++j) printf("%d %d ",rnd(0,5000),rnd(0,5000));
            printf("\n");
        }
        printf("%d %d\n",rnd(0,1e9),rnd(0,1e9));
    }
    printf("%d\n",m);
    for(int i=1;i<=m;++i)
    {
        printf("%d %d %d %lld\n",rnd(1,n),rnd(0,1e9),rnd(0,1e9),rnd(0,1e18));
    }
    return 0;
}