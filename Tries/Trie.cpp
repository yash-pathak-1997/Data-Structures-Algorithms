#include <bits/stdc++.h>

class Trie {

    public:

        Trie *children[26];
        bool isEnd;

        /** Initialize your data structure here. */
        Trie() {
            isEnd = false;
            for(int i=0;i<26;i++)
                children[i] = NULL;
        }

        /** Inserts a word into the trie. */
        void insert(string word) {
            Trie* ptr = this;
            for(int i=0;i<word.length();i++){
                int idx = word[i] - 'a';
                if(ptr->children[idx] == NULL)
                    ptr->children[idx] = new Trie();
                ptr = ptr->children[idx];
            }

            ptr->isEnd = true;
        }

        /** Returns if the word is in the trie. */
        bool search(string word) {
            Trie* ptr = this;
            for(int i=0;i<word.length();i++){
                int idx = word[i] - 'a';
                if(ptr->children[idx] == NULL)
                    return false;
                else
                    ptr = ptr->children[idx];
            }

            if(ptr->isEnd == true)
                return true;
            
            return false;
        }

        /** Returns if there is any word in the trie that starts with the given prefix. */
        bool startsWith(string word) {
            Trie* ptr = this;
            for(int i=0;i<word.length();i++){
                int idx = word[i] - 'a';
                if(ptr->children[idx] == NULL)
                    return false;
                else
                    ptr = ptr->children[idx];
            }

            return true;
        }

        /** Driver function to erase a word from Trie such that the structure of trie doesn't change*/
        void erase(string word) {
            if(search(word) == false)
                return;

            eraseHelperRecursive(this, word);
            eraseHelperIterative(this, word);
        }

        /** Erase function() - Recursive*/
        void eraseHelperRecursive(Trie* curr, string word){
            if(word.length() == 0){
                curr->isEnd = false;
                return;
            }

            int idx = word[0] - 'a';
            if(curr->children[idx] == NULL)  // Not required as we have already checked if the word exists.
                return;

            eraseHelperRecursive(curr->children[idx], word.substr(1));

            if(!hasChildren(curr) && curr != this)
                curr->children[idx] = NULL;
            
        }

        /** Erase function() - Iterative*/
        void eraseHelperIterative(Trie* curr, string word){
            stack <Trie*> nodes;
            for(int i=0;i<word.length();i++){
                int idx = word[i] - 'a';
                if(curr->children[idx] == NULL)  // Not required as we have already checked if the word exists.
                    return;

                nodes.push(curr);
                curr = curr->children[idx];
            }

            curr->isEnd = false;
            if(hasChildren(curr) == true)
                return;

            while(!nodes.empty()){
                Trie* parent = nodes.top();
                nodes.pop();

                int idx = word.back() - 'a';
                parent->children[idx] = NULL;
                word.pop_back();

                if(hasChildren(parent) || parent == this)
                    break;
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