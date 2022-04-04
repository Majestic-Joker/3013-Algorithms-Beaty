/*
Author:           Joshua Beaty
Email:            jabeaty0407@msutexas.edu
Label:            P02
Title:            wordList
Course:           3013
Semester:         Spring 2022

Description: This .hpp implements a node to hold a string, and a singly linkedList of wordNodes
*/

#include <iostream>
#include <string>

using namespace std;

struct Node{
    string data;
    Node* next;
    Node(){
        data = "";
        next = NULL;
    }
    Node(string s){
        data = s;
        next = NULL;
    }
};

class WordList {
private:
    Node *Head;
    Node *Tail;

public:
    int size;
    WordList() {
        Head = Tail = NULL;
        size = 0;
    }

    void Push(string word) {
        Node *Temp = new Node(word);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        size++;
    }

    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += Temp->data + "->";
            Temp = Temp->next;
        }

        return list;
    }

    int Pop() {
        size--;
        return 0; 
    }

    WordList operator+(const WordList &Rhs) {
        WordList NewList;
        Node *Temp = Head;

        while (Temp != NULL) {
            NewList.Push(Temp->data);
            Temp = Temp->next;
        }

        Temp = Rhs.Head;

        while (Temp != NULL) {
            NewList.Push(Temp->data);
            Temp = Temp->next;
        }

        return NewList;
    }

    string operator[](int index) {
        Node *Temp = Head;

        if (index >= size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->data;
        }
    }

    friend ostream &operator<<(ostream &os, WordList L) {
        os << L.Print();
        return os;
    }
};