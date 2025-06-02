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
main.cpp 會隨機生成大量節點插入 BST，並測量刪除中間 key 時所花費的時間
測試結果請參考result1.txt
