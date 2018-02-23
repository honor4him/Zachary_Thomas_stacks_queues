#include <iostream>
#include <stack>
#include "functions.h"
/********************************************************************
 * This is an assignment for CIS 263, Data Structures and Algorithms.
 * The first primary function determines ending braces, parentheses, 
 * and brackets. The second primary function takes an infix string
 * and converts it to postfix. Both of these functions use stacks
 * as their primary data structure.
 *
 * @author Zachary Thomas
 * @version 1.0
 *******************************************************************/

/******************************************************************
 * Helper function for iToP to determine the order of operations.
 * @param top char variable
 * @param compare char variable
 * @return boolean If top is higher or lower.
 *****************************************************************/
bool highPriority(char top, char compare);

/******************************************************************
 * Helper function for highPriority that assigns a weight of an
 * integer for an operator.
 * @param opo An operator in char format to assign value to.
 * @return int The value of the weight
 *****************************************************************/
int getWeight(char opo);

/******************************************************************
 * This function, balancedSymbols, takes in a string that may or
 * may not have parentheses. It checks to see if there is always
 * a corresponding ending to a respective symbol.
 * @param input A string that has the symbols in it.
 * @return bool Returns true if there is a closing symbol(s).
 *****************************************************************/
bool balancedSymbols(std::string input){
	
	/** Holds the stack of symbols */
	std::stack<char, std::deque<char>> symbols;
	
	// Loop through each character in the string
	for(int i = 0; i < input.length(); i++){
		if(input[i] == '[' || input[i] == '{' || input[i] == '('){
			symbols.push(input[i]);		
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

/******************************************************************
 * This function, iToP, takes an infix expression and converts it
 * using a stack. This takes the order of operations and puts the
 * string into postfix. This function also works with parentheses.
 * Help from https://www.youtube.com/watch?v=vq-nUF0G4fI
 * @param input A string that is to convert to postfix.
 * @return string Returns postfix expression.
 *****************************************************************/
std::string iToP(std::string input){

	/** Holds the operators to add to postfix */
	std::stack<char, std::deque<char>> postStack;
	
	/** Holds the postfix expression */
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

	// Returns finished postfix string
	return postfix;
}

/******************************************************************
 * Helper function for iToP to determine the order of operations.
 * @param top char variable
 * @param compare char variable
 * @return boolean If top is higher or lower.
 *****************************************************************/
bool highPriority(char top, char compare){
	
	/** Holds the weight of top*/
	int topWeight = getWeight(top);
	
	/** Holds the weight of compare*/
	int compareWeight = getWeight(compare);
	
	// Compare weight to see if the operators need to be added to postfix string
	// According to the order of operations
	if(topWeight == compareWeight)
		return true;
	else if (topWeight > compareWeight)
		return true;
	else
		return false; 	
}

/******************************************************************
 * Helper function for highPriority that assigns a weight of an
 * integer for an operator.
 * @param opo An operator in char format to assign value to.
 * @return int The value of the weight
 *****************************************************************/
int getWeight(char opo){
	
	/** Holds the weight of opo*/
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
	
	// Returns the end weight
	return weight;
}










