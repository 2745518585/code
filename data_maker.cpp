#include<bits/stdc++.h>
#include<D:\Orita\data_maker.hpp>
using namespace std;
typedef long long ll;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int T=rnd(1,1);
    printf("%d\n",T);
    while(T--)
    {
        int n=rnd(1e3,1e3);
        printf("%d\n",n);
        for(int i=1;i<=n-1;++i) printf("%d ",rnd(1,i));printf("\n");
        for(int i=1;i<=n+1;++i) printf("%d ",rnd(1,1e9));printf("\n");
    }
    return 0;
}