#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
using it=set<int>::iterator;
const int N=1000001;
int m;
set<int> Set;
int main()
{
    int x,y;
    scanf("%d%d%d",&m,&x,&y);
    Set.insert(x-y);
    Set.insert(x+y);
    for(int i=1;i<=m;++i)
    {
        int z,x,y;
        scanf("%d%d%d",&z,&x,&y);
        if(z==1)
        {
            Set.insert(x-y);
            Set.insert(x+y);
        }
        else
        {
            it p=Set.lower_bound(x);
            if(p!=Set.end()&&(*p)<=y)
            {
                printf("0\n");
                continue;
            }
            int s=1e9;
            if(p!=Set.begin()) s=min(s,x-(*prev(p)));
            if(p!=Set.end()) s=min(s,(*p)-y);
            printf("%d\n",s);
        }
    }
    return 0;
}