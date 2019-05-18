

#ifndef M3_CARCGRAPH_H
#define M3_CARCGRAPH_H


#include "IGraph.h"
using std::pair;

class CArcGraph: public IGraph {
public:
    explicit CArcGraph(size_t v): verticesCount(v), edges(v) {};
    CArcGraph(IGraph *graph);

    void AddEdge(int from, int to) override;
    size_t VerticesCount() const override;
    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;

private:
    size_t verticesCount;
    vector<pair<int, int>> edges;
};


#endif //M3_CARCGRAPH_H
