#ifndef TESTS_H
#define TESTS_H

#include"gtest/gtest.h"

#include"linReg.h"

using namespace std;

TEST(constructor,empty)
{
    LinReg lin;
    EXPECT_DOUBLE_EQ(0,lin.getA());
    EXPECT_DOUBLE_EQ(0,lin.getB());
    EXPECT_DOUBLE_EQ(0,lin.getSigma());

    EXPECT_TRUE(lin.getX().empty());
    EXPECT_TRUE(lin.getY().empty());
}

TEST(constructor,invalid1)
{
    vec X = vec(10,10);
    vec Y = vec(10,10);
    EXPECT_ANY_THROW(LinReg lin(X,Y)); //"use different x-values"
}
TEST(constructor,invalid2)
{
    vec X;
    X.push_back(1);
    X.push_back(2);
    X.push_back(2.5);
    X.push_back(3);
    X.push_back(4);
    vec Y = vec(10,10);
    EXPECT_ANY_THROW(LinReg lin(X,Y)); // size mismatch
}

TEST(results,sigma2)
{
    vec X;
    X.push_back(1);
    X.push_back(2);
    X.push_back(2.5);
    X.push_back(3);
    X.push_back(4);

    vec Y;
    Y.push_back(1);
    Y.push_back(2);
    Y.push_back(2);
    Y.push_back(3);
    Y.push_back(3.5);

    LinReg lin(X,Y);

    EXPECT_EQ(X,lin.getX());
    EXPECT_EQ(Y,lin.getY());
    EXPECT_DOUBLE_EQ(0.062499999999999944, lin.getSigma());
    EXPECT_DOUBLE_EQ(0.85,lin.getB());
    EXPECT_NEAR(0.175,lin.getA(),1e-10);
}


#endif
