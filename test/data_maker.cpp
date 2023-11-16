#include<cstdio>
#include<algorithm>
#include"D:\Orita\data_maker.hpp"
using namespace std;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int T=rnd(1,1);
    printf("%d\n",T);
    while(T--)
    {
        int n=rnd(5e5,5e5);
        printf("%d\n",n);
        for(int i=1;i<=n;++i) printf("%d ",rnd(1e9-10,1e9));
        printf("\n");
    }
    return 0;
}