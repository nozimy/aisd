/**
 *
 * Задача 1. «Представление графа».
 * Дан базовый интерфейс для представления ориентированного графа:
struct IGraph {
virtual ~IGraph() {}

	// Добавление ребра от from к to.
virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

Необходимо написать несколько реализаций интерфейса:
CListGraph, хранящий граф в виде массива списков смежности,
CMatrixGraph, хранящий граф в виде матрицы смежности,
CSetGraph, хранящий граф в виде массива хэш-таблиц,
CArcGraph, хранящий граф в виде одного массива пар {from, to}.
Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен
 скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.

 *
 */

#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CSetGraph.h"
#include "CArcGraph.h"
#include "IGraph.h"

#include "time.h"
#include "iostream"
#include "random"

using std::cout;
using std::endl;

void fillGraph(IGraph *graph, const size_t count) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, count);
    std::uniform_real_distribution<double> operation(1, 3);

    for (int i=0; i < count; i++) {
        switch ((int)operation(mt)) {
            case 1:
                graph->AddEdge((int)dist(mt), (int)dist(mt));
                break;
            case 2:
                graph->GetNextVertices((int)dist(mt));
                break;
            case 3:
                graph->GetPrevVertices((int)dist(mt));
                break;
            default:
                break;
        }
    }
}

void test() {
    size_t testEdgesCount = 10000;

    cout << "Graph Type   |  time (s)"  << endl;
    cout << "------------------------"  << endl;

    // Test List Graph
    CListGraph listGraph(testEdgesCount);
    clock_t tStart = clock();
    fillGraph(&listGraph, testEdgesCount);
    cout << "List Graph   | " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;

    // Test Arc Graph
    CArcGraph arcGraph(testEdgesCount);
    tStart = clock();
    fillGraph(&arcGraph, testEdgesCount);
    cout << "Arc Graph    | " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;

    // Test Matrix Graph
    CMatrixGraph matrixGraph(testEdgesCount);
    tStart = clock();
    fillGraph(&matrixGraph, testEdgesCount);
    cout << "Matrix Graph | " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;

    // Test Set Graph
    CSetGraph setGraph(testEdgesCount);
    tStart = clock();
    fillGraph(&setGraph, testEdgesCount);
    cout << "Set Graph    | " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;
    cout << "------------------------"  << endl << endl;

    // Test Converting to List Graph
    CListGraph listGraph1(&arcGraph);
    cout << "List Graph from arcGraph passed." << endl;

    CListGraph listGraph2(&matrixGraph);
    cout << "List Graph from matrixGraph passed." << endl;

    CListGraph listGraph3(&setGraph);
    cout << "List Graph from setGraph passed." << endl << endl;

    // Test Converting to Arc Graph
    CArcGraph arcGraph1(&listGraph);
    cout << "Arc Graph from listGraph passed." << endl;

    CArcGraph arcGraph2(&matrixGraph);
    cout << "Arc Graph from matrixGraph passed." << endl;

    CArcGraph arcGraph3(&setGraph);
    cout << "Arc Graph from setGraph passed." << endl << endl;

    // Test Converting to Matrix Graph
    CMatrixGraph matrixGraph1(&listGraph);
    cout << "Matrix Graph from listGraph passed." << endl;

    CMatrixGraph matrixGraph2(&arcGraph);
    cout << "Matrix Graph from arcGraph passed." << endl;

    CMatrixGraph matrixGraph3(&setGraph);
    cout << "Matrix Graph from setGraph passed." << endl << endl;

    // Test Converting to Set Graph
    CSetGraph setGraph1(&listGraph);
    cout << "Set Graph from listGraph passed." << endl;

    CSetGraph setGraph2(&arcGraph);
    cout << "Set Graph from arcGraph passed." << endl;

    CSetGraph setGraph3(&matrixGraph);
    cout << "Set Graph from matrixGraph passed." << endl << endl;

    cout << "Tests successfully finished";

}

int main() {
    test();
    return 0;
}