#include<cstdio>
#include<algorithm>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int T=rnd(1,1);
    printf("%d\n",T);
    while(T--)
    {
        int n=rnd(1,1e4);
        printf("%d\n",n);
        for(int i=1;i<=n;++i) printf("%d ",rnd(1,1e9));
        printf("\n");
    }
    return 0;
}