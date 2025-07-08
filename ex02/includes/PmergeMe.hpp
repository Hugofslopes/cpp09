/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:58:24 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/08 14:03:33 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_CPP
# define PMERGEME_CPP

# include <iostream>
# include <vector>
# include <list>
# include <limits>
# include <algorithm>
# include <ctime>
# include <utility>

class PergeMe{
    public: 
        PergeMe();
        ~PergeMe();
        
        void        execute(char);
        void        parseInput(char *);
        void        print();
        void        printContainer(char);

    private:
        PergeMe(const PergeMe &);
        PergeMe&    operator=(const PergeMe &);
        bool        checkDuplicates(int);
        bool        checkLimits(int );
        void        sortLt();
        void        sortVec();
        bool        checkPairsOrder();
        std::vector<int> tmp;
        std::list<int> lt;
        std::vector<int> vec;
        double vecTime;
        double ltTime;
} ;
# endif