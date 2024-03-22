#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

// #define Debug
// #define LOCAL
// #define TestCases

const int N = 2e5, Lg = 18;

int n, k;
int a[N + 5];

int nxt[N + 5];
int up[N + 5][2], down[N + 5][2];//0: prefix, 1: suffix
int occ[N + 5];

int jmp[N + 5][Lg + 5][2][2];//u/d, fr/bk

int getval(int u, int ud, int fb, int tar)
{
	if (fb == 0)
	{
		for (int k = Lg; k >= 0; k--)
		{
			if (jmp[u][k][ud][fb] >= tar)
				u = jmp[u][k][ud][fb];
		}
	}
	else
	{
		for (int k = Lg; k >= 0; k--)
		{
			if (jmp[u][k][ud][fb] <= tar)
				u = jmp[u][k][ud][fb];
		}
	}
	return u;
}

int ans = N + 1;
void update(int l, int r)
{
	if (l != -1 && r != -1)
		ans = min(ans, r - l);
	return ;
}

void solve()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);

	if (k & 1)
		return puts("-1"), void();

	for (int i = 1; i <= n; i++)
	{
		up[i][0] = occ[a[i] + 1], down[i][0] = occ[a[i] - 1];
		occ[a[i]] = i;
	}
	for (int i = 0; i <= n + 1; i++)
		occ[i] = n + 1;
	for (int i = n; i > 0; i--)
	{
		nxt[i] = occ[a[i]];
		up[i][1] = occ[a[i] + 1], down[i][1] = occ[a[i] - 1];
		occ[a[i]] = i;
	}

	up[0][0] = down[0][0] = 0, up[0][1] = down[0][1] = n + 1;
	up[n + 1][0] = down[n + 1][0] = 0, up[n + 1][1] = down[n + 1][1] = n + 1;
	for (int i = 0; i <= n + 1; i++)
	{
		jmp[i][0][0][0] = up[i][0], jmp[i][0][0][1] = up[i][1];
		jmp[i][0][1][0] = down[i][0], jmp[i][0][1][1] = down[i][1];
	}
	for (int k = 1; k <= Lg; k++)
	{
		for (int i = 0; i <= n + 1; i++)
		{
			jmp[i][k][0][0] = jmp[ jmp[i][k - 1][0][0] ][k - 1][0][0];
			jmp[i][k][1][0] = jmp[ jmp[i][k - 1][1][0] ][k - 1][1][0];
		}
		for (int i = n + 1; i >= 0; i--)
		{
			jmp[i][k][0][1] = jmp[ jmp[i][k - 1][0][1] ][k - 1][0][1];
			jmp[i][k][1][1] = jmp[ jmp[i][k - 1][1][1] ][k - 1][1][1];
		}
	}

	for (int i = 1; i <= n; i++)
	{
		int u = i, v = nxt[i], L = -1, R = -1;
		if (nxt[i] > n)
			continue;

		int l = 1, r = u;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			int upper = getval(u, 0, 0, mid), lower = getval(u, 1, 0, mid);
			if (a[upper] - a[lower] + 1 >= k / 2)
				L = mid, l = mid + 1;
			else
				r = mid - 1;
		}

		l = v, r = n;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			int upper = getval(u, 0, 1, mid), lower = getval(v, 1, 1, mid);
			if (a[upper] - a[lower] + 1 >= k / 2)
				R = mid, r = mid - 1;
			else
				l = mid + 1;
		}
		update(L, R);

		l = v, r = n, R = -1;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			int upper = getval(v, 0, 1, mid), lower = getval(u, 1, 1, mid);
			if (a[upper] - a[lower] + 1 >= k / 2)
				R = mid, r = mid - 1;
			else
				l = mid + 1;
		}
		update(L, R);

		/*==================================================================*/

		l = v, r = n, R = -1;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			int upper = getval(v, 0, 1, mid), lower = getval(v, 1, 1, mid);
			if (a[upper] - a[lower] + 1 >= k / 2)
				R = mid, r = mid - 1;
			else
				l = mid + 1;
		}

		l = 1, r = u, L = -1;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			int upper = getval(v, 0, 0, mid), lower = getval(u, 1, 0, mid);
			if (a[upper] - a[lower] + 1 >= k / 2)
				L = mid, l = mid + 1;
			else
				r = mid - 1;
		}
		update(L, R);

		l = 1, r = u, L = -1;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			int upper = getval(u, 0, 0, mid), lower = getval(v, 1, 0, mid);
			if (a[upper] - a[lower] + 1 >= k / 2)
				L = mid, l = mid + 1;
			else
				r = mid - 1;
		}
		update(L, R);
	}

	if (ans > n)
		ans = -1;
	printf("%d\n", ans);
	return ;
}

int main()
{
	#ifdef LOCAL
	freopen("data.in", "r", stdin);
	freopen("mycode.out", "w", stdout);
	#endif
	
	int T = 1;
	
	#ifdef TestCases
	scanf("%d", &T);
	#endif
	
	while (T--)
		solve();
	return 0;
}
