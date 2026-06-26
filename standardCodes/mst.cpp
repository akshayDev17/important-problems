#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

bool edgeComp(const vector<int> &a, const vector<int> &b) {
    return a[2] < b[2];
}

int djset_find(int x, vector<pair<int,int> > &par){
    // if my parent isn't the ultimate parent (ultimate parent has itself as its parent)
    if (par[x].first != x) par[x].first = djset_find(par[x].first, par);
    return par[x].first;

}

void djset_union(int x, int y, vector<pair<int,int> > &par){
    int px = djset_find(x, par), py = djset_find(y, par);
    if(par[px].second < par[py].second) {
        // x is a small tree compared to y, join x's parent to y's parent
        par[px].first = py;
        return;
    }
    else if(par[px].second > par[py].second) {
        // y is a small tree compared to x, join y's parent to x's parent
        par[py].first = px;
        return;
    }
    else{
        // both are equal lengths, lets join x's parent to y's parent and increment y's parent's rank
        par[px].first = py;
        par[py].second++;
        return;
    }
}

void KruskalMST(int V, vector<vector<int> > edges){
    /*
    Algo:
    1. sort edges in ascending order of edge weights --> ElogE step
    2. pick the current minimum weighted edge and check if picking it causes cycle-creation via disjoint set.
        2a. if an edge to be picked leads to two vertices having same parents getting connected --> cycle.
    3. stop after having picked V-1 edges
     */
    
    // initially, all vertices are their own parents, with rank = 0
    vector<pair<int,int> > dj_set(V, pair<int,int>(0, 0));
    for (int i = 0;i<V;i++) dj_set[i].first = i;

    // sort the edges
    sort(edges.begin(), edges.end(), edgeComp);

    vector<vector<int> > mstEdges;
    int numEdgesPicked = 0;

    for(int i = 0; i < edges.size();i++){
        int u = edges[i][0], v = edges[i][1];
        int par_u = djset_find(u, dj_set), par_v = djset_find(v, dj_set);
        if (par_u != par_v && numEdgesPicked < V - 1) {
            // edge can be picked
            mstEdges.push_back(edges[i]);
            numEdgesPicked++;
            djset_union(u, v, dj_set);
        }
    }

    cout << "MST from Kruskals is represented by the edges:\n";
    for(int i =0;i<mstEdges.size();i++) cout << "\t" << mstEdges[i][0] << "---"  << mstEdges[i][2] << "---" <<  mstEdges[i][1] << endl;
}

// mainly for Prims
class Triplet{
    public:
        int u, v, e;
    Triplet(int u, int v, int e) {
        this->u = u;
        this->v = v;
        this->e = e;
    }
};

class tripletComp{
public:
    bool operator() (Triplet const &a, Triplet const &b){
        // compare two triplets, based on edge weight only.
        // priority_queue in cpp by default is a max heap(std::less<T> is used), 
        // we need a min heap, and:
        // comp(a, b) = true means "a should be ordered before b" — i.e., a has 
        // lower priority, b is "greater" in the heap's eyes, put it at top. 
        return a.e > b.e;
    }
};

void insertVertexAndEdgesInPrimsMst(int u, set<int> &mstVertices, 
    priority_queue<Triplet,vector<Triplet>, tripletComp> &mstCandidateEdges,
    vector<vector<pair<int,int> > > adjList
){

    // first vertex inserted
    mstVertices.insert(u);

    for(int i = 0;i<adjList[u].size();i++) {
        int v = adjList[u][i].first, e = adjList[u][i].second;
        if (mstVertices.find(v) == mstVertices.end()){
            // v doesn't exist in mstVertices, e can be added to the priority queue
            Triplet *candidateTriplet = new Triplet(u, v, e);
            mstCandidateEdges.push(*candidateTriplet);
        }
    }
}

void PrimsMST(int V, vector<vector<int> > edges){
    /*
    Algorithm:
    1. start with a random vertex, add it to the MST
    2. take the least weighted edge of all the edges between a vertex part of MST with another vertex not yet added to the MST.
    3. add the edge and the unvisited vertex to the MST
    4. repeat till all vertices have been added to the MST

    since next minimum weighted edge is required ---> min heap
    */
    
    // reorient the graph from an edge-based representation to an adjacency list,
    // since we will reference edges as being incident on a given vertex.
    vector<vector<pair<int,int> > > adjList;adjList.resize(V);
    for(int i = 0;i<edges.size();i++){
        int u = edges[i][0],  v = edges[i][1], e = edges[i][2];
        adjList[u].push_back(pair<int,int>(v, e));
        adjList[v].push_back(pair<int,int>(u, e));
    }


    // custom class since we're storing 3 things: u, v, e.
    priority_queue<Triplet,vector<Triplet>, tripletComp> mstCandidateEdges;
    set<int> mstVertices;
    vector<vector<int> > mstEdges;
    bool flag = true;

    // "visit" the first node
    insertVertexAndEdgesInPrimsMst(0, mstVertices, mstCandidateEdges, adjList);
    
    while(flag) {

        // actual MST build up
        if (mstVertices.size() == V) {
            flag = false;
            break;
        } else {
            Triplet nextEdge = mstCandidateEdges.top();mstCandidateEdges.pop();
            int u = nextEdge.u, v = nextEdge.v, e = nextEdge.e;

            if (mstVertices.find(v) == mstVertices.end()) {
                // v not in mstVertices:
                // 1. eligible to be added in mstVertices
                // 2. edge is eligible to be added in mstEdges
            
                
                
                // add to final set of MST this edge.
                vector<int> nextEdgeAsVect;
                nextEdgeAsVect.push_back(u);nextEdgeAsVect.push_back(v);nextEdgeAsVect.push_back(e);
                mstEdges.push_back(nextEdgeAsVect);
                
                // add the vertex into mstVertices
                insertVertexAndEdgesInPrimsMst(v, mstVertices, mstCandidateEdges, adjList);
            }
        }

    }

    cout << "MST from Prims is represented by the edges:\n";
    for(int i =0;i<mstEdges.size();i++) cout << "\t" << mstEdges[i][0] << "---"  << mstEdges[i][2] << "---" <<  mstEdges[i][1] << endl;
    return;
}

int main(int argc, char* argv[]){
    bool useKrus = false, usePrims = false;
    for(int i=1;i<argc;i++){
        string arg = argv[i];
        if (arg == "--krus") useKrus = true;
        if (arg == "--prims") usePrims = true;
    }

    int T;
    cin >> T;
    while(T--){
        int V, E;
        cin >> V >> E;
        vector<vector<int> > edges;
        for(int i = 0;i<E;i++) {
            int u,v,ew;
            cin >> u >> v >> ew;
            vector<int> e;
            e.push_back(u);e.push_back(v);e.push_back(ew);
            edges.push_back(e);
        }
        if (useKrus) KruskalMST(V, edges);
        if (usePrims) PrimsMST(V, edges);
    }
    return 0;
}