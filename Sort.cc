/*
  Filename   : Sort.cc
  Author     : Matt Fossett
  Course     : CSCI 362-01
  Assignment : N/A
  Description: Test methods of the List class
*/
/************************************************************/
// System includes

#include "Timer.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::distance;
using std::endl;
using std::mt19937;
using std::sort;
using std::vector;
using iterator = vector<int>::iterator;

void
randomNumber (int size, vector<int>& toSort);

void
mergeSort (vector<int>& s, iterator first, iterator last);

void
merge (vector<int>& s, iterator first, iterator mid, iterator last);

void
quickSort (vector<int>& toSort, iterator first, iterator last);

void
insertionSort (vector<int> toSort, iterator left, iterator right);

iterator 
findPivot (vector<int>& toSort, iterator first, iterator last);

void
shellSort (vector<int>& toSort);

int
main (int argc, char* argv[])
{
  int size;
  cin >> size;
  vector<int> mergeVec;
  randomNumber (size, mergeVec);

  vector<int> quickVec (mergeVec);
  vector<int> shellVec (mergeVec);
  vector<int> stdVec (mergeVec);

  Timer<> t;
  double times[4];

  t.start ();
  mergeSort (mergeVec, mergeVec.begin (), mergeVec.end ());
  t.stop ();
  times[0] = t.getElapsedMs ();

  t.start ();
  sort (stdVec.begin (), stdVec.end ());
  t.stop ();
  times[3] = t.getElapsedMs ();

  t.start ();
  quickSort (quickVec, quickVec.begin(), quickVec.end() );
  t.stop ();
  times[1] = t.getElapsedMs();

  cout << "timeMerge: " << times[0] << endl;
  cout << "timeQuick: " << times[1] << endl;
  cout << "timeStd  : " << times[3] << endl;

  cout << endl << "Equality:" <<( quickVec == stdVec); //for (const auto elem : mergeVec)
                                //    cout << elem << ", ";
}

void
randomNumber (int size, vector<int>& toSort)
{
  std::random_device rd;
  mt19937 random (rd ());
  std::uniform_int_distribution<> dist (0, 9999);
  for (int i = 0; i < size; ++i)
    toSort.push_back (dist (random));
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
  iterator perm_first = first;
  iterator perm_mid   = mid;
  while (temp.size () != s.size ())
  {
    if (first == perm_mid)
    {
      while (mid != last)
        temp.push_back (*mid++);
      break;
    }
    else if (mid == last)
    {
      while (first != perm_mid)
        temp.push_back (*first++);
      break;
    }
    if (*first < *mid)
      temp.push_back (*first++);
    else
      temp.push_back (*mid++);
  }
  std::copy (temp.begin (), temp.end (), perm_first);
}

void
quickSort (vector<int>& toSort, iterator left, iterator right)
{
  if (distance (left, right) > 20)
  {
    iterator pivot = findPivot (toSort, left, (--right) );
    std::swap (pivot, --right);
    pivot = --right;
    iterator i = left, j = --right;
    while ( true )  
    {
      while (*i < *pivot)
        ++i;
      while (*pivot < *j)
        ++j;
      if (i < j)
        std::swap (i, j);
      else 
        break;
    }

    quickSort (toSort, left, pivot);
    quickSort (toSort, ++pivot, right);
  } 
  else 
  {
    insertionSort (toSort, left, right);
  }
}

//returns iterator pointing to median value of first, last and the median of first & last
iterator 
findPivot (vector<int>& toSort, iterator first, iterator last)
{
  iterator mid = toSort.begin() + (distance (first, last)) / 2;
  if (*first < *mid && *first > *last)
    return first;
  else if (*mid < *first && *mid > *last)
    return mid;
  else 
    return last;
}

void
insertionSort (vector<int> toSort, iterator left, iterator right)
{
    
}
