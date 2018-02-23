#include <iostream>
#include <stack>
#include "functions.h"

bool highPriority(char top, char compare);

int getWeight(char opo);

int main(int argc, char* argv[]){

	std::string arb = "{abc} [1] something here ({[123]})";
	std::string wrong = "([)]";
	
	std::string infix = "a + b * c + ( d * e + f) * g";
	std::string prefix;
	
	// Should be true
	std::cout << "The first string is:  " << balancedSymbols(arb) << std::endl;
	
	// Should be false
	std::cout << "The second string is: " << balancedSymbols(wrong) << std::endl;	

	std::cout << iToP(infix) << std::endl; 
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

	std::stack<char, std::deque<char>> postStack;	
	std::string postfix;
	
	for(int i = 0; i < input.length(); i++){
		
		// Skip current iteration if input has a space
		if(input[i] == ' ')
			continue;

		// See if char is an operator
		if(input[i] == '*' || input[i] == '/' || input[i] == '+' || input[i] == '-'){
			
			// Only push if no parentheses
			while(!postStack.empty() && postStack.top() != '(' && highPriority(postStack.top(), input[i])){
				postfix += postStack.top();
				postStack.pop();
			}

			// Insert operator
			postStack.push(input[i]);			
		}
		
		// Push if starting of parentheses
		else if(input[i] == '(')
			postStack.push(input[i]);
		
		// Push if ending of parentheses
		else if(input[i] == ')'){
			
			// Add operators to postfix
			while(!postStack.empty() && postStack.top() != '('){
				postfix += postStack.top();
				postStack.pop();
			}

			// Pop remaining parentheses
			postStack.pop();
		}
		
		// Add any remaining characters or integers to postfix if not an operator	  				
		else
			postfix += input[i];
			
	}

	// Add remaining operators
	while(!postStack.empty()){
		postfix += postStack.top();
		postStack.pop();
	}

	return postfix;
}


bool highPriority(char top, char compare){
	
	int topWeight = getWeight(top);
	int compareWeight = getWeight(compare);
	
	// Compare weight to see if the operators need to be added to postfix string
	if(topWeight == compareWeight)
		return true;
	else if (topWeight > compareWeight)
		return true;
	else
		return false; 	
}

int getWeight(char opo){
	
	int weight = 0;
	
	// Go through each operator to see which one takes order of operations
	switch(opo){
		case '+':
		case '-':
			weight = 1;
			break;
		case '*':
		case '/':
			weight = 2;
			break;
	}
	
	return weight;
}










