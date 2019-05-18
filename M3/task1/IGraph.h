
#ifndef M3_IGRAPH_H
#define M3_IGRAPH_H


#include <vector>
#include <list>
#include <set>
#include <utility>

using std::vector;

struct IGraph {
    virtual ~IGraph() {};

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;
    virtual size_t VerticesCount() const  = 0;

    // Получить вершины, в которые есть ребро из текущей вершины
    virtual vector<int> GetNextVertices(int vertex) const = 0;
    // Получить вершины, из которых есть ребро в текущую вершину
    virtual vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //M3_IGRAPH_H
