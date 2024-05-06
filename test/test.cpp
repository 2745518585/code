#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll a[N],b[N];
ll solve(ll *a,int l,int r)
{
    ll w=0,s=0;
    for(int i=l;i<=r;++i)
    {
        w=max(w+a[i],0ll);
        s=max(s,w);
    }
    return s;
}
int main(int argc,char **argv)
{
    ifstream infile(argv[1]);
    int T;
    infile>>T;
    cout<<T<<"\n"<<flush;
    while(T--)
    {
        infile>>n;
        for(int i=1;i<=n;++i) infile>>a[i];
        cerr<<n<<"\n";
        for(int i=1;i<=n;++i) cerr<<a[i]<<" ";cerr<<"\n";
        cout<<n<<"\n"<<flush;
        char c;
        while(cin>>c,c=='?')
        {
            int l,r;
            cin>>l>>r;
            cout<<solve(a,l,r)<<"\n"<<flush;
            // cerr<<l<<" "<<r<<" "<<solve(a,l,r)<<"\n";
        }
        for(int i=1;i<=n;++i) cin>>b[i];
        for(int i=1;i<=n;++i)
        {
            for(int j=i;j<=n;++j)
            {
                if(solve(a,i,j)!=solve(b,i,j)) return 1;
            }
        }
    }
    return 0;
}