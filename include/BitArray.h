#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <limits>

class BitArray
{
	friend bool operator==(const BitArray& a, const BitArray& b);
	friend bool operator!=(const BitArray& a, const BitArray& b);

	friend BitArray operator&(const BitArray& b1, const BitArray& b2);
	friend BitArray operator|(const BitArray& b1, const BitArray& b2);
	friend BitArray operator^(const BitArray& b1, const BitArray& b2);

private:
	int size = 0;
	int capacity = 0;
	std::vector<unsigned long> words;

	std::vector<bool> OneToBit(const unsigned long value);
	unsigned long OneToDec(const std::vector<bool> bit);

	unsigned long MaskWithZeroRight(int countOfZero);
	unsigned long MaskWithZeroLeft(int countOfZero);

public:
	BitArray();

	~BitArray();

	explicit BitArray(int num_bits, unsigned long value = 0);

	BitArray(const BitArray& b);

	void swap(BitArray& b);

	BitArray& operator=(const BitArray& b);

	void resize(int num_bits, bool value = false);

	void clear();

	void push_back(bool bit);

	BitArray& operator&=(const BitArray& b);

	BitArray& operator|=(const BitArray& b);

	BitArray& operator^=(const BitArray& b);

	BitArray& operator<<=(int n);

	BitArray& operator>>=(int n);

	BitArray operator<<(int n) const;

	BitArray operator>>(int n) const;

	BitArray& set(int n, bool val = true); 

	BitArray& set();

	BitArray& reset(int n);

	BitArray& reset();

	bool any() const;

	bool none() const;

	BitArray operator~();

	int count();

	bool operator[](int i);

	int get_size() const;

	bool empty() const;

	std::string to_string();
};

bool operator==(const BitArray& a, const BitArray& b);

bool operator!=(const BitArray& a, const BitArray& b);

BitArray operator&(const BitArray& b1, const BitArray& b2);

BitArray operator|(const BitArray& b1, const BitArray& b2);

BitArray operator^(const BitArray& b1, const BitArray& b2);
