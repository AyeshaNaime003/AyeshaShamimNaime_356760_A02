/*
Assignment-2

Title: Infix to Postfix Expression conversion and its evaluation using stack.

Design and implement ADT for expression conversion from infix to postfix and its evaluation using stack. Please note, operands can be a two-digit number, whereas the operators hold a single character space.

This assignment has two phases as listed below.

Write a complete stack class using arrays and upload it to a public repo on GitHub. 
Later pull that work to include the infix to postfix conversion and evaluation and push back
You should keep the Github repository public and share the link with the assignment submission.
*/
#include<iostream>
#include<string>
#include <string.h>
#include<cmath>
#include "stack.cpp"
using namespace std;
// function to check if the entered expression is valid or not
bool isValidExp(string infixExp){
    stack validityStack;; 
    for(int i = 0; i <= infixExp.length(); i++){
        char currentChar = infixExp[i];
        if(currentChar == '(' || currentChar == '{' || currentChar == '['){ // push the opening bracket into the stack
            validityStack.push(currentChar);   
        }
        // if closing bracket appears:
        // see if the stack is empty or not-> if empty then invalid
        // see if the stack top is the corresponding brackett-> if not then invalid
        // see if the stack is empty at end -> if not then invalid
        else if(currentChar == ')' || currentChar == '}' || currentChar == ']'){
            // corresponding opening brackets
            if(currentChar == ')'){
                currentChar = '(';
            }else if(currentChar == '}'){
                currentChar = '{';
            }else if(currentChar == ']'){
                currentChar = '[';
            }
            if(!validityStack.isEmpty()){
                if(validityStack.top()[0] == currentChar){
                    validityStack.pop();
                }else{
                    cout << "[INVALID EXPRESSION]\n";
                    return false;
                }
            }else{
                cout << "[INVALID EXPRESSION]\n";
                return false;
            }
        }
    }
    // need to check in the last, incase some openeing brackets corresponding braket doesnt appear
    if(!validityStack.isEmpty()){
        cout << "[INVALID EXPRESSION]\n";
        return false;
    }else{
        cout << "[VALID EXPRESSION]\n";
        return true;
    }
}
string infixToPostfix(string infixExp){ // takes an infix exp and return the postfix for evaluation
    stack operatorsStack;
    string output = "";
    // traversing through the string
    for(int i = 0; i < infixExp.length(); i++){
        char currentChar = infixExp[i];
        if(int(currentChar) >= 48 && int(currentChar) <= 57){ // add operand to output
            output += currentChar;
        }else{ // if operator appears than put space an ddecide what to with the operator
            output += " ";
            if(currentChar == '('){
                operatorsStack.push(currentChar);
            }else if(currentChar == ')'){
                while(!operatorsStack.top().compare("(")==0){ // pop all until opening bracket appears, pop opening bracket as well
                    output += operatorsStack.top() + " ";
                    operatorsStack.pop();
                }
                operatorsStack.pop();
            }else if(currentChar == '+' || currentChar == '-'){
                // remove all the higher precendence operators unless opening bracket appears or stack becomes empty
                while(!operatorsStack.isEmpty() && !operatorsStack.top().compare("(")==0){ 
                    output += operatorsStack.top() + " ";
                    operatorsStack.pop();
                }
                 operatorsStack.push(currentChar);
            }
            else if(currentChar == '*' || currentChar == '/'){
                // remove all the higher precendence operators unless opening bracket appears or stack becomes empty
                while(!operatorsStack.isEmpty() && !operatorsStack.top().compare("(")==0 && 
                (operatorsStack.top().compare("*")==0 ||
                operatorsStack.top().compare("/")==0 || 
                operatorsStack.top().compare("^")==0)){
                    output += operatorsStack.top() + " ";
                    operatorsStack.pop();
                }
                operatorsStack.push(currentChar);
            }
            else if(currentChar == '^'){
                // remove all the higher precendence operators unless opening bracket appears or stack becomes empty
                while(!operatorsStack.isEmpty() && !operatorsStack.top().compare("(")==0 && operatorsStack.top().compare("^")==0){
                    output += operatorsStack.top() + " ";
                    operatorsStack.pop();
                }
                operatorsStack.push(currentChar);
            }
        }
    }
    while(!operatorsStack.isEmpty()){ // empty the stack
        output += " " + operatorsStack.top();
        operatorsStack.pop();
    }
    return output;    
}
string postfixEvaluation(string postfixExp){
    stack evaluationStack;
    string number = "";
    bool afterOperandSpace = false;
    // traverse through the postExp
    for(int i = 0; i < postfixExp.length(); i++){
        char currentChar = postfixExp[i];
        // while loop to when an operand appears to collect the entire number
       if(int(currentChar) >= 48 && int(currentChar) <= 57){
            afterOperandSpace = true;
            number += currentChar;
        }
        else if(currentChar == ' ' && afterOperandSpace && number!=" "){
            evaluationStack.push(number);
            number = "";
        }
        // operator appears
        else if(currentChar == '+' ||  currentChar == '-' ||  currentChar == '*' ||  currentChar == '/' ||  currentChar == '^'){
            afterOperandSpace = false;
            double leftOperand, rightOperand;
            rightOperand = stod(evaluationStack.top());
            evaluationStack.pop();
            leftOperand = stod(evaluationStack.top()); 
            evaluationStack.pop();
            if(currentChar =='+'){
                evaluationStack.push(to_string(leftOperand + rightOperand));
            }else if(currentChar == '-'){
                evaluationStack.push(to_string(leftOperand - rightOperand));
            }else if(currentChar == '*'){
                evaluationStack.push(to_string(leftOperand * rightOperand));
            }else if(currentChar == '/'){
                evaluationStack.push(to_string(leftOperand / rightOperand));
            }else{
                evaluationStack.push(to_string(pow(leftOperand, rightOperand)));
            }   
        }
    }
    return evaluationStack.top();
}
int main(){
    string infixExp;
    // get infix exp from user
    cout << "Enter a valid infix expression with no spaces: ";
    getline(cin, infixExp);
    if(isValidExp(infixExp)){
        string postfixExp = infixToPostfix(infixExp);
        cout << "PostFix Expresssion: " << postfixExp << endl;
        cout << "Result: " << postfixEvaluation(postfixExp); 
    }
}