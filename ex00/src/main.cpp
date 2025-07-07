/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:19 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/07 16:44:34 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av){
    if (ac != 2)
        return (std::cerr << "Invalid number of arguments" << std::endl, 1);
    BitcoinExchange bte;
    const char * str = av[1];
    bte.parse(str, '|');
    std::string csv = "data.csv";
    const char* cstr = csv.c_str();
    bte.parse(cstr, ',');
    //bte.printMaps("csv");
    bte.print();
}
