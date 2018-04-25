/*
  Filename   : ListDriver.cc
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

using std::cout;
using std::cin;
using std::mt19937;
using std::vector;

void
randomNumber (int size, vector<int>& toSort);

void 
mergeSort (vector<int>& s, size_t first, size_t last);

void
merge (vector<int>& s, size_t first, size_t mid, size_t last);

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

    for (const auto elem : mergeVec)
        cout << elem << ", ";
    cout << std::endl;
    mergeSort (mergeVec, mergeVec.front(), mergeVec.back() );
    for (const auto elem : mergeVec)
        cout << elem << ", ";
    
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
mergeSort (vector<int>& s, size_t first, size_t last)
{
    if (last - first > 1)
    {
        size_t mid = s[first] + (s[last] - s[first]) / 2;
        mergeSort (s, first, mid);
        mergeSort (s, mid, last);
        merge (s, first, mid, last);
    }
}

void
merge (vector<int>& s, size_t first, size_t mid, size_t last)
{
    vector<int> temp;
    size_t perm_mid = mid;
    while (temp.size() != s.size())
    {
        if (first == perm_mid)
        {
            while (mid != last)
                temp.push_back (mid++);
        }
        if (mid == last)
        {
            while (first != perm_mid)
                temp.push_back (first++);
        }
        if (s[first] < s[mid])
        {
            temp.push_back (s[first]);
            ++first;
        } 
        else 
        {
            temp.push_back (s[mid]);
            ++mid;
        }
    }
    s = temp;
}