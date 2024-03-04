#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
int query(int a,int b,int c,int d)
{
    printf("? %d %d %d %d\n",a,b,c,d);
    fflush(stdout);
    char z[10];
    scanf("%s",z);
    if(z[0]=='<') return -1;
    else if(z[0]=='=') return 0;
    else return 1;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int x=0,y=0;
        for(int i=1;i<=n-1;++i)
        {
            if(query(i,i,x,x)>0) x=i;
        }
        for(int i=1;i<=n-1;++i)
        {
            int z=query(i,x,y,x);
            if(z==1) y=i;
            else if(z==0&&query(i,i,y,y)<0) y=i;
        }
        printf("! %d %d\n",x,y);
        fflush(stdout);
    }
    return 0;
}