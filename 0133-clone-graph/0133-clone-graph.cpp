class Solution {
public:
    unordered_map<Node*, Node*> mp;

    Node* cloneGraph(Node* node) {
        if (node == NULL)
            return NULL;

        if (mp.find(node) != mp.end())
            return mp[node];

        Node* copy = new Node(node->val);
        mp[node] = copy;

        for (Node* neighbor : node->neighbors) {
            copy->neighbors.push_back(cloneGraph(neighbor));
        }

        return copy;
    }
};