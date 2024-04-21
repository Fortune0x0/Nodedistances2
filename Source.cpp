

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <queue>
using namespace std;

int node_dist_sum = 0;
int check;
struct Node {
    int data;
    Node* left;
    Node* right;
};
void add_parent_nodes(Node* root, int k);
pair<int, int> findDepths(Node* root, int k, Node* visited);
unordered_map<Node*, Node*> parent;
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;

    return newNode;
}

void createTree(vector<int>myVector, Node** root, int start, int end) {
    if (start > end) {
        return;
    }
    int middle = (start + end) / 2;
    *root = createNode(myVector[middle]);
    createTree(myVector, &(*root)->left, start, middle - 1);
    createTree(myVector, &(*root)->right, middle + 1, end);
}



pair <int, int> map_parent_nodes(Node* root, int key, int k) {
    pair<int, int> null_node = make_pair(0, 0);
    Node* target = nullptr;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        if (q.front()->data == key) {
            target = q.front();
        }
        if (q.front()->left) {
            parent[q.front()->left] = q.front();
            q.push(q.front()->left);
        }
        if (q.front()->right) {
            parent[q.front()->right] = q.front();
            q.push(q.front()->right);
          
        }
        q.pop();

    }
    if (target) {
        return add_parent_nodes(target, k), findDepths(target, k, target);
    }
    cout << "Couldn't find node " << endl;
    return null_node;
}

void add_parent_nodes(Node* root, int k) {
    if (k != 0) {
        if (parent.find(root) != parent.end()) {
            findDepths(parent[root], k - 1, root);

            add_parent_nodes(parent[root], k - 1);
            //return the ending k value to next function
        }

    }
    
    //Return original root


}
pair<int, int> findDepths(Node* root, int k, Node * visited) {
    node_dist_sum += root->data;
    
    

    pair<int, int> p = make_pair(1, 0);
    if (k != 0) {
        if (root->left && root->left != visited) {
            pair<int, int>pchild = findDepths(root->left, k - 1, visited);
            p.second += pchild.first + pchild.second;
            p.first += pchild.first;


        }
        if (root->right && root->right != visited) {
            pair<int, int>pchild = findDepths(root->right, k - 1, visited);
            p.second += pchild.first + pchild.second;
            p.first += pchild.first;

        }
    }

    return p;
}

void find_total_depths_and_distances(Node* root, int key, int k) {
    pair<int, int> nodes = map_parent_nodes(root, key, k);
    
    
    cout << "Nodes traversed: " << nodes.first << "   Depths: " << nodes.second << endl << endl;
    cout << "The sum of distance of  " << "\"" <<  k << "\"" << " is " << node_dist_sum;
    //call the node_sum after calling the second function

}

int main()
{
    Node* root = nullptr;
    vector<int>MyVector = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    createTree(MyVector, &root, 0, MyVector.size() - 1);
    int k = 2;
    int target = 0;
    find_total_depths_and_distances(root, target, k);
    return 0;
}







