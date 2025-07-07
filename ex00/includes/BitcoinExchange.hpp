/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:58:24 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/07 21:49:11 by hfilipe-         ###   ########.fr       */
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
# include <limits>
# include <iomanip> 

class BitcoinExchange{
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        void                printMap() const;
        void                parse(const char *av, char);

    private:
        BitcoinExchange(const BitcoinExchange &);
        BitcoinExchange&    operator=(const BitcoinExchange &);
        int                 dateToInt(int year, int month, int day)const;
        std::string         strToDate(std::string)const;
        std::string         saveDate(std::string) const;
        double              saveNumber(std::string) const;
        void                setBtc();
        double              transform();
        void                print();
        std::string                         date;
        double                              number;
        std::multimap<std::string,double>   csv;
} ;

# endif