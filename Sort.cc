/*
  Filename   : Sort.cc
  Author     : Matt Fossett
  Course     : CSCI 362-01
  Assignment : N/A
  Description: Test methods of the List class
*/   
/************************************************************/
// System includes

#include <cstdlib>
#include <iostream>
#include <string>
#include <iterator>
#include <random>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Timer.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::mt19937;
using std::vector;
using std::distance;
using std::sort;
using iterator = vector<int>::iterator;


void
randomNumber (int size, vector<int>& toSort);

void 
mergeSort (vector<int>& s, iterator first, iterator last);

void
merge (vector<int>& s, iterator first, iterator mid, iterator last);

void 
quickSort (vector<int>& toSort);

void 
shellSort (vector<int>& toSort);

int
main (int argc, char *argv[])
{   
    int size;
    cin >> size;
    vector<int> mergeVec;
    randomNumber (size, mergeVec);

    vector<int> quickVec (mergeVec);
    vector<int> shellVec (mergeVec);
    vector<int> stdVec   (mergeVec);
    
    Timer<> t;
    double times[4];

    t.start();
    mergeSort (mergeVec, mergeVec.begin(), mergeVec.end() );
    t.stop();
    times[0] = t.getElapsedMs(); 
    
    t.start();
    sort(stdVec.begin(), stdVec.end());
    t.stop();
    times[3] = t.getElapsedMs();

    cout << "timeMerge: " << times[0] << endl;
    cout << "timeStd  : " << times[3] << endl;

    cout << endl << "Equality: ";    //for (const auto elem : mergeVec)
    //    cout << elem << ", ";
    
}   

void
randomNumber (int size, vector<int>& toSort)
{
    std::random_device rd;
    mt19937 random (rd());
    std::uniform_int_distribution<> dist(0,9999);
    for (int i=0; i<size; ++i)
        toSort.push_back (dist(random));
}

void 
mergeSort (vector<int>& s, iterator first, iterator last)
{
    if (distance (first, last) > 1)
    {
        //cout << distance(first , last) << std::endl;
        iterator mid = first + (distance (first, last) / 2);
        //cout << "first=" << *first << " mid=" << *mid <<" last=" << *(--last)  << endl;
        
        mergeSort (s, first, mid);
        
        mergeSort (s, mid, last);
        
        merge (s, first, mid, last);
         
    }
}

void
merge (vector<int>& s, iterator first, iterator mid, iterator last)
{
    vector<int> temp;
    iterator perm_first = s.begin() + distance (s.begin(), first);
    iterator perm_mid   = s.begin() + distance (s.begin(), mid  );
    while (temp.size() != s.size())
    {
        if (first == perm_mid)
        {
            while (mid != last)
            {
                temp.push_back (*mid);
                ++mid;
            }
            break;
        }
        else if (mid == last)
        {
            while (first != perm_mid)
            {
                temp.push_back (*first);
                ++first;
            }
            break;
        }
        if (*first < *mid)
        {
            temp.push_back (*first);
            ++first;
        } 
        else 
        {
            temp.push_back (*mid);
            ++mid;
        }
    }
    iterator copyToSrc = (s.begin() + distance (s.begin(), perm_first));
    std::copy (temp.begin(), temp.end(), copyToSrc);
}

void 
quickSort (vector<int>& toSort)
{
    
}