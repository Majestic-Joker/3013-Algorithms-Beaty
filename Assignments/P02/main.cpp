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
    for (int i = 0; i < wordList.size; i++) { // loop through wordList
        bool found = false;

        //if the substring matches the corresponding characters of the prefix in wordList found = true
        if(wordList[i].substr(0, substring.size()).compare(substring) == 0)
            found = true;

        if (found) {
            matches.Push(wordList[i]);   // add to matches
        }
    }

    return matches;
}

int main() {
    char k;                             // holder for character being typed
    string word = "";                   // var to concatenate letters to
    WordList words;                     // wordList of words from dictionary
    WordList matches;                   // any matches found in words

    ofstream fout("temp.txt");          //output file
    ifstream fin("dictionary.txt");     //input file

    Timer T;   // create a timer
    T.Start(); // start it

    string w = "";
    while(fin >> w)
        words.Push(w);

    T.End(); // end the current timer

    // print out how long it took to load the dictionary file
    cout << T.Seconds() << " seconds to read in\n";
    cout << T.MilliSeconds() << " milliseconds to read in\n";
    cout << T.NanoSeconds() << " nanoseconds to read in\n";

    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {
        T.Start(); // start it
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

        // Find the prefix in the wordList that matches the substring
        matches = FindWords(words, word);

        if ((int)k != 32) { // if k is not a space print it
            T.End();
            cout << T.Seconds() << " seconds" << endl;
            cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            cout << "Words Found: ";
            cout << termcolor::red;
            if(word.size() > 0){
                // This prints out all found matches
                for (int a = 0; a < matches.size; a++) {
                    //substring characters turn red rest are green
                    for(int b = 0; b < matches[a].size(); b++){
                        if(b >= word.size())
                            cout << termcolor::green;
                        cout << matches[a][b];
                    }
                    cout << ' ' << termcolor::red;
                }
                cout << termcolor::reset << endl;
            }
        }
    }
    //Output spits out to temp.txt after the search is complete
    fout << T.Seconds() << " seconds" << endl;
    fout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
    fout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
    fout << "Words Found: ";
    fout << termcolor::red;
    if(word.size() > 0){
        // This prints out all found matches
        for (int a = 0; a < matches.size; a++) {
            //substring characters turn red rest are green
            for(int b = 0; b < matches[a].size(); b++){
                if(b >= word.size())
                    fout << termcolor::green;
                fout << matches[a][b];
            }
            fout << ' ' << termcolor::red;
        }
        cout << termcolor::reset << endl;
    }
}