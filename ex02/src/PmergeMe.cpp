/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:38 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/09 16:25:40 by hfilipe-         ###   ########.fr       */
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


void splitPairsLt(const std::list<int>& input, std::list<int>& largerVals,
    std::list<int>& smallerVals) {
    std::list<int>::const_iterator it = input.begin();
    while (it != input.end()) {
        int a = *it;
        ++it;

        if (it == input.end()) {
            // Only one element left, send to largerVals
            largerVals.push_back(a);
            break;
        }

        int b = *it;
        ++it;

        if (a > b) std::swap(a, b);
        smallerVals.push_back(a);
        largerVals.push_back(b);
    }
}

void recursiveSortLt(std::list<int>& vals) {
    if (vals.size() <= 1)
        return;

    size_t mid = vals.size() / 2;
    std::list<int> left, right;

    std::list<int>::iterator it = vals.begin();
    for (size_t i = 0; i < mid; ++i, ++it)
        left.push_back(*it);
    for (; it != vals.end(); ++it)
        right.push_back(*it);

    recursiveSortLt(left);
    recursiveSortLt(right);

    vals.clear();
    std::list<int>::iterator lit = left.begin();
    std::list<int>::iterator rit = right.begin();

    while (lit != left.end() && rit != right.end()) {
        if (*lit < *rit) {
            vals.push_back(*lit);
            ++lit;
        } else {
            vals.push_back(*rit);
            ++rit;
        }
    }

    while (lit != left.end()) {
        vals.push_back(*lit);
        ++lit;
    }
    while (rit != right.end()) {
        vals.push_back(*rit);
        ++rit;
    }
}

std::list<size_t> generateJacobsthalList(size_t n) {
    std::list<size_t> jacob;

    if (n == 0)
        return jacob;

    jacob.push_back(1);
    if (n == 1)
        return jacob;

    jacob.push_back(3);

    std::list<size_t>::reverse_iterator rit = jacob.rbegin();
    while (*rit < n) {
        size_t prev = *rit;
        ++rit;
        size_t prev2 = *rit;
        jacob.push_back(prev + 2 * prev2);
        rit = jacob.rbegin(); // reset to end for next round
    }

    return jacob;
}

void insertSmallerJacobList(std::list<int>& sortedList, const std::list<int>& toInsert) {
    std::list<size_t> jacob = generateJacobsthalList(toInsert.size());

    // Step 1: Insert values at Jacobsthal positions
    size_t total = toInsert.size();

    std::list<bool> inserted;  // tracking which elements are done
    for (size_t i = 0; i < total; ++i)
        inserted.push_back(false);

    for (std::list<size_t>::iterator jIt = jacob.begin(); jIt != jacob.end(); ++jIt) {
        size_t target = *jIt;
        if (target >= total) break;

        std::list<int>::const_iterator targetIt = toInsert.begin();
        for (size_t step = 0; step < target; ++step)
            ++targetIt;

        int val = *targetIt;
        std::list<int>::iterator pos = sortedList.begin();
        while (pos != sortedList.end() && *pos < val)
            ++pos;
        sortedList.insert(pos, val);

        // Mark as inserted
        std::list<bool>::iterator mark = inserted.begin();
        std::advance(mark, target);
        *mark = true;
    }

    // Step 2: Insert remaining values
    std::list<bool>::const_iterator markIt = inserted.begin();
    std::list<int>::const_iterator valIt = toInsert.begin();
    while (markIt != inserted.end() && valIt != toInsert.end()) {
        if (!*markIt) {
            int val = *valIt;
            std::list<int>::iterator pos = sortedList.begin();
            while (pos != sortedList.end() && *pos < val)
                ++pos;
            sortedList.insert(pos, val);
        }
        ++markIt;
        ++valIt;
    }
}

void PergeMe::sortLt(){
    std::list<int> largerVals;
    std::list<int> smallerVals;

    splitPairsLt(lt, largerVals, smallerVals);
    recursiveSortLt(largerVals);
    insertSmallerJacobList(largerVals, smallerVals);

    std::cout << std::endl;
}


void splitPairs(const std::vector<int>& input,
                std::vector<int>& largerVals,
                std::vector<int>& smallerVals) {
    for (size_t i = 0; i < input.size(); i += 2) {
        int a = input[i];
        int b = (i + 1 < input.size()) ? input[i + 1] : std::numeric_limits<int>::min();

        if (b == std::numeric_limits<int>::min()) {
            largerVals.push_back(a);
        } else {
            if (a > b) std::swap(a, b);
            smallerVals.push_back(a);
            largerVals.push_back(b);
        }
    }
}

void recursiveSort(std::vector<int>& vals) {
    if (vals.size() <= 1)
        return;

    size_t mid = vals.size() / 2;
    std::vector<int> left, right;

    for (size_t i = 0; i < mid; ++i)
        left.push_back(vals[i]);
    for (size_t i = mid; i < vals.size(); ++i)
        right.push_back(vals[i]);

    recursiveSort(left);
    recursiveSort(right);

    vals.clear();
    std::vector<int>::iterator lit = left.begin();
    std::vector<int>::iterator rit = right.begin();
    while (lit != left.end() && rit != right.end()) {
        if (*lit < *rit) {
            vals.push_back(*lit);
            ++lit;
        } else {
            vals.push_back(*rit);
            ++rit;
        }
    }
    while (lit != left.end()) {
        vals.push_back(*lit);
        ++lit;
    }
    while (rit != right.end()) {
        vals.push_back(*rit);
        ++rit;
    }
}

std::vector<size_t> generateJacobsthal(size_t n) {
    std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);

    while (jacob.back() < n) {
        size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }

    return jacob;
}

void insertSmallerJacobsthal(std::vector<int>& sortedList, const std::vector<int>& toInsert) {
    std::vector<size_t> jacob = generateJacobsthal(toInsert.size());

    // Track which indices we've inserted
    std::vector<bool> inserted(toInsert.size(), false);

    for (size_t j = 0; j < jacob.size(); ++j) {
        size_t idx = jacob[j];
        if (idx >= toInsert.size())
            break;

        int val = toInsert[idx];
        std::vector<int>::iterator it = sortedList.begin();
        while (it != sortedList.end() && *it < val)
            ++it;
        sortedList.insert(it, val);
        inserted[idx] = true;
    }

    // Insert any remaining values that weren't included in Jacobsthal indices
    for (size_t i = 0; i < toInsert.size(); ++i) {
        if (!inserted[i]) {
            int val = toInsert[i];
            std::vector<int>::iterator it = sortedList.begin();
            while (it != sortedList.end() && *it < val)
                ++it;
            sortedList.insert(it, val);
        }
    }
}

void PergeMe::sortVec(){
    std::vector<int> largerVals;
    std::vector<int> smallerVals;

    splitPairs(vec, largerVals, smallerVals);
    recursiveSort(largerVals);
    insertSmallerJacobsthal(largerVals, smallerVals);
    std::cout << std::endl;
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

    std::cout << std::fixed << std::setprecision(5);
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