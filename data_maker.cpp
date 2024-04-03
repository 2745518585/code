#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
typedef long long ll;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(1,100),m=rnd(1,100);
    cout<<n<<" "<<m<<"\n";
    for(int i=1;i<=n;++i) cout<<rnd(1,m)<<" ";
    cout<<"\n";
    return 0;
}