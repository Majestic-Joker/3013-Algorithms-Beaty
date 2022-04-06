## P03 - Processing in Trie Time
### Joshua Beaty
### Description:
- Write a program that will read in a dictionary file from [dict_w_defs.json](../../Resources/04-Data/dictionary_files/dict_w_defs.json) and store it in a **Trie Tree**.
- Trie's are implemented somewhat differently than our previous data structures. 
- Time how long it takes to load the data into your Trie tree.
- After your dictionary (Trie) is loaded, we are going to perform "autosuggestions" when a user types characters at the console.
- Suggestions will start after 1 character is typed, however only the top 10 suggestions will be printed along with the total number of matching words (example output below).
- The time it takes to find each suggestion will be displayed in milliseconds, otherwise we would only see 0.00000.
- I took the project a bit further and pull the definition of the word if it's a word.

#### Input:
- back

#### Output:
- back
- 
- 69 words found in 0.078100 milliseconds
- 
- back backs backsword backstop backstitch backstress backster backstay backstair backstairs
- 
- Definition: 1. A large shallow vat; a cistern, tub, or trough, used by brewers, distillers, dyers, picklers, gluemakers, and others, for mixing or cooling wort

### Files
|   #   | File                    | Description                                                 |
| :---: | ----------------------- | ----------------------------------------------------------- |
|   1   | [main.cpp](./main.cpp)  | Main driver of the program                                  |
|   2   | [trie.hpp](./trie.hpp)  | HPP holds the stuct for trie node and class for trie |
|   3   | [dict_w_defs](./dict_w_defs.json)  | json file that holds keys and definitions        |
|   4   | [output](./output.txt)  | Output file keeps track of all searches made        |

### Instructions
- download main.exe and dict_w_defs into the same folder
- run main.exe
- pressing a character will create a prefix
- it will print out the number of words and the first 10 results with that prefix
- if the prefix matches a word in the dictionary, it'll print out the definition as well.