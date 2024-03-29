## C++ 小技巧

### split函数

自定义`split函数`, 用于C++处理类似 `1,2,3,4`这种输入:

- 推荐更快的方法

```cpp
vector<string> split2(string line, char delim)
{
    vector<string> res;
    stringstream ss(line);
    string item;
    while (getline(ss, item, delim)) {
        if (!item.empty()) {
            // while (word.size() && word[0] == ' ') word.erase(word.begin());
            res.push_back(item);
        }
    }
    return res;
}
```



- 自定义双指针法

```c++
vector<string> m_split(string line, char split_char) {
	vector<string> res;
	for (int i = 0, j = 0; i < line.size(); i++) {
		j = i;
		while ( j < line.size() && line[j] != split_char)    j++;
		// substr参数第一个表示起始下标，第二个参数是长度， [i, j-1]
        string word = line.substr(i, j - i);
        // 如果输入的分隔符是 1, 2, 3, 4, 5 这种逗号后还有一个空格的，可以在加入前去掉空格
        // while (word.size() && word[0] == ' ') word.erase(word.begin());
		res.push_back(word);
        i = j;
    }
    return res;
}
```



### 十进制数转变为二进制数存储在string

不断的 % 2, 将余数放在string中的最前端。

```cpp
j = number;
string bin_j = "";
while (j != 0) {
    bin_j = to_string(j % 2) + bin_j;
    j /= 2;
}
```











## STL用于算法

### vector

变长数组

```c++
vector<int> a(10,3);    // 定义一个长度为10的vector, 每个数都是3
vector<int> a[10];     // 定义了10个vector
a.empty();
a.size();				// empty()和size() 是所有容器都有的，时间复杂度为O(1)
a.clear();             // 并不是所有容器都有清空的函数clear()
vector.swap(vector2);
// insert方法
v.insert(v.begin(),8);//在最前面插入新元素。  
v.insert(v.begin()+2,1);//在迭代器中第二个元素前插入新元素  
v.insert(v.end(),3);//在向量末尾追加新元素。  
v.insert(v.end(),4,1);//在尾部插入4个1
v.erase():           // 有两种函数原型：
	iteratorerase(iterator position);                    // 删除某个迭代器位置的元素
	iteratorerase(iterator first, iterator last);			// 删除一段迭代器的位置

```

关于`erase()`函数的常见使用错误：

```c++
// 下面这段使用是错误的，因为erase(iter)后，iter成为了野指针，给野指针++会导致内存错误
for(auto iter=vec.begin();iter!=vec.end(); iter++)
{
      if(*iter == 3)
            veci.erase(iter);
}

// 正确写法
for(auto iter=vec.begin();iter!=vec.end(); )
{
     if( *iter == 3)
          iter = veci.erase(iter);//当删除时erase函数自动指向下一个位置，就不需要进行++
      else
            iter ++ ;    //当没有进行删除的时候，迭代器++
}


```



解决删除连续数字的一种方法：

```c++
veci.erase(remove(vec.begin(),vec.end(),3),vec.end());
```





倍增的思想：

> 系统为某一个程序分配空间的时候, 所需的时间与空间大小无关，与申请次数有关。所以，优化目标是变长数组要减小申请空间的次数；

首先先分配32个空间，当数组空间不够的时候，数组新分配的空间大小为64，再把原来的元素copy过来；

假设申请长度为n的数组，申请空间的次数`O(logn)`, 插入操作均摊下来是`O(1)`;

```c++
vector.front() /  vector.back();
push_back(); pop_back();
begin(); end();			// end()是最后一个数的后面一位
支持比较运算：按照字典序来进行比较"< >"
```



### pair<int, int>

```c++
pair<int, string> p;
p.first; p.second
支持比较运算，也是按照字典序来比，以first为第一关键字，以second为第二关键字。
p = make_pair(10,"ysq");
p = { 20, "abc"}; 
```

pair最经典的用法就是某个变量有两个属性，并且要按照其中一个属性来进行排序，就可以把需要排序的属性放到first里.

```c++
vector<pair<string, vector<int> >> vec(map.begin(), map.end());    // 初始化一个哈希表
// 自定义cmp函数
sort(vec.begin(), vec.end(), cmp);
```



如果某个变量有三个属性：`pair<int, pair<int,int>> p;`

