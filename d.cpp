//  https://codeforces.com/contest/1923/problem/D

#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> check_box, pref, a;

inline int Pref(int l, int r) {
  return pref[r] - (l > 0 ? pref[l - 1] : 0);
}
inline int Check_box(int l, int r) {
  return check_box[r] - (l > 0 ? check_box[l - 1] : 0);
}
inline bool check(int i, int l, int r) {
  if(r < l) return 0;
  return (Pref(l, r) > a[i] && (r == l || (Check_box(l, r) != 0 && Check_box(l, r) != r - l + 1))) ||
    (i + 1 == l && a[i] < a[l]) || (i - 1 == r && a[i] < a[r]);
}

inline int right_bin_search(int i, int l, int r) {
  while(l < r) {
    int m = (l + r) / 2;
    if(check(i, i + 1, m)) {
      r = m;
    } else l = m + 1;
  }
  return l;
}

inline int left_bin_search(int i, int l, int r) {
  while(l < r) {
    int m = (l + r + 1) / 2;
    if(check(i, m, i - 1)) {
      l = m;
    } else r = m - 1;
  }
  return l;
}

inline void solve() {
  int n;
  cin >> n;
  a.assign(n, 0);
  for(auto& i : a) cin >> i;
  check_box.assign(n, 0);
  for(int i = 1; i < n; ++i) {
    if(a[i] == a[i-1]) check_box[i] = check_box[i - 1];
    else check_box[i] = 1 - check_box[i - 1];
  }
  for(int i = 1; i < n; ++i) check_box[i] += check_box[i - 1];
  pref.assign(n, 0);
  pref[0] = a[0];
  for(int i = 1; i < n; ++i) pref[i] = pref[i - 1] + a[i];
  for(int i = 0; i < n; ++i) {
    int left_ans = -1;
    int right_ans = -1;
    if(check(i, 0, i - 1)) { 
      left_ans = i - left_bin_search(i, 0, i - 1);
    }
    if(check(i, i + 1, n - 1)) {
      right_ans = right_bin_search(i, i + 1, n - 1) - i;
    }
    if(left_ans == -1 && right_ans == -1) {
      cout << -1 << ' ';
    } else if(left_ans == -1) {
      cout << right_ans << ' ';
    } else if(right_ans == -1) {
      cout << left_ans << ' ';
    } else {
      cout << min(left_ans, right_ans) << ' ';
    }
  }
  cout << endl;
}

signed main() {
  int t;
  cin >> t;
  while (t--) solve();
}
