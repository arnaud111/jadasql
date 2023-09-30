#ifndef JADA_COMPARABLE_HPP
#define JADA_COMPARABLE_HPP

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

#endif //JADA_COMPARABLE_HPP
