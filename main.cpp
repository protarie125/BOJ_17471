#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;

ll N;
vl P;
vvl adj;
ll ans;
vl grp;
vl g1, g2;
vb visit;
void bfs(ll s, ll g) {
  queue<ll> Q{};
  Q.push(s);

  while (!Q.empty()) {
    auto f = Q.front();
    Q.pop();

    for (const auto& n : adj[f]) {
      if (grp[n] != g) continue;
      if (visit[n]) continue;

      Q.push(n);
      visit[n] = true;
    }
  }
}

void solve(ll k) {
  if (k == N + 1) {
    if (g1.size() == 0 || g2.size() == 0) return;

    ll count1 = 0;
    visit = vb(N + 1, false);
    for (const auto& s : g1) {
      if (visit[s]) continue;
      visit[s] = true;
      ++count1;

      bfs(s, 1);
    }
    if (count1 > 1) return;

    ll count2 = 0;
    visit = vb(N + 1, false);
    for (const auto& s : g2) {
      if (visit[s]) continue;
      visit[s] = true;
      ++count2;

      bfs(s, 2);
    }
    if (count2 > 1) return;

    ll gp1 = 0;
    for (const auto& v : g1) {
      gp1 += P[v];
    }

    ll gp2 = 0;
    for (const auto& v : g2) {
      gp2 += P[v];
    }

    ll ret = abs(gp1 - gp2);
    if (ans == -1) {
      ans = ret;
    } else {
      if (ret < ans) {
        ans = ret;
      }
    }

    return;
  }

  g1.push_back(k);
  grp[k] = 1;
  solve(k + 1);
  g1.pop_back();

  g2.push_back(k);
  grp[k] = 2;
  solve(k + 1);
  g2.pop_back();
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> N;
  P = vl(N + 1);
  for (auto i = 1; i <= N; ++i) cin >> P[i];
  adj = vvl(N + 1, vl{});
  for (auto i = 1; i <= N; ++i) {
    ll c;
    cin >> c;

    adj[i] = vl(c);
    for (auto&& d : adj[i]) cin >> d;
  }

  ans = -1;
  g1 = vl{};
  g2 = vl{};
  grp = vl(N + 1, 0);
  solve(1);
  cout << ans;

  return 0;
}