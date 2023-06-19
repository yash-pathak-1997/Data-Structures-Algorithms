#include <bits/stdc++.h> 
class Trie{

    public:

        bool isEnd;
        int count;
        Trie* children[26];

        Trie(){
            // Write your code here.
            isEnd = false;
            count = 0;
            for(int i=0;i<26;i++)
                children[i] = NULL;
        }

        void insert(string &word){
            // Write your code here.
            Trie* ptr = this;
            for(int i=0;i<word.length();i++){
                int idx = word[i] - 'a';
                if(ptr->children[idx] == NULL)
                    ptr->children[idx] = new Trie();
                ptr->children[idx]->count++;
                ptr = ptr->children[idx];
            }
            ptr->isEnd = true;
        }

        int countWordsEqualTo(string &word){
            // Write your code here.
            Trie* ptr = this;
            int c = INT_MAX;
            for(int i=0;i<word.length();i++){
                int idx = word[i] - 'a';
                if(ptr->children[idx] == NULL)
                    return 0;
                
                if(c > ptr->children[idx]->count)
                    c = ptr->children[idx]->count;

                ptr = ptr->children[idx];
            }

            if(ptr->isEnd == true)
                return c;
            return 0;
        }

        int countWordsStartingWith(string &word){
            // Write your code here.
            Trie* ptr = this;
            int c = INT_MAX;
            for(int i=0;i<word.length();i++){
                int idx = word[i] - 'a';
                if(ptr->children[idx] == NULL)
                    return 0;
                
                if(c > ptr->children[idx]->count)
                    c = ptr->children[idx]->count;

                ptr = ptr->children[idx];
            }
            return c;
        }

        void erase(string &word){
            // Write your code here.
            if(countWordsEqualTo(word) == 0)
                return;
            erasehelper(this, word);
        }

        void erasehelper(Trie* curr, string word){
            if(word.length() == 0){
                curr->isEnd = false;
                return;
            }

            int idx = word[0] - 'a';
            erasehelper(curr->children[idx], word.substr(1));

            curr->children[idx]->count--;
            if(!hasChildren(curr) && curr != this){
                if(curr->children[idx]->count <= 0)
                    curr->children[idx] = NULL;
            }
        }

        bool hasChildren(Trie* curr){
            for(int i=0;i<26;i++){
                if(curr->children[i] != NULL)
                    return true;
            }

            return false;
        }
};