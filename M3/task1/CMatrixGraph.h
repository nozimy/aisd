
#ifndef M3_CMATRIXGRAPH_H
#define M3_CMATRIXGRAPH_H


#include "IGraph.h"

class CMatrixGraph: public IGraph {
public:
    explicit CMatrixGraph(size_t v);
    CMatrixGraph(const IGraph* graph);

    void AddEdge(int from, int to) override;
    size_t VerticesCount() const override;
    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;

private:
    size_t verticesCount;
    vector<vector<bool>> edges;
};

#endif //M3_CMATRIXGRAPH_H
