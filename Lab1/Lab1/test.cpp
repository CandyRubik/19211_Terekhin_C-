#include "gtest/gtest.h"
#include "Trit_set.h"

TEST(TernarySystemTest, CapacityTest) { // This test testing method .size()
	for (int i = 0; i < 1000; i++)
	{
		Trit_set setA(i);
		ASSERT_EQ(setA.size(), i);
	}
}

TEST(TernarySystemTest, SwapTest) { // This test testing method .swap()
	Trit_set setA(6);
	Trit_set setB(10);
	setA[5] = Trit_value::TRUE;
	setA.swap(setB);
	ASSERT_EQ(setA.size(), 10);
	ASSERT_EQ(setA[5].get_value(), Trit_value::UNKNOWN);
}

TEST(TernarySystemTest, EquallyOperatorOfObjectTest) { // This test testing method .operator=
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			Trit_set setA(i);
			for (size_t k = 0; k < setA.size(); k++)
				setA[i] = Trit_value::TRUE;
			Trit_set setB(i + j);
			setB = setA;
			ASSERT_EQ(setB.size(), setA.size());
			for (size_t k = 0; k < setA.size(); k++)
			{
				ASSERT_EQ(setB[k].get_value(), setA[k].get_value());
			}
		}
	}
	Trit_set setA(5);
	setA[10] = Trit_value::TRUE;
	ASSERT_EQ(setA.size(), 11);
	ASSERT_EQ(setA[10].get_value(), Trit_value::TRUE);
}

TEST(TernarySystemTest, GetTritOperatorTest) // This test testing method .operator[]
{
	for (int j = 4; j < 31; j++)
	{
		Trit_set setA(j);
		for (int i = 0; i < j; i++)
		{
			int value = i % 3;
			switch (value)
			{
			case 0:
				setA[i] = Trit_value::UNKNOWN;
				break;
			case 1:
				setA[i] = Trit_value::TRUE;
				break;
			case 2:
				setA[i] = Trit_value::FALSE;
				break;
			}
		}
		for (int i = 0; i < j; i++)
		{
			int value = i % 3;
			switch (value)
			{
			case 0:
				ASSERT_EQ(setA[i].get_value(), Trit_value::UNKNOWN);
				break;
			case 1:
				ASSERT_EQ(setA[i].get_value(), Trit_value::TRUE);
				break;
			case 2:
				ASSERT_EQ(setA[i].get_value(), Trit_value::FALSE);
				break;
			}
		}
	}
}

TEST(TernarySystemTest, ShrinkTest) // this test testig mehod .shrink()
{
	for (int i = 0; i < 40; i++)
	{
		Trit_set setA(i);
		setA[i + 4] = Trit_value::TRUE;
		setA.shrink();
		ASSERT_EQ(setA.size(), i + 4 + 1);
		setA[i + 4] = Trit_value::UNKNOWN;
		setA.shrink();
		ASSERT_EQ(setA.size(), i);
	}
}

TEST(TernarySystemTest, LengthTest) // this test testing method .length 
{
	Trit_set setA(100);
	for (int i = 0; i < setA.size(); i++)
	{
		setA[i] = Trit_value::TRUE;
		ASSERT_EQ(setA.length(), i + 1);
	}
}

TEST(TernarySystemTest, TrimTest) // this test testing mtehod .trim()
{	
	for (int i = 10; i < 1000; i++)
	{
		Trit_set setA(i);
		setA.trim(i - 10);
		ASSERT_EQ(setA.size(), i - 9);
	}
}

TEST(TernarySystemTest, CardinalityTest) // this test testing method .cardinality()
{
	Trit_set setA(100);
	for (int i = 0; i < 100; i++)
	{
		setA[i] = Trit_value::FALSE;
		ASSERT_EQ(setA.cardinality(Trit_value::FALSE), i + 1);
	}
}

TEST(TernarySystemTest, CardinalityMapTest) // this test testing method .cardinality()(unordered map)
{
	Trit_set setA(100);
	for (int i = 0; i < 3; i++)
	{
		setA[i] = Trit_value::FALSE;
	}
	for (int i = 3; i < 6; i++)
	{
		setA[i] = Trit_value::TRUE;
	}
	for (int i = 6; i < 9; i++)
	{
		setA[i] = Trit_value::UNKNOWN;
	}
	std::unordered_map<Trit_value, size_t> map = setA.cardinality();
	ASSERT_EQ(map.at(Trit_value::TRUE), 3);
	ASSERT_EQ(map.at(Trit_value::FALSE), 3);
	ASSERT_EQ(map.at(Trit_value::UNKNOWN), 0);
}

TEST(TernarySystemTest, UnarNotOperatorTest) // this test testing metod .operator!
{
	Trit_set setB(3);
	setB[0] = Trit_value::TRUE;
	setB[1] = Trit_value::UNKNOWN;
	setB[2] = Trit_value::FALSE;
	Trit_set setA = !setB;
	ASSERT_EQ(setA[0].get_value(), Trit_value::FALSE);
	ASSERT_EQ(setA[1].get_value(), Trit_value::UNKNOWN);
	ASSERT_EQ(setA[2].get_value(), Trit_value::TRUE);
}

TEST(TernarySystemTest, BinaryAndOperatorTest) // this test testing metod .operator&
{
	Trit_set setA(3);
	setA[0] = Trit_value::TRUE;
	setA[1] = Trit_value::FALSE;
	setA[2] = Trit_value::FALSE;
	Trit_set setB(6);
	setB[0] = Trit_value::TRUE;
	setB[1] = Trit_value::UNKNOWN;
	setB[2] = Trit_value::FALSE;
	setB[3] = Trit_value::TRUE;
	setB[4] = Trit_value::TRUE;
	setB[5] = Trit_value::FALSE;
	Trit_set setC = setA & setB;
	ASSERT_EQ(setC.size(), 6);
	ASSERT_EQ(setC[0].get_value(), Trit_value::TRUE);
	ASSERT_EQ(setC[1].get_value(), Trit_value::FALSE);
	ASSERT_EQ(setC[2].get_value(), Trit_value::FALSE);
	ASSERT_EQ(setC[3].get_value(), Trit_value::UNKNOWN);
	ASSERT_EQ(setC[4].get_value(), Trit_value::UNKNOWN);
	ASSERT_EQ(setC[5].get_value(), Trit_value::FALSE);
}

TEST(TernarySystemTest, BinaryOrOperatorTest) // this test testing metod .operator|
{
	Trit_set setA(3);
	setA[0] = Trit_value::TRUE;
	setA[1] = Trit_value::FALSE;
	setA[2] = Trit_value::TRUE;
	Trit_set setB(6);
	setB[0] = Trit_value::TRUE;
	setB[1] = Trit_value::UNKNOWN;
	setB[2] = Trit_value::FALSE;
	setB[3] = Trit_value::TRUE;
	setB[4] = Trit_value::TRUE;
	setB[5] = Trit_value::FALSE;
	Trit_set setC = setA | setB;
	ASSERT_EQ(setC.size(), 6);
	ASSERT_EQ(setC[0].get_value(), Trit_value::TRUE);
	ASSERT_EQ(setC[1].get_value(), Trit_value::UNKNOWN);
	ASSERT_EQ(setC[2].get_value(), Trit_value::TRUE);
	ASSERT_EQ(setC[3].get_value(), Trit_value::TRUE);
	ASSERT_EQ(setC[4].get_value(), Trit_value::TRUE);
	ASSERT_EQ(setC[5].get_value(), Trit_value::UNKNOWN);
}