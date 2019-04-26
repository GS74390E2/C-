#include "adjacencyWDigraph.h"
#include "weightedEdge.h"

using namespace std;


int main() {
    adjacencyWDigraph<int> g(4);
    cout << "Number of Vertices = " << g.numberOfVertices() << endl;
    cout << "Number of Edges = " << g.numberOfEdges() << endl;
    cout << endl;

    g.insertEdge(new weightedEdge<int>(2, 4, 1));
    g.insertEdge(new weightedEdge<int>(1, 3, 2));
    g.insertEdge(new weightedEdge<int>(2, 1, 3));
    g.insertEdge(new weightedEdge<int>(1, 4, 4));
    g.insertEdge(new weightedEdge<int>(4, 2, 5));
    cout << "The graph is" << endl;
    cout << "Number of Vertices = " << g.numberOfVertices() << endl;
    cout << "Number of Edges = " << g.numberOfEdges() << endl;

    cout << "existsEdge(3,1) = " << g.existsEdge(3, 1) << endl;
    cout << "existsEdge(1,3) = " << g.existsEdge(1, 3) << endl;
    cout << "inDegree(3) = " << g.inDegree(3) << endl;
    cout << "outDegree(1) = " << g.outDegree(1) << endl;
    cout << "Number of Vertices = " << g.numberOfVertices() << endl;
    cout << "Number of Edges = " << g.numberOfEdges() << endl;

    cout << "Edges incident to vertex 4" << endl;
    vertexIterator<int> *gi = g.iterator(4);
    cout << gi->next() << endl;
    return 0;
}