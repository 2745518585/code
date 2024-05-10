#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(1,5000);
    for(int i=1;i<=n;++i) cout<<rnd(1,1e9)<<" ";
    for(int i=1;i<=n;++i) cout<<rnd(1,10)<<" ";
    cout<<"\n";
    auto a=rnd_tree(n);
    for(auto i:a) cout<<i.first<<" "<<i.second<<"\n";
    return 0;
}