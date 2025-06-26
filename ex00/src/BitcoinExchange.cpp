/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:38 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/06/26 21:48:48 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){	
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){
	dateList = other.dateList;
	valueList = other.valueList;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other){
	if(this != &other)
	{
		dateList = other.dateList;
		valueList = other.valueList;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(){
	if (input) {
		if (input->is_open())
			input->close();
		delete input;
		input = NULL;
	}
}

void BitcoinExchange::BitconExchange(char** av)
{
	checkOpenFile(av);
	saveDataOnList();
	addToList();
	
}

void BitcoinExchange::checkOpenFile(char** av)
{	
	input = new std::ifstream(av[1], std::ios::in | std::ios::binary);
	if (!input->is_open()) {
		std::cerr << "Error opening input file: " << av[1] << std::endl;
		delete input;
		input = NULL;
		exit(1);
	}
}

void BitcoinExchange::saveDataOnList(void){
    int			fieldIndex;
	int 		pairIndex;
	std::string	line;

	while (std::getline(*input, line)){
		std::stringstream ss(line);
		std::string item;
		fieldIndex = 0;
		while (std::getline(ss, item, '|')){
			pairIndex = fieldIndex / 2;

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
	input->close();
}

void BitcoinExchange::saveDataBOnList(void){
    int			fieldIndex;
	int 		pairIndex;
	std::string	line;

	input = new std::ifstream("data,csv", std::ios::in | std::ios::binary);
	if (!input->is_open()) {
		std::cerr << "Error opening input file: " << "data,csv" << std::endl;
		delete input;
		input = NULL;
		exit(1);
	}

	while (std::getline(*input, line)){
		std::stringstream ss(line);
		std::string item;
		fieldIndex = 0;
		while (std::getline(ss, item, ',')){
			pairIndex = fieldIndex / 2;

			if (fieldIndex % 2 == 0){
				if (pairIndex < 32)
					dataBList.push_back(item);
			}
			else{
				if (pairIndex < 32)
					rateList.push_back(item);
			}
			fieldIndex++;
		}
	}
	input->close();
}

void BitcoinExchange::addToList(void){
	std::list<std::string>::iterator it = valueList.begin();
	std::list<std::string>::iterator ite = valueList.end();  

	for (; it != ite ; it++)
		values.push_back(stringToFloat(*it));

	std::list<float>::iterator its = values.begin();
	std::list<float>::iterator ites = values.end();
	for (; its != ites ; its++)
		std::cout << *its << std::endl;    
}

float BitcoinExchange::stringToFloat(const std::string& s) {
    const char*	cstr = s.c_str();
    char* 		endptr = 0;
    double 		val = std::strtod(cstr, &endptr);

    if (endptr == cstr) {
        std::cerr << "Invalid float: " << s << std::endl;
        return (0.0f);
	}
        return (static_cast<float>(val));
}

bool isValidDate(const std::string& dateStr) {
    if (dateStr.length() != 10 || dateStr[4] != '-' || dateStr[7] != '-')
        return (false);

    int year, month, day;
    std::istringstream iss(dateStr);
    char dash1, dash2;

    if (!(iss >> year >> dash1 >> month >> dash2 >> day))
        return (false);

    if (month < 1 || month > 12 || day < 1 || day > 31)
        return (false);

    static const int daysInMonth[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (day > daysInMonth[month - 1])
        return (false);

    if (month == 2 && day == 29) {
        bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        return (isLeap);
    }
	
	return (true);
}