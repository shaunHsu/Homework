#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
class MinPQ {
   private:
    vector<T> pq;

    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }
    void heapifyUp(int i) {
        while (i > 0 && pq[i] < pq[parent(i)]) {
            swap(pq[i], pq[parent(i)]);
            i = parent(i);
        }
    }
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

   public:
    MinPQ() {}
    virtual ~MinPQ() {}
    virtual bool isEmpty() const { return pq.empty(); }
    virtual T top() const {
        if (isEmpty()) {
            throw out_of_range(
                "Priority queue is empty, cannot call top().");
        }
        return pq[0];
    }
    virtual void push(const T& value) {
        pq.push_back(value);
        heapifyUp(pq.size() - 1);
    }
    virtual T pop() {
        if (isEmpty()) {
            throw out_of_range(
                "Priority queue is empty, cannot call pop().");
        }
        T minValue = pq[0];
        pq[0] = pq.back();
        pq.pop_back();
        if (!isEmpty()) {
            heapifyDown(0);
        }
        return minValue;
    }
    int size() const { return pq.size(); }
};