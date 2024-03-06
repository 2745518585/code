#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int T=2;
    printf("0 %d\n",T);
    while(T--)
    {
        int n=2,m=rnd(0,1e9),k=rnd(0,30);
        printf("%d %d %d\n",n,m,k);
        for(int i=1;i<=n;++i) printf("%d ",rnd(0,(1<<k)-1));printf("\n");
        for(int i=1;i<=n;++i) printf("%d ",rnd(0,m));printf("\n");
    }
    return 0;
}