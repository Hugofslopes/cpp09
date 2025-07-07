/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:38 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/07 22:56:51 by hfilipe-         ###   ########.fr       */
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

void RPN::parseInput(std::string Ndate){
	char*   end;
	int 	nb;
	nb = std::strtod(Ndate.c_str(), &end);
	if (nb > std::numeric_limits<int>::max() ||
    nb < std::numeric_limits<int>::min())
        std::cerr << "Error: too large a number." << std::endl, exit (1);
	else
		rpn.push(Ndate);
}

std::string intToString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

void RPN::print(){
	char*   end;
	int 	nb;

	if (rpn.empty())
		std::cerr << "Error: empty stack, nothing to print" << std::endl, exit (1);

	nb = std::strtod(rpn.top().c_str(), &end);
	std::cout << nb << std::endl;
}

void RPN::calculate(char op){
	char*   end;
	int n1, n2, n3;
	n1 = std::strtod(rpn.top().c_str(), &end);
	rpn.pop(); 
	n2 = std::strtod(rpn.top().c_str(), &end);
	switch (op) {
        case '+':
            n3 = n2 + n1;
			break;
        case '-':
            n3 = n2 - n1;
			break;
        case '*':
            n3 = n2 * n1;
			break;
        case '/':
			if (n1 == 0) 
				std::cerr << "Error: Division by zero" << std::endl, exit(1);
			n3 = n2 / n1;
			break;
	}
	rpn.push(intToString(n3));
}

void RPN::applyRPN(char* av) {
    std::stringstream ss(av);
    std::string token;

    while (ss >> token) { 
        if (token.find('(') != std::string::npos || 
            token.find(')') != std::string::npos || 
            token.find('.') != std::string::npos) {
            std::cerr << "Error" << std::endl, exit (1);
        }

        if (token == "+" || token == "-" || token == "*" || token == "/"){
			if (rpn.size() < 2)
				std::cerr << "Error: insufficient operands for operator '" 
				<< token << "'" << std::endl, exit(1);
            calculate(token[0]);
		}
        else
            parseInput(token);
    }
}