注意：在`hashmap`或者`hashset`中，`pair<int, int> `不能单独作为键值对中的key值，因为C++中会自动把key值作一个hash函数，而`pair<type, type> `型，编译器没有自动指定hash函数，需要手动添加：

一种简单的hash方法如下：

```c++
struct SimplePairHash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return p.first ^ p.second;
    }
};

std::unordered_set<std::pair<int, int>, SimplePairHash> m_set;
```



### string

**字符串**

```cpp
string s;
size();length();
empty();
clear();
erase();  // 支持删除某一项

// erase例子
string a = "abcde";
auto temp = a.erase(3, 1);
cout << "temp = " << temp << endl; // abce
cout << "a = " << a << endl;		// abce


支持用大于号、小于号直接进行比较；当两个字符串的长度相同时，按照字典序排序进行比较。
s.substr(1, 2); 		// 第一个参数是字串的开始下标，第二个参数是子串长度(若很大，直接输出到最后一个元素)
printf("%s\n", s.c_str());
s.c_str();   // 返回字符串最开始的指针

// 如果没有找到某个字符, string会返回string::npos;
// 其中pos是unsigned int类型
int pos = s.find(strs[i]);
if (pos == string::npos){
    return;
}

// 字符串头文件下的find()函数
string st1("babbabab");
cout << st1.find("bab", 2) << endl;    // 3

```



**判断一个字符串是否是另一个字符串的前缀**

```cpp
string a = "abcde";
string b = "abc";

// 注意要转变为c型字符串，且最后一个参数是字符串的长度
if (strncmp(a.c_str(), b.c_str(), 3) == 0) {
    cout << "yes" << endl;
}
else {
    cout << "no" << endl;
}
```





### queue

`push(), front() , pop(), back()`

> 注意，queue, priority_queue , stack都没有clear函数

清空queue容器的方法：

```c++
q = queue<int>();
```



### priority_queue

优先队列,实际上就是堆，**默认是大顶堆**， `less<int>`仿函数, 堆顶元素是最大值。

```c++
push(); //插入一个元素
top();  //返回堆顶元素, 注意这里和普通的队列不同，普通队列是front()
pop();  //弹出堆顶元素

// 将大顶堆改成小顶堆
1. heap.push(-x);
2. 
    #include<queue>
    #include<vector>
    priority_queue<int, vector<int>, greater<int>> heap;       // 小根堆

// 如何自定义比较，注意下面比较函数的定义，别弄反了。
1. 自己写一个仿函数：定义一个类/结构体，然后重载bool operator()(int a, int b)函数;
struct cmp
{
    // 表示大的排序在后面，即小根堆
	bool operator()(const fruit& f1, const fruit& f2)
	{
		return f1.price > f2.price;
	}
};

2. 在结构体中重载 < 符号，注意声明函数为const， 否则编译不通过;
struct fruit
{
	int price;
	// 注意此处一定要声明为const，否则编译时无法通过
	// const修饰的是类函数隐藏的第一个参数 this指针，这表明this指针只读，也即类成员不可修改
	// 注意该用法只能是成员函数，要是类的静态函数或者是非成员函数就不可以在函数名后面加上const
    // 下面这个表示如果当前元素比后面的元素要小，则交换位置，大根堆。
	bool operator < (const fruit& f1) const
	{
		return this->price < f1.price;
	}
};
```



再列举一个例子：

```cpp
#include <bits/stdc++.h>

using namespace std;

struct A{
    int l, r;
    int label;
    bool operator < (const A &a)const {
        return l < a.l;
    }
};
// less和自定义结构体中的＜号是对应的，greater和 > 号是对应的
priority_queue<A, vector<A>, less<A>> q;
int main()
{
    q.push({1, 2, 3});
    q.push({3, 4, 5});
    q.push({4, 5, 6});
    while(q.size()) {
        auto t = q.top();
        q.pop();
        cout << t.l << ' ' << t.r << ' ' << t.label << endl;
    }
    return 0;
}

// 最后输出
// 4 5 6
// 3 4 5
// 1 2 3
```











### stack

```c++
push();			// 栈顶插入
top(); 			// 栈顶元素
pop();         // 弹出栈顶元素
size();
empty();
```



### deque

双端队列, 效率偏低；

```c++
size();
empty();
clear();
front();
back();
push_back();
pop_back();
push_front();   pop_front();
[]
begin()/ end()
```



