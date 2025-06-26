/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:19 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/06/26 16:10:58 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

float stringToFloat(const std::string& s) {
    const char* cstr = s.c_str();
    char* endptr = 0;
    double val = std::strtod(cstr, &endptr);

    if (endptr == cstr) {
        std::cerr << "Invalid float: " << s << std::endl;
        return (0.0f);
    }
        return (static_cast<float>(val));
    }

int main(int ac, char **av){
    if(ac != 2){
        return (std::cerr << "Invalid number of arguments" << std::endl, 1);
    }
        std::ifstream input(av[1], std::ios::in | std::ios::binary);
	if (!input){
        return(std::cerr << "Error opening input file: " << av[1] << std::endl,
        1);
    }
    
    std::list<std::string> dateList;
    std::list<std::string> valueList;
    int fieldIndex;
	std::string line;
	while (std::getline(input, line)){
		std::stringstream ss(line);
        std::string item;
        fieldIndex = 0;
        while (std::getline(ss, item, '|')){
            int pairIndex = fieldIndex / 2;

            if (fieldIndex % 2 == 0){
                if (pairIndex < 32)
                    dateList.push_back(item);
            }
            else{
                if (pairIndex < 32)
                    valueList.push_back(item);
            }
            fieldIndex++;
        }
    }
    input.close();
    std::list<std::string>::iterator it = dateList.begin();
	std::list<std::string>::iterator ite = dateList.end();
    for (; it != ite ; it++)
        std::cout << *it << std::endl;    
    it = valueList.begin();
	ite = valueList.end();

    std::list<float> values;
    
    std::list<float>::iterator its;
    its = values.begin();
    
    for (; it != ite ; it++, its++)
        values.push_back(stringToFloat(*it));
    

    std::list<float>::iterator ites;
    its = values.begin();
	ites = values.end();
    for (; its != ites ; its++)
        std::cout << *its << std::endl;    
    
}
