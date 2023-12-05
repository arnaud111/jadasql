//
// Created by macaron on 01/10/23.
//

#ifndef JADA_INSTANCEOF_HPP
#define JADA_INSTANCEOF_HPP

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

#endif //JADA_INSTANCEOF_HPP
