/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:38 by hfilipe-          #+#    #+#             */
/*   Updated: 2025/07/23 15:44:07 by hfilipe-         ###   ########.fr       */
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
std::list<int> generateJacobsthalSequenceLt(int n) {
    std::list<int> seq;

    if (n >= 1) 
        seq.push_back(0);
    if (n >= 3) 
        seq.push_back(2);

    int k = 3;
    while (true) {
        int sign = (k % 2 == 0) ? 1 : -1;
        int power = (1 << (k + 1));
        int j = (power + sign) / 3;

        if (j >= n)
            break;

        seq.push_back(j - 1);
        ++k;
    }
    return seq;
}

void binaryInsertLt(std::list<int>& sorted, int value) {
    std::list<int>::iterator low = sorted.begin();
    std::list<int>::iterator high = sorted.end();
    int size = std::distance(low, high);

    while (size > 0) {
        std::list<int>::iterator mid = low;
        std::advance(mid, size / 2);
        if (*mid < value) {
            low = mid;
            ++low;
            size -= size / 2 + 1;
        } 
        else {
            size /= 2;
        }
    }
    sorted.insert(low, value);
}

void fordJohnsonSortLt(std::list<int>& arr) {
    if (arr.size() <= 1)
        return;

    std::list<int> larger;
    std::list<int> smaller;

    std::list<int>::iterator it = arr.begin();
    while (std::distance(it, arr.end()) >= 2) {
        int a = *it;
        ++it;
        int b = *it;
        ++it;

        if (a > b)
            std::swap(a, b);
        smaller.push_back(a);
        larger.push_back(b);
    }

    bool hasLeftover = (it != arr.end());
    int leftover = hasLeftover ? *it : 0;

    fordJohnsonSortLt(larger);

    std::list<int> result = larger;

    std::list<int> smallList;
    for (std::list<int>::iterator sit = smaller.begin(); sit != smaller.end(); ++sit)
        smallList.push_back(*sit);

    std::list<char> inserted(smallList.size(), 0);
    std::list<int> jacOrder = generateJacobsthalSequenceLt(smallList.size());

    std::list<int>::iterator smallIt;
    std::list<char>::iterator insIt;

    for (std::list<int>::iterator iIt = jacOrder.begin(); iIt != jacOrder.end(); ++iIt) {
        int index = *iIt;
        smallIt = smallList.begin();
        insIt = inserted.begin();
        std::advance(smallIt, index);
        std::advance(insIt, index);

        binaryInsertLt(result, *smallIt);
        *insIt = 1;
    }

    smallIt = smallList.begin();
    insIt = inserted.begin();
    while (smallIt != smallList.end()) {
        if (!*insIt)
            binaryInsertLt(result, *smallIt);
        ++smallIt;
        ++insIt;
    }

    if (hasLeftover)
        binaryInsertLt(result, leftover);

    arr = result;
}

                                        //SORT VEC
std::vector<int> generateJacobsthalSequence(int n) {
    std::vector<int> seq;

    if (n >= 1) 
        seq.push_back(0);
    if (n >= 3) 
        seq.push_back(2);

    int k = 3;
    while (true) {
        int sign = (k % 2 == 0) ? 1 : -1;
        int j = ((1 << (k + 1)) + sign) / 3;

        if (j >= n)
            break;

        seq.push_back(j - 1);
        ++k;
    }
    return seq;
}

void binaryInsert(std::vector<int>& sorted, int value) {
    std::vector<int>::iterator first = sorted.begin();
    std::vector<int>::iterator last = sorted.end();

    while (first < last) {
        std::vector<int>::iterator mid = first + (last - first) / 2;
        if (*mid < value)
            first = mid + 1;
        else
            last = mid;
    }
    sorted.insert(first, value);
}

void fordJohnsonSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    std::vector<int> smaller, larger;
    size_t i = 0;

    for (; i + 1 < arr.size(); i += 2) {
        if (arr[i] < arr[i + 1]) {
            smaller.push_back(arr[i]);
            larger.push_back(arr[i + 1]);
        } 
        else {
            smaller.push_back(arr[i + 1]);
            larger.push_back(arr[i]);
        }
    }

    bool hasLeftover = (arr.size() % 2 == 1);
    int leftover = hasLeftover ? arr.back() : 0;

    fordJohnsonSort(larger);
    std::vector<int> result = larger;

    std::vector<bool> inserted(smaller.size(), false);
    std::vector<int> jacOrder = generateJacobsthalSequence(smaller.size());

    for (std::vector<int>::iterator it = jacOrder.begin(); it != jacOrder.end(); ++it) {
        int index = *it;
        if (index < static_cast<int>(smaller.size())) {
            binaryInsert(result, smaller[index]);
            inserted[index] = true;
        }
    }

    for (size_t j = 0; j < smaller.size(); ++j)
        if (!inserted[j])
            binaryInsert(result, smaller[j]);

    if (hasLeftover)
        binaryInsert(result, leftover);

    arr = result;
}

void PergeMe::execute(char type){
    std::clock_t start;
    std::clock_t end;
    
    if (type == 'l')
    {
        start = std::clock();
        fordJohnsonSortLt(lt);
    }
    else if (type == 'v')
    {
        start = std::clock();
        fordJohnsonSort(vec);
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