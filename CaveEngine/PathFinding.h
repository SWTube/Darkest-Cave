#pragma once
#include<vector>
using namespace std;
struct Coordinates {
    int x;
    int y;
};
// Assumption: VertexType is a type for which the "=", 
// "==", and "<<" operators are defined
class Path
{
public:
    Path();                  // Default of 50 vertices
    Path(int maxV);          // maxV <= 50
    ~Path();
    //  void MakeEmpty();
    //  bool IsEmpty() const;
    //  bool IsFull() const;
    void AddVertex(int, int, int);
    void AddEdge(int, int);
    void DeleteEdge(int fromVertex, int toVertex);
    vector<int> AstarPathFinder(int, int);
    bool IsConnect(int, int);
    vector<int> ConsecutivePathFinder(int a, vector<int> list);
    void MakeExample();
    //  void ClearMarks();
    //  void MarkVertex(VertexType);
    //  bool IsMarked(VertexType);
private:
    int numVertices; //vertex ����
    int maxVertices; //max vertex
    int* vertices; //vertex�� ����
    Coordinates* cds; //vertex���� ��ǥ ����
    int edges[50][50];
};

Path::Path()
// Post: Arrays of size 50 are dynamically allocated for  
//       marks and vertices.  numVertices is set to 0; 
//       maxVertices is set to 50.
{
    numVertices = 0;
    maxVertices = 50;
    vertices = new int[50];
    cds = new Coordinates[50];
}

Path::Path(int maxV)
// Post: Arrays of size maxV are dynamically allocated for  
//       marks and vertices.  
//       numVertices is set to 0; maxVertices is set to maxV.
{
    numVertices = 0;
    maxVertices = maxV;
    vertices = new int[maxV];
    cds = new Coordinates[maxV];
}


// Post: arrays for vertices and marks have been deallocated.
Path::~Path()
{
    delete[] vertices;
    delete[] cds;
}
const int NULL_EDGE = 0;


void Path::AddVertex(int vertex, int x, int y)
// Post: vertex has been stored in vertices.
//       Corresponding row and column of edges has been set 
//       to NULL_EDGE.
//       numVertices has been incremented.
{
    vertices[numVertices] = vertex;
    cds[numVertices].x = x;
    cds[numVertices].y = y;
    for (int index = 0; index < numVertices; index++)
    {
        edges[numVertices][index] = NULL_EDGE;
        edges[index][numVertices] = NULL_EDGE;
    }
    numVertices++;
}

int IndexIs(int* vertices, int vertex)
// Post: Returns the index of vertex in vertices.
{

    int index = 0;


    while (!(vertex == vertices[index]))
        index++;
    return index;
}


void Path::AddEdge(int fromVertex,
    int toVertex)
    // Post: Edge (fromVertex, toVertex) is stored in edges.
{
    int row;
    int col;

    row = IndexIs(vertices, fromVertex);
    col = IndexIs(vertices, toVertex);
    edges[row][col] = 1;
}

void Path::DeleteEdge(int fromVertex, int toVertex)
{
    int row;
    int col;
    row = IndexIs(vertices, fromVertex);
    col = IndexIs(vertices, toVertex);
    edges[row][col] = NULL_EDGE;
}

