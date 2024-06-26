#include<cstdio>
#include<algorithm>
#include<deque>
#include<vector>
using namespace std;
const int N=1000001;
int n,q,k;
char a1[N],a2[N];
vector<pair<int,int>> ans;
int sum(int x)
{
    return ((x-1)%n+n)%n+1;
}
void movel(char *a,int &t,deque<char> &Q)
{
    int k=Q.size();
    --t;
    a[sum(t+k)]=Q.back();
    Q.pop_back();
    Q.push_front(a[sum(t)]);
}
void mover(char *a,int &t,deque<char> &Q)
{
    int k=Q.size();
    a[sum(t)]=Q.front();
    Q.pop_front();
    Q.push_back(a[sum(t+k)]);
    ++t;
}
int main()
{
    scanf("%d%d%s%s",&n,&k,a1+1,a2+1);
    int q=0;
    for(int i=1;i<=n;++i) q+=(a1[i]=='C');
    bool u=false;
    if(q>n/2) swap(a1,a2),q=n-q,u=true;
    deque<char> Q1,Q2;
    int t1=1,t2=1;
    for(int i=1;i<=k+1;++i) Q1.push_back(a1[i]);
    for(int i=1;i<=k;++i) Q2.push_back(a2[i]);
    for(int i=1;i<=q;++i)
    {
        while(Q1.back()!='C') mover(a1,t1,Q1);
        while(Q2.front()!='B') movel(a2,t2,Q2);
        Q1.pop_back();
        Q1.push_front('B');
        Q2.pop_front();
        Q2.push_back('C');
        ans.push_back(make_pair(sum(t1),sum(t2)));
        ans.push_back(make_pair(sum(t1+1),sum(t2)));
    }
    printf("%d\n",ans.size());
    for(auto i:ans)
    {
        if(u) swap(i.first,i.second);
        printf("%d %d\n",i.first,i.second);
    }
    return 0;
}