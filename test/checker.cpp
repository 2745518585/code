#include<bits/stdc++.h>
#include"include/testlib.h"
using namespace std;
const int N=1001;
int n,a[N],b[N];
int main(int argc,char **argv)
{
    registerTestlibCmd(argc,argv);
    n=inf.readInt();
    for(int i=1;i<=n;++i) a[i]=inf.readInt();
    for(int i=1;i<=n;++i) b[i]=inf.readInt();
    string p1=ans.readString(),p2=ouf.readString();
    if(p1!=p2)
    {
        quitf(_wa,"Wrong Answer");
    }
    int m=ouf.readInt();
    for(int l=1;l<=m;++l)
    {
        int x=ouf.readInt(),y=ouf.readInt(),w=0;
        if(x<1||x>n||y<1||y>n)
        {
            quitp(2,"invaild operation");
        }
        if(x>y)
        {
            for(int i=x+1;i<=y;++i) w+=(a[x]<a[i]?1:-1);
            if(w!=0)
            {
                quitp(2,"invaild operation");
            }
            for(int i=x+1;i<=y;++i) swap(a[i-1],a[i]);
        }
        else
        {
            for(int i=x-1;i>=y;--i) w+=(a[x]<a[i]?1:-1);
            if(w!=0)
            {
                quitp(2,"invaild operation");
            }
            for(int i=x-1;i>=y;--i) swap(a[i+1],a[i]);
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]!=b[i])
        {
            quitf(_wa,"Wrong Answer");

        }
    }
    quitf(_ok,"Accepted");
    return 0;
}