#include<cstdio>
#include<algorithm>
#include<random>
#include<map>
using namespace std;
map<int,int> Map;
int move(int x)
{
    printf("walk %d\n",x);
    fflush(stdout);
    int z;
    scanf("%d",&z);
    return z;
}
int rnd()
{
    mt19937 rnd(random_device{}());
    return (uniform_int_distribution<int>(1,1e9))(rnd);
}
int main()
{
    int p=0;
    for(int i=1;i<=1000;++i) p=max(p,move(rnd()));
    for(int i=1;i<=4500;++i)
    {
        int x=move(1);
        if(Map.count(x))
        {
            printf("guess %d\n",i-Map[x]);
            fflush(stdout);
            return 0;
        }
        Map[x]=i;
    }
    move(p);
    for(int i=1;i<=4500;++i)
    {
        int x=move(4500);
        if(Map.count(x))
        {
            printf("guess %d\n",i*4500-Map[x]+p);
            fflush(stdout);
            return 0;
        }
    }
    return 0;
}