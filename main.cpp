//
//  main.cpp
//  boggle solver
//
//  Created by Jose A. Mena on 10/27/17.
//  Copyright © 2017 Jose A. Mena. All rights reserved.
//

#include <iostream>
#include <set>
#include <vector>
#include <tuple>

using namespace std;

bool hasVisited(int i, int j, set<tuple<int,int>> &seen) {
    set<tuple<int,int>>::iterator it = seen.find(make_tuple(i, j));
    return it != seen.end();
}

void removeSeen(int i, int j, set<tuple<int,int>> &seen) {
    set<tuple<int,int>>::iterator it = seen.find(make_tuple(i, j));
    if (it == seen.end()) return;
    seen.erase(it);
}

void findAllPaths(vector<vector<char>> &board,
                  int i,
                  int j,
                  string &word,
                  set<tuple<int,int>> &seen,
                  set<string> &dict) {
    
    word += board[i][j];
    set<string>::iterator dictIt = dict.find(word);
    if (dictIt != dict.end()) {
        cout << "found: " << word << endl;
    }
    
    seen.insert(make_tuple(i,j));
    
    if (i + 1 < board.size() && !hasVisited(i + 1, j, seen)) {
        findAllPaths(board,
                     i + 1,
                     j,
                     word,
                     seen,
                     dict);
    }
    
    if (j + 1 < board[0].size() && !hasVisited(i, j + 1, seen)) {
        findAllPaths(board,
                     i,
                     j + 1,
                     word,
                     seen,
                     dict);
    }
    
    if (i - 1 >= 0 && !hasVisited(i - 1, j, seen)) {
        findAllPaths(board,
                     i - 1,
                     j,
                     word,
                     seen,
                     dict);
        
    }
    
    if (j - 1 >= 0 && !hasVisited(i, j - 1, seen)) {
        findAllPaths(board,
                     i,
                     j - 1,
                     word,
                     seen,
                     dict);
    }
    
    //if we got here, we have nowhere else to go
    //so remove last character from word and from seen
    removeSeen(i, j, seen);
    word.erase(word.length() - 1);
    
}

void findAllWords(vector<vector<char>> &board, set<string> &dict) {

    string word = "";
    set<tuple<int, int>> seen;
    
    for (int i = 0; i < board.size(); i++) {
        vector<char> &row = board[i];
        for (int j = 0; j < row.size(); j++) {
            findAllPaths(board, i, j, word, seen, dict);
        }
    }
    
}

int main(int argc, const char * argv[]) {
    vector<vector<char>> board = {
                                    {'a', 'd', 'g'},
                                    {'b', 'e', 'h'},
                                    {'c', 'f', 'i'}
    };
    
    set<string> words;
    words.insert("abc");
    words.insert("hello");
    words.insert("beh");
    words.insert("ghi");
    words.insert("gda");
    
    findAllWords(board, words);
    return 0;
}
