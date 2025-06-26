/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:58:24 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/06/26 21:38:11 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BITCOINEXCHANGE_CPP
# define BITCOINEXCHANGE_CPP

# include <iostream>
# include <fstream>
# include <list>
# include <sstream>
# include <string>
# include <stdlib.h>

class BitcoinExchange{
	public:
		BitcoinExchange();
		void BitconExchange(char** av);
		~BitcoinExchange();
	
	private:
		
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange& operator=(const BitcoinExchange &other);
		

		void	checkOpenFile(char**av);
		void	saveDataOnList(void);
		void	saveDataBOnList(void);
		void	addToList(void);
		float 	stringToFloat(const std::string& s);
		
		std::list<std::string>	dateList;
		std::list<std::string>	valueList;
		std::ifstream			*input;
		std::list<float>		values;
	
};

# endif