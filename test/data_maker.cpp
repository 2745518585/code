#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_all(argc,argv);
    int n=rnd(1,5),m=rnd(1,5);
    cout<<n<<" "<<m<<"\n";
    for(int i=1;i<=n;++i) cout<<rnd(1,5)<<" ";cout<<"\n";
    for(int i=1;i<=m;++i) cout<<rnd_pair<_LOE>(1,n)<<" "<<rnd(1,5)<<" "<<rnd(0,1)<<"\n";
    return 0;
}