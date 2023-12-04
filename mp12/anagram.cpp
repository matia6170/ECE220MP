#include "anagram.h"
#include <iostream>
#include <fstream>
#include <string>
/*
MP12
partners: hyunwoo6, crjung2, awinick2
*/

/***
An AnagramDict constructor. This Constructor takes in a filepath
and then creates a binary tree out of all the words inside the
binary tree.

Input:
std::string filename - the path to the file

Output:
N/A
***/
using namespace std;

AnagramDict::AnagramDict(std::string filename) {
    filename_ = filename;
    std::string path = "dictionaries/" + filename_;
    std::ifstream file;
    file.open(path.c_str());
    /**
        Your code goes below here
    **/
    string word;
    while (file >> word) {
        addWord(word);
    }
    file.close();

}

/***
An AnagramDict member function. This function sorts the given word in
lexicographical order

Input:
std::string word - the word that needs to be sorted

Output:
std::string - the sorted version of the input
***/
std::string AnagramDict::sortWord(std::string word) {
    /**
        Your code goes below here
    **/
    sort(word.begin(), word.end());
    return word;
}

/***
An AnagramDict member function. This function adds a word to the tree.
If the words sorted version already exists in the tree add it to the linked
list of that node. If the sorted word does not exist in the tree create a new
node and insert it into the tree
Duplicated words should not be added to the tree.
Input:
std::string word - the word that needs to inserted

Output:
N/A
***/
void AnagramDict::addWord(std::string word) {
    /**
        Your code goes below here
    **/
    string sortedWord = sortWord(word);
    list<string> wordlist;
    Node<string, list<string> > *node = tree.find_node(sortedWord);

    if (node == NULL) {
        wordlist.push_back(word);
        Node<string, list<string> > *newNode = new Node<string, list<string> >(sortedWord, wordlist);
        tree.insert_node(tree.getRoot(), newNode);
    } else {
        
        wordlist = node->getData();

        list<string>::iterator it = wordlist.begin();
        while (it != wordlist.end()) {
            if (*it == word) {
                return;
            }
            it++;
        }
        
        wordlist.push_back(word);
        node->setData(wordlist);
    }

}

/***
An AnagramDict member function. Does a preorder, postorder, or inorder traversal
and then prints out all the anagrams and words.

The output file should be the traversal order of the tree, but only the data on each line.
View on wiki for more information.

Input:
std::string order - The type of order you want to traverse. Can be "pre", "post", "in"

Output:
N/A
***/
void AnagramDict::saveAnagrams(std::string order) {
    std::string path = "output/" + order + "_" + filename_;
    std::ofstream file;
    file.open(path.c_str());
    if (!file.is_open()) {
        //create new file
        file.open(path.c_str(), std::ios::out);
    }
    /**
        Your code goes below here
    **/

    list<Node<string, list<string> > > words;

    if (order == "pre") {
        tree.pre_order(tree.getRoot(), words);
    } else if (order == "post") {
        tree.post_order(tree.getRoot(), words);
    } else if (order == "in") {
        tree.in_order(tree.getRoot(), words);
    }
    list<Node<string, list<string> > >::iterator it = words.begin();
    while(it != words.end()) {
        list<string> wordlist = it->getData();

        list<string>::iterator it2 = wordlist.begin();
        while (it2 != wordlist.end()) {
            file << *it2 << " ";
            it2++;
        }
        file << endl;
        it++;
    }
    file.close();



}