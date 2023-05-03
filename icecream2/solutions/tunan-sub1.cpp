#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;
typedef pair<int, int> pii;

int N, M, P;
vector<pii> graph[100005];
long long ans;

void solve(int s, int t) {
    priority_queue<pii, vector<pii>, greater<pii>> pq{};
    vector<int> dist(N, 2069696969);
    dist[s] = 0;
    pq.emplace(0, s);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        if (u == t) {
            ans += dist[u];
            return;
        }
        for (auto [v, w] : graph[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
}

int main() {
    cin >> N >> M >> P;
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    vector<int> a(P);
    for (int i = 0; i < P; i++) {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i + 1 < P; i++) {
        solve(a[i], a[i+1]);
    }
    cout << ans << "\n";
}
