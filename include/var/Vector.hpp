/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#ifndef SAPI_VAR_VECTOR_HPP_
#define SAPI_VAR_VECTOR_HPP_

#include <vector>
#include <algorithm>
#include <functional>

#include "../arg/Argument.hpp"

namespace var {

/*! \brief Vector Class
 * \details The Vector class
 * is similar to std::vector but is embedded friendly.
 *
 *
 */
template<typename T> class Vector:
		public api::WorkObject {
public:

	using Position = arg::Argument<size_t, struct VectorPositionTag>;
	using Count = arg::Argument<size_t, struct VectorCountTag>;

	/*! \details Constructs an empty object.
		*
		*/
	Vector(){}

	/*! \details Constructs a vector with \a count uninitialized items. */
	Vector(size_t count){
		m_vector.resize(count);
	}

	Vector (std::initializer_list<T> il) : m_vector(il){}
	Vector& operator=(std::initializer_list<T> il){ m_vector = il; }


	~Vector(){}

	Vector<T> & operator << (const T & a){
		return push_back(a);
	}

	using iterator = typename std::vector<T>::iterator;
	using const_iterator = typename std::vector<T>::const_iterator;
	using reverse_iterator = typename std::vector<T>::reverse_iterator;
	using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

	const_iterator begin() const noexcept { return m_vector.begin(); }
	iterator begin() noexcept { return m_vector.begin(); }

	const_iterator end() const noexcept { return m_vector.end(); }
	iterator end() noexcept { return m_vector.end(); }

	const_iterator cbegin() const noexcept { return m_vector.cbegin(); }
	const_iterator cend() const noexcept { return m_vector.cend(); }

	const_reverse_iterator rbegin() const noexcept { return m_vector.rbegin(); }
	reverse_iterator rbegin() noexcept { return m_vector.rbegin(); }

	const_reverse_iterator rend() const noexcept { return m_vector.rend(); }
	reverse_iterator rend() noexcept { return m_vector.rend(); }

	const_reverse_iterator crbegin() const noexcept { return m_vector.crbegin(); }
	const_reverse_iterator crend() const noexcept { return m_vector.crend(); }

	iterator insert(
			const_iterator position,
			const T & value
			){
		return m_vector.insert(position, value);
	}

	Vector<T>& insert(Position position, const T & value){
		insert(begin() + position.argument(), value);
		return *this;
	}

	iterator insert(
			const_iterator position,
			size_t n,
			const T & value
			){
		return m_vector.insert(position, n, value);
	}

	iterator insert(
			const_iterator position,
			T && value
			){
		return m_vector(position, value);
	}

	Vector<T>& insert(Position position, T && value){
		insert(begin() + position.argument(), value);
		return *this;
	}

	iterator insert(
			const_iterator position,
			std::initializer_list<T> il
			){
		return m_vector.insert(position, il);
	}

	Vector<T> & operator << (const Vector<T> & a){
		for(u32 i=0; i < a.count(); i++){
			*this << a.at(i);
		}
		return *this;
	}

	T & at(u32 position){ return m_vector.at(position); }
	const T & at(u32 position) const { return m_vector.at(position); }

	T & back(){ return m_vector.back(); }
	const T & back() const { return m_vector.back(); }

	T & front(){ return m_vector.front(); }
	const T & front() const { return m_vector.front(); }

	Vector<T> & push_back(const T & a ){
		m_vector.push_back(a);
		return *this;
	}

	Vector<T> & pop_back(){
		m_vector.pop_back();
		return *this;
	}

	Vector& shrink_to_fit(){
		m_vector.shrink_to_fit();
		return *this;
	}

	Vector& erase(
			Position position,
			Count count){
		m_vector.erase(
					m_vector.begin() + position.argument(),
					m_vector.begin() + position.argument() + count.argument()
					);
		return *this;
	}

	Vector& remove(u32 pos){
		return erase(Position(pos), Count(1));
	}



	const T & operator[](size_t offset) const { return m_vector[offset]; }
	T & operator[](size_t offset){ return m_vector[offset]; }

	/*! \details Finds an object in the array.
		*
		* @param a The equivalent object to find
		* @return The index of the object or count() it if wasn't found
		*
		*/
	size_t find(const T & a) const {
		return std::find(begin(), end(), a) - begin();
	}

	size_t find(
			const T & a,
			std::function<bool(const T & a, const T & b)> compare
			){
		for(u32 i=0; i < count(); i++){
			if( compare(this->at(i), a) ){
				return i;
			}
		}
		return count();
	}

	T * search(const T & a){
		return (T*)bsearch(
					&a,
					std::vector<T>::data(),
					count(),
					sizeof(T),
					ascending
					);
	}

	T * search(
			const T & a,
			int (*compare)(const void *, const void *)
			){
		return (T*)bsearch(
					&a,
					std::vector<T>::data(),
					count(),
					sizeof(T),
					compare
					);
	}

	/*!
		* \details Fills the vector will the specified value.
		* \param value The value to assign to each element of the vector
		*/
	Vector<T>& fill(const T & value){
		for(auto & element: m_vector){
			element = value;
		}
		return *this;
	}

	Vector<T>& resize(size_t count){
		m_vector.resize(count);
		return *this;
	}

	Vector<T>& reserve(size_t count){
		m_vector.reserve(count);
		return *this;
	}


	int free(){
		m_vector.clear();
		return 0;
	}

	static bool ascending(
			const T & a,
			const T & b
			){
		return a < b;
	}

	static bool descending(const T & a, const T & b){
		return b < a;
	}

	typedef bool (*sort_compartor_t)(const T & a, const T & b);

	void sort(sort_compartor_t compare_function){
		std::sort(begin(), end(), compare_function);
	}

	size_t size() const {
		return count() * sizeof(T);
	}



	/*! \details Returns the number of elemens in the Vector.
		*
		* The count includes the number of elements added to the vector
		* using push_back() or insert(). If the resize() method is called,
		* it will directly set the count() and ensure there is enough
		* memory available to hold count() items.
		*
		*
		*/
	u32 count() const { return m_vector.size(); }

	Vector<T> operator + (const Vector<T> & a) const {
		return operate(a, add);
	}

	Vector<T> operator - (const Vector<T> & a) const {
		return operate(a, subtract);
	}

	Vector<T> operator * (const Vector<T> & a) const {
		return operate(a, multiply);
	}

	Vector<T> operator / (const Vector<T> & a) const {
		return operate(a, divide);
	}

	Vector<T> operator + (const T & a) const {
		return operate_single(a, add);
	}

	Vector<T> operator - (const T & a) const {
		return operate_single(a, subtract);
	}

	Vector<T> operator * (const T & a) const {
		return operate_single(a, multiply);
	}

	Vector<T> operator / (const T & a) const {
		return operate_single(a, divide);
	}

	Vector<T> operator << (u32 a) const {
		Vector<T> result;
		result.resize(count());
		if( a < count() ){
			for(u32 i=0; i < count()-a; i++){
				result.at(i) = at(i+a);
			}
		}
		return result;
	}

	Vector<T> operator >> (u32 a) const {
		Vector<T> result;
		result.resize(count());
		if( a < count() ){
			for(u32 i=0; i < count()-a; i++){
				result.at(i+a) = at(i);
			}
		}
		return result;
	}

	void clear(){
		m_vector.clear();
	}

	bool is_empty() const { return m_vector.empty(); }


	std::vector<T> & vector(){ return m_vector; }
	const std::vector<T> & vector() const { return m_vector; }

	const T * data() const { return m_vector.data(); }
	T * data(){ return m_vector.data(); }

	void * to_void(){ return (void*)m_vector.data(); }
	const void * to_const_void() const { return (const void*)m_vector.data(); }

	T sum() const {
		T result;
		for(const auto & value: *this){
			result += value;
		}
		return result;
	}

	T mean() const {
		return sum() / count();
	}

	T variance() const {
		T mean = this->mean();
		T result;
		for(const auto & value: *this){
			result += (value - mean)*(value - mean);
		}
		return result / count();
	}

protected:

	Vector<T> operate(const Vector<T> & a, T (*fn)(const T &, const T &)) const {
		Vector<T> result;
		u32 c = a.count() < count() ? a.count() : count();
		for(u32 i=0; i < c; i++){
			result.push_back(fn(this->at(i), a.at(i)));
		}
		return result;
	}

	Vector<T> operate_single(const T & a, T (*fn)(const T &, const T &)) const {
		Vector<T> result;
		u32 c = count();
		for(u32 i=0; i < c; i++){
			result.push_back(fn(this->at(i), a));
		}
		return result;
	}

	static T add(const T & a, const T & b){ return a+b; }
	static T subtract(const T & a, const T & b){ return a-b; }
	static T multiply(const T & a, const T & b){ return a*b; }
	static T divide(const T & a, const T & b){ return a/b; }

	static bool compare(const Vector<T> & a, const Vector<T> & b){
		u32 i;
		if( a.count() != b.count() ){
			return false;
		}
		for(i=0; i < a.count(); i++){
			if( a[i] != b[i] ){
				return false;
			}
		}
		return true;
	}

private:

	std::vector<T> m_vector;

};

}

#endif // SAPI_VAR_VECTOR_HPP_
