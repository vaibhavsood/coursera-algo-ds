#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket opening_bracket(next, position+1);
            opening_brackets_stack.push(opening_bracket);
        }

        if (next == ')' || next == ']' || next == '}') {
            if (opening_brackets_stack.empty() == true) {
              std::cout << position+1;
              return 0;
            }
            // Process closing bracket, write your code here
            Bracket opening_bracket = opening_brackets_stack.top();
            if (opening_bracket.Matchc(next) == false) {
              std::cout << position+1;
              return 0;
            }
            opening_brackets_stack.pop();
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.empty() == true) {
       std::cout << "Success";
    } else {
       Bracket opening_bracket = opening_brackets_stack.top();
       std::cout << opening_bracket.position;
    }

    return 0;
}
