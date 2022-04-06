// Author:           Terry Griffin & Joshua Beaty
// Email:            terry.griffin@msutexas.edu & jabeaty0407@msutexas.edu
// Label:            P03
// Title:            P03 - Processing in Trie Time
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//       Implementing a trie based autocomplete

#include "mygetch.hpp"      // From Dr. Griffin
#include "termcolor.hpp"    // From Dr. Griffin
#include "timer.hpp"        // From Dr. Griffin
#include "JsonFacade.hpp"   // From Dr. Griffin
#include "trie.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool debug = false;

#define RED termcolor::red

/**
 * Description:
 *      Prints out the results of the wordList to the console and to the output file.
 * Params:
 *      WordList wordList - WordList of matches
 * 
 * Returns:
 *      NULL
 */
void PrintResult(vector<string> matches, Timer t, char k, string sub, ofstream& fout){
    string output = "";
    //limit output to just 10 results
    int results = matches.size();
    if(results > 10)
        results = 10;

    output += sub;
    output += "\n\n";
    output += to_string(matches.size());
    output += " words found in ";
    output += to_string((double)((double)(t.NanoSeconds())/1000000));
    output += " milliseconds\n\n";  
    cout << output;
    fout << output;
    cout << termcolor::red;

    // This prints out some matches
    for (int a = 0; a < results; a++) {
        //substring characters turn red rest are green
        for(int b = 0; b < matches[a].size(); b++){
            if(b >= sub.size())
                cout << termcolor::green;
            cout << matches[a][b];
            fout << matches[a][b];
        }
        cout << ' ' << termcolor::red;
        fout << ' ';
    }

    cout << termcolor::reset << endl;
    fout << '\n' << endl;
}

int main() {
    char k;                                 // holder for character being typed
    string word = "";                       // var to concatenate letters to
    Trie words;                             // wordList of words from dictionary
    vector<string> matches;                 // any matches found in words

    ofstream fout("output.txt");            //output file
    ifstream fin("dictionary.txt");         //input file
    JsonFacade jsonF("dict_w_defs.json");   //input json

    Timer T;   // create a timer
    T.Start(); // start it

    /*
    string w = "";
    while(fin >> w)
        words.insert(w);
    */
    for(string s : jsonF.getKeys())
        words.insert(s);

    T.End(); // end the current timer

    // print out how long it took to load the dictionary file
    cout << to_string((double)((double)T.MilliSeconds()/1000)) << " seconds to read in " << words.size() << " words\n";
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
            matches = words.find_all(word);
            T.End();
            PrintResult(matches, T, k, word, fout);

            if(word.compare(matches[0]) == 0)
                cout << "\nDefinition: " << jsonF.getValue(word).substr(0, 150) << '\n';
        }
        else
            cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

    }
}