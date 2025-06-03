# 41243225

作業一,組員:41243227

## 題目類別
有三個題目分別是,(一) Max Heap 與 Min Heap 實作,(二) Binary Search Tree 實作,(三)漂動緩衝區 k-路合併

## (一) Max Heap 與 Min Heap 實作說明
實作最大堆積 (Max Heap) 與最小堆積 (Min Heap)，並提供插入與列印功能

## 程式實作 Min Heap

### heapifyUp：插入元素後向上調整
```cpp

void heapifyUp(int i) {
    while (i > 0 && pq[i] < pq[parent(i)]) {
        swap(pq[i], pq[parent(i)]);
        i = parent(i);
    }
}

```

### heapifyDown：刪除元素後向下調整
```cpp
void heapifyDown(int i) {
    int minIndex = i;
    int l = leftChild(i);
    int r = rightChild(i);
    int size = pq.size();

    if (l < size && pq[l] < pq[minIndex]) {
        minIndex = l;
    }
    if (r < size && pq[r] < pq[minIndex]) {
        minIndex = r;
    }
    if (i != minIndex) {
        swap(pq[i], pq[minIndex]);
        heapifyDown(minIndex);
    }
}
```

### push：加入新元素
```cpp
virtual void push(const T& value) {
    pq.push_back(value);
    heapifyUp(pq.size() - 1);
}
```

### pop：刪除並回傳最小值
```cpp
virtual T pop() {
    if (isEmpty()) {
        throw out_of_range("Priority queue is empty, cannot call pop().");
    }
    T minValue = pq[0];
    pq[0] = pq.back();
    pq.pop_back();
    if (!isEmpty()) {
        heapifyDown(0);
    }
    return minValue;
}
```
## 程式實作 Max Heap
因為主要只是把 Min Heap 的比較符號 < 換為 >,並保持邏輯則不在多做

## (二) Binary Search Tree 實作
實作二元搜尋樹 (Binary Search Tree)，並提供插入、搜尋、刪除以及中序、前序、後序遍歷功能。

## 程式實作

### 重點函式
### insert：插入節點

```cpp
Node<K, V>* insertRecursive(Node<K, V>* current, K key, V value) {
    if (current == nullptr) {
        return new Node<K, V>(key, value);
    }
    if (key < current->key) {
        current->left = insertRecursive(current->left, key, value);
    } else if (key > current->key) {
        current->right = insertRecursive(current->right, key, value);
    } else {
        current->value = value; // 更新值
    }
    return current;
}
```

### remove：刪除節點
```cpp
Node<K, V>* removeRecursive(Node<K, V>* current, K key) {
    if (current == nullptr) return nullptr;
    if (key < current->key) {
        current->left = removeRecursive(current->left, key);
    } else if (key > current->key) {
        current->right = removeRecursive(current->right, key);
    } else {
        if (current->left == nullptr && current->right == nullptr) {
            delete current;
            return nullptr;
        } else if (current->left == nullptr) {
            Node<K, V>* temp = current->right;
            delete current;
            return temp;
        } else if (current->right == nullptr) {
            Node<K, V>* temp = current->left;
            delete current;
            return temp;
        } else {
            Node<K, V>* temp = findMin(current->right);
            current->key = temp->key;
            current->value = temp->value;
            current->right = removeRecursive(current->right, temp->key);
        }
    }
    return current;
}
```

### height：計算樹高
```cpp
int calculateHeight(Node<K, V>* node) {
    if (node == nullptr) return -1;
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}
```

### 測試程式輸出說明
main.cpp 會隨機生成大量節點插入 BST，並測量刪除中間 key 時所花費的時間</br>
測試結果請參考result1.txt</br>

### (三)漂動緩衝區 k-路合併

## (a)題目條件簡述
總記錄數：n </br>
記憶體容量：𝑆 ≪ 𝑛，全部用於 I/O buffer </br>
Seek time： ts </br>
Latency time： t1 </br>
傳輸時間：每筆 record 要 tt 秒 </br>
在外部排序的第二階段中，所有記錄都會從磁碟讀入並合併處理一次 </br>

### 總輸入時間估算
每筆資料的平均讀取時間為 (ts+t1)/B+tt </br>
B = ⌊S/(k+1)⌋ </br>
tinput = n( (ts+t1) / (⌊S/(k+1)⌋) +tt) </br>

## (b)題目條件簡述

t=80ms=0.08s </br>
tcpy=20ms=0.02s </br>
tr=10^−3s </br>
n=200,000 </br>
m=64 </br>
S=2000 </br>

### 計算
r=⌈ 200000/64 ⌉=3125 </br>
tI/O= ts + t1 + S*tt =80+20+2000*1=2100 ms </br>
tinput(k)=2100 * r * ⌈logk(r)⌉ </br>

### 標格

|   k |   log_k(r) |   ceil(log_k(r)) |   t_input(k) (ms) |
|----:|-----------:|-----------------:|------------------:|
|   2 |   11.6096  |               12 |       7.875e+07   |
|   4 |    5.80482 |                6 |       3.9375e+07  |
|   8 |    3.86988 |                4 |       2.625e+07   |
|  10 |    3.49485 |                4 |       2.625e+07   |
|  16 |    2.90241 |                3 |       1.96875e+07 |
|  32 |    2.32193 |                3 |       1.96875e+07 |
|  64 |    1.93494 |                2 |       1.3125e+07  |
| 128 |    1.65852 |                2 |       1.3125e+07  |
| 512 |    1.28996 |                2 |       1.3125e+07  |

### 是否有 k 讓 t_cpu ≈ t_input(k)？
有,因為 t_cpu 是常數，但 t_input(k) 隨 k 遞減 </br>
若 t_cpu = X，則可根據上表找出最接近的 t_input(k)，調整 k 來讓兩者相等 </br>
