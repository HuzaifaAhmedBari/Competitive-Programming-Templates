struct BitTrieNode {
	BitTrieNode* next[2];
	BitTrieNode() {
		next[0] = next[1] = nullptr;
	}
};

struct BitTrie {
	BitTrieNode* root;
	static const int BITS = 31; // for int (use 63 for long long)

	BitTrie() {
		root = new BitTrieNode();
	}

	// Insert number into trie
	void insert(long long num) {
		BitTrieNode* node = root;
		for(int i = BITS; i >= 0; i--) {
			int b = (num >> i) & 1;
			if(!node->next[b]) node->next[b] = new BitTrieNode();
			node = node->next[b];
		}
	}

	// Query maximum number stored
	long long getMax() {
		BitTrieNode* node = root;
		long long ans = 0;
		for(int i = BITS; i >= 0; i--) {
			if(node->next[1]) {
				ans |= (1LL << i);
				node = node->next[1];
			} else if(node->next[0]) {
				node = node->next[0];
			}
		}
		return ans;
	}

	// Query minimum number stored
	long long getMin() {
		BitTrieNode* node = root;
		long long ans = 0;
		for(int i = BITS; i >= 0; i--) {
			if(node->next[0]) {
				node = node->next[0];
			} else if(node->next[1]) {
				ans |= (1LL << i);
				node = node->next[1];
			}
		}
		return ans;
	}

	// Query maximum XOR with num
	long long maxXor(long long num) {
		BitTrieNode* node = root;
		long long ans = 0;
		for(int i = BITS; i >= 0; i--) {
			int b = (num >> i) & 1;
			if(node->next[1 - b]) {
				ans |= (1LL << i);
				node = node->next[1 - b];
			} else {
				node = node->next[b];
			}
		}
		return ans;
	}

	// Query minimum XOR with num
	long long minXor(long long num) {
		BitTrieNode* node = root;
		long long ans = 0;
		for(int i = BITS; i >= 0; i--) {
			int b = (num >> i) & 1;
			if(node->next[b]) {
				node = node->next[b];
			} else {
				ans |= (1LL << i);
				node = node->next[1 - b];
			}
		}
		return ans;
	}

	// Query maximum OR with num (greedy pick 1 if exists)
	long long maxOr(long long num) {
		BitTrieNode* node = root;
		long long ans = num;
		for(int i = BITS; i >= 0; i--) {
			if(((num >> i) & 1) == 0 && node->next[1]) {
				ans |= (1LL << i);
				node = node->next[1];
			} else if(node->next[(num >> i) & 1]) {
				node = node->next[(num >> i) & 1];
			} else {
				break;
			}
		}
		return ans;
	}

    // Query minimum OR with num
    long long minOr(long long num) {
        BitTrieNode* node = root;
        long long ans = num;
        for(int i = BITS; i >= 0; i--) {
            int b = (num >> i) & 1;
            if(b == 1) {
                if(node->next[1]) node = node->next[1];
                else if(node->next[0]) node = node->next[0];
                else break;
            } else { // b == 0
                if(node->next[0]) {
                    node = node->next[0];
                } else if(node->next[1]) {
                    ans |= (1LL << i); // forced to take 1 here
                    node = node->next[1];
                } else break;
            }
        }
        return ans;
    }

	// Query maximum AND with num
	long long maxAnd(long long num) {
		BitTrieNode* node = root;
		long long ans = 0;
		for(int i = BITS; i >= 0; i--) {
			if(((num >> i) & 1) && node->next[1]) {
				ans |= (1LL << i);
				node = node->next[1];
			} else if(node->next[(num >> i) & 1]) {
				node = node->next[(num >> i) & 1];
			} else if(node->next[0]) {
				node = node->next[0];
			} else {
				break;
			}
		}
		return ans;
	}

    // Query minimum AND with num
    long long minAnd(long long num) {
        BitTrieNode* node = root;
        long long ans = 0;
        for(int i = BITS; i >= 0; i--) {
            int b = (num >> i) & 1;
            if(b == 1) {
                if(node->next[0]) {
                    node = node->next[0]; // force AND bit to 0
                } else if(node->next[1]) {
                    ans |= (1LL << i); // forced to keep this bit as 1
                    node = node->next[1];
                } else break;
            } else {
                if(node->next[0]) node = node->next[0];
                else if(node->next[1]) node = node->next[1];
                else break;
            }
        }
        return ans;
    }
};
