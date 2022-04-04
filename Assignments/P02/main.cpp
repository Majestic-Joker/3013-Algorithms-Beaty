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
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define RED termcolor::red

/**
 * Description:
 *      Finds partial matches in an array of strings and returns them. It
 *      doesn't matter where in the string the match is.
 * Params:
 *      vector<string>  array       - array to search
 *      string          substring   - substring to search for in each word
 * 
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> FindWords(vector<string> array, string substring) {
    vector<string> matches; // to hold any matches
    for (int i = 0; i < array.size(); i++) { // loop through array
        bool found = false;

        if(array[i].substr(0, substring.size()).compare(substring) == 0)
            found = true;

        if (found) {
            matches.push_back(array[i]);   // add to matches
        }
    }

    return matches;
}

int main() {
    char k;                             // holder for character being typed
    string word = "";                   // var to concatenate letters to
    vector<string> words;               // array of words
    vector<string> matches;             // any matches found in vector of animals

    ofstream fout("temp.txt");          //output file
    ifstream fin("dictionary.txt");     //input file

    Timer T;   // create a timer
    T.Start(); // start it

    string w = "";
    while(fin >> w)
        words.push_back(w);

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

        // Find any animals in the array that partially match
        // our substr word
        matches = FindWords(words, word);

        if ((int)k != 32) { // if k is not a space print it
            T.End();
            cout << T.NanoSeconds() << " nano" << endl;
            cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            cout << "Words Found: ";
            cout << termcolor::red;
            if(word.size() > 0){
                // This prints out all found matches
                for (string match : matches) {
                    //substring characters turn red rest are green
                    for(int i = 0; i < match.size(); i++){
                        if(i >= word.size())
                            cout << termcolor::green;
                        cout << match[i];
                    }
                    cout << ' ' << termcolor::red;
                }
                cout << termcolor::reset << endl;
            }
        }
    }
}