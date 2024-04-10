---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/binary-trie.hpp
    title: "\u7B26\u53F7\u306A\u3057\u6574\u6570\u306E\u591A\u91CD\u96C6\u5408\u3092\
      \u7BA1\u7406\u3059\u308B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A
  bundledCode: "#line 1 \"test/aoj-itp1-1-a.binary-trie.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A\"\n\n#include <algorithm>\n\
    #include <vector>\n#include <assert.h>\n#include <iostream>\n#include <random>\n\
    \n#line 2 \"cpp/binary-trie.hpp\"\n\n#line 4 \"cpp/binary-trie.hpp\"\n#include\
    \ <memory>\n#include <utility>\n\n/**\n * @brief \u7B26\u53F7\u306A\u3057\u6574\
    \u6570\u306E\u591A\u91CD\u96C6\u5408\u3092\u7BA1\u7406\u3059\u308B\n * @tparam\
    \ `d` \u6271\u3046\u6574\u6570\u5024\u306E\u30D3\u30C3\u30C8\u5E45\u300264\u4EE5\
    \u4E0B\u3067\u3042\u308B\u3053\u3068\u3092\u8981\u8ACB\n */\ntemplate <unsigned\
    \ int d> class BinaryTrie {\n    static_assert(d <= 64, \"d must be 64 or less\"\
    );\n    struct BinaryTrieNode {\n        std::shared_ptr<BinaryTrieNode> children[2]\
    \ = {nullptr, nullptr};\n        unsigned int level, subcnt = 0;\n        unsigned\
    \ long long xval = 0;\n\n        BinaryTrieNode(int lvl) : level(lvl) {}\n   \
    \     bool get_bit(unsigned long long v) const { return (v >> (level - 1)) & 1;\
    \ }\n        bool is_leaf() const { return level == 0; }\n        // \u5B50\u306E\
    \u72B6\u614B\u304Cvalid\u304B\u3069\u3046\u304B\n        // 0: xx, 1: xo, 2: ox,\
    \ 3: oo\n        int state_children() const {\n            return ((bool)children[1]\
    \ << 1) | (bool)children[0];\n        }\n        // xor\u306E\u5024\u3092\u5B50\
    \u30CE\u30FC\u30C9\u306B\u4F1D\u64AD\u3059\u308B\n        void affect_xor() {\n\
    \            if (get_bit(xval)) {\n                std::swap(children[0], children[1]);\n\
    \            }\n            if (children[0])\n                children[0]->xval\
    \ ^= xval;\n            if (children[1])\n                children[1]->xval ^=\
    \ xval;\n            xval = 0;\n        }\n    };\n    using NodePtr = std::shared_ptr<BinaryTrieNode>;\n\
    \    NodePtr root_ptr = std::make_shared<BinaryTrieNode>(d);\n\n  public:\n  \
    \  /**\n     * @brief \u96C6\u5408\u306Bn\u3092\u8FFD\u52A0 (O(d))\n     */  \n\
    \    void insert(unsigned long long n) {\n        NodePtr cur_ptr = root_ptr;\n\
    \        while (!cur_ptr->is_leaf()) {\n            cur_ptr->affect_xor();\n \
    \           cur_ptr->subcnt += 1;\n            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->get_bit(n)];\n\
    \            if (!nxt_ptr) {\n                nxt_ptr = std::make_shared<BinaryTrieNode>(cur_ptr->level\
    \ - 1);\n            }\n            cur_ptr = nxt_ptr;\n        }\n        assert(cur_ptr->is_leaf());\n\
    \        cur_ptr->subcnt += 1;\n    }\n\n    int size() const { return root_ptr->subcnt;\
    \ }\n\n    /**\n     * @brief \u96C6\u5408\u304B\u3089n\u3092\u691C\u7D22\u3057\
    \u3001\u898B\u3064\u304B\u3063\u305F\u6570\u3092\u6C42\u3081\u308B (O(d))\n  \
    \   */\n    int count(unsigned long long n) const {\n        NodePtr cur_ptr =\
    \ root_ptr;\n        while (!cur_ptr->is_leaf()) {\n            cur_ptr->affect_xor();\n\
    \            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->get_bit(n)];\n    \
    \        if (!nxt_ptr) {\n                return 0;\n            }\n         \
    \   cur_ptr = nxt_ptr;\n        }\n        return (cur_ptr ? cur_ptr->subcnt :\
    \ 0);\n    }\n\n    /**\n     * @brief \u96C6\u5408\u304B\u3089n\u3092\u524A\u9664\
    \ (O(d))\n     * @note \u5B58\u5728\u3057\u306A\u3044\u8981\u7D20\u3092\u6307\u5B9A\
    \u3057\u305F\u3068\u304D\u3001\u4F55\u3082\u8D77\u3053\u3089\u306A\u3044\n   \
    \  */\n    void erase(unsigned long long n) const {\n        unsigned int cnt\
    \ = count(n);\n        if (cnt == 0)\n            return;\n        NodePtr cur_ptr\
    \ = root_ptr;\n        while (true) {\n            cur_ptr->affect_xor();\n  \
    \          cur_ptr->subcnt -= cnt;\n            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->get_bit(n)];\n\
    \            if (nxt_ptr->subcnt == cnt) {\n                nxt_ptr = nullptr;\n\
    \                return;\n            }\n            cur_ptr = nxt_ptr;\n    \
    \    }\n    }\n\n    /**\n     * @brief \u96C6\u5408\u304B\u3089n\u3092\u4E00\u3064\
    \u3060\u3051\u524A\u9664 (O(d))\n     * @note \u5B58\u5728\u3057\u306A\u3044\u8981\
    \u7D20\u3092\u6307\u5B9A\u3057\u305F\u3068\u304D\u3001\u4F55\u3082\u8D77\u3053\
    \u3089\u306A\u3044\n     */\n    void erase_one_element(unsigned long long n)\
    \ const {\n        if (count(n) == 0)\n            return;\n        NodePtr cur_ptr\
    \ = root_ptr;\n        while (!cur_ptr->is_leaf()) {\n            cur_ptr->affect_xor();\n\
    \            cur_ptr->subcnt -= 1;\n            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->get_bit(n)];\n\
    \            if (nxt_ptr->subcnt == 1) {\n                nxt_ptr = nullptr;\n\
    \                return;\n            }\n            cur_ptr = nxt_ptr;\n    \
    \    }\n        cur_ptr->subcnt -= 1;\n    }\n\n    /**\n     * @brief \u6607\u9806\
    \u3067n\u756A\u76EE\u306E\u8981\u7D20\u3092\u63A2\u7D22 (O(d))\n     * @note n\u304C\
    trie\u6728\u306E\u30B5\u30A4\u30BA\u4EE5\u4E0A\u306A\u5834\u5408\u3001assert\n\
    \     */\n    unsigned long long nth_element(int n) const {\n        assert(0\
    \ <= n && n < size());\n        unsigned long long ret = 0;\n        NodePtr cur_ptr\
    \ = root_ptr;\n        while (!cur_ptr->is_leaf()) {\n            cur_ptr->affect_xor();\n\
    \            ret <<= 1;\n            int state = cur_ptr->state_children();\n\
    \            NodePtr &z_ptr = cur_ptr->children[0];\n            NodePtr &o_ptr\
    \ = cur_ptr->children[1];\n            assert(state > 0);\n            if (state\
    \ == 1 || (state == 3 && n < z_ptr->subcnt)) {\n                cur_ptr = z_ptr;\n\
    \            } else {\n                n -= (state & 1 ? z_ptr->subcnt : 0);\n\
    \                ret |= 1;\n                cur_ptr = o_ptr;\n            }\n\
    \        }\n        return ret;\n    }\n\n    /**\n     * @brief n\u4EE5\u4E0A\
    \u306E\u8981\u7D20\u3092\u63A2\u7D22 (O(d))\n     * @return \u63A2\u7D22\u3057\
    \u305F\u5024\u304C\u6607\u9806\u3067\u4F55\u756A\u76EE\u304B (0-indexed)\u3002\
    \u8A72\u5F53\u3059\u308B\u8981\u7D20\u304C\u306A\u3051\u308C\u3070trie\u6728\u306E\
    \u30B5\u30A4\u30BA\u304C\u8FD4\u308B\n     */\n    int lower_bound(unsigned long\
    \ long n) const {\n        int ret = 0;\n        NodePtr cur_ptr = root_ptr;\n\
    \        while (!cur_ptr->is_leaf()) {\n            cur_ptr->affect_xor();\n \
    \           bool b = cur_ptr->get_bit(n);\n            NodePtr &nxt_ptr = cur_ptr->children[b];\n\
    \            NodePtr &z_ptr = cur_ptr->children[0];\n            if (b && z_ptr)\
    \ {\n                ret += z_ptr->subcnt;\n            }\n            if (!nxt_ptr)\
    \ {\n                break;\n            }\n            cur_ptr = nxt_ptr;\n \
    \       }\n        return ret;\n    }\n\n    /**\n     * @brief n\u3088\u308A\u5927\
    \u304D\u306A\u8981\u7D20\u3092\u63A2\u7D22 (O(d))\n     * @return \u63A2\u7D22\
    \u3057\u305F\u5024\u304C\u6607\u9806\u3067\u4F55\u756A\u76EE\u304B (0-indexed)\u3002\
    \u8A72\u5F53\u3059\u308B\u8981\u7D20\u304C\u306A\u3051\u308C\u3070trie\u6728\u306E\
    \u30B5\u30A4\u30BA\u304C\u8FD4\u308B\n     */\n    int upper_bound(unsigned long\
    \ long n) const {\n        return (n < UINT64_MAX ? lower_bound(n + 1) : size());\n\
    \    }\n\n    /**\n     * @brief \u96C6\u5408\u306E\u3059\u3079\u3066\u306E\u8981\
    \u7D20\u306Bxor\u3092\u4F5C\u7528\n     */\n    void apply_xor(unsigned long long\
    \ n) { root_ptr->xval ^= n; }\n\n    /**\n     * @brief \u8981\u7D20\u3092\u3059\
    \u3079\u3066\u524A\u9664\u3059\u308B\u3002\u78BA\u4FDD\u3057\u305F\u30E1\u30E2\
    \u30EA\u9818\u57DF\u3082\u524A\u9664\u3055\u308C\u308B\n     */\n    void clear()\
    \ {\n        root_ptr = std::make_shared<BinaryTrieNode>(d);\n    }\n};\n#line\
    \ 10 \"test/aoj-itp1-1-a.binary-trie.test.cpp\"\n\nusing namespace std;\n\nint\
    \ main(void) {\n\n    std::random_device rd;\n    std::mt19937 gen(rd());\n  \
    \  std::uniform_int_distribution<unsigned long long> dist(0, UINT64_MAX);\n  \
    \  std::vector<unsigned long long> pool;\n    for (int i = 0; i < 24; ++i) {\n\
    \        pool.push_back(dist(gen));    \n    }\n    pool.push_back(UINT64_MAX);\n\
    \n    auto randgen_from_pool = [&]() {\n        return pool[dist(gen) % pool.size()];\n\
    \    };\n\n    std::vector<unsigned long long> A;\n    BinaryTrie<64> BT;\n  \
    \  for (int i = 0; i < 10000; ++i) {\n        unsigned long long x = randgen_from_pool();\n\
    \        A.push_back(x);\n        BT.insert(x);\n    }\n    for (int i = 0; i\
    \ < 10000; ++i) {\n        int q = dist(gen) % 8;\n        unsigned long long\
    \ x = randgen_from_pool();\n        switch (q) {\n        case 0:\n          \
    \  A.push_back(x);\n            BT.insert(x);   \n            break;\n       \
    \ case 1:\n            A.erase(std::remove_if(A.begin(), A.end(), [&](unsigned\
    \ long long a) { return a == x; }), A.end());\n            BT.erase(x);\n    \
    \        break;\n        case 2:\n            if (std::find(A.begin(), A.end(),\
    \ x) != A.end()) {\n                A.erase(std::find(A.begin(), A.end(), x));\
    \    \n            }\n            BT.erase_one_element(x);\n            break;\n\
    \        case 3:\n            for (auto& a : A) a ^= x;\n            BT.apply_xor(x);\n\
    \            break;\n        case 4:\n            std::sort(A.begin(), A.end());\n\
    \            assert(std::lower_bound(A.begin(), A.end(), x) - A.begin() == BT.lower_bound(x));\n\
    \            assert(std::upper_bound(A.begin(), A.end(), x) - A.begin() == BT.upper_bound(x));\n\
    \            break;\n        case 5:\n            if (x >= A.size()) break;\n\
    \            std::sort(A.begin(), A.end());\n            assert(A[x] == BT.nth_element(x));\n\
    \            break;\n        case 6:\n            assert((int)std::count(A.begin(),\
    \ A.end(), x) == BT.count(x));\n            break;\n        case 7:\n        \
    \    assert((int)A.size() == BT.size());\n        default:\n            break;\n\
    \        }\n    }\n    std::cout << \"Hello World\\n\";\n\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A\"\n\n\
    #include <algorithm>\n#include <vector>\n#include <assert.h>\n#include <iostream>\n\
    #include <random>\n\n#include \"../cpp/binary-trie.hpp\"\n\nusing namespace std;\n\
    \nint main(void) {\n\n    std::random_device rd;\n    std::mt19937 gen(rd());\n\
    \    std::uniform_int_distribution<unsigned long long> dist(0, UINT64_MAX);\n\
    \    std::vector<unsigned long long> pool;\n    for (int i = 0; i < 24; ++i) {\n\
    \        pool.push_back(dist(gen));    \n    }\n    pool.push_back(UINT64_MAX);\n\
    \n    auto randgen_from_pool = [&]() {\n        return pool[dist(gen) % pool.size()];\n\
    \    };\n\n    std::vector<unsigned long long> A;\n    BinaryTrie<64> BT;\n  \
    \  for (int i = 0; i < 10000; ++i) {\n        unsigned long long x = randgen_from_pool();\n\
    \        A.push_back(x);\n        BT.insert(x);\n    }\n    for (int i = 0; i\
    \ < 10000; ++i) {\n        int q = dist(gen) % 8;\n        unsigned long long\
    \ x = randgen_from_pool();\n        switch (q) {\n        case 0:\n          \
    \  A.push_back(x);\n            BT.insert(x);   \n            break;\n       \
    \ case 1:\n            A.erase(std::remove_if(A.begin(), A.end(), [&](unsigned\
    \ long long a) { return a == x; }), A.end());\n            BT.erase(x);\n    \
    \        break;\n        case 2:\n            if (std::find(A.begin(), A.end(),\
    \ x) != A.end()) {\n                A.erase(std::find(A.begin(), A.end(), x));\
    \    \n            }\n            BT.erase_one_element(x);\n            break;\n\
    \        case 3:\n            for (auto& a : A) a ^= x;\n            BT.apply_xor(x);\n\
    \            break;\n        case 4:\n            std::sort(A.begin(), A.end());\n\
    \            assert(std::lower_bound(A.begin(), A.end(), x) - A.begin() == BT.lower_bound(x));\n\
    \            assert(std::upper_bound(A.begin(), A.end(), x) - A.begin() == BT.upper_bound(x));\n\
    \            break;\n        case 5:\n            if (x >= A.size()) break;\n\
    \            std::sort(A.begin(), A.end());\n            assert(A[x] == BT.nth_element(x));\n\
    \            break;\n        case 6:\n            assert((int)std::count(A.begin(),\
    \ A.end(), x) == BT.count(x));\n            break;\n        case 7:\n        \
    \    assert((int)A.size() == BT.size());\n        default:\n            break;\n\
    \        }\n    }\n    std::cout << \"Hello World\\n\";\n\n}\n"
  dependsOn:
  - cpp/binary-trie.hpp
  isVerificationFile: true
  path: test/aoj-itp1-1-a.binary-trie.test.cpp
  requiredBy: []
  timestamp: '2024-04-10 15:58:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj-itp1-1-a.binary-trie.test.cpp
layout: document
redirect_from:
- /verify/test/aoj-itp1-1-a.binary-trie.test.cpp
- /verify/test/aoj-itp1-1-a.binary-trie.test.cpp.html
title: test/aoj-itp1-1-a.binary-trie.test.cpp
---
