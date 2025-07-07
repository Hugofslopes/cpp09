/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:38 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/07 16:44:21 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){
    btc = other.btc;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other){
    if(this != &other)
    {
        btc = other.btc;
    }
    return *this;
}

int BitcoinExchange::dateToInt(int year, int month, int day)const{
    return year * 10000 + month * 100 + day;
}

void BitcoinExchange::intToDate(int dateInt, int& year, int& month, int& day)const{
    year = dateInt / 10000;
    month = (dateInt / 100) % 100;
    day = dateInt % 100;
}

std::string BitcoinExchange::saveDate(std::string date)const{
    std::stringstream   ss(date);
    std::string         str;
    int                 fieldIndex = 0;
    int                 year = 0, month = 0, day = 0, nbdate = 0;

    while (std::getline(ss, str, '-')) {
        if (fieldIndex == 0)
            year = std::atoi(str.c_str());
        else if (fieldIndex == 1)
            month = std::atoi(str.c_str());
        else if (fieldIndex == 2)
            day = std::atoi(str.c_str());
        else
            return ("Invalid date format");
        fieldIndex++;
    }
    if (fieldIndex != 3) 
        return("Invalid date format");
    nbdate = dateToInt(year, month, day);
    std::ostringstream oss;
    oss << date;
    return oss.str();
}

float BitcoinExchange::saveNumber(std::string number)const{
    float nb;
    char* end;
    nb = static_cast<float>(std::strtod(number.c_str(), &end));
    return (nb);
}

void BitcoinExchange::printMaps(const std::string str) const{
    
    if (str == "btc")
        for (std::multimap<std::string, float>::const_iterator it = btc.begin(); it != btc.end(); ++it)
            std::cout << "date-" << it->first << ",\t" << "value-" << it->second << std::endl;
    else
        for (std::multimap<std::string, float>::const_iterator it = csv.begin(); it != csv.end(); ++it)
            std::cout << "date-" << it->first << ",\t" << "value-" << it->second << std::endl;
}

void BitcoinExchange::setBtc(std::string date, float number, char type)
{
    type == '|'? btc.insert(std::make_pair(date, number)) : csv.insert(std::make_pair(date, number));
}

void BitcoinExchange::parse(const char *av, char delimiter){
    std::ifstream input(av);
    if (!input)
        return (std::cerr << "Error opening input file: " << av << std::endl, exit (1));

    std::string line;
    std::string date;
    float       number;
    
    while (std::getline(input, line)) {
        std::stringstream ss(line);
        std::string date, numberStr;

        if (!std::getline(ss, date, delimiter) || !std::getline(ss, numberStr, delimiter)){
            setBtc("Error: bad input => " + line, -1, delimiter);
            continue;
        }
        number = saveNumber(numberStr);
        date = saveDate(date);
        setBtc(date, number, delimiter);
    }
}

float BitcoinExchange::transform(std::multimap<std::string, float>::iterator itBtc) {
    std::multimap<std::string, float>::iterator itCsv = csv.begin();
    float value = 0 ;
    for (; itBtc != btc.end() ; itBtc++){
        for (; itCsv != csv.end() ; itCsv++){
            if (itBtc->first == itCsv->first)
                break ;
        }
        if (itCsv != csv.end())
            if (itBtc->second < 2147483648 && itBtc->second >= -2147483648)
                value = itBtc->second * itCsv->second;
    }
    return (value);
}

void BitcoinExchange::print() {
    std::multimap<std::string, float>::iterator itBtc = btc.begin();
    for (; itBtc != btc.end() ; itBtc++){
        if (itBtc->second > 2147483648 || itBtc->second < -2147483648)
            std::cerr << "Error: too large a number." << std::endl;
        else if (itBtc->second < 0)
            std::cerr << "Error: not a positive number." << std::endl;
        else if (itBtc->first.find("Error: bad input => "))
            std::cerr << itBtc->first << std::endl;
        else
        {
            std::cout << itBtc->first << " => " << itBtc->second << " = " 
            << transform(itBtc) << '.' << std::endl;
        }
    }
}