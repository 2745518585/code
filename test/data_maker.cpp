#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int T=rnd(1,1);
    cout<<T<<"\n";
    while(T--)
    {
        int n=rnd(1,5),m=rnd(1,5);
        cout<<n<<" "<<m<<"\n";
        for(int i=1;i<=m;++i)
        {
            cout<<rnd(1,n)<<" "<<rnd(1,n)<<"\n";
        }
    }
    return 0;
}