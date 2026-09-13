#pragma once

#include <assert.h>
#include <limits>
#include <memory>
#include <utility>

/**
 * @brief 符号なし整数の多重集合を管理する
 * @tparam `d` 扱う整数値のビット幅。Tの桁以下であることを要請
 */
template <unsigned int d, typename T = unsigned long long>
class BinaryTrie {
    static_assert(std::numeric_limits<T>::is_integer);
    static_assert(!std::numeric_limits<T>::is_signed);
    static_assert(d <= std::numeric_limits<T>::digits, "d must be T digits or less");
    struct BinaryTrieNode {
        std::shared_ptr<BinaryTrieNode> children[2] = {nullptr, nullptr};
        unsigned int level, subcnt = 0;
        T xval = 0;

        BinaryTrieNode(int lvl) : level(lvl) {}
        bool get_bit(T v) const { return ((v >> (level - 1)) & 1) > 0; }
        bool is_leaf() const { return level == 0; }
        // 子の状態がvalidかどうか
        // 0: xx, 1: xo, 2: ox, 3: oo
        int state_children() const {
            return ((bool)children[1] << 1) | (bool)children[0];
        }
        // xorの値を子ノードに伝播する
        void affect_xor() {
            if (get_bit(xval)) {
                std::swap(children[0], children[1]);
            }
            if (children[0])
                children[0]->xval ^= xval;
            if (children[1])
                children[1]->xval ^= xval;
            xval = 0;
        }
    };
    using NodePtr = std::shared_ptr<BinaryTrieNode>;
    NodePtr root_ptr = std::make_shared<BinaryTrieNode>(d);

  public:
    /**
     * @brief 集合にnを追加 (O(d))
     */  
    void insert(T n) {
        NodePtr cur_ptr = root_ptr;
        while (!cur_ptr->is_leaf()) {
            cur_ptr->affect_xor();
            cur_ptr->subcnt += 1;
            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->get_bit(n)];
            if (!nxt_ptr) {
                nxt_ptr = std::make_shared<BinaryTrieNode>(cur_ptr->level - 1);
            }
            cur_ptr = nxt_ptr;
        }
        assert(cur_ptr->is_leaf());
        cur_ptr->subcnt += 1;
    }

    int size() const { return root_ptr->subcnt; }

    /**
     * @brief 集合からnを検索し、見つかった数を求める (O(d))
     */
    int count(T n) const {
        NodePtr cur_ptr = root_ptr;
        while (!cur_ptr->is_leaf()) {
            cur_ptr->affect_xor();
            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->get_bit(n)];
            if (!nxt_ptr) {
                return 0;
            }
            cur_ptr = nxt_ptr;
        }
        return (cur_ptr ? cur_ptr->subcnt : 0);
    }

    /**
     * @brief 集合からnを削除 (O(d))
     * @note 存在しない要素を指定したとき、何も起こらない
     */
    void erase(T n) const {
        unsigned int cnt = count(n);
        if (cnt == 0)
            return;
        NodePtr cur_ptr = root_ptr;
        while (true) {
            cur_ptr->affect_xor();
            cur_ptr->subcnt -= cnt;
            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->get_bit(n)];
            if (nxt_ptr->subcnt == cnt) {
                nxt_ptr = nullptr;
                return;
            }
            cur_ptr = nxt_ptr;
        }
    }

    /**
     * @brief 集合からnを一つだけ削除 (O(d))
     * @note 存在しない要素を指定したとき、何も起こらない
     */
    void erase_one_element(T n) const {
        if (count(n) == 0)
            return;
        NodePtr cur_ptr = root_ptr;
        while (!cur_ptr->is_leaf()) {
            cur_ptr->affect_xor();
            cur_ptr->subcnt -= 1;
            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->get_bit(n)];
            if (nxt_ptr->subcnt == 1) {
                nxt_ptr = nullptr;
                return;
            }
            cur_ptr = nxt_ptr;
        }
        cur_ptr->subcnt -= 1;
    }

    /**
     * @brief 昇順でn番目の要素を探索 (O(d))
     * @note nがtrie木のサイズ以上な場合、assert
     */
    T nth_element(int n) const {
        assert(0 <= n && n < size());
        T ret = 0;
        NodePtr cur_ptr = root_ptr;
        while (!cur_ptr->is_leaf()) {
            cur_ptr->affect_xor();
            ret <<= 1;
            int state = cur_ptr->state_children();
            NodePtr &z_ptr = cur_ptr->children[0];
            NodePtr &o_ptr = cur_ptr->children[1];
            assert(state > 0);
            if (state == 1 || (state == 3 && n < (int)z_ptr->subcnt)) {
                cur_ptr = z_ptr;
            } else {
                n -= (state & 1 ? z_ptr->subcnt : 0);
                ret |= 1;
                cur_ptr = o_ptr;
            }
        }
        return ret;
    }

    /**
     * @brief n以上の要素を探索 (O(d))
     * @return 探索した値が昇順で何番目か (0-indexed)。該当する要素がなければtrie木のサイズが返る
     */
    int lower_bound(T n) const {
        int ret = 0;
        NodePtr cur_ptr = root_ptr;
        while (!cur_ptr->is_leaf()) {
            cur_ptr->affect_xor();
            bool b = cur_ptr->get_bit(n);
            NodePtr &nxt_ptr = cur_ptr->children[b];
            NodePtr &z_ptr = cur_ptr->children[0];
            if (b && z_ptr) {
                ret += z_ptr->subcnt;
            }
            if (!nxt_ptr) {
                break;
            }
            cur_ptr = nxt_ptr;
        }
        return ret;
    }

    /**
     * @brief nより大きな要素を探索 (O(d))
     * @return 探索した値が昇順で何番目か (0-indexed)。該当する要素がなければtrie木のサイズが返る
     */
    int upper_bound(T n) const {
        return (n < std::numeric_limits<T>::max() ? lower_bound(n + 1) : size());
    }

    /**
     * @brief 集合のすべての要素にxorを作用
     */
    void apply_xor(T n) { root_ptr->xval ^= n; }

    /**
     * @brief 要素をすべて削除する。確保したメモリ領域も削除される
     */
    void clear() {
        root_ptr = std::make_shared<BinaryTrieNode>(d);
    }
};
