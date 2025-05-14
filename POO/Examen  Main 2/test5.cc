#include "computer2.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>
using namespace std;

TEST(Computer2, Extractor)
{
	Computer c("Computer1","PIV");
	cout << c;
}

TEST(Computer2, Insertador)
{
	Computer c("","");
	cin >> c;
}