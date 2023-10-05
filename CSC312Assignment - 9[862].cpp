#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int d) {
        data = d;
        left = NULL;
        right = NULL;
    }
};


class cmp {
public:
    bool operator()(Node* a, Node* b) {
        return a->data > b->data;
    }
};

class Solution {
public:
    void traverse(Node* root, vector<string>& ans, string temp) {
        // Base case
        if (root->left == NULL && root->right == NULL) {
            ans.push_back(temp);
            return;
        }

        traverse(root->left, ans, temp + '0');
        traverse(root->right, ans, temp + '1');
    }

    vector<string> huffmanCodes(string S, vector<int> f, int N) {
        // Declaration of priority_queue
        // priority_queue<DataType, ContainerType, CompareFunction> pq;
        priority_queue<Node*, vector<Node*>, cmp> pq;

        for (int i = 0; i < N; i++) {
            Node* temp = new Node(f[i]);
            pq.push(temp);
        }

        while (pq.size() > 1) {
            Node* left = pq.top();
            pq.pop();

            Node* right = pq.top();
            pq.pop();

            Node* newNode = new Node(left->data + right->data);
            newNode->left = left;
            newNode->right = right;
            pq.push(newNode);
        }

        Node* root = pq.top();
        vector<string> ans;
        string temp = "";
        traverse(root, ans, temp);
        return ans;
    }
};

int main() {
    string input = "The rupee opened stronger after the dollar index fell to below hundred and ten levels, said Anil Kumar Bhansali, Head of Treasury, Finrex Treasury Advisors.";
    map<char, int> frequencies;

    // Calculate character frequencies
    for (char c : input) {
        if (c != ' ') {
            frequencies[c]++;
        }
    }

    // characters and frequencies ke liye array bna rhe
    vector<char> characters;
    vector<int> freq_values;

    for (auto entry : frequencies) {
        characters.push_back(entry.first);
        freq_values.push_back(entry.second);
    }

    int N = characters.size();

    for (int i = 0; i < N; i++) {
        cout << "'" << characters[i] << "': " << freq_values[i] << endl;
    }

    Solution solution;

    vector<string> huffmanCodes = solution.huffmanCodes(input, freq_values, N);

    cout << "---------------------------" << endl<< endl;
    cout << "Character Huffman Codes:" << endl<<endl;
    cout << "---------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "'" << characters[i] << "': " << huffmanCodes[i] << endl;
    }

    return 0;
}
