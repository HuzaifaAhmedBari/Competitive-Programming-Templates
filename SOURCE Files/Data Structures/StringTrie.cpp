struct TrieNode {
    TrieNode* next[26];
    bool isEnd;
    int count;

    TrieNode() {
        for (int i = 0; i < 26; i++) next[i] = nullptr;
        isEnd = false;
        count = 0;
    }
};

struct Trie {
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    // Insert word
    void insert(const string &word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->next[idx]) node->next[idx] = new TrieNode();
            node = node->next[idx];
            node->count++;
        }
        node->isEnd = true;
    }

    // Search full word
    bool search(const string &word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->next[idx]) return false;
            node = node->next[idx];
        }
        return node->isEnd;
    }

    // Check if prefix exists
    bool startsWith(const string &prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->next[idx]) return false;
            node = node->next[idx];
        }
        return true;
    }

    // Count words with given prefix
    int countPrefix(const string &prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->next[idx]) return 0;
            node = node->next[idx];
        }
        return node->count;
    }
};