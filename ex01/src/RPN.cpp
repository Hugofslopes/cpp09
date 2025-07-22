/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:38 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/22 19:09:08 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(){}

RPN::~RPN(){}

RPN::RPN(const RPN &other){
	rpn = other.rpn;
}

RPN& RPN::operator=(const RPN &other){
	if (this != &other)
	rpn = other.rpn;
	return (*this);
}

int stringToInt(const std::string& s) {
    std::istringstream iss(s);
    int value;
	
    iss >> value;
    return value;
}

void RPN::parseInput(std::string token){
	int 	nb = stringToInt(token);
	
	if (nb > std::numeric_limits<int>::max() ||
    nb < std::numeric_limits<int>::min())
        std::cerr << "Error: too large a number." << std::endl, exit (1);
	else
		rpn.push(nb);
}

void RPN::print(){
	if (rpn.empty())
		std::cerr << "Error: empty stack, nothing to print" << std::endl, exit (1);

	std::cout << rpn.top()<< std::endl;
}

void RPN::calculate(std::string token){
	int a,b,res;

	if (rpn.size() < 2) {
		std::cerr << "Error: insufficient operands for operator '"
		<< token << "'" << std::endl, exit(1);
	}
	b = rpn.top(); 
	rpn.pop();
	a = rpn.top(); 
	rpn.pop();
	if (token == "+") 
		res = a + b;
	else if (token == "-") 
		res = a - b;
	else if (token == "*") 
		res = a * b;
	else if (token == "/") {
		if (b == 0) {
			std::cerr << "Error: Division by zero" << std::endl, exit(1);
		}
		res = a / b;
	}
	rpn.push(res);
}

void RPN::applyRPN(const std::string& input) {
    std::stringstream ss(input);
    std::string token;

    while (ss >> token) {
        if (token.find('(') != std::string::npos || token.find(')') != std::string::npos || \
		token.find('.') != std::string::npos || token.length() > 1 || (!isdigit(token[0]) && \
		token != "+" && token != "-" && token != "*" && token != "/"))
            std::cerr << "Error: Invalid token '" << token << "'" << std::endl, exit(1);
		if (token == "+" || token == "-" || token == "*" || token == "/")
			calculate(token);
		else
			parseInput(token);
    }
}