#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(1,5),m=rnd(1,5),q=rnd(1,5);
    cout<<n<<" "<<m<<" "<<q<<"\n";
    for(int i=1;i<=q;++i)
    {
        cout<<rnd_pair<_LOE>(1,n)<<" "<<rnd(1,m)<<"\n";
    }
    return 0;
}