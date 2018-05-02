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
printStuff (vector<int>& v)
{
  cout << "\n[";
  for (int e : v)
    cout << " " << e;
  cout  << " ]\n";
}
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
  
  /*
  cout << "\n[";
  for (int e : quickVec)
    cout << " " << e;
*/
  cout << " ]\n";
  //printStuff ( stdVec);
  cout << "timeMerge: " << times[0] << endl;
  cout << "timeQuick: " << times[1] << endl;
  cout << "timeStd  : " << times[3] << endl;

  cout << endl << "Equality:" <<( quickVec == stdVec); 
  cout << endl;




  cout << "\n in sort test";
  vector<int> smol;
 //smol.push_back(1);
  smol.push_back(2);
  insertionSort(smol, smol.begin(), smol.end());
 // printStuff(smol);


  printStuff (quickVec);
  printStuff (stdVec);

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
   // iterator last = right-1;
    iterator pivot = findPivot (toSort, left, right-1 );
   
    iterator i = left, j = pivot-1;
    while ( true )  
    {
      while (*i < *pivot ) 
        ++i;
      while ( *j > *pivot )
        --j;
      if (distance (i,j) > 0)
        std::swap (*i, *j);
      else 
        break;
    }
    std::swap (*i, *pivot);
    quickSort (toSort, left, i);
    quickSort (toSort, (i+1), right);
  } 
  else 
    insertionSort (toSort, left, right);
}

//returns iterator pointing to median value of first, last and the median of first & last
iterator 
findPivot (vector<int>& toSort, iterator left, iterator right)
{
  iterator center = toSort.begin() + (distance (left, right) / 2);
  if (*center < *left)
    std::swap (*left, *center);
  if (*right < *left )
    std::swap (*left, *right);
  if (*right < *center)
    std::swap (*center, *right);
  std::swap (*center, *right);
  return right;

}

void
insertionSort (vector<int> toSort, iterator left, iterator right)
{
   iterator front = left;
   iterator j;
   ++left;
   while (left < right)
   {
      int key = *left;
      j = (left-1);

       while (distance (front, j) >= 0 && *j > key)
       {
           *(j+1) = *j;
           --j;
       }
       *(j+1) = key;
       ++left;
   }
}

