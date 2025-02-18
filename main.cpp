#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct intNode {
    int data;
    intNode* next;
    intNode(int value) : data(value), next(nullptr) {};
};

class Stos {
private:
    intNode* top;
public:

    Stos() : top(nullptr) {}

    const bool isEmpty() {
        return top == nullptr;
    }

    void add() {
        if (!isEmpty())
            top->data++;
    }

    void push(int value) {
        intNode* newNode = new intNode(value);
        if (isEmpty()) {
            top = newNode;
        }   
        else {
            newNode->next = top;
            top = newNode;
        }
    }

    void pop() {
        if (!isEmpty()) {
            intNode* temp = top;
            top = top->next;
            delete temp;
        }
        else {
            std::cout << "Nie mozesz wykonac pop() na pustym stosie." << std::endl;
        }       
    }

    int peek() {
        if (!isEmpty()) {
            return top->data;
        }
        else {
            std::cout << "Nie mozesz wykonac peek() na pustym stosie." << std::endl;
            return -1; 
        }
    }

    void display() {
        if (isEmpty()) {
            std::cout << "Stos jest pusty." << std::endl;
            return;
        }

        intNode* current = top;
        while (current != nullptr) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n"); 
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        } 
    }

    ~Stos() {
        while (!isEmpty()) {
            pop();
        }
    }
};

bool isNumber(const char* input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if ((input[i] < '0' || input[i] > '9')) {
            //printf("is NOT a number\n");
            return false;
        }            
    }
    //printf("is a number\n");
    return true;
}

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isOperator(const char ch) {
    switch(ch) {
    case '+':
    case '-':
    case '*':
    case '/':
    case 'N':
    case 'I':
    case 'M':
    case 'X':
        return true;
    default:
        return false;
    }
}

int priority(char ch) {
    switch (ch) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case 'N':
        return 3;
    case 'I':
    case 'M':
    case 'X':
        return 4;
    default:
        return 0;
    }
}

void conversion(char* infix, char* postfix) {
    Stos stos;
    Stos counter;
    int i = 0;
    int j = 0;
    while (infix[i] != '\0') {
        char c = infix[i];

        if (c == ' ') { // if there's a space in the formula, go to the next character
            i++;
            continue;        
        }

        else if (isOperator(c)) {
            if (!stos.isEmpty() && c == 'N' && stos.peek() == 'N') { // if there's negation after negation, add to stack and move on
                stos.push(c);
                i++;
                continue;            
            }
            if (c == 'M') { // in case of MIN and MAX it checks the next letter and stores it on the stack as MIN = M, MAX = X
                i++;
                c = infix[i];
                if (c == 'I')  
                    c = 'M';
                else if (c == 'A')
                    c = 'X';
                i++;
            }
            while (!stos.isEmpty() && priority(c) <= priority(stos.peek()) && j != 0) { // j != 0 because there should be no operation at the very beginning, before the numbers
                postfix[j++] = stos.peek();
                postfix[j++] = ' ';
                stos.pop();
            }
            stos.push(c);
        }

        else if (isDigit(c)) { // if a number, write it on the board
            while (isDigit(c)) {
                postfix[j++] = c;
                i++;
                c = infix[i];
            }
            postfix[j++] = ' ';
            if (!stos.isEmpty() && stos.peek() == 'N') { // if a number and the operation is N, we can immediately apply the negation
                postfix[j++] = 'N';
                postfix[j++] = ' ';
                stos.pop(); 
            }
        }

        else if (c == '(') {
            counter.push(0);
            stos.push(c);
        }   

        else if (c == ')') { 
            while (stos.peek() != '(') { // if there's a closing bracket, pop everything off the stack until you get rid of the bracket
                postfix[j++] = stos.peek();
                postfix[j++] = ' ';
                stos.pop();
            }

            stos.pop();
            if (!stos.isEmpty()) {
                if (stos.peek() == 'N') { // if there was N before the bracket, the bracket is negated
                    postfix[j++] = 'N';
                    postfix[j++] = ' ';
                    stos.pop();
                }

                else if (stos.peek() == 'I') { // if there was IF before the bracket, the IF function follows
                    postfix[j++] = 'I';
                    postfix[j++] = 'F';
                    postfix[j++] = ' ';
                    stos.pop();
                }

                else if (stos.peek() == 'X') {
                    postfix[j++] = 'M';
                    postfix[j++] = 'A';
                    postfix[j++] = 'X';
                    sprintf(postfix + j, "%d", counter.peek() + 1);
                    j += strlen(postfix + j);
                    postfix[j++] = ' ';
                    stos.pop();
                }

                else if (stos.peek() == 'M') {
                    postfix[j++] = 'M';
                    postfix[j++] = 'I';
                    postfix[j++] = 'N';
                    sprintf(postfix + j, "%d", counter.peek() + 1);
                    j += strlen(postfix + j);
                    postfix[j++] = ' ';
                    stos.pop();
                }

                if (!counter.isEmpty())
                    counter.pop();
            }
        }

        else if (c == ','){
            while (!stos.isEmpty() && isOperator(stos.peek())) { // is used to write out operations before the comma
                postfix[j++] = stos.peek();
                postfix[j++] = ' ';
                stos.pop();
            }   
            counter.add();
        }
        i++;
    }

    while (!stos.isEmpty()) { // prints all characters left on the stack after traversing the entire formula
        postfix[j++] = stos.peek();
        postfix[j++] = ' ';
        stos.pop();
    }
    postfix[j] = '\0';
}

