#ifndef trie_h
#define trie_h
using namespace std;
const int ALPHABET_SIZE = 26; 
// trie node 
struct Node 
{ 
    struct Node *children[ALPHABET_SIZE]; 
    bool isWord; 
}; 
  
class Trie{
	public:
		Trie();
		bool search(string query);
		void insert(string word);
		int insertFromFile();
		Node* getNode();
		int charToIndex(char c); 
		int indexToChar(int index);
		void printAllWordsInNode(Node* root, string prefix);
		void suggestCorrection(string query);
		void getCorrections();
	private:
		Node* root;
};

#endif