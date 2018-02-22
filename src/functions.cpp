#include <iostream>
#include <stack>
#include "functions.h"

int main(int argc, char* argv[]){

	std::string arb = "{abc} [1] something here ({[123]})";
	std::string wrong = "([)]";
	
	std::string infix = " 3 + 2 * 5 - 2 / 2"; // = 12
	std::string prefix;
	
	// Should be true
	std::cout << "The first string is:  " << balancedSymbols(arb) << std::endl;
	
	// Should be false
	std::cout << "The second string is: " << balancedSymbols(wrong) << std::endl;	

}


bool balancedSymbols(std::string input){
	
	std::stack<char, std::deque<char>> symbols;
	
	// Loop through each character in the string
	for(int i = 0; i < input.length(); i++){
		if(input[i] == '[' || input[i] == '{' || input[i] == '('){
			symbols.push(input[i]);		
			
			std::cout << symbols.top() << std::endl;
		}

		// Test ending expression
		if(input[i] == ']' || input[i] == '}' || input[i] == ')'){
			
			// If there was nothing before
			if(symbols.empty())
				return false;
			
			// Check for cases
			else if(symbols.top() == '[' && input[i] == ']')
				symbols.pop();
			else if(symbols.top() == '{' && input[i] == '}')
				symbols.pop();
			else if(symbols.top() == '(' && input[i] == ')')
				symbols.pop();
		}
	}
	
	// Returns true if there is nothing in stack
	return symbols.empty();
}

std::string iToP(std::string input){
	
	std::string postfix;

	return postfix;
}
