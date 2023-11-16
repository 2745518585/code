#include<cstdio>
#include<algorithm>
using namespace std;
int n,w1,w2,q1=1e9,q2=1e9;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        w1+=x,w2+=y;
        q1=min(q1,x),q2=min(q2,y);
    }
    if(w1<w2) printf("%d",w2+q1);
    else printf("%d",w1+q2);
    return 0;
}