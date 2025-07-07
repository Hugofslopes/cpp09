/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:38 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/07 21:49:08 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){
    date = other.date;
    number = other.number;
    csv = other.csv;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other){
    if(this != &other)
    {
        date = other.date;
        number = other.number;
        csv = other.csv;
    }
    return *this;
}

int BitcoinExchange::dateToInt(int year, int month, int day)const{
    return year * 10000 + month * 100 + day;
}

std::string BitcoinExchange::strToDate(std::string date)const{
    std::string str;
    char* end;
    int dateInt, year, month, day;
    
    dateInt = static_cast<int>(std::strtod(date.c_str(), &end));
    year = dateInt / 10000;
    month = (dateInt / 100) % 100;
    day = dateInt % 100;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << year << '-'
        << std::setw(2) << month << '-'
        << std::setw(2) << day;

    return oss.str();
    return(str);
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
    oss << nbdate;
    return oss.str();
}

double BitcoinExchange::saveNumber(std::string number)const{
    char*   end;

    return (std::strtod(number.c_str(), &end));
}

void BitcoinExchange::printMap() const{
    for (std::multimap<std::string, double>::const_iterator it = csv.begin(); it != csv.end(); ++it)
        std::cout << "date-" << it->first << ",\t" << "value-" << it->second << std::endl;
}

void BitcoinExchange::setBtc()
{
    csv.insert(std::make_pair(date, number));
}

void BitcoinExchange::parse(const char *av, char delimiter){
    std::ifstream input(av);
    if (!input)
        return (std::cerr << "Error opening input file: " << av << std::endl, exit (1));

    std::string line;
    std::getline(input, line);
    std::string Ndate;

    while (std::getline(input, line)) {
        std::stringstream ss(line);
        std::string Ndate, numberStr;
        if (!std::getline(ss, Ndate, delimiter) || !std::getline(ss, numberStr, delimiter)){
            date = "Error: bad input => " + Ndate;
            number = 0;
            print();
            continue;
        }
        number = saveNumber(numberStr);
        date = saveDate(Ndate);
        if (delimiter == '|')
            print();
        else
            setBtc();
    }
}

double BitcoinExchange::transform() {
    std::multimap<std::string, double>::iterator itCsv = csv.find(date);
    double value = 0;
    char* end;
    std::string str;
    
    if (itCsv != csv.end())
            value = number * itCsv->second;
    else if (std::strtod(date.c_str(), &end) < 20090102)
            value = number * csv.begin()->second;
    else{
        int nDate = static_cast<int>(std::strtod(date.c_str(), &end));
        while (nDate >= 20090102) 
        {
            nDate--;
            std::ostringstream oss;
            oss << nDate;
            str = oss.str();
            itCsv = csv.find(str);
            if (itCsv != csv.end())
                return (number * itCsv->second);
        }
    }
    return (value);
}

void BitcoinExchange::print() {
    if (number > std::numeric_limits<int>::max() ||
    number < std::numeric_limits<int>::min())
        std::cerr << "Error: too large a number." << std::endl;
    else if (number  < 0)
        std::cerr << "Error: not a positive number." << std::endl;
    else if (date.find("Error: bad input => ")  != std::string::npos)
        std::cerr << date << std::endl;
    else
        std::cout << strToDate(date) << " => " << number << " = " 
        << transform() << std::endl;
}