## P02 - Processing in Linear Time
### Joshua Beaty
### Description:
- Write a program that will read in a dictionary file from [dictionary.txt](dictionary.txt) and store it in a **linked list**.
- Define a `wordNode` to be a struct or a class to hold a `word`. Definitions might come later. Then the `json` library will be very handy!
- The linked list should hold `wordNodes`.
- Time how long it takes to load the data into your linked list (we will use that later as well).
- After your dictionary (linked list) is loaded, we are going to perform "autosuggestions" when a user types characters at the console.
- Suggestions will start after 1 character is typed, however only the top 10 suggestions will be printed along with the total number of matching words.
- Matching suggestions will ONLY be words that match the substring starting from position zero. For example: `cat` would match `cat`, `caterpillar`, and `cattle`. But NOT `wildcat`.
- As typing, the time it takes to find suggestions will be displayed in seconds.

#### Input:
- baz

#### Output:
- baz
- 
- 6 words found in 36.929000 seconds
- 
- bazaar bazaars bazon bazoo bazooka bazookas

### Files
|   #   | File                    | Description                                                 |
| :---: | ----------------------- | ----------------------------------------------------------- |
|   1   | [main.cpp](./main.cpp)  | Main driver of the program                                  |
|   2   | [wordList.hpp](./wordList.hpp)  | HPP holds the stuct for node and class for WordList |
|   3   | [dictionary](./dictionary.txt)  | Dictionary for word completion        |
|   4   | [output](./output.txt)  | Output file keeps track of all searches made        |

### Instructions
- download main.exe and dictionary.txt into the same folder
- run main.exe
- pressing a character will create a prefix
- it will print out the number of words and the first 10 results with that prefix(NOTE: this takes 30+ seconds on my machine.)