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
		// x�� �ݵ�� y���� ��ũ�� �۾ƾ���.
		// ���� �׷��� ���� ��� x�� y�� ��ü�Ѵ�.

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
		// ���� ��ȣ�� DisjointSet�� ��� ��ȣ�� 1�� ���̰� ���Ƿ� (DisjoinSet�� Zero-Base, ���� ��ȣ�� 1���� ����)
		// �� �������� -1�� ����.
	}

	vector<Edge> MST =  Kruskal(map, node_count);
	// �ּ� ���� Ʈ���� ���� ��

	int result = 0 , max_cost = 0;

	for (int i = 0; i < MST.size(); i++) {
		max_cost = max(MST[i].weight, max_cost);
		// ������� �ּ� ����Ʈ������ ���� ����ġ�� ū ������ �����Ͽ� ������ �ΰ��� �ɰ���.
		result += MST[i].weight;
	}

	
	result -= max_cost;
	// ���� ��뿡�� ������ �ɰ��� ������ ����� ����.
	cout << result;

	return 0;
}