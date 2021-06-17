#pragma once
#ifndef _JVECTOR_
#define _JVECTOR_

#include <memory>
#include <iterator>
#include <climits>

#include "jstd_core.h"

_JSTD_BEGIN
// JVector const iterator



// JVector insert iterator


// JVector core
template<class T>
class JVector
{
public:
	using value_type             = T;
	using size_type              = std::size_t;
	using difference_type        = std::ptrdiff_t;
	using reference              = T&;
	using const_reference        = const T&;
	using iterator               = T*;
	using const_iterator         = const T*;
	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
	value_type *data_array;
	constexpr static size_type default_capacity = 10;
	size_type number_of_elements;
	size_type data_capacity;

public:
	JVector() = default;

	explicit JVector(size_type count) : number_of_elements(0), data_capacity(count) 
	{ 
		data_array = new value_type[count]; 
	}

	JVector(size_type count, const T &value) : JVector(count) 
	{ 
		data_array[count - 1] = value; 
	}

	JVector(const JVector &other) 
	{}

	JVector(JVector &&other) noexcept 
	{}

	JVector(std::initializer_list<T> init) : JVector(init.size())
	{
		for (auto &element : init)
			push_back(element);
	}

	~JVector() noexcept 
	{ 
		delete[] data_array; 
	}

	void assign(size_type count, const T &value);

	template< class InputIt >
	void assign(InputIt first, InputIt last);

	void assign(std::initializer_list<T> ilist);


	JVector &operator=(const JVector &other)
	{
		return *this;
	}

	JVector &operator=(JVector &&other) noexcept
	{
		return *this;
	}

	JVector &operator=(std::initializer_list<T> ilist)
	{
		return *this;
	}

	// Element access
	_NODISCARD reference at(size_type pos)
	{ 
		return data_array[pos]; 
	}

	_NODISCARD const_reference at(size_type pos) const 
	{ 
		return data_array[pos]; 
	}

	_NODISCARD reference operator[](size_type pos) 
	{ 
		return at(pos); 
	}

	_NODISCARD const_reference operator[](size_type pos) const
	{ 
		return at(pos); 
	}

	_NODISCARD reference front() noexcept
	{ 
		return *data_array; 
	}

	_NODISCARD reference front() const noexcept
	{ 
		return *data_array;
	}

	_NODISCARD reference back() noexcept
	{ 
		return data_array[number_of_elements - 1]; 
	}

	_NODISCARD const_reference back() const noexcept
	{ 
		return data_array[number_of_elements - 1]; 
	}

	value_type* data() noexcept 
	{ 
		return data_array; 
	}

	const value_type* data() const noexcept 
	{ 
		return data_array; 
	}

	// Iterators
	_NODISCARD iterator begin() noexcept
	{
		return data_array;
	}

	_NODISCARD const_iterator begin() const noexcept
	{
		return const_iterator(data_array);
	}

	_NODISCARD iterator end() noexcept
	{
		return data_array + number_of_elements;
	}

	_NODISCARD const_iterator end() const noexcept
	{
		return const_iterator(data_array + number_of_elements);
	}

	_NODISCARD reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(end());
	}

	_NODISCARD const_reverse_iterator rbegin() const noexcept
	{
		return const_reverse_iterator(end());
	}

	_NODISCARD reverse_iterator rend() noexcept
	{
		reverse_iterator(begin());
	}

	_NODISCARD reverse_iterator rend() const noexcept
	{
		const_reverse_iterator(begin());
	}

	_NODISCARD const_iterator cbegin() const noexcept
	{ 
		return begin(); 
	}

	_NODISCARD const_iterator cend() const noexcept
	{ 
		return end(); 
	}

	_NODISCARD const_reverse_iterator crbegin() const noexcept
	{ 
		return rbegin(); 
	}

	_NODISCARD const_reverse_iterator crend() const noexcept {
		return rend();
	}

	// Capacity
	_NODISCARD bool empty() const noexcept
	{ 
		return begin() == end(); 
	}

	_NODISCARD size_type size() const noexcept
	{ 
		return static_cast<size_type>(end() - begin());
	}

	_NODISCARD size_type max_size() const noexcept
	{ 
		return std::numeric_limits<difference_type>::max();
	}

	void reserve(size_type new_cap);

	size_type capacity() const noexcept 
	{ 
		return data_capacity; 
	}

	void shrink_to_fit()
	{

	}

	// Modifiers
	void clear() noexcept;

	iterator insert(const_iterator pos, const T &value);

	iterator insert(const_iterator pos, T &&value);

	iterator insert(const_iterator pos, size_type count, const T &value);

	template< class InputIt >
	iterator insert(const_iterator pos, InputIt first, InputIt last);

	iterator insert(const_iterator pos, std::initializer_list<T> ilist);

	template< class... Args >
	iterator emplace(const_iterator pos, Args&&... args);

	iterator erase(const_iterator pos) noexcept(std::is_nothrow_move_assignable_v<value_type>)
	{
		auto end_pos = end();
		
		return iterator(end_pos);
	}

	iterator erase(const_iterator first, const_iterator last) noexcept(std::is_nothrow_move_assignable_v<value_type>)
	{


		return;
	}

	void push_back(const T &value)
	{
		if (number_of_elements == data_capacity)
			change_data_size(data_capacity << 1);

		data_array[number_of_elements] = value;
		++number_of_elements;
	}

	void push_back(T &&value);

	template<class... Args>
	reference emplace_back(Args&&... args);

	void pop_back();

	void resize(size_type count);

	void resize(size_type count, const value_type &value);

	void swap(JVector &other) noexcept;

	// operator
	/*
	bool operator==(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator!=(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator<(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator<=(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator>(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator>=(const JVector<T> &lhs, const JVector<T> &rhs);
	*/


private:
	void change_data_size(size_type new_size)
	{
		value_type *newArray = new value_type[new_size];
		std::copy(begin(), end(), newArray);
		delete[] data_array;
		data_array = newArray;
	}

	void assign_range(iterator first, iterator last)
	{

	}

};
_JSTD_END
#endif // !_JVECTOR_