### set,map,multiset, multimap

基于平衡二叉树（红黑树）来实现的，**动态维护有序序列**；

```c++
// set里不能有重复元素
set<int> s;
s.insert();			// 插入元素的时间复杂度O(logn)
size();
empty();
find();			// 查找一个数，不存在返回end迭代器
count()       // 返回某一个数的个数, 通常可以用count()函数来判断set和map里是否包含某个元素
erase();	// 如果输入一个数x，删除所有x；如果输入一个迭代器，删除这个迭代器；  O( k + logn)
begin()/ end();  //++ --的时间复杂度也是O(logn)

// multiset里可以有重复元素
multiset<int> ms;

lower_bound() / upper_bound();
lower_bound(x)  返回大于等于x的最小的数的迭代器;
upper_bound(x)	返回大于x的最小的数的迭代器，不存在返回end();

```

* map, multimap

```c++
insert(make_pair("ysq", 111));     // 插入的数是一个pair
erase();     // 输入的参数是pair或者迭代器键值对
find(key);      // 查找以 key 为键的键值对，如果找到，则返回一个指向该键值对的正向迭代器；反之，则返回一个指向容器中最后一                   个键值对之后位置的迭代器（如果 end() 方法返回的迭代器）
[];          //可以像用数组一样使用map, 时间复杂度是O(logn),数组的下标是O(1)
iter->first; iter->second;
map<string, int> a;
a["yxc"] = 1;
cout<< a["yxc"]<<endl;
```



#### map中的排序：

```cpp
#include <bits/stdc++.h>

using namespace std;

struct A{
    int l, r;
    int label;
    bool operator < (const A &a)const {
        return l < a.l;
    }
};
// 按照key值排序, 且大的排在前面
map<int, A, greater<int>> m;
int main()
{
    m.insert({2, {1, 2 ,3}});
    m.insert({1, {2, 3, 4}});
    // 2 1 2 3
    // 1 2 3 4
    for (auto [k, v] : m) {
        cout << k << ' ' << v.l << ' ' << v.r << ' ' << v.label <<endl;
    }
    return 0;
}
```



如果map中的key是一个结构体:

```cpp
#include <bits/stdc++.h>

using namespace std;

struct A{
    int l, r;
    int label;
    bool operator < (const A &a)const {
        return l < a.l;
    }
};

map<A, int, less<A>> m;
int main()
{
    m.insert({{2, 3, 4}, 1});
    m.insert({{1, 2 ,3}, 2});
    
    // 1 2 3 2
    // 2 3 4 1
    for (auto [k, v] : m) {
        cout << k.l << ' ' << k.r << ' ' << k.label << ' ' << v <<endl;
    }
    return 0;
}
```

如果map要按照value值排序：
**可以将map中的元素按照pair的方式存储在序列容器vector<>中，利用vector里的sort来排序。**

```cpp
bool compare(const pair<string,int>& a, const pair<string,int>& b){
	if( a.second == b.second )   return a.first < b.first;
    else return a.second > b.second;
}
map<string,int> m{{"a",1},{"b",2},{"c",3}};

vector<pair<string,int>> v(m.begin(), m.end());//将map中的元素拷贝到vector中

sort(v.begin(), v.end(), compare);//实现value的排序

```






### unordered_set, unordered_map, unordered_multiset, unordered_multimap

基于哈希表来实现的， 和上面类似，增删改查的时间复杂度是O(1)；

缺点是不支持lower_bound() / upper_bound(), 也不支持迭代器的++ 和 --;

```c++
// 初始化
std::unordered_map<std::string, size_t> people {{"Jan",44}, {"Jim", 33}, {"Joe", 99}}; // Name,age


// //复制一个已有的unordered_map
unordered_map<char, int> hs(hw);
// 一个键key, 映射多个值，把多个值放入一个vector中.
unordered_map<string, vector<int>> m_counter;
// 初始化空间的方法.
m_counter[current_word] = vector<int>(3, 0);
// 注意，如果要判断hash表中是否含有某个键，不能用if(map[key] == 0) ，这会自动建立一个key
if(map.count(key)){}


// 遍历map的一种简单写法，适合用于写算法, 需要满足C++17
for (auto [k, v] : map) {
    cout << k << " " << v << endl;
}

for (auto &[k, v] : map) {
    // 这种遍历方式只能改变value值，key键是不能变的
}


//另一种写法
for (auto iter = map.begin(); iter != map.end(); ++iter) {
    cout << iter->first << " " << iter->second << endl;
}
```



