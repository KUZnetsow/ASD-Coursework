#include "pch.h"
#include "CppUnitTest.h"
#include "..\\TermWork\graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(Test)
	{
	public:
		graph test;
		TEST_METHOD(Test1)
		{
			fstream in("D:\\TermWork\\TermWork\\in.txt");
			test.inputVertex(in);
			in.open("D:\\TermWork\\TermWork\\in.txt");
			test.inputEdge(in);
			Assert::AreEqual(test.MaxFlow(), 5);
		}

		TEST_METHOD(Test2)
		{
			fstream in("D:\\TermWork\\TermWork\\test1.txt");
			test.inputVertex(in);
			in.open("D:\\TermWork\\TermWork\\test1.txt");
			test.inputEdge(in);
			Assert::AreEqual(test.MaxFlow(), 7);
		}

		TEST_METHOD(Test3)
		{
			fstream in("D:\\TermWork\\TermWork\\test2.txt");
			test.inputVertex(in);
			in.open("D:\\TermWork\\TermWork\\test2.txt");
			test.inputEdge(in);
			Assert::AreEqual(test.MaxFlow(), 9);
		}
	};
}