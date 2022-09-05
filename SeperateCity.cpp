#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {

	int id;
	int rank;
	int parent;

	Node(int _id) : id(_id), rank(0), parent(_id) {}

};

struct Edge {
	int src;
	int dst;
	int weight;

	bool operator >(const Edge& e) const {
		return weight > e.weight;
	}

	bool operator <(const Edge& e) const {
		return weight < e.weight;
	}

};

class DisjointSet {
private:
	vector<Node> nodes;

public:

	void make_set(int x) { nodes.emplace_back(x); }

	int find(int id) {

		while (id != nodes[id].parent)
			id = nodes[id].parent;

		return id;
	}

	void union_set(int x, int y) {
		int root_x = find(x);
		int root_y = find(y);

		if (root_x == root_y)
			return;

		if (nodes[root_x].rank > nodes[root_y].rank)
			swap(root_x, root_y);
		// x는 반드시 y보다 랭크가 작아야함.
		// 만약 그렇지 못할 경우 x와 y를 교체한다.

		nodes[root_x].parent = nodes[root_y].parent;
		nodes[root_y].rank++;
	}

};


vector<Edge> Kruskal(vector<Edge>& graph, int vertex_count) {

	sort(graph.begin(), graph.end(), greater<>());

	DisjointSet dset;

	for (int i = 0; i < vertex_count; i++)
		dset.make_set(i);

	vector<Edge> MST;

	while (graph.empty() == false) {
		Edge e = graph.back();
		graph.pop_back();

		if (dset.find(e.src) != dset.find(e.dst)) {
			MST.emplace_back(Edge{ e.src, e.dst, e.weight });
			dset.union_set(e.src, e.dst);
		}

	}

	return MST;
}


int main() {

	vector<Edge> map;

	int node_count;
	int edge_count;

	cin >> node_count >> edge_count;
	
	map.reserve(edge_count);

	for (int i = 0; i < edge_count; i++) {
		int src, dst, cost;
		cin >> src >> dst >> cost;
		map.push_back({src - 1, dst - 1, cost});
		// 엣지 번호와 DisjointSet의 노드 번호가 1씩 차이가 나므로 (DisjoinSet은 Zero-Base, 엣지 번호는 1부터 시작)
		// 각 정점에서 -1씩 뺀다.
	}

	vector<Edge> MST =  Kruskal(map, node_count);
	// 최소 신장 트리를 만든 후

	int result = 0 , max_cost = 0;

	for (int i = 0; i < MST.size(); i++) {
		max_cost = max(MST[i].weight, max_cost);
		// 만들어진 최소 신장트리에서 가장 가중치가 큰 엣지를 제거하여 마을을 두개로 쪼갠다.
		result += MST[i].weight;
	}

	
	result -= max_cost;
	// 최종 비용에서 마을을 쪼개는 엣지의 비용을 뺀다.
	cout << result;

	return 0;
}