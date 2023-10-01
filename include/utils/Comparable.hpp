#ifndef JADA_COMPARABLE_HPP
#define JADA_COMPARABLE_HPP

#include <type_traits>

template<typename T>
class Comparable {
public:
	virtual bool operator< (T const& other) const =0;
	virtual bool operator<= (T const& other) const =0;
	virtual bool operator> (T const& other) const =0;
	virtual bool operator>= (T const& other) const =0;
	virtual bool operator== (T const& other) const =0;
	virtual bool operator!= (T const& other) const =0;
};

template <class T>
concept comparable = std::is_base_of<Comparable<T>, T>::value;

#endif //JADA_COMPARABLE_HPP
