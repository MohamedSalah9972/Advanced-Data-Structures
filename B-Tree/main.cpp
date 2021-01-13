#include <iostream>

using namespace std;
template <typename T,int order>
class Node {
public:
    T *key;
    int numKeys;
    Node **child;
    bool isLeaf;

    void print() {
        cout << endl;
        for (int i = 0; i < numKeys; ++i) {
            cout << key[i] ;
            if(i<numKeys-1)
                cout<<", ";
        }
        for (int i = 0; i < numKeys + 1; ++i) {
            if (child[i] != nullptr)
                child[i]->print();
        }

    }

    Node() {
        key = new T[order];
        isLeaf = true;
        child = new Node<T, order> *[order + 1];
        numKeys = 0;
        for (int i = 0; i <= order; i++) {
            child[i] = nullptr;
        }
    }

    Node(bool isLeaf) {
        this->isLeaf = isLeaf;
        key = new T[order];
        child = new Node<T, order> *[order + 1];
        numKeys = 0;
        for (int i = 0; i <= order; i++) {
            child[i] = nullptr;
        }
    }

    Node<T, order> *insert(T k, Node<T, order> *node, Node<T, order> *root) {
        if (isLeaf) {
            int i = numKeys - 1;
            while (i >= 0 && key[i] > k) {
                key[i + 1] = key[i];
                i--;
            }
            key[i + 1] = k;
            numKeys = numKeys + 1;
        } else {
            int i = 0;
            while (i < numKeys && k > key[i]) {
                i++;
            }
            child[i]->insert(k, this, root);
        }
        if (numKeys == order) {
            if (this == root) {
                auto *s = new Node<T, order>();
                s->isLeaf = false;
                s->child[0] = this;
                s->split(this);
                return s;

            } else {
                node->split(this);
            }


        }
        return root;
    }

    void split(Node<T, order> *node) {
        auto *rightNode = new Node<T, order>();
        int idx = 0, middleIndex = (order - 1) / 2;
        T middleValue = node->key[middleIndex];
        int numKeyNode = node->numKeys;
        for (int i = middleIndex + 1; i < numKeyNode; i++) {
            rightNode->key[idx] = node->key[i];
            idx++;
            node->numKeys = (node->numKeys) - 1;
            rightNode->numKeys = (rightNode->numKeys) + 1;
        }
        if (!node->isLeaf) {
            int j = 0;
            for (int i = (order + 1) / 2; i <= order; i++) {
                rightNode->child[j++] = node->child[i];
            }
            rightNode->isLeaf = node->isLeaf;
        }
        int j = order - 1;
        while (child[j] != node) {
            child[j + 1] = child[j];
            j--;
        }
        child[j + 1] = rightNode;
        j = numKeys;
        while (j > 0 && key[j - 1] > middleValue) {
            key[j] = key[j - 1];
            j--;
        }
        key[j] = middleValue;
        numKeys = numKeys + 1;
        node->numKeys = (node->numKeys) - 1;
    }
};
template <typename T,int order>
class BTree{
private:
    Node<T,order>* root;
public:

    BTree(){
        root = nullptr;
    }
    void Print(){
        if(root!=nullptr)
            root->print();
    }

    void Insert(T k){
        if(root==nullptr){
            root=new Node<T,order>(true);
            root->key[0]=k;
            root->numKeys=1;
        }
        else{
            root = root->insert(k, root,root);
        }
    }
};




int main(){
    BTree<char,5> t;
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');
    t.Print();
    BTree<int,3> t1;

    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);

    t1.Print();
}
