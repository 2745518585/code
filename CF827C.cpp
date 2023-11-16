#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=150001,M=11,K=5;
int n,m,b[N],T[M][M][K][N];
char a[N];
void add(int T[],int x,int k)
{
    T[x]+=k;
    while(x<=n)
    {
        x+=(x&-x);
        T[x]+=k;
    }
}
int sum(int T[],int x)
{
    int s=T[x];
    while(x>=1)
    {
        x-=(x&-x);
        s+=T[x];
    }
    return s;
}
int main()
{
    b['A']=1,b['T']=2,b['G']=3,b['C']=4;
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=10;++j) add(T[j][i%j][b[a[i]]],i,1);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x;
            char z[10];
            scanf("%d%s",&x,z);
            for(int j=1;j<=10;++j) add(T[j][x%j][b[a[x]]],x,-1);
            a[x]=z[0];
            for(int j=1;j<=10;++j) add(T[j][x%j][b[a[x]]],x,1);
        }
        else if(z==2)
        {
            int x,y;
            char z[20];
            scanf("%d%d%s",&x,&y,z+1);
            int q=strlen(z+1),s=0;
            for(int i=1;i<=q;++i)
            {
                s+=(sum(T[q][(x+i-1)%q][b[z[i]]],y)-sum(T[q][(x+i-1)%q][b[z[i]]],x-1));
            }
            printf("%d\n",s);
        }
    }
    return 0;
}