### bitset

压位， 节省内存；

比如想要开辟一个10000 * 10000 bool数组，如果直接开辟，就需要$10^8 = 100MB$内存，但是如果限制内存为64MB, 那么就需要用bitset来存储；

```cpp
bitset<10000> s;
~, &, |, ^;
>>, << ;
== , !=;
[]; 取出来某一位
count(); //返回有多少个1
any/ none() ;     // 判断是否至少有一个1， noen()判断是否全为空
set(); //把所有位置设为1
set(k,v);
reset();		// 把所有位变成0
flip();        // 等价于~
flip(k)			// 把第k位取反
```



### 迭代器和下标的转换

```cpp
// 迭代器转化为下标
distance是计算两个iterator直接的距离;
index = distance(container.begin(), iter);			// 得到iter的下标: index

// 下标转化为迭代器
advance是将iterator移动指定个元素;
iter = container.begin();
advance(iter, index);						// 得到index位置的迭代器iter


// 注意vector.front(), vector.back(), vector.begin(), vector.end() 的区别
前两者都是返回元素的引用，后两者才是返回迭代器
```





### 函数对象

* 重载**函数调用操作符**的类，其对象常称为**函数对象**
* **函数对象**使用重载的()时，行为类似函数调用，也叫**仿函数**

本质： 函数对象(仿函数)是一个**类**，不是一个函数

**特点：**

* 函数对象在使用时，可以像普通函数那样调用, 可以有参数，可以有返回值；
* 函数对象超出普通函数的概念，函数对象可以有自己的状态, 在自己的类里面添加成员属性值；
* **函数对象可以作为参数传递。**

```c++
class MyAdd {
public:
	int operator()( int v1, int v2){
		return v1 + v2;
	}
};

void test() {
	MyAdd myAdd;
	cout << myAdd(10, 10) << endl;
}

int main() {
	test();
	return 0;
}
```





###  谓词

####  谓词概念



**概念：**

* 返回**bool类型的仿函数**称为**谓词**
* 如果operator()接受一个参数，那么叫做一元谓词
* 如果operator()接受两个参数，那么叫做二元谓词



####  一元谓词

**示例：**

```C++
#include <vector>
#include <algorithm>

//1.一元谓词
class GreaterFive{
	bool operator()(int val) {
		return val > 5;
	}
};

void test01() {

	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	// 传递GreaterFive() 匿名的函数对象
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());
	if (it == v.end()) {
		cout << "没找到!" << endl;
	}
	else {
		cout << "找到:" << *it << endl;
	}

}

int main() {

	test01();

	system("pause");

	return 0;
}
```

总结：参数只有一个的谓词，称为一元谓词

![image-20210815104841211](STL总结.assets/image-20210815104841211.png)

出现`Pred`时，表示是一个谓词；



#### 二元谓词

**经典sort示例：**

```C++
#include <vector>
#include <algorithm>
//二元谓词
class MyCompare
{
public:
	bool operator()(int num1, int num2)
	{
		return num1 > num2;
	}
};

void test01()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(40);
	v.push_back(20);
	v.push_back(30);
	v.push_back(50);

	//默认从小到大
	sort(v.begin(), v.end());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "----------------------------" << endl;

	//使用函数对象改变算法策略，排序从大到小
	sort(v.begin(), v.end(), MyCompare());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```



### 内建函数对象

####  内建函数对象意义

**概念：**

* STL内建了一些函数对象

**分类:**

* 算术仿函数，加减乘除

* 关系仿函数，对比，大于小于，相等不相等

* 逻辑仿函数; 基本用不到

**用法：**

* 这些仿函数所产生的对象，用法和一般函数完全相同
* 使用**内建函数对象**，需要引入头文件 `#include<functional>`、



#### 算术仿函数

**功能描述：**

* 实现四则运算
* 其中`negate`是一元运算，其他都是二元运算



**仿函数原型：**

* `template<class T> T plus<T>`                //加法仿函数
* `template<class T> T minus<T>`              //减法仿函数
* `template<class T> T multiplies<T>`    //乘法仿函数
* `template<class T> T divides<T>`         //除法仿函数
* `template<class T> T modulus<T>`         //取模仿函数
* `template<class T> T negate<T>`           //取反仿函数  10 --》 -10



