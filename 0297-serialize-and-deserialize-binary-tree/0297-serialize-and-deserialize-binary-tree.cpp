class Codec {
public:
    // Convert tree into a string
    string serialize(TreeNode* root) {
        if (root == NULL) {
            return "#,";
        }

        return to_string(root->val) + "," +
               serialize(root->left) +
               serialize(root->right);
    }

    // Convert string back into a tree
    TreeNode* build(queue<string>& q) {
        string s = q.front();
        q.pop();

        if (s == "#") {
            return NULL;
        }

        TreeNode* root = new TreeNode(stoi(s));

        root->left = build(q);
        root->right = build(q);

        return root;
    }

    TreeNode* deserialize(string data) {
        queue<string> q;
        string s = "";

        for (char c : data) {
            if (c == ',') {
                q.push(s);
                s = "";
            } else {
                s += c;
            }
        }

        return build(q);
    }
};