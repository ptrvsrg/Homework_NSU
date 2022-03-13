#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////  GRAPH TYPE  ///////////////////////////////////

typedef struct TGraph TGraph;
struct TGraph
{
    int VertexCount;
    int* Matrix;
};

TGraph CreateGraph(int vertexCount)
{
    TGraph graph = { vertexCount, NULL };
    graph.Matrix = calloc(vertexCount * vertexCount, sizeof(*graph.Matrix));
    assert(graph.Matrix != NULL);
    return graph;
}

void PushEdge(int begin, int end, TGraph graph)
{
    graph.Matrix[graph.VertexCount * (begin - 1) + (end - 1)] = 1;
}

void DestroyGraph(TGraph* graph)
{
    free(graph->Matrix);
}

///////////////////////////////////  MATRIX  ///////////////////////////////////

int* CreateIdentityMatrix(int size)
{
    int* result = calloc(size * size, sizeof(*result));
    assert(result != NULL);

    for (int i = 0; i < size; ++i)
    {
        result[i * size + i] = 1;
    }
    
    return result;
} 

int* MatrixMultiplication(int size, int* matrix1, int* matrix2)
{
    int* result = calloc(size * size, sizeof(*result));
    assert(result != NULL);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < size; ++k)
            {
                result[i * size + j] += matrix1[i * size + k] * matrix2[k * size + j];
            }
        }
    }
    
    return result;
}

int* MatrixExponentiation(int size, int* matrix, int exp)
{
    if (exp == 0)
    {
        return CreateIdentityMatrix(size);
    }
    else if (exp == 1)
    {
        return matrix;
    }
    else if ((exp & 1) == 0)
    {
        int* intermediateMatrix = MatrixExponentiation(size, matrix, exp / 2);
        return MatrixMultiplication(size, intermediateMatrix, intermediateMatrix);
    }
    
    return MatrixMultiplication(size, matrix, MatrixExponentiation(size, matrix, exp - 1));
}

int CountPathsWithNVertices(int begin, int end, int vertexCount, TGraph graph)
{
    if(vertexCount == 0 || vertexCount == 1)
    {
        return 0;
    }

    int* matrix = MatrixExponentiation(graph.VertexCount, graph.Matrix, vertexCount - 1);

    int result = matrix[(begin - 1) * graph.VertexCount + (end - 1)];
    free(matrix);

    return result;
}

///////////////////////////////////  MAIN  ///////////////////////////////////

int main(void)
{
    TGraph graph = CreateGraph(4);
    PushEdge(1, 2, graph);
    PushEdge(1, 3, graph);
    PushEdge(2, 4, graph);
    PushEdge(3, 4, graph);

    int vertexCount = 3;
    int begin = 1;
    int end = 4;

    printf("Count of paths with %d vertices from %d to %d is %d\n", vertexCount, begin, end, CountPathsWithNVertices(begin, end, vertexCount, graph));

    DestroyGraph(&graph);

    return EXIT_SUCCESS;
}