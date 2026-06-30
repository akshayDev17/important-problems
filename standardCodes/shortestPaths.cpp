/*
 * Shortest Path Algorithms
 *
 * | Property        | Dijkstra   | Bellman-Ford | Floyd-Warshall |
 * |-----------------|------------|--------------|----------------|
 * | Source          | Single     | Single       | All pairs      |
 * | Negative weights| No         | Yes          | Yes            |
 * | Negative cycles | No         | Detects      | Detects        |
 * | Time            | O(E log V) | O(VE)        | O(V^3)         |
 */

#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<climits>

using namespace std;

bool isCycleViaBellmanFord(int V, vector<vector<pair<int,int> > > adjList){
    // add a dummy vertex connected to all other vertices with an edge of weight 0
    //  this is so that we ensure the graph has 1 vertex who can reach all other vertices of the graph.
    // this is done so that then the negative cycle can be reached/travelled through.
    // or else, if this is not done and then any vertex is chosen as source at random, 
    //  it may be possible that the negative cycle exists in a disconnected component 
    //  unreachable from this randomly selected source.
    vector<vector<pair<int,int> > > dummyAdjList = adjList;
    // dummyAdjList.

    return false;
}

vector<int> dijkstraSingleSource(int V, vector<vector<pair<int,int> > > adjList, int source) {
    
    vector<int> dist(V, INT_MAX);dist[source] = 0;
    
    // Step-1: add all vertices to the priority queue.
    priority_queue<pair<int,int>,vector<pair<int,int> >, greater<pair<int,int> > > dijktraQ;
    dijktraQ.push(pair<int,int>(0, source));

    while(!dijktraQ.empty()){
        pair<int,int> top = dijktraQ.top();dijktraQ.pop();
        int d_sv = top.first, v = top.second;

        if (d_sv > dist[v]) {
            // skip branch since shortest distance of v from source already found out, 
            // this pair in the min heap was a stale entry
            continue;
        } else {
        
            //  Step-2: iterate all edges incident on v (and the other vertex as `w`), and see if these edges can be used to update d_sw.
            //    if updateable, update the dist[s][w] and also to the priority queue the pair <w, d_sw'>
            for(int w_idx =0;w_idx<adjList[v].size();w_idx++){
                int w = adjList[v][w_idx].first, e_vw = adjList[v][w_idx].second;
                if (dist[v] != INT_MAX && dist[w] > dist[v] + e_vw) {
                    dist[w] = dist[v] + e_vw;
                    dijktraQ.push(pair<int,int>(dist[w], w));
                }
            }
        }
    }

    return dist;
}

void dijkstra(int V, vector<vector<pair<int,int> > > adjList, int source, bool allPair) {
    // allPair: true means all vertices are sources, ignore source

    /*
    Algorithm: For a source vertex u;
    1. init with all vertices distance as d[v] = inf, d[u] = 0.
    2. for all vertices, push (v, d[v]) to a min-heap, ordered on d[v].
    3. take out the top vertex, say its v. for all vertices w joined to v by edge e, if d[v] > d[w] + edgeWeight(e), update d[v] and push this pair to the heap.
    4.
    5. to be on safe side, a test case could be a googly, hence better to see if 
        the graph is dijktra's eligible, i.e. doesn't have any negative edge.
    */

    // step-1: dijkstra's eligibility
    bool isGraphDijktraEligible = true;

    for(int u = 0;u<V;u++) {
        for(int v = 0;v< adjList[u].size();v++){
            int e = adjList[u][v].second;
            if (e < 0) isGraphDijktraEligible = false;
        }
    }

    if (!isGraphDijktraEligible) {
        cout << "\tThis graph is not eligible for dijktra-based shortest-path as it has a negative edge.\n";
        return;
    }

    if (allPair) {

        // Step-2: init the pairwise distance mat.
        vector<int> tmp(V, INT_MAX);
        vector<vector<int> > dist(V, tmp);

        // Step-3: process each vertex as source
        for (int s = 0;s<V;s++) dist[s] = dijkstraSingleSource(V, adjList, s);

        // Step-4: print the dist mat
        for(int u = 0;u<V;u++){
            for(int v = 0;v<V;v++)  cout << dist[u][v] << " ";
            cout << endl;
        }
        cout << endl;
        return;
    } else {
        vector<int> dist = dijkstraSingleSource(V, adjList, source);
        cout << "\tShortest path from vertex " << source << endl << "\t";
        for (int i = 0;i<V;i++) cout << dist[i] << " ";
        cout << "\n\n";
    }
}

class Edge{
    public:
        int u, v, e;
    Edge(int u, int v, int e){
        this->u = u;
        this->v = v;
        this->e = e;
    }
};

vector<int> bellmandFordSingleSource(int V, vector<vector<pair<int, int> > > adjList, int source) {
    vector<int> dist(V, INT_MAX); dist[source] = 0;

    // convert adjacency list representation to edge list represeetation
    vector<Edge> edges;

    for(int u = 0;u<V;u++){
        for(int v_idx = 0;v_idx<adjList[u].size();v_idx++){
            int v = adjList[u][v_idx].first, e = adjList[u][v_idx].second;
            edges.push_back(Edge(u, v, e));
        }
    }

    // for V-1 iterations, visit all edges and try to update the min distance from source for incident vertices.
    for(int u = 0;u<V-1;u++){
        for(int e_idx = 0;e_idx < edges.size();e_idx++){
            int v1 = edges[e_idx].u, v2 = edges[e_idx].v, w = edges[e_idx].e;

            // assume edge is v1--->v2
            if (dist[v1] != INT_MAX && dist[v2] > dist[v1]+w){
                // taking edge e_idx leads to a shortened distance from the source for the next vertex.
                dist[v2] = dist[v1]+w;
            }
        }
    }
    return dist;

}

