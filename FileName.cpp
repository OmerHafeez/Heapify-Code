#include <iostream>

using namespace std;

class MinHeap {
public:
    int* heap;
    int capacity;
    int size;


    void heapify(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != idx) {
            swap(heap[idx], heap[smallest]);
            heapify(smallest);
        }
    }



    MinHeap(int capacity) : capacity(capacity), size(0) {
        heap = new int[capacity];
    }


    ~MinHeap() {
        delete[] heap;
    }


    void insert(int value) {
        if (size == capacity)
            return; 

        int idx = size;
        heap[idx] = value;
        ++size;

        int parent = (idx - 1) / 2;
        while (idx > 0 && heap[parent] > heap[idx]) {
            swap(heap[idx], heap[parent]);
            idx = parent;
            parent = (idx - 1) / 2;
        }
    }


    int extractMin() {
        if (size == 0)
            return -1; 

        int minVal = heap[0];
        heap[0] = heap[size - 1];
        --size;

        heapify(0);

        return minVal;
    }


    bool isEmpty() {
        return size == 0;
    }
};

class Graph {
private:
    int n; 
    int** adjList; 

public:
    Graph(int n) : n(n) {
        adjList = new int* [n];
        for (int i = 0; i < n; ++i) {
            adjList[i] = new int[n];
            for (int j = 0; j < n; ++j)
                adjList[i][j] = 1e9; 
        }
    }


    void addEdge(int u, int v, int w) {
        adjList[u][v] = w;
    }

    int* dijkstra(int s) {
        int* dist = new int[n]; 
        bool* visited = new bool[n](); 

        for (int i = 0; i < n; ++i) {
            dist[i] = 1e9; 
        }
        dist[s] = 0; 

        MinHeap pq(n);
        pq.insert(0);

        while (!pq.isEmpty()) {
            int u = pq.extractMin(); 

            if (visited[u]) continue; 
            visited[u] = true;

            for (int v = 0; v < n; ++v) {
                if (adjList[u][v] != 1e9) { 
                    if (dist[v] > dist[u] + adjList[u][v]) { 
                        dist[v] = dist[u] + adjList[u][v];
                        pq.insert(v);
                    }
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (dist[i] == 1e9)
                dist[i] = -1;
        }

        delete[] visited;
        return dist;
    }
};

int main() {
    int n, m; 
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    Graph graph(n);

    cout << "Enter edges in the format (u v w) where u is source, v is destination, and w is weight:\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    int* shortestDistances = graph.dijkstra(source);

    cout << "Shortest distances from source vertex " << source << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i << ": ";
        if (shortestDistances[i] != -1)
            cout << shortestDistances[i] << "\n";
        else
            cout << "Unreachable\n";
    }

    delete[] shortestDistances;

    return 0;
}
