struct BitTrieNode {
	BitTrieNode* next[2];
	int cnt;
	BitTrieNode() {
		next[0] = next[1] = nullptr;
		cnt = 0;
	}
};

struct BitTrie {
	BitTrieNode* root;
	static const int BITS = 31; // for int (use 63 for long long)

	BitTrie() {
		root = new BitTrieNode();
	}

	// Insert number
	void insert(long long num) {
		BitTrieNode* node = root;
		node->cnt++;
		for(int i = BITS; i >= 0; i--) {
			int b = (num >> i) & 1;
			if(!node->next[b])
				node->next[b] = new BitTrieNode();
			node = node->next[b];
			node->cnt++;
		}
	}

	// Remove numbers
	void remove(long long num) {
		BitTrieNode* node = root;
		node->cnt--;

		for(int i = BITS; i >= 0; i--) {
			int b = (num >> i) & 1;
			BitTrieNode* nxt = node->next[b];

			nxt->cnt--;
			if(nxt->cnt == 0) {
				delete nxt;
				node->next[b] = nullptr;
				return;
			}
			node = nxt;
		}
	}

	// Maximum XOR
	long long maxXor(long long num) {
		BitTrieNode* node = root;
		long long ans = 0;
		for(int i = BITS; i >= 0; i--) {
			int b = (num >> i) & 1;
			if(node->next[1 - b] && node->next[1 - b]->cnt > 0) {
				ans |= (1LL << i);
				node = node->next[1 - b];
			} else {
				node = node->next[b];
			}
		}
		return ans;
	}

	// Minimum XOR
	long long minXor(long long num) {
		BitTrieNode* node = root;
		long long ans = 0;
		for(int i = BITS; i >= 0; i--) {
			int b = (num >> i) & 1;
			if(node->next[b] && node->next[b]->cnt > 0) {
				node = node->next[b];
			} else {
				ans |= (1LL << i);
				node = node->next[1 - b];
			}
		}
		return ans;
	}

	// Check if trie is empty
	bool empty() {
		return root->cnt == 0;
	}
};