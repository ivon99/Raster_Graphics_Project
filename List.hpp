#ifndef _LIST_HPP_
#define _LIST_HPP_
#include <iostream>
#include <fstream>

template <typename T>
class List{
    protected:
    static const int INITIAL_CAPACITY =5;
    int m_size;
    int m_capacity;
    T* m_array;

  // --helper functions--
  void copyFrom(const List& other);
  void clear();
  void resize(int newCapacity);

  public:
  //--Big 4--
  List(int capacity=0);
  List(const List& other);
  List& operator=(const List& other);
  ~List();

  // --getters--
  int getSize()const;
  int getCapacity() const;
  T& getElement(int index);
  const T getElement(int index) const;

  //--methods for list--
  void addElement(const T& newElement);
  void deleteElement(int index);

  //--operators overloading
  T& operator[](int index);
  const T& operator[](int index)const;
  //friend std::ostream& operator<<(std::ostream out,const List& object);
   
  //--(de)serialization (file methods)-- 
  // !! Only works if T has serialize(outFile) and constructor from file
  void serialize(std::ofstream& outFile);
  void deserialize(std::ifstream& inFile) const;
  
};

template <typename T>
std::ostream& operator<<(std::ostream& out,const List<T>& object);

#include "List.tmpl"

#endif