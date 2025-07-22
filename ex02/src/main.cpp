/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:19 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/22 19:11:08 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av){
    if (ac < 3)
        return (std::cerr << "Invalid number of arguments" << std::endl, 1);
    
    PergeMe perge;    
    for (size_t i = 1; av[i]; i++)
        perge.parseInput(av[i]);
    
    perge.execute('l');
    perge.execute('v');
    perge.print();
    
    perge.printContainer('l');
    perge.printContainer('v');
}