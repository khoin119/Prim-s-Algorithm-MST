#include <iostream>
using namespace std;


const int VERTEXCOUNT = 5;


template <typename T>
class Node {
private:
    T* data;
    Node<T>* leftChild;
    Node<T>* rightChild;
    Node<T>* parent;


public:

    Node(T* data) {
        this->data = data;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
    }

    void setData(T* value) {
        data = value;
    }

    T* getData() {
        return data;
    }

    void setLeftChild(Node<T>* node) {
        leftChild = node;
    }

    Node<T>* getLeftChild(){
        return leftChild;
    }

    void setRightChild(Node<T>* node) {
        rightChild = node;
    }

    Node<T>* getRightChild() {
        return rightChild;
    }

    void setParent(Node<T>* node) {
        parent = node;
    }

    Node<T>* getParent() const {
        return parent;
    }

    void print(){
        cout << *data << endl;
    }


};


template <typename T>
class BinaryHeap {
private:

    Node<T> *root;
    int numberOfElements;
    int height;

public:

    BinaryHeap() {
        root = nullptr;
        numberOfElements = 0;
        height = 0;
    }

    BinaryHeap(T *value) {
        root = new Node<T>(value);
        numberOfElements = 1;
        height = 0;
    }

    ~BinaryHeap() {
        destroyTree(root);
    }

    void destroyTree(Node<T>* node) {
        if (node != nullptr) {
            destroyTree(node->getLeftChild());
            destroyTree(node->getRightChild());
            delete node;
        }
    }


    void setRoot(T *newRoot) {
        root = newRoot;
    }

    T *getRoot() {
        return root;
    }

    void setNumberOfElements(int num) {
        numberOfElements = num;
    }

    int getNumberOfElements() {
        return numberOfElements;
    }

    void setHeight(int h) {
        height = h;
    }

    int getHeight() {
        return height;
    }


    void insertElement(T* data) {
        Node<T>* newNode = new Node<T>(data);
        if (root == nullptr) {
            root = newNode;
        } else {
            insertHelper(newNode, root);
        }
        numberOfElements++;
    }

    // helper function to recursively insert an element into the heap
    void insertHelper(Node<T>* newNode, Node<T>* parent) {
        if (parent->getLeftChild() == nullptr) {
            parent->setLeftChild(newNode);
        } else if (parent->getRightChild() == nullptr) {
            parent->setRightChild(newNode);
        } else {
            insertHelper(newNode, parent->getLeftChild()); // if both children exist, go into the left child to maintain the complete binary tree property
        }
        newNode->setParent(parent);

        heapifyUp(newNode); // adjust heap property after insertion
    }


    // helper function to maintain heap property after insertion
    void heapifyUp(Node<T>* node) {
        Node<T>* parent = node->getParent();

        while (parent != nullptr && node->getData()->compare(*(parent->getData())) < 0) {
            T* temp = node->getData();
            node->setData(parent->getData());
            parent->setData(temp);
            node = parent;
            parent = node->getParent();
        }
    }


    Node<T>* deleteMin() {
        if (root == nullptr) {
            return nullptr;
        }
        T* minData = root->getData();
        Node<T>* lastNode = findLastNode();
        if (lastNode != root) {
            root->setData(lastNode->getData());
            deleteLastNode(lastNode);
            heapifyDown(root);
        } else {
            delete root;
            root = nullptr;
        }
        numberOfElements--;
        return new Node<T>(minData);
    }

    void heapifyDown(Node<T>* node) {
        while (node != nullptr) {
            Node<T>* smallest = node;
            Node<T>* leftChild = node->getLeftChild();
            Node<T>* rightChild = node->getRightChild();

            if (leftChild != nullptr && leftChild->getData()->compare(*(smallest->getData())) < 0) {
                smallest = leftChild;
            }
            if (rightChild != nullptr && rightChild->getData()->compare(*(smallest->getData())) < 0) {
                smallest = rightChild;
            }

            if (smallest != node) {
                T* temp = node->getData();
                node->setData(smallest->getData());
                smallest->setData(temp);
                node = smallest;
            } else {
                break;
            }
        }
    }


