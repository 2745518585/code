#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n;
struct str
{
    int s1,s2;
    str():s1(0),s2(0){}
    str(int s1,int s2):s1(s1),s2(s2){}
    friend str max(str a,str b)
    {
        if(a.s1>b.s1) return str(a.s1,max(a.s2,b.s1));
        else return str(b.s1,max(a.s1,b.s2));
    }
}f[N];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<=(1<<n)-1;++i)
    {
        int x;
        scanf("%d",&x);
        f[i]=str(x,0);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=(1<<n)-1;++j)
        {
            if(j&(1<<(i-1))) f[j]=max(f[j],f[j^(1<<(i-1))]);
        }
    }
    int s=f[0].s1+f[0].s2;
    for(int i=1;i<=(1<<n)-1;++i)
    {
        s=max(s,f[i].s1+f[i].s2);
        printf("%d\n",s);
    }
    return 0;
}