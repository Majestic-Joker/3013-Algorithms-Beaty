// Author:           Terry Griffin & Joshua Beaty
// Email:            terry.griffin@msutexas.edu & jabeaty0407@msutexas.edu
// Label:            P02
// Title:            P02 - Processing in Linear Time
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//       Implementing a linked list based auto complete

#include "mygetch.hpp"      // From Dr. Griffin
#include "termcolor.hpp"    // From Dr. Griffin
#include "timer.hpp"        // From Dr. Griffin
#include "wordList.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define RED termcolor::red

/**
 * Description:
 *      Finds the prefix matches in a wordList of strings and returns them.
 * Params:
 *      WordList wordList - WordList to search
 *      string substring   - substring to search for in each word
 * 
 * Returns:
 *      WordList - holding all the matches to substring
 */
WordList FindWords(WordList wordList, string substring) {
    WordList matches; // to hold any matches
    int count = 0;
    bool found = false;
    for (int i = 0; i < wordList.size; i++) { // loop through wordList
        if(found)
            found = false;

        //if the substring matches the corresponding characters of the prefix in wordList found = true
        if(wordList[i].substr(0, substring.size()).compare(substring) == 0)
            found = true;

        if (found && count < 10) {
            matches.Push(wordList[i]);   // add to matches
            count++;
        }
    }

    return matches;
}

/**
 * Description:
 *      Prints out the results of the wordList to the console and to the output file.
 * Params:
 *      WordList wordList - WordList of matches
 * 
 * Returns:
 *      NULL
 */
void PrintResult(WordList wordList, Timer t, char k, string sub, ofstream& fout){
    string output = "";
    //limit output to just 10 results
    int results = wordList.size;
    if(results > 10)
        results = 10;

    output += sub;
    output += "\n\n";
    output += to_string(wordList.size);
    output += " words found in ";
    output += to_string((double)((double)(t.MilliSeconds())/1000));
    output += " seconds\n\n";  
    cout << output;
    fout << output;
    cout << termcolor::red;

    // This prints out some matches
    for (int a = 0; a < results; a++) {
        //substring characters turn red rest are green
        for(int b = 0; b < wordList[a].size(); b++){
            if(b >= sub.size())
                cout << termcolor::green;
            cout << wordList[a][b];
            fout << wordList[a][b];
        }
        cout << ' ' << termcolor::red;
        fout << ' ';
    }

    cout << termcolor::reset << endl;
    fout << '\n' << endl;
}

int main() {
    char k;                             // holder for character being typed
    string word = "";                   // var to concatenate letters to
    WordList words;                     // wordList of words from dictionary
    WordList matches;                   // any matches found in words

    ofstream fout("output.txt");          //output file
    ifstream fin("dictionary.txt");     //input file
    
    Timer T;   // create a timer
    T.Start(); // start it

    string w = "";
    while(fin >> w)
        words.Push(w);

    T.End(); // end the current timer

    // print out how long it took to load the dictionary file
    cout << to_string((double)((double)T.MilliSeconds()/1000)) << " seconds to read in\n";
    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {
        system("clear");
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        // 8 is backspace on my machine.
        if ((int)k == 127 || (int)k == 8) {
            if (word.size() > 0) {
                word = word.substr(0, word.size() - 1);
            }
        } else {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) {
                cout << "Letters only!" << endl;
                continue;
            }
            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) {
                k += 32;
            }
            word += k; // append char to word
        }
        // only use resources if we have a substring to search and the most recent char wasn't a space
        if(word.size() > 0 && (int)k != 32){
            T.Start();
            // Find the prefix in the wordList that matches the substring
            matches = FindWords(words, word);
            T.End();
            PrintResult(matches, T, k, word, fout);
        }
    }
}