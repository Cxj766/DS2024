#include <iostream>
#include <stdexcept>

typedef int Rank; // 秩
#define DEFAULT_CAPACITY 3 // 默认的初始容量

template <typename T>
class Vector {
protected:
    Rank _size;         // 当前大小
    int _capacity;      // 当前容量
    T* _elem;          // 数据指针

    void copyFrom(T const* A, Rank lo, Rank hi);  // 复制数组区间 A[lo, hi)
    void expand();    // 扩容
    void shrink();    // 缩容
    bool bubble(Rank lo, Rank hi); // 扫描交换
    void bubbleSort(Rank lo, Rank hi); // 冒泡排序算法
    Rank max(Rank lo, Rank hi); // 选取最大元素
    void selectionSort(Rank lo, Rank hi); // 选择排序算法
    void merge(Rank lo, Rank mi, Rank hi); // 归并算法
    void mergeSort(Rank lo, Rank hi); // 归并排序算法
    Rank partition(Rank lo, Rank hi); // 轴点构造算法
    void quickSort(Rank lo, Rank hi); // 快速排序算法
    void heapSort(Rank lo, Rank hi); // 堆排序

public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0); // 容量为 c、大小为 s、所有元素初始化为 v
    Vector(T const* A, Rank lo, Rank hi); // 数组区间复制
    Vector(T const* A, Rank n); // 数组整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi); // 向量区间复制
    Vector(Vector<T> const& V); // 向量整体复制

    ~Vector(); // 析构函数

    // 读访问接口
    Rank size() const { return _size; } // 当前大小
    bool empty() const { return _size == 0; } // 是否为空
    Rank find(T const& e) const; // 无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi) const; // 无序向量区间查找

    // 可写访问接口
    T& operator[](Rank r) const; // 重载下标操作符
    Vector<T>& operator=(Vector<T> const&); // 重载赋值操作符
    T remove(Rank r); // 删除秩为 r 的元素
    Rank insert(Rank r, T const& e); // 插入元素
    Rank insert(T const& e) { return insert(_size, e); } // 作为末元素插入
    void sort(Rank lo, Rank hi); // 对 [lo, hi) 排序
    void sort() { sort(0, _size); } // 整体排序
    void traverse(void (*visit)(T&)); // 遍历（使用函数指针）
    template <typename VST> void traverse(VST& visit); // 遍历（使用函数对象）
};

template <typename T>
Vector<T>::Vector(int c, int s, T v) : _size(s), _capacity(c) {
    _elem = new T[_capacity];
    for (_size = 0; _size < s; _size++) {
        _elem[_size] = v; // 初始化所有元素
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] _elem; // 释放内部空间
}

// 复制数组区间 A[lo, hi)
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
    _capacity = hi - lo; // 设定容量为 hi - lo
    _elem = new T[_capacity];
    _size = 0;
    for (Rank i = lo; i < hi; i++) {
        _elem[_size++] = A[i]; // 逐个复制
    }
}

template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return; // 如果空间足够则返回
    T* oldElem = _elem; // 备份旧数组
    _capacity = (_capacity < 1) ? 1 : 2 * _capacity; // 扩容
    _elem = new T[_capacity]; // 重新分配内存
    for (Rank i = 0; i < _size; i++) {
        _elem[i] = oldElem[i]; // 复制旧数组到新数组
    }
    delete[] oldElem; // 释放旧数组内存
}

template <typename T>
T& Vector<T>::operator[](Rank r) const {
    if (r < 0 || r >= _size) throw std::out_of_range("Index out of range");
    return _elem[r]; // 返回第 r 个元素
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
    if (this != &V) { // 自我赋值检查
        delete[] _elem; // 释放旧数组
        copyFrom(V._elem, 0, V._size); // 复制新数组
    }
    return *this; // 返回自身
}

template <typename T>
T Vector<T>::remove(Rank r) {
    if (r < 0 || r >= _size) throw std::out_of_range("Index out of range");
    T e = _elem[r]; // 备份待删除元素
    for (Rank i = r + 1; i < _size; i++) {
        _elem[i - 1] = _elem[i]; // 前移
    }
    _size--; // 规模减小
    _elem[_size].~T(); // 调用析构函数（如果 T 需要）
    if (_size < _capacity / 4) shrink(); // 可能需要缩容
    return e; // 返回被删除的元素
}

// 其他算法（排序、查找等）可以继续实现

template <typename T>
void Vector<T>::shrink() {
    if (_size * 4 > _capacity) return; // 如果装填因子大于 1/4，返回
    T* oldElem = _elem; // 备份旧数组
    _capacity = _capacity / 2; // 缩容为一半
    _elem = new T[_capacity]; // 重新分配内存
    for (Rank i = 0; i < _size; i++) {
        _elem[i] = oldElem[i]; // 复制旧数组到新数组
    }
    delete[] oldElem; // 释放旧数组内存
}

template <typename T>
Rank Vector<T>::find(T const& e) const {
    for (Rank i = 0; i < _size; i++) {
        if (_elem[i] == e) return i; // 找到返回索引
    }
    return -1; // 未找到返回 -1
}
