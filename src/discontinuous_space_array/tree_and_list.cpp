#include <glog/logging.h>
#include <gtest/gtest.h>
#include <functional>

class Node {
   public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

auto construct_tree_from_vector = [](std::vector<int> nums) {
    std::function<void(Node*, int)> insert_to_tree = [&](Node* cur, int val) {
        if (val < cur->val) {
            if (cur->left) {
                insert_to_tree(cur->left, val);
                return;
            }
            cur->left = new Node(val);
        } else {
            if (cur->right) {
                insert_to_tree(cur->right, val);
                return;
            }
            cur->right = new Node(val);
        }
    };
    Node* root = new Node(nums[nums.size() / 2]);
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] == root->val) continue;
        insert_to_tree(root, nums[i]);
    }
    return root;
};

void PrintTree(Node* cur) {
    if (!cur) return;
    PrintTree(cur->left);
    std::cout << "\t" << cur->val << std::endl;
    PrintTree(cur->right);
}

// 剑指offer 36题
// --- 考察中序遍历　－－－
// 中序遍历，增加一个参数表示上一层循环的最后一个值
Node* TreeToLinkedList(Node* root) {
    auto head = root;
    while (head->left) head = head->left;
    std::function<Node*(Node*, Node*)> convert = [&](Node* cur, Node* last) {
        if (!cur) return cur;

        // 先遍历左子树，并返回last节点
        if (cur->left) {
            last = convert(cur->left, last);
        }
        //　处理当前节点，同时更新last节点
        if (last) last->right = cur;
        cur->left = last;
        last = cur;

        // 处理右子树，同时更新last节点
        if (cur->right) last = convert(cur->right, last);
        return last;
    };
    convert(root, nullptr);
    return head;
}

TEST(BinatryTree, JZ36) {
    // 1. construct a binary search tree
    std::vector<int> vec1{1, 2, 3, 4, 5};
    auto root1 = construct_tree_from_vector(vec1);
    PrintTree(root1);

    // 2. convert to linked list
    auto ans = TreeToLinkedList(root1);

    // 3. print result
    Node* tail = ans;
    while (tail) {
        std::cout << tail->val << std::endl;
        tail = tail->right;
    }
}

int main(int arc, char** argv) {
    testing::InitGoogleTest(&arc, argv);
    return RUN_ALL_TESTS();

    return 0;
}