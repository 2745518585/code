#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(1,10),m=rnd(1,10);
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;++i) printf("%d ",rnd(1,10));printf("\n");
    for(int i=1;i<=m;++i)
    {
        if(rnd(2)) printf("1 %d %d\n",rnd(1,n),rnd(1,10));
        else cout<<"2 "<<rnd_pair<_LOE>(1,n)<<"\n";
    }
    return 0;
}