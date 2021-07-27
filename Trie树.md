## Trie树

读作“try” 树， 也叫**前缀树**，**字典树** , **单词查找树**

**高效地存储和查找字符串集合的数据结构**，关于 Trie 的应用场景， 8 个字：**一次建树，多次查询**。

时间复杂度为$O(|s|)$. |s|是每次插入或查询的字符串的长度。



典型例题如下：

维护一个字符串集合，支持两种操作：

1. `I x` 向集合中插入一个字符串 x；
2. `Q x` 询问一个字符串在集合中出现了多少次。

共有 N 个操作，输入的字符串总长度不超过 $10^5$，字符串仅包含小写英文字母。

#### 输入格式

第一行包含整数 N，表示操作数。

接下来 N 行，每行包含一个操作指令，指令为 `I x` 或 `Q x` 中的一种。

#### 输出格式

对于每个询问指令 `Q x`，都要输出一个整数作为结果，表示 x 在集合中出现的次数。

每个结果占一行。

#### 数据范围

$1≤N≤2∗10^4$

#### 输入样例：

```
5
I abc
Q abc
Q ab
I ab
Q ab
```

#### 输出样例：

```
1
0
1
```



思路：

设置一棵树，根结点是里面内容为空，每来一个单词，都对其中的所有字符构建一条路径；并在终止位置设置一个标记。

![image-20210727134413256](Trie树.assets/image-20210727134413256.png)

* 方法一：**使用指针来实现这棵树**。

```c++
#include<iostream>
#include<string>
#include<cstring>
using namespace std;

class Trie {
private:
    // 以当前字符为结尾的word的个数
	int cntEnd;
    // 26个子节点
	Trie * son[26];
public:
	Trie() {
		cntEnd = 0;
        // memset()函数是cstring头文件中，赋值0是可以用之后的NULL来进行推导
		memset(son, 0, sizeof(son));
	}
	void insert(string word) {
		Trie * cur = this;
		for (int i = 0; i < word.size(); i++) {
			int c = word[i] - 'a';
			if (cur->son[c] == NULL) {
				if( i == word.size() - 1)	cur->cntEnd += 1;
				else
				{
					cur->son[c] = new Trie();
					cur = cur->son[c];
				}
			}
			else {
				if (i == word.size() - 1) {
					cur->cntEnd += 1;
					return;
				}
				cur = cur->son[c];
			}
		}
		
	}

	int query(string word) {
		Trie * cur = this;
		for (int i = 0; i < word.size(); i++) {
			int c = word[i] - 'a';
			if (cur->son[c] == NULL) {
				if (i == word.size() - 1)    return cur->cntEnd;
				else    return 0;
			}
			else {
				if (i == word.size() - 1)  break;
				else   cur = cur->son[c];
			}
		}
		return cur->cntEnd;
	}
};

int main() {
	int n;
	scanf("%d", &n);
	Trie t;
	while (n--) {
		string op, word;
		cin >> op >> word;
		if (op == "I")   t.insert(word);
		else    printf("%d\n", t.query(word));

	}
	return 0;
}


```



* 方法二：用二维数组来模拟树。**速度大概是第一种方式四倍**, 推荐使用第二种

```c++
#include<iostream>

using namespace std;
const int N = 1e5 + 10;
char str[N];

int idx, son[N][26], cnt[N];

void insert(char str[]){
    int p = 0;
    // due to char[] over by '\0'，so we can use str[i] to judge isOver
    for(int i = 0; str[i]; i ++){
        int u = str[i] - 'a';
        if( !son[p][u] )  son[p][u] = ++ idx;
        p = son[p][u];
    }
    cnt[p] ++;
}

int query(char str[]){
    int p = 0;
    for(int i = 0; str[i]; i ++){
        int u = str[i] - 'a';
        if( !son[p][u] )    return 0;
        else p = son[p][u];
    }
    return cnt[p];
}

int main(){
    int n;
    cin >> n;
    while( n -- ){
        char op[2];
        scanf("%s%s", op, str);
        if(op[0] == 'I')    insert(str);
        else    printf("%d\n", query(str));
    }
    return 0;

}
```

