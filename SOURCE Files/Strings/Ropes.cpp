#include <ext/rope>
using namespace __gnu_cxx;
using rp = rope<char>;

// Usage:
// 1. Insert:  s.insert(pos, "str");   // O(log N + |str|)
// 2. Erase:   s.erase(pos, len);      // O(log N)
// 3. Substr:  s.substr(pos, len);     // O(log N) -> returns new rope
// 4. Access:  s[i];                   // O(log N)
// 5. Concat:  s += t;                 // Amortized O(1), worst O(log N)
// 6. Persist: rp s2 = s1;             // O(1)

// int main() {
//	rp s;
//	s += "Hello";              // s = "Hello"
//	s.insert(5, " World");     // s = "Hello World"
//	rp s2 = s;                 // s2 is a persistent copy of s (O(1))
//	s.erase(0, 6);             // s = "World" (s2 is still "Hello World")
//	cout << s << " " << s2;    // Output: World Hello World
// }