#include "../include/BitArray.h"
#include <gtest/gtest.h>

TEST(BitArrayTest, Throws)
{
	EXPECT_ANY_THROW(BitArray b(30, 1));

	BitArray a(61, 2147483655);
	EXPECT_ANY_THROW(a.resize(60, true));

	EXPECT_ANY_THROW(a.set(69, true));

	BitArray aa(33, 80), bb(35, 197);
	EXPECT_ANY_THROW(aa &= bb);
	EXPECT_ANY_THROW(aa |= bb);
	EXPECT_ANY_THROW(aa ^= bb);

	BitArray BB(32, 2281701381), AA(34, 2281701381);
	EXPECT_ANY_THROW(BB[34]);

	EXPECT_ANY_THROW(AA & BB);
	EXPECT_ANY_THROW(AA | BB);
	EXPECT_ANY_THROW(AA ^ BB);
}

TEST(BitArrayTest, Constructors)
{
	BitArray a, c(32, 35), d(a);
	EXPECT_EQ("", a.to_string());
	EXPECT_EQ(0, a.get_size());

	EXPECT_EQ(32, c.get_size());
	EXPECT_EQ("00000000000000000000000000100011", c.to_string());

	EXPECT_EQ(a.to_string(), d.to_string());
}

TEST(BitArrayTest, Swap)
{
	BitArray a, c(35, 234563456), b(c);

	a.swap(c);

	EXPECT_EQ(a.to_string(), b.to_string());
	EXPECT_EQ("", c.to_string());
}

TEST(BitArrayTest, ClearAndEmpty)
{
	BitArray b(55, 34564657);

	EXPECT_FALSE(b.empty());

	b.clear();
	EXPECT_EQ(0, b.get_size());
	EXPECT_EQ("", b.to_string());

	EXPECT_TRUE(b.empty());
}

TEST(BitArrayTest, Resize)
{
	BitArray e(61, 2147483655);

	e.resize(31);
	EXPECT_EQ(31, e.get_size());
	EXPECT_EQ("1000000000000000000000000000011", e.to_string());

	e.resize(34, true);
	EXPECT_EQ(34, e.get_size());
	EXPECT_EQ("1000000000000000000000000000011111", e.to_string());

	e.resize(60);
	EXPECT_EQ(60, e.get_size());
	EXPECT_EQ("100000000000000000000000000001111100000000000000000000000000", e.to_string());
}

TEST(BitArrayTest, PushBack)
{
	BitArray aa(33, 80), bb(35, 197), cc(32, 80), dd(32, 80);

	cc.push_back(true);
	dd.push_back(false);
	aa.push_back(true);

	EXPECT_EQ(33, cc.get_size());
	EXPECT_EQ(33, dd.get_size());
	EXPECT_EQ(34, aa.get_size());

	EXPECT_EQ("000000000000000000000000010100001", cc.to_string());
	EXPECT_EQ("000000000000000000000000010100000", dd.to_string());
	EXPECT_EQ("0000000000000000000000000101000001", aa.to_string());
}

// TEST(BitArrayTest, LogicOperations)
// {
// 	BitArray a(32, 3454), b(32, 1234), c(32, 6978), d(32, 675885), ss(34, 3452324);

// 	a &= b;
// 	EXPECT_EQ("00000000000000000000010001010010", a.to_string());

// 	a |= c;
// 	EXPECT_EQ("00000000000000000001111101010010", a.to_string());

// 	a ^= d;
// 	EXPECT_EQ("00000000000010100100111101111111", a.to_string());

// 	a = b & c;
// 	EXPECT_EQ("00000000000000000000000001000010", a.to_string());

// 	a = c | d;
// 	EXPECT_EQ("00000000000010100101101101101111", a.to_string());

// 	a = d ^ b;
// 	EXPECT_EQ("00000000000010100101010011111111", a.to_string());

// 	d = a;
// 	EXPECT_TRUE(a == d);
// 	EXPECT_FALSE(a == ss);
// 	EXPECT_FALSE(d == c);

// 	EXPECT_TRUE(a != c);
// 	EXPECT_TRUE(a != ss);
// 	EXPECT_FALSE(a != d);

// 	a = ~a;
// 	EXPECT_EQ("11111111111101011010101100000000", a.to_string());
// }

// TEST(BitArrayTest, BitShift)
// {
// 	BitArray aaa(32, 2281701382), bbb(32, 2281701382), aaaa(34, 2281701381);
// 	aaa.push_back(true);

// 	aaa <<= 1;
// 	EXPECT_EQ("000100000000000000000000000011010", aaa.to_string());
// 	aaa <<= 1;
// 	EXPECT_EQ("001000000000000000000000000110100", aaa.to_string());
// 	bbb <<= 1;
// 	EXPECT_EQ("00010000000000000000000000001100", bbb.to_string());

// 	aaaa >>= 1;
// 	EXPECT_EQ("0100010000000000000000000000001010", aaaa.to_string());
// 	aaaa >>= 1;
// 	EXPECT_EQ("0010001000000000000000000000000101", aaaa.to_string());
// 	aaaa >>= 1;
// 	EXPECT_EQ("0001000100000000000000000000000010", aaaa.to_string());
// 	bbb >>= 1;
// 	EXPECT_EQ("00001000000000000000000000000110", bbb.to_string());
// }

TEST(BitArrayTest, Set)
{
	BitArray aaa(32, 2281701382), bbb(35, 3546546);
	aaa.set(8);
	EXPECT_TRUE(aaa[7]);
	aaa.set(8, false);
	EXPECT_FALSE(aaa[7]);

	bbb.set();
	EXPECT_EQ("11111111111111111111111111111111111", bbb.to_string());
}

TEST(BitArrayTest, Reset)
{
	BitArray aaa(34, UINT32_MAX);

	aaa.reset(8);
	EXPECT_FALSE(aaa[7]);

	aaa.reset();
	EXPECT_EQ("0000000000000000000000000000000000", aaa.to_string());
}


TEST(BitArrayTest, ExistenceOfTrue)
{
	BitArray a(43), b(32, 432542);

	EXPECT_FALSE(b.none());
	EXPECT_FALSE(a.any());

	EXPECT_TRUE(a.none());
	EXPECT_TRUE(b.any());

	EXPECT_EQ(11, b.count());
	EXPECT_EQ(0, a.count());
}
