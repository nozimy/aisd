
#ifndef M3_CLISTGRAPH_H
#define M3_CLISTGRAPH_H

#include "IGraph.h"
using std::list;

class CListGraph: public IGraph {
public:
    explicit CListGraph(size_t v): verticesCount(v), in(v), out(v) {}
    CListGraph(const IGraph* graph);

    void AddEdge(int from, int to) override;
    size_t VerticesCount() const override;
    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;

private:
    size_t verticesCount;
    vector<list<int>> in;
    vector<list<int>> out;
};

#endif //M3_CLISTGRAPH_H