**示例：**

```C++
#include <functional>
//negate
void test01()
{
	negate<int> n;
	cout << n(50) << endl;
}

//plus
void test02()
{
    // 这里默认加法的两个类型是相同的
	plus<int> p;
	cout << p(10, 20) << endl;
}

int main() {

	test01();
	test02();

	system("pause");

	return 0;
}
```

总结：使用内建函数对象时，需要引入头文件 `#include <functional>`



####  关系仿函数

**功能描述：**

- 实现关系对比



**仿函数原型：**

* `template<class T> bool equal_to<T>`                    //等于
* `template<class T> bool not_equal_to<T>`            //不等于
* `template<class T> bool greater<T>`                      //大于
* `template<class T> bool greater_equal<T>`          //大于等于
* `template<class T> bool less<T>`                           //小于
* `template<class T> bool less_equal<T>`               //小于等于



**示例：**

```C++
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;
class MyCompare
{
public:
	bool operator()(int v1,int v2)
	{
		return v1 > v2;
	}
};
void test01()
{
	vector<int> v;

	v.push_back(10);
	v.push_back(30);
	v.push_back(50);
	v.push_back(40);
	v.push_back(20);

    // 10 30 50 40 20 
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	//自己实现仿函数
	//sort(v.begin(), v.end(), MyCompare());
	//STL内建仿函数 大于仿函数
	sort(v.begin(), v.end(), greater<int>());

    // 50 40 30 20 10
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

int main() {

	test01();

	return 0;
}
```

总结：关系仿函数中最常用的就是greater<>大于， 不写默认是less<int>()



### STL常用算法

**概述**:

* 算法主要是由头文件`<algorithm>` `<functional>` `<numeric>`组成。



* `<algorithm>`是所有STL头文件中最大的一个，范围涉及到比较、 交换、查找、遍历操作、复制、修改等等
* `<numeric>`体积很小，只包括几个在序列上面进行简单数学运算的模板函数
* `<functional>`定义了一些模板类,用以声明函数对象。



#### 去重技巧：

```c++
1. sort + erase + unique
sort(nums.begin(), nums.end());
nums.erase(unique(nums.begin(), nums.end()), nums.end());

2. 放在set里
set.insert(num);
```





#### 遍历算法: for_each, transform

以下的算法也可以调用普通函数

```c++
for_each(iterator beg, iterator end, _func);   // _func普通函数或者函数对象
//遍历算法
void print01(int val){
    cout << val << " ";
}
// 调用普通函数不加括号，传递的是函数指针
for_each(v.begin(), v.end(), print01);


class print02{
public:
    void operator()(int val){
        cout << val << " ";
    }
}; 


for_each(v.begin(), v.end(), print02());		//调用函数对象

// ============ //
class TransForm
{
public:
	int operator()(int val)
	{
		return val;
	}
};
transform(iterator beg1, iterator end1, iterator beg2, _func);
vector<int>vTarget; //目标容器
vTarget.resize(v.size()); // 目标容器需要提前开辟空间
transform(v.begin(), v.end(), vTarget.begin(), TransForm());

```



#### 查找算法:find,count

```c++
find(iterator beg, iterator end, value);       // value为要查找的元素
// find在algorithm头文件下，如果没找到, 返回arr.end(); 如果找到了，返回迭代器。
vector<int> arr{1,2,3,4};
auto pos = find(arr.begin(), arr.end(), 5);
if (pos == arr.end()) {
    cout << "yes" << endl;				// 返回 yes
}



find_if(iterator beg, iterator end, _Pred);  
adjacent_find(iterator beg, iterator end);   //查找相邻重复元素，两个元素相邻，并且相等。返回迭代器；找不到返回end()
bool binary_search(iterator beg, iterator end, value);  // 二分查找。必须原来的元素是有序的
count(iterator beg, iterator end, value);       //统计元素个数
count_if(iterator beg, iterator end, _Pred);     // 按照谓词来统计元素个数
```





#### 排序算法:sort,merge,reverse,lower_bound()， upper_bound()

