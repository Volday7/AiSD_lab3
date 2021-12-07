#pragma once
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <list>
#include <complex>

template <class T>

class Polynom {
private:
	std::list<T> l;
public:
	auto begin() { return l.begin(); }
	const auto begin() const { return l.begin(); }
	auto end() { return l.end(); }
	const auto end() const { return l.end(); }
	Polynom<T>(int degree) {
		if (degree < 0) throw "Invalid degree";
		else {
			size_t count = 1;
			while(count != degree + 2) {
				l.push_front(1);
				count++;
			}
		}
	}

	int Size() {
		int size = 0;
		for (auto it = l.begin(); it != l.end(); it++) {
			size++;
		}
		return size;
	}

	T& operator[](int index) {
		if ((index >= 0) && (index < Size())) {
			int count = 0;
			for (auto it = l.begin(); it != l.end(); it++) {
				if (count == index) return *it;
				count++;
			}
		}
		else throw "Invalid index";
	}

	void Set(T newcoef, int degree) {
		if ((degree >= 0) && degree <= Size()) {
			int count = Size();
			count -= 1;
			for (auto it = l.begin(); it != l.end(); it++) {
				if (count == degree) *it = newcoef;
				count--;
			}
		}
		else throw "Invalid degree";
	}

	Polynom<T> operator+(Polynom<T>& rhs) {
		if (l.empty()) return rhs;
		if (!rhs.l.max_size()) return *this;
		int size1 = Size();
		int size2 = rhs.Size();
		if (size1 == size2) {
			Polynom<T> res(*this);
			auto it_rhs = rhs.begin();
			for (auto it = res.begin(); it != res.end(); it++) {
				*it = *it + *it_rhs;
				it_rhs++;
			}
			return res;
		}
		else {
			if (size1 > size2) {
				Polynom<T> res(*this);
				int size_max = size1;
				int size_min = size2;
				auto it_rhs = rhs.begin();
				auto it = res.begin();
				int i = 0;
				for (it; i < size_max - size_min; it++) {
					i++;
				}
				for (it; it != res.end(); it++) {
					*it = *it + *it_rhs;
				}
				return res;
			}
			else { 
				Polynom<T> res(rhs);
				int size_max = size2;
				int size_min = size1;
				auto it_rhs = l.begin();
				auto it = res.begin();
				int i = 0;
				for (it; i < size_max - size_min; it++) {
					i++;
				}
				for (it; it != res.end(); it++) {
					*it = *it + *it_rhs;
				}
				return res;
			}
		}
	}

	Polynom<T> operator-(Polynom<T>& rhs) {
		if (l.empty()) return rhs;
		if (!rhs.l.max_size()) return *this;
		int size1 = Size();
		int size2 = rhs.Size();
		if (size1 == size2) {
			Polynom<T> res(*this);
			auto it_rhs = rhs.begin();
			for (auto it = res.begin(); it != res.end(); it++) {
				*it = *it - *it_rhs;
				it_rhs++;
			}
			return res;
		}
		else {
			if (size1 > size2) {
				Polynom<T> res(*this);
				int size_max = size1;
				int size_min = size2;
				auto it_rhs = rhs.begin();
				auto it = res.begin();
				int i = 0;
				for (it; i < size_max - size_min; it++) {
					i++;
				}
				for (it; it != res.end(); it++) {
					*it = *it - *it_rhs;
				}
				return res;
			}
			else {
				Polynom<T> res(rhs);
				int size_max = size2;
				int size_min = size1;
				auto it_rhs = l.begin();
				auto it = res.begin();
				int i = 0;
				for (it; i < size_max - size_min; it++) {
					i++;
				}
				for (it; it != res.end(); it++) {
					*it = *it - *it_rhs;
				}
				return res;
			}
		}
	}

	Polynom operator*(T scalar) {
		Polynom<T> res(*this);
		for (auto it = res.begin(); it != res.end(); it++) {
			*it = *it * scalar;
		}
		return res;
	}

	T Result(T x) {
		T result = 0;
		Polynom<T> res(*this);
		int i = Size();
		i -= 1;
		for (auto it = res.begin(); it != res.end(); it++) {
			result += *it * (T)pow(x, i);
			i--;
		}
		return result;
	}

	friend std::ostream& operator<<(std::ostream& out, Polynom<T>& pol) {
		int count = 0;
		for (auto it = pol.begin(); it != pol.end(); it++) {
			count++;
		}
		count -= 1;
		out << "Polynom: "; 
		for (auto it = pol.begin(); it != pol.end(); it++) {
			out << (T)*it << "*x^" << count;
			if (count != 0) out << " + ";
			count--;
		}
		return out;
	}
};