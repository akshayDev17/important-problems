#include<bits/stdc++.h>
using namespace std;

class TrieNodeMap{
public:
	unordered_map<char, TrieNodeMap*> children;
	/* 
	use an array of size 26/52 if we know 
	in advance that the only 
	characters involved are the english alphabets
	*/
	bool endOfWord;
	TrieNodeMap(){
		children.clear();
		endOfWord = false;
	}
	void setEndOfWord(bool val){
		endOfWord = val;
	}
	void insert(string newWord){
		TrieNodeMap *curr = this;
		for(int i = 0;i<newWord.length();i++){
			if(curr->children.find(newWord[i]) == curr->children.end()){
				TrieNodeMap *temp = new TrieNodeMap();
				curr->children[newWord[i]] = temp;
			}
			curr = curr->children[newWord[i]];
		}
		curr->setEndOfWord(true);		
	}
	void printAll(){
		stack<pair<string, TrieNodeMap*> > st;
		pair<string, TrieNodeMap*> p("", this);
		st.push(p);
		while(!st.empty()){
			p = st.top();st.pop();
			TrieNodeMap *curr = p.second;
			string temp_str = p.first;
			if(curr->endOfWord){cout << temp_str << endl;}
			for(auto it: curr->children){
				p.first = temp_str + it.first;
				p.second = it.second;
				st.push(p);
			}
		}	
	}
	bool search(string word){
		TrieNodeMap *curr = this;
		cout << curr->children.size() << endl;
		for(int i = 0;i<word.length();i++){
			if(curr->children.find(word[i]) == curr->children.end())
				return false;
			else
				curr = curr->children[word[i]];
		}
		return curr->endOfWord;
	}
	void deleteWord(string word){
		if(this->search(word)){
			TrieNodeMap *curr = this;
			for(int i = 0;i<word.length();i++)
				curr = curr->children[word[i]];
			curr->setEndOfWord(false);
		}
		return;		
	}
	bool prefixSearch(string word){
		TrieNodeMap *curr = this;
		cout << curr->children.size() << endl;
		for(int i = 0;i<word.length();i++){
			if(curr->children.find(word[i]) == curr->children.end())
				return false;
			else
				curr = curr->children[word[i]];
		}
		return true;
	}
};

int main(int argc, char const *argv[])
{
	// collections of strings stored here
	// idle for storing a dictionary of words
	// prefix based search
	// can place strings in a lex-sorted manner in a trie

	// input total words to be entered in the trie
	int n;cout << "Enter total words\n" ;cin >> n;
	TrieNodeMap *root = new TrieNodeMap();
	for(int j = 0;j<n;j++){
		string query_str;cin >> query_str;
		root->insert(query_str);	
	}
	
	root->printAll();
	root->deleteWord("akshay");
	root->printAll();
	// cout << root->search("akshay") << endl;
	return 0;
}