    void deleteLastNode(Node<T>* lastNode) {

        if (!root || !lastNode) { // check if either the heap or the last node is invalid
            return;
        }

        Node<T>* parent = lastNode->getParent(); // Get the parent of the last node

        if (!parent) { // Get the parent of the last node

            delete lastNode; // Delete the last node and set the root to null
            root = nullptr;
            return;
        }

        bool isLeftChild = false; // use binary bits to determine if the last node is a left or right child
        Node<T>* current = root;
        int mask = numberOfElements >> 1; // initialize mask to half of the number of elements


        while (mask > 0) {  // loop until the mask becomes zero
            if (numberOfElements & mask) { // if the bit corresponding to the mask is set
                if (parent->getRightChild() == lastNode) { // check if the right child of the parent is the last node
                    isLeftChild = false;
                    break;
                }
                current = current->getRightChild(); // move to the right child of the current node
            } else {
                if (parent->getLeftChild() == lastNode) { // if the bit is not set, check if the left child of the parent is the last node
                    isLeftChild = true;
                    break;
                }
                current = current->getLeftChild(); // move to the left child of the current node
            }
            mask >>= 1; // shift the mask to the right
            parent = current; // update the parent node
        }

        delete lastNode; // delete the last node

        if (isLeftChild) { // set the appropriate child pointer of the parent to null
            parent->setLeftChild(nullptr);
        } else {
            parent->setRightChild(nullptr);
        }
    }

    Node<T>* findLastNode() {
        if (!root) {  // check if the heap is empty
            return nullptr; // return null if the heap is empty
        }

        Node<T>* current = root; // start traversal from the root
        int mask = numberOfElements >> 1; // initialize mask to half of the number of elements

        // traverse the heap using binary bits to find the last node
        while (mask > 0) {
            if (numberOfElements & mask) {  // if the bit corresponding to the mask is set
                current = current->getRightChild(); // move to the right child of the current node
            } else {
                current = current->getLeftChild(); // if the bit is not set, move to the left child of the current node
            }
            mask >>= 1; // shift the mask to the right
        }

        return current;
    }

};


class Data {
private:

    int sourceVertex;
    int destinationVertex;
    int edgeCost;


public:

    Data() {
        sourceVertex = 0;
        destinationVertex = 0;
        edgeCost = 0;
    }

    Data(int source, int dest, int cost) { // source vertex, destination vertex, and edge cost
        sourceVertex = source;
        destinationVertex = dest;
        edgeCost = cost;
    }

    Data(int cost) { // only edge cost
        sourceVertex = 0;
        destinationVertex = 0;
        edgeCost = cost;
    }

    void setSourceVertex(int val) {
        sourceVertex = val;
    }

    int getSourceVertex() {
        return sourceVertex;
    }

    void setDestinationVertex(int val) {
        destinationVertex = val;
    }

    int getDestinationVertex() {
        return destinationVertex;
    }

    void setEdgeCost(int val) {
        edgeCost = val;
    }

    int getEdgeCost() {
        return edgeCost;
    }

    void print() {
        cout << edgeCost << " ";
    }

    int compare(Data& other) {
        if (this->edgeCost > other.edgeCost) {
            return 1;
        } else if (this->edgeCost < other.edgeCost) {
            return -1;
        }
        return 0;
    }
};


void runPrims(int G[VERTEXCOUNT][VERTEXCOUNT], BinaryHeap<Data>* binHeap) {
    bool visited[VERTEXCOUNT] = {false}; // bool array to keep track of visited nodes


    visited[0] = true; // start with the first vertex

    for (int j = 1; j < VERTEXCOUNT; ++j) { // add all edges adjacent to the first vertex to the binary heap
        if (G[0][j] != 0) {
            Data* edge = new Data(0, j, G[0][j]);
            binHeap->insertElement(edge);
        }
    }

    cout << "Prim's MST is Edge -> Cost" << endl;

    // actual prim's algorithm loop to process edges until all vertices are visited
    while (binHeap->getNumberOfElements() > 0) {
        // extract the minimum-cost edge from the binary heap
        Node<Data>* minEdgeNode = binHeap->deleteMin();
        Data minEdge = *(minEdgeNode->getData());
        delete minEdgeNode;

        int source = minEdge.getSourceVertex(); // extract information from the minimum-cost edge
        int dest = minEdge.getDestinationVertex();
        int cost = minEdge.getEdgeCost();

        if (!visited[dest]) { // if the destination vertex is not visited, add the edge to the MST
            visited[dest] = true; // set the destination vertex as visited
            cout << source << " - " << dest << " -> " << cost << endl;

            for (int j = 0; j < VERTEXCOUNT; ++j) { // add all edges adjacent to the newly visited vertex to the binary heap
                if (G[dest][j] != 0 && !visited[j]) {
                    Data* edge = new Data(dest, j, G[dest][j]);
                    binHeap->insertElement(edge);
                }
            }
        } // jump back up to the while loop and continue until 0 nodes in the heap
    }
}


int main() {

    int G[VERTEXCOUNT][VERTEXCOUNT] = {{0, 3, 65, 0, 0},
                                       {3, 0, 85, 20, 45},
                                       {65, 85, 0, 41, 77},
                                       {0, 20, 41, 0, 51},
                                       {0, 45, 77, 51, 0}};


    BinaryHeap<Data>* binHeap = new BinaryHeap<Data>();

    runPrims(G, binHeap);

    return 0;
}
