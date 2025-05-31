#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "bst.cpp"

using namespace std;

void BSTTest() {
    uint16_t nn[] = {100,  500,  1000, 2000, 3000, 4000,
                     5000, 6000, 7000, 8000, 9000, 10000};
    BST<uint16_t, uint16_t> BST;
    mt19937 mt(chrono::high_resolution_clock::now().time_since_epoch().count());
    for (uint16_t n : nn) {
        for (size_t i = 0; i < n; i++) {
            uint32_t num = mt() % UINT32_MAX;
            BST.insert(i, num);
        }
        uint16_t BSTHeight = BST.height();
        auto start = chrono::high_resolution_clock::now();
        BST.remove(n / 2);
        auto end = chrono::high_resolution_clock::now();
        auto duration =
            chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "BST n=" << n << ", BST Height: " << BSTHeight
             << ", log2(N): " << log2(n) << ", ratio: " << BSTHeight / log2(n)
             << ", remove time: " << duration.count() << endl;
    }
}
int main() {
    BSTTest();
    return 0;
}