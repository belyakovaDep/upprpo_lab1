#include "../include/BitArray.h"
#include <algorithm>

	std::vector<bool> BitArray::OneToBit(const unsigned long value)
	{
		std::vector<bool> result;
		result.resize(32);
		unsigned long copy = value;

		for (int i = 0; copy != 0; i++)
		{
			result[31 - i] = ((copy % 2) == 1);
			copy /= 2;
		}

		return result;
	}

	unsigned long BitArray::OneToDec(const std::vector<bool> bit)
	{
		unsigned long result = 0;

		for (int i = 0; i < 31; i++)
		{
			result += pow(2, i) * bit[31 - i];
		}
		return result;
	}

	unsigned long BitArray::MaskWithZeroRight(int countOfZero) {
		if (countOfZero % 32 == 0) return 0;
		return (UINT32_MAX << countOfZero);
	}

	unsigned long BitArray::MaskWithZeroLeft(int countOfZero) {
		if (countOfZero % 32 == 0) return 0;
		return (UINT32_MAX >> countOfZero);
	}

	BitArray::BitArray() = default;
	BitArray::~BitArray() = default;

	BitArray::BitArray(int num_bits, unsigned long value)
	{
		if (num_bits < 32 && value != 0)
		{
			throw std::invalid_argument("Cannot array: the size is too small");
		}

		else
		{
			words.resize((num_bits + 32 - 1) / 32);
			words[0] = value;
			size = num_bits;
			capacity = words.size();
		}
	}

	BitArray::BitArray(const BitArray& b)
	{
		words.resize(b.words.size());
		words = b.words;
		size = b.size;
		capacity = b.capacity;
	}

	void BitArray::swap(BitArray& b)
	{
		std::swap(words, b.words);
		std::swap(size, b.size);
		std::swap(capacity, b.capacity);
	}

	BitArray& BitArray::operator=(const BitArray& b)
	{
		words = std::move(b.words);
		capacity = std::move(b.capacity);
		size = std::move(b.size);
		return *this;
	}

	void BitArray::resize(int num_bits, bool value)
	{
		if (num_bits <= size && value == true) throw std::invalid_argument("You cannot write a new value into the reduced BitArray");

		else if (num_bits <= size)
		{
			//replace the reference
			for (int i = 0; i < capacity - ((num_bits + 32 - 1)/32); i++)
			{
				words.pop_back();
			}

			if (num_bits % 32 != 0) words.back() &= MaskWithZeroRight(32 - (num_bits % 32));
			
			capacity = words.size();
			size = num_bits;
		}

		else if (num_bits > size && value == true)
		{
			words.back() |= MaskWithZeroLeft(size);

			words.resize((num_bits + 32 - 1) / 32);

			for (int i = 0; i < words.size() - capacity; i++)
			{
				words[capacity + i] = UINT32_MAX;
			}

			capacity = words.size();
			size = num_bits;

			if (num_bits % 32 != 0) words.back() &= MaskWithZeroRight(capacity*32 - size);
		}

		else if (num_bits > size && value == false)
		{
			words.resize((num_bits + 32 - 1) / 32);
			capacity = words.size();
			size = num_bits;
		}
	}

	void BitArray::clear()
	{
		words.clear();
		capacity = 0;
		size = 0;
	}

	void BitArray::push_back(bool bit)
	{
		if (capacity*32 > size && bit)
		{
			int number_of_bit = size % 32 + 1;
			words[size / 32] |= (MaskWithZeroRight(32 - number_of_bit) & MaskWithZeroLeft(number_of_bit - 1));
		}

		else if (capacity*32 == size && bit)
		{
			words.push_back(0);
			words.back() |= MaskWithZeroRight(31);
			capacity++;
		}

		else if (capacity*32 == size && !bit)
		{
			words.push_back(0);
			capacity++;
		}
		size++;
	}

	BitArray& BitArray::operator&=(const BitArray& b)
	{
		if (size != b.size) throw std::length_error("BitArrays are not the same sizes");

		for (int i = 0; i < capacity; i++)
		{
			words[i] &= b.words[i];
		}
		return *this;
	}

	BitArray& BitArray::operator|=(const BitArray& b)
	{
		if (size != b.size) throw std::length_error("BitArrays are not the same sizes");

		for (int i = 0; i < capacity; i++)
		{
			words[i] |= b.words[i];
		}
		return *this;
	}

	BitArray& BitArray::operator^=(const BitArray& b)
	{
		if (size != b.size) throw std::length_error("BitArrays are not the same sizes");

		for (int i = 0; i < capacity; i++)
		{
			words[i] ^= b.words[i];
		}
		return *this;
	}

	BitArray& BitArray::operator<<=(int n)
	{
		for (int j = 0; j < n; j++) 
		{
			for (int i = 0; i < capacity - 1; i++)
			{
				words[i] <<= 1;
				if ((words[i + 1] & MaskWithZeroRight(31)) != 0) words[i] |= MaskWithZeroLeft(31);
			}
			words.back() <<= 1;
		}
		return *this;
	}

	BitArray& BitArray::operator>>=(int n)
	{
		for (int j = 0; j < n; j++)
		{
			for (int i = 1; i < capacity; i++)
			{
				words[i] >>= 1;
				if ((words[i - 1] & MaskWithZeroLeft(31)) != 0) words[i] |= MaskWithZeroRight(31);
			}
			words[0] >>= 1;
		}

		if(size%32 != 0) words.back() &= MaskWithZeroRight(capacity * 32 - size);
		return *this;
	}

	BitArray BitArray::operator<<(int n) const
	{
		BitArray newOne(*this);
		newOne<<=n;
		return newOne;
	}

	BitArray BitArray::operator>>(int n) const
	{
		BitArray newOne(*this);
		newOne >>= n;
		return newOne;
	}

	BitArray& BitArray::set(int n, bool val)
	{
		if (n > size || n < 0) throw std::out_of_range("The index is out of range");
		unsigned long mask;

		if (val)
		{
			mask = (MaskWithZeroLeft(n - 1)) & (MaskWithZeroRight(32 - n));
			words[n / 32] |= mask;
		}

		else
		{
			mask = ((MaskWithZeroLeft(n)) | (MaskWithZeroRight(32 - n + 1)));
			words[n / 32] &= mask;
		}

		return *this;
	}

	BitArray& BitArray::set()
	{
		for (int i = 0; i < size / 32; i++)
		{
			words[i] = UINT32_MAX;
		}

		if(size % 32 != 0) words.back() = MaskWithZeroRight(32 - size % 32);
		
		return *this;
	}

	BitArray& BitArray::reset(int n)
	{
		this->set(n, false);
		return *this;
	}

	BitArray& BitArray::reset()
	{
		for (int i = 0; i < capacity; i++)
		{
			words[i] = 0;
		}
		return *this;
	}

	bool BitArray::any() const
	{
		for (int i = 0; i < capacity; i++)
		{
			if (words[i] != 0) return true;
		}

		return false;
	}

	bool BitArray::none() const
	{
		for (int i = 0; i < capacity; i++)
		{
			if (words[i] != 0) return false;
		}

		return true;
	}

	BitArray BitArray::operator~()
	{
		BitArray newOne(*this);

		for (int i = 0; i < capacity; i++)
		{
			newOne.words[i] = ~newOne.words[i];
		}
		if(size % 32 != 0) newOne.words.back() &= MaskWithZeroRight(newOne.capacity*32 - newOne.size);

		return newOne;
	}

	int BitArray::count()
	{
		int count = 0;
		for (int i = 0; i < capacity; i++)
		{
			std::vector<bool> bit = this->OneToBit(words[i]);
			count += std::count(bit.begin(), bit.end(), true);
		}

		return count;
	}

	bool BitArray::operator[](int i)
	{
		if (i >= size) throw std::out_of_range("The index is out of range");

		std::vector<bool> array = this->OneToBit(words[i / 32]);

		return array[i % 32];
	}

	int BitArray::get_size() const
	{
		return size;
	}

	bool BitArray::empty() const
	{
		if (size == 0) return true;
		return false;
	}

	std::string BitArray::to_string()
	{
		if (size == 0) return "";

		std::string bitwise = "";
		for (int i = 0; i < size/32; i++)
		{
			std::vector<bool> interimBit = this->OneToBit(words[i]);
			for (int j = 0; j < 32; j++)
			{
				if (interimBit[j]) bitwise += '1';
				else bitwise += '0';
			}
		}

		std::vector<bool> interimBit = this->OneToBit(words.back());

		for (int j = 0; j < size % 32; j++)
		{
			if (interimBit[j]) bitwise += '1';
			else bitwise += '0';
		}

		return bitwise;
	}
