#include<cstdio>
#include<deque>
using namespace std;
int n,m,a[1000001];
struct str
{
    int x,s;
};
deque<str> q;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        while(!q.empty()&&q.front().x<=i-m) q.pop_front();
        while(!q.empty()&&q.back().s>a[i]) q.pop_back();
        q.push_back((str){i,a[i]});
        if(i>=m) printf("%d ",q.front().s);
    }
    printf("\n");
    q.clear();
    for(int i=1;i<=n;++i)
    {
        while(!q.empty()&&q.front().x<=i-m) q.pop_front();
        while(!q.empty()&&q.back().s<a[i]) q.pop_back();
        q.push_back((str){i,a[i]});
        if(i>=m) printf("%d ",q.front().s);
    }
    return 0;
}