```text
sort(iterator beg, iterator end, _Pred);    // 比较函数可以是谓词，可以是普通函数
random_shuffle(iterator beg, iterator end);  // 指定范围内的元素随机调整次序，使用时记得加随机数种子
//merge中容器元素合并，并存储到另一容器中
// 注意: 两个容器必须是有序的 ; dest :目标容器开始迭代器, 合并出来的元素不是有序的
merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);  
reverse(iterator beg, iterator end);              //用的多！
lower_bound(), upper_bound()用于有序数组或容器中:
	lower_bound(first, last, val)用来寻找数组或容器的[first,last)范围内第一个值大于等于val的元素位置，若是数组，返回指针；若是容器，返回迭代器。
    upper_bound(first, last, val)返回第一个大于val值的元素位置。
begin <    x <= lower_bound < upper_bound     < end                                          
```



#### 拷贝和替换算法:copy,swap,replace

```c++
copy(iterator beg, iterator end, iterator dest);           // dest目标起始迭代器 记得提前开辟空间
replace(iterator beg, iterator end, oldvalue, newvalue);   // 将区间内的旧元素替换成新元素
replace_if(iterator beg, iterator end, _pred, newvalue);   // 利用谓词来替换
swap(container c1, container c2);                          // 两个容器需要同种类型
```



#### 算术生成算法: accumulate,fill

算术生成算法属于小型算法，使用时包含的头文件为 `#include <numeric>`

```c++
// 计算容器元素累计总和
// beg 开始迭代器
// end 结束迭代器
// value 起始值
accumulate(iterator beg, iterator end, value);
// res = accumulate(euler + 1, euler + n + 1, (LL)0);    从euler[1] 到euler[n]的累计求和，且返回类型为long long
fill(iterator beg, iterator end, value);        // 填充指定的值
// 二维数组使用fill来填充
fill(&g[0][0], &g[0][0] + N * N, '.');
// 一维数组使用fill来填充
fill(col, col + N, false);
```



#### 常用的集合算法:求交集并集，差集

```c++
// 求两个容器的交集 注意:两个集合必须是有序序列
set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
// 使用方法
#include <vector>
#include <algorithm>

class myPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test01()
{
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < 10; i++)
    {
		v1.push_back(i);
		v2.push_back(i+5);
	}

	vector<int> vTarget;
	//取两个里面较小的值给目标容器开辟空间
	vTarget.resize(min(v1.size(), v2.size()));

	//返回目标容器的最后一个元素的迭代器地址
	vector<int>::iterator itEnd = 
        set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

	for_each(vTarget.begin(), itEnd, myPrint());
	cout << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

**总结：** 

* 求交集的两个集合必须的有序序列
* 目标容器开辟空间需要从**两个容器中取小值**
* set_intersection返回值既是交集中最后一个元素的位置



```c++
// 求两个集合的并集 注意:两个集合必须是有序序列   set_union返回值是并集中最后一个元素的位置
set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest); 
//求两个集合的差集  注意:两个集合必须是有序序列
set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
```



## 字符串处理函数

```c++
#include<cctype>
isalpha()             // 判断一个字符是不是字母，对中文字符会报错。
```



### 正则表达式库的使用

```cpp
// #include <regex>
#include <bits/stdc++.h>

using namespace std;
void test();
void test2();
void test_replace();


int main(){
    test();
    test2();
    test_replace();
    return 0;
}

void test()
{
    // 只能搜索在test_str中出现的第一个符合的单词
    // 查找不是在字符c之后的ei组合存在的单词
	string pattern("[^c]ei");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	regex r(pattern);
	smatch results;
	string test_str("receipt reinforce theif receive");
	if (regex_search(test_str, results, r))
		cout << results.str() << endl;//reinforce
}

void test2()
{
    // sregex的方法可以检查出所有匹配的部分
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    smatch result;
    string test_str("receipt reinforce theif receive");
    for (sregex_iterator it(test_str.begin(), test_str.end(), r), end_it; 
    it != end_it; it ++ ){
        cout << it -> str() << endl;
    }
    // reinforce theif
}


void test_replace()
{
    // regex_replace 将正则表达式匹配出来的部分全部替换成自定义的字符串
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    smatch result;
    string test_str("receipt reinforce theif receive");
    string to_replace("abcabc");
    string ret = regex_replace(test_str, r, to_replace);
    cout << ret << endl;  //receipt abcabc abcabc receive
}
```