//'except' can pe placed next to functions which dont have to use throws
bool operator==(const BitArray& a, const BitArray& b)
{
	if (a.size != b.size) return false;

	for (int i = 0; i < (a.size + 32 - 1) / 32; i++)
	{
		if (a.words[i] != b.words[i]) return false;
	}

	return true;
}

bool operator!=(const BitArray& a, const BitArray& b)
{
	if (a.size != b.size) return true;

	for (int i = 0; i < a.capacity; i++)
	{
		if (a.words[i] != b.words[i]) return true;
	}

	return false;
}

BitArray operator&(const BitArray& b1, const BitArray& b2)
{
	if (b1.size != b2.size) throw std::length_error("BitArrays are not the same sizes");

	BitArray newOne(b1);

	for (int i = 0; i < b1.capacity; i++)
	{
		newOne.words[i] &= b2.words[i];
	}

	return newOne;
}

BitArray operator|(const BitArray& b1, const BitArray& b2)
{
	if (b1.size != b2.size) throw std::length_error("BitArrays are not the same sizes");

	BitArray newOne(b1);

	for (int i = 0; i < b1.capacity; i++)
	{
		newOne.words[i] |= b2.words[i];
	}

	return newOne;
}

BitArray operator^(const BitArray& b1, const BitArray& b2)
{
	if (b1.size != b2.size) throw std::length_error("BitArrays are not the same sizes");

	BitArray newOne(b1);

	for (int i = 0; i < b1.capacity; i++)
	{
		newOne.words[i] ^= b2.words[i];
	}

	return newOne;
}
