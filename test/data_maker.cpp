#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(1,100),m=rnd(1,100);
    cout<<n<<" "<<m<<"\n";
    for(int i=1;i<=n;++i)
    {
        cout<<rnd_pair<_LOE>(1,n)<<"\n";
    }
    for(int i=1;i<=m;++i)
    {
        cout<<rnd_pair<_LOE>(1,n)<<"\n";
    }
    return 0;
}