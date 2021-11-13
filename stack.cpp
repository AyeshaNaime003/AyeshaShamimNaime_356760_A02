#include<iostream>
using namespace std;
class stack{
    const int SIZE = 20; // The stack size will remian constant, if more is added then STACK OVERFLOW message will occur
    string array[20];
    int topIndex = -1;
    public:
        bool isFull(){
            return topIndex == SIZE - 1;}
        bool isEmpty(){
            return topIndex == -1;}
        // overloaded function: can push string or char into the stack
        void push(string pushingChar){
            array[++topIndex] = pushingChar;
        }
        void push(char pushingChar){
            array[++topIndex] = pushingChar;
        }
        void pop(){
            topIndex--;
        }
        string top(){
            return array[topIndex];
        }
};