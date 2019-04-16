#include <iostream>
#include <fstream>
#include "spellCheck.h"
using namespace std;

//Default constructor
Trie::Trie(){
	root = nullptr;
}
//Creates a new Node
Node* Trie::getNode(){
	Node* newNode = new Node;
	for(int i = 0 ; i<ALPHABET_SIZE; i++){
		newNode->children[i] = nullptr;
	}
	newNode->isWord = false;
	return newNode;
}
//Gets index character needs to be placed at in a trie
int Trie::charToIndex(char c){
	return c -'a';
}
//Gives character at that corresponding index
int Trie::indexToChar(int index){
	return 97+index;
}
//Insert function
void Trie::insert(string word){
	if(root == nullptr){
		root = getNode();
	}
	Node* current = root;
	for(int i = 0; i<word.length(); i++){
		//Index of where in the children array the references should be set 
		int index = charToIndex(word[i]);
		if(current->children[index]==nullptr){
			current->children[index] = getNode();
		}
		current = current->children[index];
	}
	//Marking isWord
	current->isWord = true;
}
//Insert from file
int Trie::insertFromFile(){
	string in;
	int wordsInserted = 0;
	ifstream myfile("words.txt");
	if (myfile.is_open()){
	 	while (myfile>>in){
      		insert(in);
      		wordsInserted++;
    	}
   		myfile.close();
   		return wordsInserted;	
	 }
	 else{
	 	return -1;
	 }
}
//Search function
bool Trie::search(string query){
	if(root==nullptr){
		return false;
	}
	Node* current = root;
	for(int i = 0; i<query.length(); i++){
		int index = charToIndex(query[i]);
		if(!current->children[index]){
			return false;
		}
		current = current->children[index];
	}
	return current!=nullptr && current->isWord;
		
}
//Gets all words recursively in a given node
void Trie::printAllWordsInNode(Node* root, string prefix){
	if(root->isWord){
		cout<<prefix<<endl;
	}
  for (int i = 0; i < ALPHABET_SIZE; i++) {
  	string temp;
  	temp+=prefix;
    if (root->children[i] != nullptr) {
    	temp+=indexToChar(i);
        printAllWordsInNode(root->children[i], temp);
    }
  }
  return;
}
//Suggests possible completions given a prefix
void Trie::suggestCorrection(string prefix){
	Node* current = root;
	for(int i = 0; i<prefix.length(); i++){
		int index = charToIndex(prefix[i]);
		if(!current->children[index]){
			cout<<'\n'<<"No suggestions found"<<endl;
			return;
		}
		current = current->children[index];
	}
	cout<<'\n'<<"Did you mean:"<<endl;
	printAllWordsInNode(current, prefix);
}

//Function to get corrections given user input
void Trie::getCorrections(){
	string input;
	if(insertFromFile()==-1){
		cout<<"There was an error reading the dictonary file"<<endl;
	}

	cout<<'\n'<<"Enter a word "<<endl;
	cin>>input;
	cout<<'\n'<<"You entered: "<<input<<endl;
	suggestCorrection(input);
}
//Test function
int main(){
	Trie x;
	x.getCorrections();

}

