#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:  
  
  /**
   * Using 0-based indexing
  */
  std::vector<T> data_;
  int m_;

  PComparator c_;

  /**
   * node access helper functions
   */ 

  // DOES NOT check if node exists
  size_t nthChild(size_t node, int child) const;
 
  // DOES NOT check if node exists
  size_t parent(size_t node) const;

  bool nodeExists(size_t node) const;
};


// Add implementation of member functions here
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::parent(size_t node) const
{
  return (node - 1) / m_;
}


template <typename T, typename PComparator>
size_t Heap<T,PComparator>::nthChild(size_t node, int child) const
{
  if (child < 1 || child > m_) {
    throw std::range_error("Invalid number of children");
  }
  return (m_ * node) + child;
}


template <typename T, typename PComparator>
bool Heap<T,PComparator>::nodeExists(size_t node) const
{
  return node < data_.size();
}


template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return data_.empty();
}


template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return data_.size();
}


// Constructor
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
{
  c_ = c;
  m_ = m;
}


// Destructor
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data_[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::underflow_error("Heap is empty");
  }

  // swap first and last elements
  std::swap(data_[0], data_[size() - 1]);
  data_.pop_back();

  // trickle down
  size_t currentNodeIndex = 0;
  while (true) {

    size_t bestChildIndex = nthChild(currentNodeIndex, 1);
    
    // node is a leaf, end loop
    if (!nodeExists(bestChildIndex)) break;

    // find best child
    for (int i = 2; i <= m_ ; i++) {
      size_t childIndex = nthChild(currentNodeIndex, i);
      
      if (!nodeExists(childIndex)) break;
      
      if ((c_(data_[childIndex], data_[bestChildIndex]))) {
          bestChildIndex = childIndex;
      }
    }

    T& current = data_[currentNodeIndex];
    T& bestChild = data_[bestChildIndex];

    // compare current and best child
    if (c_(bestChild, current)) {
      std::swap(current, bestChild);
      currentNodeIndex = bestChildIndex;
    }
    else break;
  }
}


template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  data_.push_back(item);
  size_t currentNodeIndex = size() - 1;

  // trickle up
  while (currentNodeIndex != 0) {
    size_t parentIndex = parent(currentNodeIndex);
    
    T& current = data_[currentNodeIndex];
    T& parent = data_[parentIndex];

    if (c_(current, parent)) {
      std::swap(current, parent);
      currentNodeIndex = parentIndex;
    }
    else break;
  }
}


#endif