int operacja(const char* input, Stos* liczby) {

    if (isOperator(*input)) {
        int wynik = -1;
        if (strcmp(input, "+") == 0) {
            printf("+ ");
            liczby->display();
            int second = liczby->peek();
            liczby->pop();
            wynik = liczby->peek() + second;
            liczby->pop();
        }

        else if (strcmp(input, "-") == 0) {
            printf("- ");
            liczby->display();
            int second = liczby->peek();
            liczby->pop();
            wynik = liczby->peek() - second;
            liczby->pop();
        }

        else if (strcmp(input, "*") == 0) {
            printf("* ");
            liczby->display();
            int second = liczby->peek();
            liczby->pop();
            wynik = liczby->peek() * second;
            liczby->pop();
        }

        else if (strcmp(input, "/") == 0) {
            printf("/ ");
            liczby->display();
            int second = liczby->peek();
            liczby->pop();
            if (second == 0) {
                printf("ERROR\n");
                liczby->pop();
                return 1;
            }
            else {
                wynik = liczby->peek() / second;
                liczby->pop();
            }
        }

        else if (strcmp(input, "IF") == 0) {
            printf("IF ");
            liczby->display();
            int c = liczby->peek();
            liczby->pop();
            int b = liczby->peek();
            liczby->pop();
            int a = liczby->peek();
            liczby->pop();
            if (a > 0)
                wynik = b;
            else
                wynik = c;
        }

        else if (strcmp(input, "N") == 0) {
            printf("N ");
            liczby->display();
            wynik = -liczby->peek();
            liczby->pop();
        }

        else if (strncmp(input, "MIN", 3) == 0) { // MIN()
            int amount = atoi(input + 3);
            printf("MIN%d ", amount);
            liczby->display();
            int min = -1;
            for (int i = 0; i < amount; i++) {
                if (i == 0 || liczby->peek() < min)
                    min = liczby->peek();
                liczby->pop();
            }
            wynik = min;
        }

        else if (strncmp(input, "MAX", 3) == 0) { // MAX()
            int amount = atoi(input + 3);
            printf("MAX%d ", amount);
            liczby->display();
            int max = -1;
            for (int i = 0; i < amount; i++) {
                if (i == 0 || liczby->peek() > max)
                    max = liczby->peek();
                liczby->pop();
            }
            wynik = max;
        }
        liczby->push(wynik);
    }
    return 0;
}

void printChars(char* text) {
    int i = 0;
    while (text[i] != '\0') {
        putchar(text[i]);
        i++;
    }
    printf("\n");
}

int main() {
    Stos liczby;
    Stos operacje;
    const int MAX_ELEMENTS = 100;
    
    int iloscOperacji;
    cin >> iloscOperacji;
    cin.ignore();

    for (int wykonanie = 1; wykonanie <= iloscOperacji; wykonanie++) {
        int error = 0;
        char input[10000];
        fgets(input, sizeof(input), stdin);

        char postfix[10000];
        conversion(input, postfix);
        printChars(postfix);
        int count = 0;
        char* token = strtok(postfix, " ");
        while (token != NULL && count < MAX_ELEMENTS && !error) {
            if (isNumber(token))
                liczby.push(atoi(token));
            else
                error = operacja(token, &liczby);
            token = strtok(NULL, " ");
        }

        if (error) {
            liczby.clear();
            operacje.clear();       
        }
        else {
            printf("%d\n\n", liczby.peek());
            liczby.pop();
        }  
    }
    return 0;
}