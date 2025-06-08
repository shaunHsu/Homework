#include <algorithm>  // For std::max
#include <cstdint>    // For uint16_t if needed, though height will use int
#include <iostream>

// Node structure for key-value pairs
template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node<K, V>* left;
    Node<K, V>* right;

    Node(K k, V val) : key(k), value(val), left(nullptr), right(nullptr) {}
};

template <typename K, typename V>
class BST {
   public:
    Node<K, V>* root;

    BST() : root(nullptr) {}

    // Insert a key-value pair
    void insert(K key, V value) { root = insertRecursive(root, key, value); }

    // Search for a key and return a pointer to its value
    // Returns nullptr if key is not found
    V* search(K key) {
        Node<K, V>* resultNode = searchRecursive(root, key);
        if (resultNode != nullptr) {
            return &(resultNode->value);
        }
        return nullptr;
    }

    // Calculate the height of the tree
    // Height of an empty tree is -1, height of a tree with one node is 0
    int height() {  // Changed to int
        return calculateHeight(root);
    }

    // Remove a node with the given key
    void remove(K key) { root = removeRecursive(root, key); }
    void removeTest() {
        if (root == nullptr) {
            std::cout << "Tree is empty. Nothing to remove." << std::endl;
            return;
        }

        int maxDepth = -1;
        Node<K, V>* deepestNode = nullptr;

        // 從根節點開始，初始深度為 0，尋找最深的節點
        findDeepestNodeRecursive(root, 0, maxDepth, deepestNode);

        if (deepestNode != nullptr) {
            K keyToDelete = deepestNode->key;
            remove(keyToDelete);
        } else {
            // 這個情況在樹不為空時不應該發生
            std::cout << "Could not find a deepest node." << std::endl;
        }
    }

    ~BST() { destroyRecursive(root); }

   private:
    void findDeepestNodeRecursive(Node<K, V>* current, int currentDepth,
                                  int& maxDepth, Node<K, V>*& deepestNode) {
        if (current == nullptr) {
            return;
        }

        // 如果當前節點的深度大於已知的最大深度，就更新紀錄
        if (currentDepth > maxDepth) {
            maxDepth = currentDepth;
            deepestNode = current;
        }

        // 繼續往左右子樹尋找
        findDeepestNodeRecursive(current->left, currentDepth + 1, maxDepth,
                                 deepestNode);
        findDeepestNodeRecursive(current->right, currentDepth + 1, maxDepth,
                                 deepestNode);
    }
    Node<K, V>* insertRecursive(Node<K, V>* current, K key, V value) {
        if (current == nullptr) {
            return new Node<K, V>(key, value);
        }

        if (key < current->key) {
            current->left = insertRecursive(current->left, key, value);
        } else if (key > current->key) {
            current->right = insertRecursive(current->right, key, value);
        } else {
            // If key already exists, update the value (optional behavior)
            current->value = value;
        }
        return current;
    }

    Node<K, V>* searchRecursive(Node<K, V>* current, K key) {
        if (current == nullptr || current->key == key) {
            return current;
        }

        if (key < current->key) {
            return searchRecursive(current->left, key);
        } else {
            return searchRecursive(current->right, key);
        }
    }

    void inorderRecursive(Node<K, V>* current) {
        if (current != nullptr) {
            inorderRecursive(current->left);
            std::cout << current->key << ":" << current->value << " ";
            inorderRecursive(current->right);
        }
    }

    void destroyRecursive(Node<K, V>* node) {
        if (node) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }

    int calculateHeight(Node<K, V>* node) {  // Changed to int
        if (node == nullptr) {
            return -1;
        }
        // leftHeight and rightHeight should also ideally be int
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return std::max(leftHeight, rightHeight) + 1;
    }

    Node<K, V>* findMin(Node<K, V>* node) {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node<K, V>* removeRecursive(Node<K, V>* current, K key) {
        if (current == nullptr) {
            return nullptr;  // Key not found
        }

        // Navigate to the node to be deleted
        if (key < current->key) {
            current->left = removeRecursive(current->left, key);
        } else if (key > current->key) {
            current->right = removeRecursive(current->right, key);
        } else {
            // Node with the key found

            // Case 1: Node has no children (leaf node)
            if (current->left == nullptr && current->right == nullptr) {
                delete current;
                return nullptr;
            }
            // Case 2: Node has one child
            else if (current->left == nullptr) {
                Node<K, V>* temp = current->right;
                delete current;
                return temp;
            } else if (current->right == nullptr) {
                Node<K, V>* temp = current->left;
                delete current;
                return temp;
            }
            // Case 3: Node has two children
            else {
                Node<K, V>* temp =
                    findMin(current->right);  // Find inorder successor
                current->key = temp->key;
                current->value = temp->value;
                current->right = removeRecursive(
                    current->right, temp->key);  // Delete the inorder successor
            }
        }
        return current;
    }
};