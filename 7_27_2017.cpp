/****************************************************************************
27. Serialization and Deserialization of a Binary Tree  (LeetCode 297)  // TODO
- preOrder/ levelOrder for serilization
- use special character to indicate null child
Problem is:
If input is "", after deserialize & serialize, the return string is "#"
    string s = "";
    auto root = r.deserialize(s);
    auto ret = r.serialize(root);
*/
class Codec {
public:
    // 1,2,4,#,#,#,3,#,7,#,#
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "#";
        return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        return mydeserialize(data);
    }
    TreeNode* mydeserialize(string& data){
        if (data.empty() || data[0] == '#'){
            if (data.size() > 1) data = data.substr(2);
            return nullptr;
        }
        TreeNode *node = new TreeNode(helper(data));
        node->left = mydeserialize(data);
        node->right = mydeserialize(data);
        return node;
    }
    int helper(string& data){
        int pos = data.find(',');
        if (pos == -1) throw invalid_argument("error");
        int ret  = stoi(data.substr(0, pos));
        data = data.substr(pos + 1);
        return ret;
    }
};

class BinaryTree {
public:
    TreeNode* root;
    void serialize(ostream& os) {
        mySerialize(os, root);
    }

    void mySerialize(ostream& os, TreeNode* root) {
        if (root == nullptr) {
            os << "# ";
            return;
        }
        os << root->val << " ";
        mySerialize(os, root->left);
        mySerialize(os, root->right);
    }

    BinaryTree deserialize(istream& is) {
        BinaryTree ret;
        ret.root = myDeserialize(is);
        return ret;
    }
    TreeNode* generateTree(string input) {
        Codec c;
        root = c.deserialize(input);
    }
    TreeNode* myDeserialize(istream& is) {
        while(!is.eof()) {
            string word;
            is >> word;
            if (word == "#") return nullptr;
            TreeNode* root = new TreeNode(stoi(word));
            root->left = myDeserialize(is);
            root->right = myDeserialize(is);
            return root;
        }
    }
};
int main() {
     string input = "1,2,4,#,#,#,3,#,7,#,#";
     BinaryTree bt;
     bt.generateTree(input);
     filebuf f;
     f.open("in.txt", ios::out);
     ostream os(&f);
     bt.serialize(os);
     f.close();
     f.open("in.txt", ios::in);
     istream in(&f);
     auto tree = bt.deserialize(in);
     Codec c;
     cout << c.serialize(tree.root) << endl;
};
