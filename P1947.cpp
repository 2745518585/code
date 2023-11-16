#include <cstdio>
extern "C" int Seniorious(int);
extern "C" int Chtholly(int n,int m)
{
    int l=1,r=n;
    while(l<=r)
    {
        int z=l+r>>1,p=Seniorious(z);
        if(p==0) return z;
        else if(p==1) r=z-1;
        else l=z+1;
    }
    return l;
}