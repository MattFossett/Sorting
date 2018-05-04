/*
  Filename   : Sort.cc
  Author     : Matt Fossett
  Course     : CSCI 362-01
  Assignment : N/A
  Description: Test methods of the List class

  Table of Results

  N:       20,000,000            40,000,000             80,000,000    
  ============================================================================
  Merge    6354.62  (986639932)  13383.30 (2053281083)  27770.84 (4266548415)
  Quick    1314.08   (20115755)   2702.81   (40115656)   5527.38   (80112085)
  Shell    5332.00 (1886297903)  12148.60 (4312522006)  27986.28 (9442491664)
  std      1117.32                2249.43                5351.19

*/
/************************************************************/
// System includes

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

/************************************************************/
// Local Includes
#include "Timer.hpp"

/************************************************************/
// Using declarations
using std::cin;
using std::cout;
using std::distance;
using std::endl;
using std::mt19937;
using std::sort;
using std::vector;
using iterator = vector<int>::iterator;

/************************************************************/
// Function prototypes
void
printVector (vector<int>& v);

void
randomNumber (vector<int>& toSort);

size_t
mergeSort (vector<int>& v);

size_t
mergeSortHelper (vector<int>& s, iterator first, iterator last);

size_t
merge (vector<int>& s, iterator first, iterator mid, iterator last);

size_t
quickSort (vector<int>& v);

size_t
quickSortHelper (vector<int>& toSort, iterator first, iterator last);

size_t
insertionSort (vector<int>& toSort, size_t left, size_t right);

iterator
findPivot (iterator first, iterator last);

size_t
shellSort (vector<int>& v);

size_t
shellSortHelper (vector<int>& toSort, iterator first, iterator last);

/************************************************************/

int
main (int argc, char* argv[])
{
  vector<int> stdVec;
  randomNumber (stdVec);

  vector<int> quickVec (stdVec);
  vector<int> shellVec (stdVec);
  vector<int> mergeVec (stdVec);

  Timer<> t;
  double times[4];

  t.start ();
  size_t mergeCompares = mergeSort (mergeVec);
  t.stop ();
  times[0] = t.getElapsedMs ();

  t.start ();
  size_t quickCompares = quickSort (quickVec);
  t.stop ();
  times[1] = t.getElapsedMs();

  t.start ();
  size_t shellCompares = shellSort (shellVec);
  t.stop ();
  times[2] = t.getElapsedMs();

  t.start ();
  sort (stdVec.begin (), stdVec.end ());
  t.stop ();
  times[3] = t.getElapsedMs ();

  printf ("\nMerge time: %.2f ms", times[0]);
  cout << "\nMerge compares: " << mergeCompares << endl;
  
  printf ("\nQuick time: %.2f ms", times[1]);
  cout << "\nQuick compares: " << quickCompares << endl;

  printf ("\nShell time: %.2f ms", times[2]);
  cout << "\nShell compares: " << shellCompares << endl;

  printf ("\nstd   time: %.2f ms \n", times[3]);
  
  cout << endl << "Merge ok? " << std::boolalpha << ( mergeVec == stdVec);
  cout << endl << "Quick ok? " << std::boolalpha << ( quickVec == stdVec);
  cout << endl << "Shell ok? " << std::boolalpha << ( shellVec == stdVec);

  return EXIT_SUCCESS;
}

void
randomNumber (vector<int>& toSort)
{
  int size;
  cout << "N ==> ";
  cin >> size;
  std::random_device rd;
  mt19937 random (rd ());
  std::uniform_int_distribution<> dist (0, 9999);
  for (int i = 0; i < size; ++i)
    toSort.push_back (dist (random));
}

size_t
mergeSort (vector<int>& v)
{
  return (mergeSortHelper (v, v.begin(), v.end() ));
}

size_t
mergeSortHelper (vector<int>& s, iterator first, iterator last)
{
  size_t compare = 0;
  if (distance (first, last) > 1)
  {
    iterator mid = first + (distance (first, last) / 2);
    compare += mergeSortHelper (s, first, mid);
    compare += mergeSortHelper (s, mid, last);
    compare += merge (s, first, mid, last);
  }
  return compare;
}

size_t
merge (vector<int>& s, iterator first, iterator mid, iterator last)
{
  size_t count = 0;
  vector<int> temp;
  temp.reserve (distance (first,last));
  iterator perm_first = first;
  iterator perm_mid   = mid;
  while (temp.size () != s.size ())
  {
    ++count;
    if (first == perm_mid)
    {
      ++count;
      while (mid != last)
      {
        temp.push_back (*mid++);
        ++count;
      }
      break;
    }
    else if (mid == last)
    {
      ++count;
      while (first != perm_mid)
      {  
        temp.push_back (*first++);
        ++count;
      }
      break;
    }
    if (*first < *mid)
      temp.push_back (*first++);
    else
      temp.push_back (*mid++);
    ++count;
  }
  std::copy (temp.begin (), temp.end (), perm_first);
  return count;
}

iterator
partition (iterator left, iterator right)
{
  iterator pivot_itr = findPivot(left, right);

  const int pivot = *pivot_itr;
  iterator i = left, j = pivot_itr;
  while (true)
  {
    while (*++i < pivot );
    while (*--j > pivot );
    if (distance (i, j) <= 0) break;
    std::iter_swap (i, j);
  }
  std::iter_swap (i, pivot_itr);
  return i;
}

size_t
quickSort (vector<int>& v)
{
  return quickSortHelper(v, v.begin(), v.end());
}

size_t
quickSortHelper (vector<int>& toSort, iterator left, iterator right)
{
  size_t count = 0;
  if (distance (left, right) < 20)
  {
    ++count;
    return count += insertionSort (toSort, distance(toSort.begin(), left), distance(toSort.begin(), right));
  }
  iterator mid = partition(left, right);
  count += quickSortHelper (toSort, left, mid);
  count += quickSortHelper (toSort, mid, right);
  return count;
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

size_t
insertionSort (vector<int>& toSort, size_t left, size_t right)
{
  size_t count = 0;
  iterator start = toSort.begin() + left;
  iterator back = toSort.begin() + right;
  for (iterator front = start + 1; front != back; ++front)
  {
    ++count;
    int key = *front;
    iterator j = (front - 1);
    while (distance (start, j) >= 0 && key < *j)
    {
      ++count;
      *(j + 1) = *j;
      --j;
    }
    *(j + 1) = key;
  }
    return count;
}

size_t
shellSort (vector<int>& v)
{
  return shellSortHelper (v, v.begin(), v.end());
}

size_t
shellSortHelper (vector<int>& toSort, iterator first, iterator last)
{
    size_t count = 0;
    size_t h = 1;
    while (h < distance (first, last))
    {
      h = 3 * h + 1;
      ++count;
    }
    size_t sortSize = distance (first,last);
    //add d to toSort.begin() for subscripts from first to last
    size_t d = distance (toSort.begin() , first);
    for (size_t gap = sortSize / 2; gap > 0; gap /= 2)
    {
      ++count;
      for (size_t i = gap; i < sortSize; ++i)
      {
        ++count;
        int temp = toSort[i+d];
        size_t j;
        for (j = i; j >= gap && toSort[j - gap] > temp; j -= gap)
        {
          ++count;
          toSort[j + d] = toSort[(j+d) - gap];
        }
        toSort[j+d] = temp;
      }
    }
    return count;
}

void
printVector (vector<int>& v)
{
  cout << "\n[";
  for (int e : v)
    cout << " " << e;
  cout  << " ]\n";
}
