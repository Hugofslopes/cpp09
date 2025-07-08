/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:38 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/08 14:04:38 by hfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PergeMe::PergeMe(){}

PergeMe::~PergeMe(){}

PergeMe::PergeMe(const PergeMe &other){
    tmp = other.tmp;
    lt = other.lt;
    vec = other.vec;
    vecTime = other.vecTime;
    ltTime = other.ltTime;
}

PergeMe& PergeMe::operator=(const PergeMe &other){
    if (this != &other)
    {
        tmp = other.tmp;
        lt = other.lt;
        vec = other.vec;
        vecTime = other.vecTime;
        ltTime = other.ltTime;
    }
    return (*this);
}

bool PergeMe::checkLimits(int nb){
    if (nb > std::numeric_limits<int>::max() ||
    nb < std::numeric_limits<int>::min())
        return (true);
    return (false);
}

bool PergeMe::checkDuplicates(int value){
    std::vector<int>::iterator itV = vec.begin();
    for (; itV != vec.end() ; itV++)
        if (*itV == value)
            return (true);
    return (false);
}

void PergeMe::parseInput(char *arg){
	char*   end;
	int 	nb;
    
	nb = std::strtod(arg, &end);
    if (nb < 0){
        std::cerr << "Error: number must be a positive integer." << std::endl, exit (1);
    }
    if (checkLimits(nb))
        std::cerr << "Error: too large a number." << std::endl, exit (1);
    if (checkDuplicates(nb))
        std::cerr << "Error: the program does not allow duplicates" 
        << std::endl, exit (1);
    tmp.push_back(nb);
	lt.push_back(nb);
    vec.push_back(nb);
}

void PergeMe::sortLt(){
    
    // GROUP in PAIRS!!
    //COMPARE INSIDE PAIRS TO GET THE BIGGER
    //RECURSIVELY SORT LARGER ELEMNTS OF EACH PAIR
    //INSERT AT THE START OF OTHER STACK THE ELEMENT OF THE SMALLEST
    
}

bool PergeMe::checkPairsOrder() {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[i - 1]) {
            return false;
        }
    }
    return true;
}

void PergeMe::sortVec(){
    std::vector<std::pair<int, int> > vecPairs;
    std::vector<int>::iterator itTp = vec.begin();
    int nbE;
    int nbO;

    for (size_t i = 0; itTp != vec.end(); i++){
        if (!(i % 2)){
            nbE = *itTp;
            itTp = vec.erase(itTp);
        }
        else {
            nbO = *itTp;
            itTp = vec.erase(itTp);
            vecPairs.push_back(
            std::make_pair((nbE < nbO ? nbE : nbO), (nbE > nbO ? nbE : nbO)));
        }
    }
    std::vector<std::pair<int, int> >::iterator itPair = vecPairs.begin();
    while (itPair != vecPairs.end()) {
        vec.push_back(itPair->first);
        vec.push_back(itPair->second);
        itPair = vecPairs.erase(itPair);
    }
    printContainer('v');   
    while (!checkPairsOrder())
        sortVec();
}

void PergeMe::execute(char type){
    std::clock_t start;
    std::clock_t end;
    
    if (type == 'l')
    {
        start = std::clock();
        sortLt();
    }
    else if (type == 'v')
    {
        start = std::clock();
        sortVec();
    }
    end = std::clock();
    if (type == 'l')
        ltTime = double(end - start) / CLOCKS_PER_SEC;
    else if (type == 'v')
        vecTime = double(end - start) / CLOCKS_PER_SEC;
}

void PergeMe::print(){
    std::vector<int>::iterator itTp = tmp.begin();
    
    std::cout << "before: ";
    for (; itTp != tmp.end(); itTp++)
        std::cout << *itTp << ' ';
    std::cout << std::endl;

    std::sort(tmp.begin(), tmp.end());
    std::cout << "after: ";
    itTp = tmp.begin();
    for (; itTp != tmp.end(); itTp++)
        std::cout << *itTp << ' ';
    std::cout << std::endl;

    std::cout << "Time to process a range of " << vec.size() 
    << " elements with std::vector : " << vecTime << " us" << std::endl;

    std::cout << "Time to process a range of " << lt.size() 
    << " elements with std::list : " << ltTime << " us" << std::endl;
}

void   PergeMe::printContainer(char type){
    if (type == 'l')
    {
        std::list<int>::iterator itTp = lt.begin();
        for (; itTp != lt.end(); itTp++)
            std::cout << *itTp << ' ';
        std::cout << std::endl;
    }

    else if (type == 'v')
    {
        std::vector<int>::iterator itTp = vec.begin();
        for (; itTp != vec.end(); itTp++)
            std::cout << *itTp << ' ';
        std::cout << std::endl;
    }
}