struct PathNumber {
    int f = 0;
    int h = 0;
    int g = 0;
};
vector<int> Path::AstarPathFinder(int startVertex, int endVertex) {
    int fromIndex; //���������� index
    int toIndex; //�������� index
    vector<int> queueIn; //��μ����� ���� vector
    vector<int> queueClosed; //�ѹ� ���� ��(������ �ϱ�����)
    vector<int> path;
    fromIndex = IndexIs(vertices, startVertex); //�������� index �ο�
    toIndex = IndexIs(vertices, endVertex); //������ index �ο�
    PathNumber currentNode; //���� ����� f, h, g�� ������ ���� ��������
    int currentIndex = fromIndex; //����index�� ���۰����� ����
    int currentValue = vertices[currentIndex]; //���� value���� �ο�
    bool isSame = false;//while�� break��
    while (!isSame)
    {

        path.push_back(currentValue);
        queueClosed.push_back(currentValue);
        for (int i = 0; i < numVertices; i++)
        {
            auto isFind = find(queueClosed.begin(), queueClosed.end(), vertices[i]); //queueClosed�� �˻��Ͽ� �� �� ������ ������ üũ
            if (edges[currentIndex][i] == 1 && isFind == queueClosed.end()) //������� ����Ǿ�����, ������ �������� �˻�
            {
                queueIn.push_back(vertices[i]);

            }
        }
        PathNumber* pN = new PathNumber[queueIn.size()]; //queueIn���� ���ҵ��� f,g,h�� ������ ���� �迭 ����

        for (int i = 0; i < queueIn.size(); i++)
        {
            currentIndex = IndexIs(vertices, queueIn[i]);
            if (currentIndex == toIndex) //���� �ߴٸ� ����
            {
                isSame = true;
                path.push_back(queueIn[i]);
                vector<int> pathCopy = path;
                for (int j = 1; j < path.size(); j++)
                {
                    if (IsConnect(path[j - 1], path[j]) == false)
                    {

                        vector<int> temp = AstarPathFinder(startVertex, path[j]);
                        for (int k = 0; k < temp.size(); k++)
                        {
                            if (pathCopy[k] != temp[k])
                            {
                                pathCopy.erase(pathCopy.begin() + k);
                                k--;
                            }
                        }
                    }
                }
                path = pathCopy;
                return path;
            }
            pN[i].g = abs(cds[fromIndex].x - cds[currentIndex].x) + abs(cds[fromIndex].y - cds[currentIndex].y); //������������ ���� ����������� �Ÿ�
            pN[i].h = abs(cds[toIndex].x - cds[currentIndex].x) + abs(cds[toIndex].y - cds[currentIndex].y); //���������� ���� ����������� �Ÿ�
            pN[i].f = pN[i].g + pN[i].h; //g�� h�� ��
        }


        int minF = 1000; //�ּڰ����� ��� Ž���� �ϱ� ���� ���� ����
        int maxG = -1;
        int count = 0; //f���� ���� ���� path�� index���� �����ϱ� ���� ���� ����
        for (int i = 0; i < queueIn.size(); i++)
        {
            if (minF >= pN[i].f && pN[i].g >= currentNode.g) //g���� ������ �ڷΰ��� �Ŷ� ����
            {
                minF = pN[i].f;
                maxG = pN[i].g;
                count = i;
            }

        }
        currentNode.g = pN[count].g;
        currentNode.h = pN[count].h;
        currentNode.f = currentNode.g + currentNode.h;
        currentIndex = IndexIs(vertices, queueIn[count]);
        currentValue = vertices[currentIndex];

        for (int i = 0; i < queueIn.size(); i++)
        {
            if (queueIn[i] == currentValue)
            {
                queueIn.erase(queueIn.begin() + i);
                break;
            }
        }
        if (currentIndex == toIndex)
        {
            path.push_back(currentValue);
            isSame = true;
        }
    }
    return path;
}
bool Path::IsConnect(int a, int b)
{
    if (edges[IndexIs(vertices, a)][IndexIs(vertices, b)] == 1 || edges[IndexIs(vertices, b)][IndexIs(vertices, a)] == 1)
    {
        return true;
    }
    else
        return false;
}
vector<int> Path::ConsecutivePathFinder(int a, vector<int> list)
{
    vector<int> tump;
    vector<int> result;
    for (int i = 0; i < a - 1; i++)
    {
        tump = AstarPathFinder(list[i], list[i + 1]);
        for (int i = 0; i < tump.size(); i++)
        {
            result.push_back(tump[i]);
        }
    }
    return result;
}