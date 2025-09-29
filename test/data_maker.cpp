#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_all(argc,argv);
    int TOT=rnd(1,1000);
    printf("%d\n",TOT);
    while(TOT--)
    {
        int n=rnd(1,10),m=rnd(1,10);
        printf("%d %d\n",n,m);
        auto a=rnd_range(n),b=rnd_range(n);
        for(auto i:a) printf("%d ",i);printf("\n");
        for(auto i:b) printf("%d ",i);printf("\n");
        for(int i=1;i<=m;++i)
        {
            printf("%d %d %d\n",rnd(1,2),rnd(1,n),rnd(1,n));
        }
    }
    return 0;
}