#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_all(argc,argv);
    int n=2e6;
    for(int i=1;i<=n;++i) printf("%c",rnd('a','z'));printf("\n");
    for(int i=1;i<=n;++i) printf("%c",rnd('a','z'));printf("\n");
    print_info(n);
    return 0;
}