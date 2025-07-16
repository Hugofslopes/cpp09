/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:38 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/16 11:44:15 by hfilipe-         ###   ########.fr       */
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

                                        //SORT LIST
void splitPairsLt(const std::list<int>& input, std::list<int>& largerVals,
std::list<int>& smallerVals) {
    std::list<int>::const_iterator it = input.begin();
    int a, b;

    while (it != input.end()) {
        a = *it;
        ++it;

        if (it == input.end()) {
            largerVals.push_back(a);
            break;
        }

        b = *it;
        ++it;

        if (a > b) 
            std::swap(a, b);
        smallerVals.push_back(a);
        largerVals.push_back(b);
    }
}

void recursiveSortLt(std::list<int>& vals) {
    if (vals.size() <= 1)
        return;

    size_t mid = vals.size() / 2;  // Find midpoint
    std::list<int> left, right;
    std::list<int>::iterator it = vals.begin();
    
    for (size_t i = 0; i < mid; ++i, ++it)
        left.push_back(*it); // Copy first half into left

    for (; it != vals.end(); ++it)
        right.push_back(*it);  // Copy second half into right

    recursiveSortLt(left);  // Recursively sort left half
    recursiveSortLt(right); // Recursively sort right half

    vals.clear();  // Prepare to rebuild sorted list

    std::list<int>::iterator lit = left.begin();
    std::list<int>::iterator rit = right.begin();

    // Merge sorted halves
    while (lit != left.end() && rit != right.end()) {
        if (*lit < *rit) {
            vals.push_back(*lit);
            ++lit;
        } 
        else {
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

//Fibonacci: F(n)= F(n−1) + F(n−2)F(n) = F(n−1) + F(n−2)

//Jacobsthal: J(n) = J(n−1) + 2⋅J(n−2)J(n) = J(n−1) + 2⋅J(n−2)

std::list<size_t> generateJacobsthalList(size_t n) {
    std::list<size_t> jacob;
    size_t prev, prev2;
    std::list<size_t>::reverse_iterator rit;

    if (n == 0)
        return jacob;

    jacob.push_back(1); 
    jacob.push_back(3);

    rit = jacob.rbegin();

    while (*rit < n) {
        prev = *rit;  // Last element
        ++rit;               // Move to second-to-last
        prev2 = *rit; // Second-to-last element
        jacob.push_back(prev + 2 * prev2);  // J(n) = J(n-1) + 2*J(n-2)
        rit = jacob.rbegin();  // Reset to new last element for next loop
    }

    return jacob;  // Return full Jacobsthal list
}

void insertSmallerJacobList(std::list<int>& sortedList, const std::list<int>& toInsert) {
    std::list<size_t> jacob = generateJacobsthalList(toInsert.size());  // Jacobsthal indices

    size_t total = toInsert.size();

    std::list<bool> inserted;  // Track which elements were inserted
    for (size_t i = 0; i < total; ++i)
        inserted.push_back(false);  // Initialize to false

    // Step 1: Insert elements at Jacobsthal positions
    for (std::list<size_t>::iterator jIt = jacob.begin(); jIt != jacob.end(); ++jIt) {
        size_t target = *jIt;
        if (target >= total) 
            break; 

        std::list<int>::const_iterator targetIt = toInsert.begin();
        for (size_t step = 0; step < target; ++step)
            ++targetIt;  // Move to the target index

        int val = *targetIt;  // Get value to insert
        std::list<int>::iterator pos = sortedList.begin();
        while (pos != sortedList.end() && *pos < val)
            ++pos;  // Find correct insertion point (sorted order)
        sortedList.insert(pos, val);  // Insert into sorted list

        // Mark as inserted
        std::list<bool>::iterator mark = inserted.begin();
        std::advance(mark, target);
        *mark = true;
    }

    // Step 2: Insert remaining elements that were not handled by Jacobsthal indices
    std::list<bool>::const_iterator markIt = inserted.begin();
    std::list<int>::const_iterator valIt = toInsert.begin();
    while (markIt != inserted.end() && valIt != toInsert.end()) {
        if (!*markIt) {
            int val = *valIt;  // Get the value to insert
            std::list<int>::iterator pos = sortedList.begin();
            while (pos != sortedList.end() && *pos < val)
                ++pos;  // Find insertion position
            sortedList.insert(pos, val);  // Insert value
        }
        ++markIt;
        ++valIt;
    }
}

void PergeMe::sortLt() {
    std::list<int> largerVals;
    std::list<int> smallerVals;

    splitPairsLt(lt, largerVals, smallerVals);
    recursiveSortLt(largerVals);          
    insertSmallerJacobList(largerVals, smallerVals);
    lt = largerVals;
}

                                        //SORT VECTOR
void splitPairs(const std::vector<int>& input, std::vector<int>& largerVals,
std::vector<int>& smallerVals) {
    int a, b;

    for (size_t i = 0; i < input.size(); i += 2) {
        a = input[i];

        if (i + 1 == input.size())
            largerVals.push_back(a); 
        else {
            b = input[i + 1];
            if (a > b) 
                std::swap(a, b);
            smallerVals.push_back(a);
            largerVals.push_back(b);
        }
    }
}

void recursiveSort(std::vector<int>& vals) {
    if (vals.size() <= 1)
        return; 

    size_t mid = vals.size() / 2;  // Find midpoint for splitting
    std::vector<int> left, right;

    for (size_t i = 0; i < mid; ++i)
        left.push_back(vals[i]);  // Copy first half into left
    
    for (size_t i = mid; i < vals.size(); ++i)
        right.push_back(vals[i]);  // Copy second half into right

    recursiveSort(left);  
    recursiveSort(right); 
    
    vals.clear();  // Clear original vector to rebuild it

    std::vector<int>::iterator lit = left.begin();
    std::vector<int>::iterator rit = right.begin();

    while (lit != left.end() && rit != right.end()) {
        if (*lit < *rit) {
            vals.push_back(*lit);
            ++lit;
        } 
        else {
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
    jacob.push_back(1);  // First Jacobsthal number
    jacob.push_back(3);  // Second Jacobsthal number

    while (jacob.back() < n) 
        jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);  

    return jacob; 
}

void insertSmallerJacobsthal(std::vector<int>& sortedList, const std::vector<int>& toInsert) {
    std::vector<size_t> jacob = generateJacobsthal(toInsert.size());

    std::vector<bool> inserted(toInsert.size(), false);  // Track which elements are inserted

    for (size_t j = 0; j < jacob.size(); ++j) {
        size_t idx = jacob[j];
        if (idx >= toInsert.size())
            break; 

        int val = toInsert[idx];  // Get value at Jacobsthal index
        std::vector<int>::iterator it = sortedList.begin();
        while (it != sortedList.end() && *it < val)
            ++it;  // Find correct insertion point (sorted order)
        sortedList.insert(it, val);  // Insert value
        inserted[idx] = true;  // Mark as inserted
    }

    for (size_t i = 0; i < toInsert.size(); ++i) {
        if (!inserted[i]) {  // If value was not inserted via Jacobsthal
            int val = toInsert[i];
            std::vector<int>::iterator it = sortedList.begin();
            while (it != sortedList.end() && *it < val)
                ++it;  // Find insertion point
            sortedList.insert(it, val);  // Insert value
        }
    }
}

void PergeMe::sortVec() {
    std::vector<int> largerVals; 
    std::vector<int> smallerVals;

    splitPairs(vec, largerVals, smallerVals);  
    recursiveSort(largerVals);  
    insertSmallerJacobsthal(largerVals, smallerVals);
    vec = largerVals;
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