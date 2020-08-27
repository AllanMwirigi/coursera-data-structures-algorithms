#include <iostream>
#include <stack>
#include <string>

/**
 * In this problem you will implement a feature for a text editor to find errors in the usage of brackets 
 * in the code.
 * Input Format. Input contains one string 𝑆 which consists of big and small latin letters, digits, 
 *                  punctuation marks and brackets from the set []{}().
 * Constraints. The length of 𝑆 is at least 1 and at most 10pow(5)
 * Output Format. If the code in 𝑆 uses brackets correctly, output “Success" (without the quotes). Otherwise,
 *  output the 1-based index of the first unmatched closing bracket, and if there are no unmatched closing
 *  brackets, output the 1-based index of the first unmatched opening bracket.
 * 
*/

struct Bracket {
    // constructor
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

    int unmatchedPos = -1;
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // push any opening brackets to stack
            opening_brackets_stack.push(Bracket(next, position));
        }

        if (next == ')' || next == ']' || next == '}') {
            if (opening_brackets_stack.empty()){
                // if stack is empty, first bracket in string is a closing brace
                unmatchedPos = position;
                break;
            }
            // if a closing bracket found, evaluate if equal to bracket at top of stack
            Bracket top = opening_brackets_stack.top();
            bool equal = top.Matchc(next);
            if (equal) {
                opening_brackets_stack.pop(); // remove the bracket at top of stack, since it has been matched
            } else {
                unmatchedPos = position; // position of unmatched closing bracket
                break;
            }
        }
    }

    if (unmatchedPos != -1) {
        std::cout << unmatchedPos + 1; // use 1-based indexing
    } 
    else if (!opening_brackets_stack.empty()) {
        // there was no unmatched closing bracket but stack is not empty, meaning there is an unmatched opening brace
        std::cout << opening_brackets_stack.top().position + 1; // print the first unmatched opening brace
    }
    else {
        std::cout << "Success";
    }

    return 0;
}
