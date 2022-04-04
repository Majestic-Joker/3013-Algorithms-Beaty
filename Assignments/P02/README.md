## P02 - Processing in Linear Time
### Joshua Beaty
### Description:
- Write a program that will read in a dictionary file from [dictionary.txt](dictionary.txt) and store it in a **linked list**.
- Define a `wordNode` to be a struct or a class to hold a `word`. Definitions might come later. Then the `json` library will be very handy!
- The linked list should hold `wordNodes`.
- Time how long it takes to load the data into your linked list (we will use that later as well).
- After your dictionary (linked list) is loaded, we are going to perform "autosuggestions" when a user types characters at the console.
- Suggestions will start after 1 character is typed, however only the top 10 suggestions will be printed along with the total number of matching words (example output below).
- Matching suggestions will ONLY be words that match the substring starting from position zero. For example: `cat` would match `cat`, `caterpillar`, and `cattle`. But NOT `wildcat`.
- As typing, the time it takes to find suggestions will be displayed in seconds.
- In addition I have included a file to help color text. Docs are here: https://termcolor.readthedocs.io/ but I included some examples in [main.cpp](main.cpp).

### Files

|   #   | File                    | Description                                        |
| :---: | ----------------------- | -------------------------------------------------- |
|   1   | [main.cpp](./main.cpp)  | Main driver of the program                         |
|   2   | [dictionary](./dictionary.txt)  | Dictionary for word completion        |

### Instructions

- click the links if desired