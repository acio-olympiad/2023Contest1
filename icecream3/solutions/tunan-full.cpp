#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> pii;
const int MAX = 100001;

vector<pii> graph[200005];
int N, M;

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[u+MAX].emplace_back(v+MAX, w);
        graph[v].emplace_back(u, w);
        graph[v+MAX].emplace_back(u+MAX, w);
        graph[u].emplace_back(v+MAX, 0);
        graph[v].emplace_back(u+MAX, 0);
    }
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> dist(MAX*2, 2069696969);
    auto maybe = [&](uint64_t d, size_t v) {
        if(d >= dist[v]) return;
        pq.emplace(dist[v] = d, v);
    };

    maybe(0, 1);
    
    while (!pq.empty()) {
        const auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (const auto [v, w] : graph[u]) {
            maybe(dist[u] + w, v);
        }
    }

    cout << dist[N+MAX] << "\n";
}
