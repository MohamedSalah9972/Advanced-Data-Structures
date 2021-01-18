#include <iostream>
using namespace std;

int* append(int *arr,int &size,int element){ // function to push in dynamic array
    int* newIndex = new int[size+1]; // create new array for indexes with old size + 1
    for (int i = 0; i < size; ++i) {
        newIndex[i] = arr[i]; // copy old to new
    }
    newIndex[size] = element;
    size++;
    return newIndex;
}

template <class T>
class LinkedListNode {
public:
    int *index;
    int indexSize=0;
    LinkedListNode(){
        indexSize = 0;
        index = nullptr;
    }

    char data;
    LinkedListNode *nxt; // next child
    T *trieNode;
};

template <class T>
class LinkedList {
private:
    LinkedListNode<T> *head;
public:
    LinkedList() {
        head = nullptr;
    }

    T *insert(char value, int idx) {
        LinkedListNode<T> *newNode = new LinkedListNode<T>();
        newNode->data = value;
        newNode->trieNode = new T();
        newNode->nxt = nullptr;
        if (head == nullptr) { /// if list is empty (specail case)
            head = newNode; /// head link newNode
            head->index = append(head->index,head->indexSize,idx);
            return head->trieNode;
        }
        auto it = search(value);
        if (it != nullptr) {
            it->index=append(it->index,it->indexSize, idx);
            return it->trieNode;
        }
        LinkedListNode<T> *last;
        last = head;
        while (last->nxt != nullptr) { /// get last node which its next = NULL
            last = last->nxt;
        }

        last->nxt = newNode;
        newNode->index = append(newNode->index,newNode->indexSize, idx);
        return newNode->trieNode;
    }

    LinkedListNode<T>* search(char c) {
        LinkedListNode<T> *returnNode = nullptr;
        LinkedListNode<T> *node = head;
        while (node != nullptr) {
            if (node->data == c) {
                returnNode = node;
                break;
            }
            node = node->nxt;
        }
        return returnNode;
    }
};


class TrieNode {
public:
    LinkedList<TrieNode> *list= new LinkedList<TrieNode>();
    void insert(char *word, int idx) {
        if (word[idx - 1] == '$') // if it's end of chars
            return;
        TrieNode *node = list->insert(word[idx],idx);
        node->insert(word,idx+1);
    }

     LinkedListNode<TrieNode> *search(char* word,int idx){
        if(list->search(word[idx]) != nullptr){
            if(word[idx+1] == NULL){
                return list->search(word[idx]);
            }
            return list->search(word[idx])->trieNode->search(word,idx+1);
        }
    }
};


class SuffixTrie {
private:
    TrieNode root;
public:

    SuffixTrie(char *word) {
        int i = 0;
        while (!i || word[i - 1] != '$') {
            root.insert(word, i);
            i++;
        }
    }

    void Search(char *a) {
        auto it = root.search(a, 0);
        int len = 0;
        while (*a != NULL) {
            a++;
            len++;
        }
        for (int i = 0; i < it->indexSize; ++i) {
            cout << it->index[i] - len + 1 << ' ';
        }
        cout << endl;
    }
};
int main() {

    SuffixTrie t("bananabanaba$");

    t.Search("ana"); // Prints: 1 3 7
    t.Search("naba"); // Prints: 4 8
    return 0;
}
