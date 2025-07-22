/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:58:24 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/22 18:58:55 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_CPP
# define RPN_CPP

# include <iostream>
# include <sstream>
# include <fstream>
# include <stack>
# include <cstdlib>
# include <limits>

class RPN{
	public:
		RPN();
		~RPN();
		
		void applyRPN(const std::string& input);
		void print();
	
	private:
		RPN(const RPN &);
		RPN& operator=(const RPN &);

		void parseInput(std::string);
		void calculate(std::string);
		std::stack<int> rpn;
} ;

# endif