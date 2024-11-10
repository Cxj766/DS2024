// huffman_encoding.cpp
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <cctype>
using namespace std;

// 1. 二叉树节点结构
class BinTreeNode {
public:
    char data;              // 字符
    int weight;            // 权重（频率）
    BinTreeNode* left;     // 左子节点
    BinTreeNode* right;    // 右子节点

    BinTreeNode(char d = '\0', int w = 0)
        : data(d), weight(w), left(nullptr), right(nullptr) {}
};

// 2. 二叉树类
class BinTree {
protected:
    BinTreeNode* root;

public:
    BinTree() : root(nullptr) {}

    BinTreeNode* getRoot() { return root; }
    void setRoot(BinTreeNode* node) { root = node; }

    // 判断是否为叶子节点
    bool isLeaf(BinTreeNode* node) const {
        return (node != nullptr && node->left == nullptr && node->right == nullptr);
    }

    // 释放树的内存
    void clear(BinTreeNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    ~BinTree() {
        clear(root);
    }
};

// 3. 用于优先队列的比较器
struct CompareNodes {
    bool operator()(BinTreeNode* a, BinTreeNode* b) {
        return a->weight > b->weight;
    }
};

// 4. Huffman树类
class HuffTree : public BinTree {
private:
    map<char, string> huffmanCodes;  // 存储每个字符的Huffman编码

    // 递归生成Huffman编码
    void generateCodes(BinTreeNode* node, string code) {
        if (node) {
            if (isLeaf(node)) {
                huffmanCodes[node->data] = code;
            }
            generateCodes(node->left, code + "0");
            generateCodes(node->right, code + "1");
        }
    }

public:
    HuffTree() : BinTree() {}

    // 构建Huffman树
    void build(const map<char, int>& freq) {
        priority_queue<BinTreeNode*, vector<BinTreeNode*>, CompareNodes> pq;

        // 创建叶子节点并加入优先队列
        for (const auto& pair : freq) {
            pq.push(new BinTreeNode(pair.first, pair.second));
        }

        // 构建Huffman树
        while (pq.size() > 1) {
            BinTreeNode* left = pq.top(); pq.pop();
            BinTreeNode* right = pq.top(); pq.pop();

            BinTreeNode* parent = new BinTreeNode('\0', left->weight + right->weight);
            parent->left = left;
            parent->right = right;

            pq.push(parent);
        }

        root = pq.top();

        // 生成Huffman编码
        generateCodes(root, "");
    }

    // 获取字符的Huffman编码
    string getCode(char c) const {
        auto it = huffmanCodes.find(tolower(c));
        return (it != huffmanCodes.end()) ? it->second : "";
    }

    // 编码字符串
    string encode(const string& text) {
        string encoded;
        for (char c : text) {
            if (isalpha(c)) {
                encoded += getCode(c);
            }
        }
        return encoded;
    }

    // 打印所有字符的Huffman编码
    void printCodes() const {
        for (const auto& pair : huffmanCodes) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }
};

// 5. 位图类（用于存储二进制编码）
class Bitmap {
private:
    vector<bool> bits;

public:
    Bitmap() {}

    // 添加一个二进制位
    void append(bool bit) {
        bits.push_back(bit);
    }

    // 从字符串添加二进制位
    void appendBits(const string& bitStr) {
        for (char c : bitStr) {
            append(c == '1');
        }
    }

    // 获取位图的字符串表示
    string toString() const {
        string result;
        for (bool bit : bits) {
            result += (bit ? '1' : '0');
        }
        return result;
    }
};

// 6. Huffman编码串类
class HuffCode {
private:
    Bitmap code;

public:
    HuffCode() {}

    // 添加Huffman编码
    void append(const string& huffmanCode) {
        code.appendBits(huffmanCode);
    }

    // 获取编码的字符串表示
    string toString() const {
        return code.toString();
    }
};

// 主函数，用于测试
int main() {
    // 统计I have a dream演讲中26个字母的频率（简化版本）
    map<char, int> letterFreq = {
        {'a', 1000}, {'b', 200},  {'c', 300},  {'d', 400},  {'e', 1200},
        {'f', 250},  {'g', 300},  {'h', 600},  {'i', 800},  {'j', 100},
        {'k', 150},  {'l', 500},  {'m', 400},  {'n', 700},  {'o', 750},
        {'p', 200},  {'q', 50},   {'r', 600},  {'s', 500},  {'t', 900},
        {'u', 400},  {'v', 150},  {'w', 300},  {'x', 50},   {'y', 300},
        {'z', 100}
    };

    // 创建并构建Huffman树
    HuffTree huffTree;
    huffTree.build(letterFreq);

    // 打印所有字母的Huffman编码
    cout << "Huffman Codes for all letters:" << endl;
    huffTree.printCodes();
    cout << endl;

    // 测试一些单词的编码
    vector<string> testWords = { "dream", "freedom", "hope", "justice" };

    for (const string& word : testWords) {
        string encoded = huffTree.encode(word);
        cout << "Word: " << word << endl;
        cout << "Encoded: " << encoded << endl << endl;

        // 使用HuffCode类存储编码
        HuffCode huffCode;
        huffCode.append(encoded);
        cout << "HuffCode: " << huffCode.toString() << endl << endl;
    }

    return 0;
}


