#include<cstdio>
#include<algorithm>
using namespace std;
bool query(int);
void modify(int,bool);
bool WereYouLast(int n,int m)
{
    if(n==1024)
    {
        int s=0;
        for(int i=1;i<=10;++i) s|=(query(i)<<(i-1));
        ++s;
        for(int i=1;i<=10;++i) modify(i,(s&(1<<(i-1)))!=0);
        return s==1024;
    }
    int t=0;
    for(int i=1;i<=5;++i) t|=(query(i)<<(i-1));
    int p=0;
    while((1<<p)!=n) ++p;
    if(t==p) return true;
    if(query(t+10))
    {
        modify(t+10,0);
        ++t;
    }
    else
    {
        modify(t+10,1);
        if(t==p-1) t=p;
        else t=0;
    }
    for(int i=1;i<=5;++i) modify(i,(t&(1<<(i-1)))!=0);
    return false;
}