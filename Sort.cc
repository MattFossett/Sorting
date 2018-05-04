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
insertionSort (vector<int>& toSort, size_t left, size_t right);

iterator
findPivot (iterator first, iterator last);

void
shellSort (vector<int>& toSort, iterator first, iterator last);

int
main (int argc, char* argv[])
{
  int size;
  cin >> size;
  vector<int> stdVec;
  randomNumber (size, stdVec);

  vector<int> quickVec (stdVec);
  vector<int> shellVec (stdVec);
  vector<int> mergeVec (stdVec);

  Timer<> t;
  double times[4];

/*
  t.start ();
  mergeSort (mergeVec, mergeVec.begin (), mergeVec.end ());
  t.stop ();
  times[0] = t.getElapsedMs ();
*/

  t.start ();
  sort (stdVec.begin (), stdVec.end ());
  t.stop ();
  times[3] = t.getElapsedMs ();


  t.start ();
  shellSort (shellVec, shellVec.begin(), shellVec.end() );
  t.stop ();
  times[2] = t.getElapsedMs();

  //printStuff (quickVec);
  t.start ();
  quickSort (quickVec, quickVec.begin(), quickVec.end() );
  t.stop ();
  times[1] = t.getElapsedMs();
  //printStuff (quickVec);

  /*
  cout << "\n[";
  for (int e : quickVec)
    cout << " " << e;
  cout << " ]\n";
  */

  cout << "timeMerge: " << times[0] << endl;
  cout << "timeQuick: " << times[1] << endl;
  cout << "timeStd  : " << times[3] << endl;
  cout << "shellVec  : " << times[2] << endl;

  cout << endl << "Quick Equality:" <<( quickVec == stdVec);
  cout << endl;
  cout << endl << "Shell Equality:" <<( shellVec == stdVec);
  cout << endl;




  cout << "\n in sort test";
  vector<int> smol;
 //smol.push_back(1);
  smol.push_back(2);
  insertionSort(smol, 0, smol.size());
 // printStuff(smol);


  //printStuff (quickVec);
  //printStuff (stdVec);

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
  temp.reserve(distance(first,last));
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

iterator
partition (iterator left, iterator right)
{
  iterator pivot_itr = findPivot(left, right);
  const int pivot = *pivot_itr;
  iterator i = left, j = pivot_itr;
  while (true)
  {
    while (*++i < pivot )
      ;
    while (*--j > pivot )
      ;
    if (distance (i, j) <= 0) break;
    std::iter_swap (i, j);
  }
  std::iter_swap (i, pivot_itr);
  return i;
}

void
quickSort (vector<int>& toSort, iterator left, iterator right)
{
  if (distance (left, right) <= 20)
  {
    insertionSort (toSort, distance(toSort.begin(), left), distance(toSort.begin(), right));
    return;
  }
  iterator mid = partition(left, right);
  quickSort (toSort, left, mid);
  quickSort (toSort, mid, right);
}

//returns iterator pointing to median value of first, last and the median of first & last
iterator
findPivot (iterator left, iterator right)
{
  --right;
  iterator center = left + (distance (left, right) / 2);
  if (*center < *left)
    std::swap (*left, *center);
  if (*right < *left )
    std::swap (*left, *right);
  if (*right < *center)
    std::swap (*center, *right);
  std::swap (*center, *--right);
  return right;
}

void
insertionSort (vector<int>& toSort, size_t left, size_t right)
{
   iterator start = toSort.begin() + left;
   iterator back = toSort.begin() + right;
   for (iterator front = start + 1; front != back; ++front)
   {
      int key = *front;
      iterator j = (front - 1);
      while (distance (start, j) >= 0 && key < *j)
      {
          *(j + 1) = *j;
          --j;
      }
      *(j + 1) = key;
   }
}

void
shellSort (vector<int>& toSort, iterator first, iterator last)
{
    size_t h = 1;
    while (h < distance(first, last)) {
      h = 3 * h + 1;
    }
    size_t sortSize = distance(first,last);
    //add d to toSort.begin() for subscripts from first to last
    size_t d = distance ( toSort.begin() , first);
    //for (size_t h = 1; h <= d/4; h=(h+3) * 3 )
    for (size_t gap = sortSize / 2; gap > 0; gap /= 2)
    {
        for (size_t i = gap; i < sortSize; ++i)
        {
            int temp = toSort[i+d];
            size_t j;
            for (j = i; j >= gap && toSort[j - gap] > temp; j -= gap)
                toSort[j + d] = toSort[(j+d) - gap];
            toSort[j+d] = temp;
        }
    }
}
