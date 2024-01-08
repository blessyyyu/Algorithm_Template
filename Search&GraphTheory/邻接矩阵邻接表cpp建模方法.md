## 建图方法

### 邻接矩阵

```cpp
const int N = 10;
class Graph
{
private:
    int v;
    std::vector<std::vector<int>> g;
public:
    Graph()
    {
        v = N;           // vertext 节点数
        g = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
    }

    void addEdge(int a, int b, int c)
    {
        g[a][b] = c;
        g[b][a] = c;
    }
}; 
```



### 邻接表

如果都用类的方法表示节点和边，代码如下所示

```cpp
const int N = 10;
class AdjencyGraph
{
private:
    // 边、弧节点
    struct ArcNode{
        int adjVex;
        int weight;
        ArcNode *next;
    };
    // 顶点节点
    struct VNode{
        string name;
        ArcNode *first;
    };
public:
    AdjencyGraph(){
        // 这里仅仅构造一个顶点
        VNode vertex({"1", new ArcNode[N]});
        ArcNode cur_node = vertex.first[0];
        // 依次连接起来
        for (int i = 0; i < N; i ++) {
            vertex.first[i].adjVex = i;
            vertex.first[i].weight = 0;
            if (i) {
                cur_node.next = &vertex.first[i];
                cur_node = vertex.first[i];
            }
        }
    }
};
```

