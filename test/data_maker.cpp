#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    printf("1\n");
    int n=rnd(1,100),m=rnd(1,100);
    printf("%d %d\n",n,m);
    for(int i=1;i<=m;++i) cout<<rnd_pair<_LES>(0,n)<<" "<<rnd(1,100)<<"\n";
    return 0;
}