void bellmanFord(int V, vector<vector<pair<int,int> > > adjList, int source, bool allPair) {
    // allPair: true means all vertices are sources, ignore source
    if (allPair) {
        vector<int> tmp (V, INT_MAX);
        vector<vector<int> > dist(V, tmp);
        for(int s = 0;s<V;s++) dist[s] = bellmandFordSingleSource(V, adjList, s);

        cout << "\nUsing Bellman-Ford as an all-pair shortest path algorithm:\n";
        for(int u = 0;u<V;u++){
            for(int v= 0;v<V;v++) cout << dist[u][v] << " ";
            cout << endl;
        }
        cout << endl;
        return;
    } else {
        vector<int> res = bellmandFordSingleSource(V, adjList, source);
        cout << "Shortest path from " << source << ": ";
        for(int u = 0;u<V;u++) cout << res[u] << " ";
        cout << endl << endl;
    }
}



void floydWarshall(int V, vector<vector<pair<int,int> > > adjList) {
    // floydWarshall is by construction an allPair shortest path algorithm
    /* 
    1. allPair distance matrix
    2. init all source,source with 0, and all u,v vertices connected by edge e with its edge weight.
    3. floyd warshall's a DP solution to the all-pair shortest path problem:
      3a. distance between 2 vertices i and k is the minimum of the:
        distance between i and an intermediate vertex j, plus the distance between vertex j and vertex k, 
        distance between i and k via another intermediate vertex j' where strictly j' != j.
    4. now, w.r.t. the implementation
        4a. if the terminal vertices are fixed and only the intermediate vertex is varied, it means that:
            4a1. i = 0, k = 1, say j = 2, it means 0-->2 and 2-->1 is already optimized, which 
                won't be the case since i and k (the outermost and 2nd outermost) are at 0 and 1, 
                meaning the first pair is yet to be solved.
            4a2. this means we rather need to maintain the intermediate and rather iterate 
                over the terminal indexes.
            4a3. Moreover, only processing the triplet such that the individual pairs have already 
                been processed is the **main goal** hence the inner loops for the terminal vertices
                also start from 0 and end at V-1, because:
                - j = 0, i = 0, k = 0 --> [0][0] --> already solved
                - j = 0, i = 0, k = 1 --> [0][1] --> unupdated regardless of an edge exists or not. 
                    this means that a j >= 2 is what might lead to a shorter distance-value discovery,
                    which has to come in later.
                - j = 0, i = 0, k = 2 ---> [0][2] ---> could be updated if [0][1] + [1][2] is shorter.
                - .... j = 0, i = 1,  k= 0 ---> [1][0] --> unupdated regardless of an edge exists or not. 
                - j = 0, i = 1,  k= 1 ---> [1][1] --> already solved
                - j = 0, i = 1,  k= 2 ---> [1][2] --> could be updated if [1][0] + [0][2] is shorter. 
                    even if we assume that [1][0] is unsolved for now, NOTICE THAT when j will advance, 
                    we again have the opportunity to process [1][0], hence eventually process-n-likely-update
                    [1][2].
    */
    vector<int> tmp(V, INT_MAX);
    vector<vector<int> > dist(V, tmp);

    for(int i = 0;i<adjList.size();i++){
        dist[i][i] = 0;
        for(int j = 0;j<adjList[i].size();j++){
            // edges incident between i and adjList[j]
            int v2 = adjList[i][j].first, e2 = adjList[i][j].second;
            dist[i][v2] = e2;
        }
    }

    for(int j = 0;j<V;j++) {
        for(int i = 0;i<V;i++){
            for(int k = 0;k<V;k++){
                if(dist[i][j] != INT_MAX && dist[j][k] != INT_MAX && dist[i][k] > dist[i][j] + dist[j][k]) {
                    dist[i][k] = dist[i][j] + dist[j][k];
                }
            }
        }
    }
    cout << "Using Floyd Warshall All-pair shortest path algorithm:\n";
    for(int u = 0;u<V;u++){
        for(int v = 0;v<V;v++) cout << dist[u][v] << " ";
        cout << endl;
    }
    cout << endl;
    return;
}

int main(int argc, char* argv[]){
    // use dijkstra, bellman ford, floyd warshall
    bool useDijk, useBf, useFw;
    for(int i = 1;i<argc;i++){
        string arg = argv[i];
        if (arg == "--dijk") useDijk = true;
        if (arg == "--bf") useBf = true;
        if (arg == "--fw") useFw = true;
    }

    // iterate through all test cases
    int T; cin >> T;
    while(T--){
        // get current test-case's no. of vertices and edges
        int V, E; cin >> V >> E;

        vector<vector<pair<int,int> > > adjList(V);

        // get the graph as edge list
        for(int i =0;i<E;i++){
            int u, v, e;
            cin >> u >> v >> e;
            adjList[u].push_back(pair<int,int>(v, e));
            adjList[v].push_back(pair<int,int>(u, e)); // undirected graph
        }

        // do all pair shortest paths.
        if (useDijk) dijkstra(V, adjList, -1, true);
        if (useBf) bellmanFord(V, adjList, -1, true);
        if (useFw) floydWarshall(V, adjList);
    }
    return 0;
}