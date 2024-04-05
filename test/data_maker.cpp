#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(1,5),k=rnd(1,n);
    printf("%d %d\n",n,k);
    auto a=rnd_tree(n);
    for(auto i:a) printf("%d %d\n",i.first,i.second);
    for(int i=1;i<=n;++i) printf("%d ",rnd(1,n));
    return 0;
}