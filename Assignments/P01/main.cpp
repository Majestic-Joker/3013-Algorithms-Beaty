///////////////////////////////////////////////////////////////////////////////
//
// Author:           Terry Griffin & Joshua Beaty
// Email:            terry.griffin@msutexas.edu & jabeaty0407@msutexas.edu
// Label:            P01
// Title:            P01 - Resizing the Array Based Stack
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//       Resizing an array based stack
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack {
private:
    int *A;   // pointer to array of int's
    int size; // current max stack size
    int top;  // top of stack

    // top = number of items in the stack + 1
    // size = array size

    // size = 100
    // (top + 1) / size

public:
    double upperLimit = .85;
    double lowerLimit = .15;
    double growStat = 2.0;
    double shrinkStat = .5;
    int maxSize;
    int resizeCount;

    /**
    * ArrayStack
    * 
    * Description:
    *      Constructor no params
    * 
    * Params:
    *     - None
    * 
    * Returns:
    *     - NULL
    */
    ArrayStack() {
        size = 10;
        A = new int[size];
        top = -1;
        maxSize = size;
        resizeCount = 0;
    }

    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(int s) {
        size = s;
        A = new int[s];
        top = -1;
        maxSize = size;
        resizeCount = 0;
    }

    int GetSize(){
        return size;
    }

    /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
    bool Empty() {
        return (top <= -1);
    }

    /**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
    bool Full() {
        return (top >= size - 1);
    }

    /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Peek() {
        if (!Empty()) {
            return A[top];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Pop() {
        int returnMe = 0;
        if (Empty()) {
            if(top > 10)
                ContainerShrink();
        }
        if (!Empty()) {
            returnMe =  A[top--];
            if(top>10)          //should maintain a minimum size of 10
                if(top < (size*lowerLimit))
                    ContainerShrink();
        }
        return returnMe;
    }

    /**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void Print() {
        for (int i = 0; i <= top; i++) {
            cout << A[i] << " ";
        }
        cout << endl;
    }

    /**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      [bool] ; success = true
  */
    bool Push(int x) {
        if (Full()) {
            ContainerGrow();
        }
        if (!Full()) {
            A[++top] = x;
            if(top > (size*upperLimit))
                ContainerGrow();
            return true;
        }

        return false;
    }

  /**
  * Public void: ContainerGrow
  * 
  * Description:
  *      Resizes the container for the stack by the growth stat
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void ContainerGrow() {
        resizeCount++;
        int newSize = size * growStat;
        if(newSize > maxSize)
            maxSize = newSize;
        int* B; 

        B = new int[newSize];           // allocate new memory
        for (int i = 0; i <= top; i++) { // copy values to new array
            B[i] = A[i];
        }
        delete[] A;                     // delete old array
        size = newSize;                 // save new size

        A = B;                          // reset array pointer
    }

  /**
  * Public void: ContainerShrink
  * 
  * Description:
  *      Resizes the container for the stack by cutting its capacity by the shrink stat.
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void ContainerShrink() {
        resizeCount++;
        int newSize = size * shrinkStat;         // resizes array
        int* B = new int[newSize];           // allocate new memory
        for (int i = 0; i <= top; i++) { // copy values to new array
            B[i] = A[i];
        }
        delete[] A;                     // delete old array
        size = newSize;                 // save new size
        A = B;                          // reset array pointer
    }
};

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char** argv) {
    ArrayStack stack;

    if(argc == 5){
        stack.upperLimit = strtod(argv[1],nullptr);
        stack.lowerLimit = strtod(argv[2],nullptr);
        stack.growStat = strtod(argv[3],nullptr);
        stack.shrinkStat = strtod(argv[4],nullptr);
    }

    srand(time(NULL));
    int r = 0;
    int count = 0;
    ifstream fin;

    fin.open("nums_test.dat");

    while(fin >> r){
        if((r%2) < 1)  //Even
            stack.Push(r);
        else        //Not even
            stack.Pop();
        count++;
    }

    /*
    for (int i = 0; i < 20; i++) {
        r = rand() % 100;
        if(!(r%2))  //Even
            if (!stack.Push(r)) {
                cout << "Push failed" << endl;
            }
        else        //Not even
            if(!stack.Pop())
                cout << "Pop failed" << endl;
        count++;
    }
    */
    /*
    for (int i = 0; i < 20; i++) {
        r = 2*(i+1);
        if((r%2) < 1)  //Even
            stack.Push(r);
        else        //Not even
            stack.Pop();
        count++;
    }
    */

    //stack.Print();

    cout << "\n######################################################################\n";
    cout << "\tAssignment 4 - Resizing the Stack\n";
    cout << "\tCMPS 3013\n";
    cout << "\tJoshua Beaty\n\n";
    cout << "\tConfig Params:\n";
    cout << "\t\tFull Threshold: " << stack.upperLimit << "\n";
    cout << "\t\tShrink Threshold: " << stack.lowerLimit << "\n";
    cout << "\t\tGrow Ratio: " << stack.growStat << "\n";
    cout << "\t\tShrink Ratio: " << stack.shrinkStat << "\n\n";
    cout << "\tProcessed " << count << " commands.\n\n";
    cout << "\tMax Stack Size: " <<  stack.maxSize << "\n";
    cout << "\tEnd Stack Size: " << stack.GetSize() << "\n";
    cout << "\tStack Resized: " << stack.resizeCount << " times\n";
    cout << "######################################################################\n";
}