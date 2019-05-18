
#ifndef M3_CSETGRAPH_H
#define M3_CSETGRAPH_H


#include "IGraph.h"
using std::vector;
using std::set;

class CSetGraph: public IGraph {
public:
    explicit CSetGraph(size_t v): verticesCount(v), in(v), out(v) {}
    CSetGraph(const IGraph* graph);

    void AddEdge(int from, int to) override;
    size_t VerticesCount() const override;
    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;

private:
    size_t verticesCount;
    vector<set<int>> in;
    vector<set<int>> out;
};


#endif //M3_CSETGRAPH_H
