/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:58:24 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/07 16:42:48 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_CPP
# define BITCOINEXCHANGE_CPP

# include <iostream>
# include <fstream>
# include <map>
# include <sstream>
# include <string>
# include <stdlib.h>
# include <algorithm>

class BitcoinExchange{
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        void                printMaps(const std::string btc) const;
        void                parse(const char *av, char);
        void                print();

    private:
        BitcoinExchange(const BitcoinExchange &);
        BitcoinExchange&    operator=(const BitcoinExchange &);
        int                 dateToInt(int year, int month, int day)const;
        void                intToDate(int dateInt, int& year, int& month, int& day)const;
        std::string         saveDate(std::string) const;
        float               saveNumber(std::string) const;
        void                setBtc(std::string, float, char);
        float               transform(std::multimap<std::string, float>::iterator itBtc);
        std::multimap<std::string,float> btc;
        std::multimap<std::string,float> csv;
} ;

# endif