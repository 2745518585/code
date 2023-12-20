#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(2,5),m=rnd(1,5);
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;++i)
    {
        printf("%d %d\n",rnd(1,2),rnd(1,2));
    }
    auto a=rnd_tree(n);
    for(auto i:a) printf("%d %d\n",i.first,i.second);
    for(int i=1;i<=m;++i)
    {
        printf("%d %d\n",rnd(1,n),rnd(1,n));
    }
    return 0;
}