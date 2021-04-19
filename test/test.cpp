#include "gtest/gtest.h"
#include <cstring>
#include "aux_functions.h"
#define _USE_MATH_DEFINES
#include "math.h"

extern "C"
{
#include <time.h>
#include <stdlib.h>
}

#define tolerance 1e-6
const char* const cart = "cart";
const char* const pol = "pol";
const char* const add = "add";
const char* const sub = "sub";
const char* const mul = "mul";
const char* const dvs = "dvs";
TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
    srand((unsigned int)time(NULL));
}

TEST(SomaCartesiana, ZeroInputsCheckReturnValue) {
    Cart x = { 0.0, 0.0 };
    Cart x_expected = { 0.0, 0.0 };
    Cart y = { 0.0, 0.0 };

    unsigned ret = somacartesiana(&x, y);

    ASSERT_EQ(0, ret);
}

TEST(SomaCartesiana, ZeroInputsCheckX) {
    Cart x = { 0.0, 0.0 };
    Cart x_expected = { 0.0, 0.0 };
    Cart y = { 0.0, 0.0 };

    unsigned ret = somacartesiana(&x, y);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(SomaCartesiana, xRealPartZeroyRealPartNonZeroCheckX) {
    Cart x = { 0.0, 0.0 };
    Cart y = { 1.1, 0.0 };
    Cart x_expected = { 1.1, 0.0 };

    unsigned ret = somacartesiana(&x, y);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(SomaCartesiana, xImaginaryPartZeroyImaginaryPartNonZeroCheckX) {
    Cart x = { 0.0, 0.0 };
    Cart y = { 0.0, 1.7 };
    Cart x_expected = { 0.0, 1.7 };

    unsigned ret = somacartesiana(&x, y);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(SomaCartesiana, xRandomyRandomCheckX) {
    Cart x = { 0.0001 * (double)rand(), 0.0001 * (double)rand() };
    Cart y = { 0.0001 * (double)rand(), 0.0001 * (double)rand() };
    Cart x_expected{ x.a + y.a, x.b + y.b };

    unsigned ret = somacartesiana(&x, y);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Cartesian2Polar, ZeroInputCheckReturnValue) {
    Cart x = { 0.0, 0.0 };
    Pol w_expected = { 0.0, 0.0 };
    Pol w;

    unsigned ret = cartesian2polar(&w, x);

    ASSERT_EQ(0, ret);
}

TEST(Cartesian2Polar, ZeroInputCheckOutputW) {
    Cart x = { 0.0, 0.0 };
    Pol w_expected = { 0.0, 0.0 };
    Pol w;

    cartesian2polar(&w, x);

    ASSERT_TRUE(PolNear(w_expected, w, tolerance));
}

TEST(Cartesian2Polar, ZeroPiInputCheckOutputW) {
    Cart x = { 2.25, 0.0 };
    Pol w_expected = { 2.25, 0.0 };
    Pol w;

    cartesian2polar(&w, x);

    ASSERT_TRUE(PolNear(w_expected, w, tolerance));
}
TEST(Cartesian2Polar, PiOverTwoInputCheckOutputW) {
    Cart x = { 0.0, 1.5 };
    Pol w_expected = { 1.5, M_PI_2 };
    Pol w;

    cartesian2polar(&w, x);

    ASSERT_TRUE(PolNear(w_expected, w, tolerance));
}

TEST(Cartesian2Polar, PiInputCheckOutputW) {
    Cart x = { -1.33, 0.0 };
    Pol w_expected = { 1.33, M_PI };
    Pol w;

    cartesian2polar(&w, x);

    ASSERT_TRUE(PolNear(w_expected, w, tolerance));
}

TEST(Cartesian2Polar, MinusPiOverTwoInputCheckOutputW) {
    Cart x = { 0, -1.337 };
    Pol w_expected = { 1.337, -M_PI_2 };
    Pol w;

    cartesian2polar(&w, x);

    ASSERT_TRUE(PolNear(w_expected, w, tolerance));
}

TEST(Cartesian2Polar, FirstQuadrantInputCheckOutputW) {
    Cart x = { 1.01324972243, 0.585 };
    Pol w_expected = { 1.17, M_PI / 6 };
    Pol w;

    cartesian2polar(&w, x);

    ASSERT_TRUE(PolNear(w_expected, w, tolerance));
}

TEST(Cartesian2Polar, SecondQuadrantInputCheckOutputW) {
    Cart x = { -6.685, 11.5787596486 };
    Pol w_expected = { 13.37, 2 * M_PI / 3 };
    Pol w;

    cartesian2polar(&w, x);

    ASSERT_TRUE(PolNear(w_expected, w, tolerance));
}

TEST(Cartesian2Polar, ThirdQuadrantInputCheckOutputW) {
    Cart x = { -6.685, -11.5787596486 };
    Pol w_expected = { 13.37, -2 * M_PI / 3 };
    Pol w;

    cartesian2polar(&w, x);

    ASSERT_TRUE(PolNear(w_expected, w, tolerance));
}

TEST(Cartesian2Polar, FourthQuadrantInputCheckOutputW) {
    Cart x = { 1.01324972243, -0.585 };
    Pol w_expected = { 1.17, -M_PI / 6 };
    Pol w;

    cartesian2polar(&w, x);

    ASSERT_TRUE(PolNear(w_expected, w, tolerance));
}

TEST(MultiplyPolar, ZeroInputsCheckReturnValue) {
    Pol x = { 0.0, 0.0 };
    Pol x_expected = { 0.0, 0.0 };
    Pol y = { 0.0, 0.0 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, FirstInputZeroCheckOutputX) {
    Pol x = { 0.0, 0.0 };
    Pol x_expected = { 0.0, 0.0 };
    Pol y = { 2.2, M_PI_2 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, FirstInputZeroModuleNonZeroAngleCheckOutputX) {
    Pol x = { 0.0, M_PI_4 };
    Pol x_expected = { 0.0, 0.0 };
    Pol y = { 2.2, M_PI_2 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, FirstInputModuleHasInfinityCheckOutputX) {
    Pol x = { INFINITY, M_PI_4 };
    Pol y = { 2.2, M_PI_2 };
    Pol x_expected = { INFINITY, 3 * M_PI_4 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, FirstInputModuleHasInfinityCheckReturnValue) {
    Pol x = { INFINITY, M_PI_4 };
    Pol y = { 2.2, M_PI_2 };
    Pol x_expected = { INFINITY, 3 * M_PI_4 };

    unsigned ret = multiplypolar(&x, y);

    ASSERT_EQ(2, ret);
}

TEST(MultiplyPolar, SecondInputModuleHasInfinityCheckOutputX) {
    Pol x = { 1.33, M_PI_4 };
    Pol y = { INFINITY, M_PI_4 };
    Pol x_expected = { INFINITY, M_PI_2 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, SecondInputModuleHasInfinityCheckReturnValue) {
    Pol x = { 1.33, M_PI_4 };
    Pol y = { INFINITY, M_PI_4 };
    Pol x_expected = { INFINITY, M_PI_2 };

    unsigned ret = multiplypolar(&x, y);

    ASSERT_EQ(2, ret);
}

TEST(MultiplyPolar, FirstInputModuleZeroSecondInputModuleHasInfinityCheckOutputX) {
    Pol x = { 0.0, M_PI_4 };
    Pol y = { INFINITY, M_PI_4 };
    Pol x_expected = { 0.0, 0.0 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, FirstInputModuleSecondInputModuleHasInfinityCheckReturnValue) {
    Pol x = { 0.0, M_PI_4 };
    Pol y = { INFINITY, M_PI_4 };
    Pol x_expected = { 0.0, 0.0 };

    unsigned ret = multiplypolar(&x, y);

    ASSERT_EQ(0, ret);
}

TEST(MultiplyPolar, FirstInputModuleHasInfinitySecondInputZeroCheckOutputX) {
    Pol x = { INFINITY, M_PI_4 };
    Pol y = { 0.0, M_PI_2 };
    Pol x_expected = { 0.0, 0.0 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, FirstInputModuleHasInfinitySecondInputZeroCheckReturnValue) {
    Pol x = { INFINITY, M_PI_4 };
    Pol y = { 0.0, M_PI_2 };
    Pol x_expected = { 0.0, 0.0 };

    unsigned ret = multiplypolar(&x, y);

    ASSERT_EQ(0, ret);
}

TEST(MultiplyPolar, BothInputsHasInfinityCheckOutputX) {
    Pol x = { INFINITY, M_PI_4 };
    Pol y = { INFINITY, M_PI_2 };
    Pol x_expected = { INFINITY, 3 * M_PI_4 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, BothInputsHasInfinityCheckReturnValue) {
    Pol x = { INFINITY, M_PI_4 };
    Pol y = { INFINITY, M_PI_2 };
    Pol x_expected = { INFINITY, 3 * M_PI_4 };

    unsigned ret = multiplypolar(&x, y);

    ASSERT_EQ(2, ret);
}

TEST(MultiplyPolar, BothInputsAreHugeCheckOutputX) {
    Pol x = { _HUGE_ENUF, M_PI_4 };
    Pol y = { _HUGE_ENUF, M_PI_2 };
    Pol x_expected = { INFINITY, 3 * M_PI_4 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, BothInputsAreHugeCheckReturnValue) {
    Pol x = { _HUGE_ENUF, M_PI_4 };
    Pol y = { _HUGE_ENUF, M_PI_2 };
    Pol x_expected = { INFINITY, 3 * M_PI_4 };

    unsigned ret = multiplypolar(&x, y);

    ASSERT_EQ(2, ret);
}

TEST(MultiplyPolar, FirstInputModuleHugeCheckOutputX) {
    Pol x = { _HUGE_ENUF, M_PI_4 };
    Pol y = { 2.2, M_PI_2 };
    Pol x_expected = { _HUGE_ENUF * 2.2, 3 * M_PI_4 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, FirstInputModuleHugeCheckReturnValue) {
    Pol x = { _HUGE_ENUF, M_PI_4 };
    Pol y = { 2.2, M_PI_2 };
    Pol x_expected = { _HUGE_ENUF * 2.2, 3 * M_PI_4 };

    unsigned ret = multiplypolar(&x, y);

    ASSERT_EQ(0, ret);
}

TEST(MultiplyPolar, SecondInputModuleHugeCheckOutputX) {
    Pol x = { 13.37, M_PI_2 };
    Pol y = { _HUGE_ENUF, M_PI_2 };
    Pol x_expected = { _HUGE_ENUF * 13.37, M_PI };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, SecondInputModuleHugeCheckReturnValue) {
    Pol x = { 13.37, M_PI_2 };
    Pol y = { _HUGE_ENUF, M_PI_2 };
    Pol x_expected = { _HUGE_ENUF * 13.37, -M_PI };

    unsigned ret = multiplypolar(&x, y);

    ASSERT_EQ(0, ret);
}

TEST(MultiplyPolar, Positive13PIresultangleCheckReturnValue) {
    Pol x = { 1.1, 12 * M_PI };
    Pol y = { 1.0, M_PI };
    Pol x_expected = { 1.1, M_PI };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, Negative13PIresultangleCheckReturnValue) {
    Pol x = { 1.1, -12 * M_PI };
    Pol y = { 1.0, -M_PI };
    Pol x_expected = { 1.1, M_PI };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, Positive12PIresultangleCheckReturnValue) {
    Pol x = { 1.1, 13 * M_PI };
    Pol y = { 1.0, -M_PI };
    Pol x_expected = { 1.1, 0.0 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, Negative12PIresultangleCheckReturnValue) {
    Pol x = { 1.1, -13 * M_PI };
    Pol y = { 1.0, M_PI };
    Pol x_expected = { 1.1, 0.0 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, SecondQuadrantCheckOutput) {
    Pol x = { 1.1, 13 * M_PI };
    Pol y = { 1.0, -M_PI_4 };
    Pol x_expected = { 1.1, 3 * M_PI_4 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, FourthQuadrantCheckOutput) {
    Pol x = { 1.1, 12 * M_PI };
    Pol y = { 1.0, -M_PI_4 };
    Pol x_expected = { 1.1, -M_PI_4 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, FirstQuadrantCheckOutput) {
    Pol x = { 1.1, 11 * M_PI };
    Pol y = { 1.0, 5 * M_PI_4 };
    Pol x_expected = { 1.1, M_PI_4 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, NinetyDegreeResultCheckOutput) {
    Pol x = { 1.1, 11 * M_PI };
    Pol y = { 1.0, -M_PI_2 };
    Pol x_expected = { 1.1, M_PI_2 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(MultiplyPolar, MinusNinetyDegreeResultCheckOutput) {
    Pol x = { 1.1, 11 * M_PI };
    Pol y = { 1.0, -3 * M_PI_2 };
    Pol x_expected = { 1.1, -M_PI_2 };

    multiplypolar(&x, y);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(NormalizeAngle, FirstHemisphereAngleCheckOutput) {
    Pol x = { 1.1, 7 * M_PI / 8 };
    Pol x_expected = { 1.1, 7 * M_PI / 8 };

    normalizeangle(&x);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(NormalizeAngle, SecondHemisphereAngleCheckOutput) {
    Pol x = { 1.1, 9 * M_PI / 8 };
    Pol x_expected = { 1.1, -7 * M_PI / 8 };

    normalizeangle(&x);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(NormalizeAngle, FirstHemisphereNegAngleCheckOutput) {
    Pol x = { 1.1, -9 * M_PI / 8 };
    Pol x_expected = { 1.1, 7 * M_PI / 8 };

    normalizeangle(&x);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(NormalizeAngle, SecondHemisphereNegAngleCheckOutput) {
    Pol x = { 1.1, -7 * M_PI / 8 };
    Pol x_expected = { 1.1, -7 * M_PI / 8 };

    normalizeangle(&x);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(NormalizeAngle, CincoPI_2InputAngleCheckOutput) {
    Pol x = { 1.1, 5 * M_PI / 2 };
    Pol x_expected = { 1.1, M_PI_2 };

    normalizeangle(&x);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(NormalizeAngle, SetePI_2InputAngleCheckOutput) {
    Pol x = { 1.1, 7 * M_PI / 2 };
    Pol x_expected = { 1.1, -M_PI_2 };

    normalizeangle(&x);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(NormalizeAngle, PiInputAngleCheckOutput) {
    Pol x = { 1.1, M_PI };
    Pol x_expected = { 1.1, M_PI };

    normalizeangle(&x);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(NormalizeAngle, T13PiInputAngleCheckOutput) {
    Pol x = { 1.1, 13 * M_PI };
    Pol x_expected = { 1.1, M_PI };

    normalizeangle(&x);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(NormalizeAngle, T26PiInputAngleCheckOutput) {
    Pol x = { 1.1, 26 * M_PI };
    Pol x_expected = { 1.1, 0.0 };

    normalizeangle(&x);

    ASSERT_TRUE(PolNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, InfinityNormCheckReturnValue) {
    Pol w = { INFINITY, 0.0 };
    Cart x;
    Cart x_expected = { INFINITY, 0 };

    unsigned ret = polar2cartesian(&x, w);

    ASSERT_EQ(2, ret);
}

TEST(Polar2Cartesian, InfinityAngleCheckReturnValue) {
    Pol w = { sqrt(2), INFINITY };
    Cart x;
    Cart x_expected = { INFINITY, INFINITY };

    unsigned ret = polar2cartesian(&x, w);

    ASSERT_EQ(2, ret);
}

TEST(Polar2Cartesian, ZeroNormInfinityAngleCheckReturnValue) {
    Pol w = { 0.0, INFINITY };
    Cart x;
    Cart x_expected = { 0, 0 };

    unsigned ret = polar2cartesian(&x, w);

    ASSERT_EQ(0, ret);
}


TEST(Polar2Cartesian, NonInfinityAngleCheckReturnValue) {
    Pol w = { sqrt(2), _HUGE_ENUF };
    Cart x;
    Cart x_expected = { 0.9979, 0.0648 };

    unsigned ret = polar2cartesian(&x, w);

    ASSERT_EQ(0, ret);
}

TEST(Polar2Cartesian, NonInfinityNormCheckReturnValue) {
    Pol w = { _HUGE_ENUF, 0.0 };
    Cart x;
    Cart x_expected = { _HUGE_ENUF, 0.0 };

    unsigned ret = polar2cartesian(&x, w);

    ASSERT_EQ(0, ret);
}


TEST(Polar2Cartesian, ZeroAngleInputCheckCoordenatesOutput) {
    Pol w = { sqrt(2), 0.0 };
    Cart x;
    Cart x_expected = { sqrt(2), 0.0 };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, Pi_4AngleInputCheckCoordenatesOutput) {
    Pol w = { sqrt(2), M_PI / 4 };
    Cart x;
    Cart x_expected = { 1.0, 1.0 };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, Pi_2AngleInputCheckCoordenatesOutput) {
    Pol w = { sqrt(2), M_PI_2 };
    Cart x;
    Cart x_expected = { 0.0, sqrt(2) };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, T3Pi_4AngleInputCheckCoordenatesOutput) {
    Pol w = { sqrt(2), 3 * M_PI_4 };
    Cart x;
    Cart x_expected = { -1.0, 1.0 };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, PiAngleInputCheckCoordenatesOutput) {
    Pol w = { sqrt(2), M_PI };
    Cart x;
    Cart x_expected = { -sqrt(2), 0.0 };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, C5Pi_4AngleInputCheckCoordenatesOutput) {
    Pol w = { sqrt(2), 5 * M_PI_4 };
    Cart x;
    Cart x_expected = { -1.0, -1.0 };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, T3Pi_2AngleInputCheckCoordenatesOutput) {
    Pol w = { sqrt(2), 3 * M_PI_2 };
    Cart x;
    Cart x_expected = { 0.0, -sqrt(2) };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, S7Pi_4AngleInputCheckCoordenatesOutput) {
    Pol w = { sqrt(2), 7 * M_PI_4 };
    Cart x;
    Cart x_expected = { 1.0, -1.0 };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, NonInfinityAngleCheckCoordenatesOutput) {
    Pol w = { sqrt(2), 10000 };
    Cart x;
    Cart x_expected = { -1.346551035, -0.432204014 };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, NonInfinityNormCheckCoordenatesOutput) {
    Pol w = { _HUGE_ENUF, 0.0 };
    Cart x;
    Cart x_expected = { _HUGE_ENUF, 0.0 };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(Polar2Cartesian, ZeroNormInfinityAngleCheckCoordenatesOutput) {
    Pol w = { 0.0, INFINITY };
    Cart x;
    Cart x_expected = { 0, 0 };

    polar2cartesian(&x, w);

    ASSERT_TRUE(CartNear(x_expected, x, tolerance));
}

TEST(ComplexSum, S1CartesianoS2CartesianoCheckOutputS1) {
    CplxNum s1 = { {13.37, 0.0 } , (char*)cartesian };
    CplxNum s2 = { {0.0, 13.37 } , (char*)cartesian };
    CplxNum s1_expected = { {13.37, 13.37 } , (char*)cartesian };

    complexsum(&s1, s2);

    ASSERT_TRUE(ComplexNumberNear(s1_expected, s1, tolerance));
}

TEST(ComplexSum, S1PolarS2PolarCheckOutputS1) {
    CplxNum s1 = { {13.37, M_PI_2 } , (char*)polar };
    CplxNum s2 = { {13.37, -M_PI_2 } , (char*)polar };
    CplxNum s1_expected = { {0.0, 0.0 } , (char*)polar };

    complexsum(&s1, s2);

    ASSERT_TRUE(ComplexNumberNear(s1_expected, s1, tolerance));
}

TEST(ComplexSum, S1CartesianoS2PolarCheckOutputS1) {
    CplxNum s1 = { {sqrt(2), sqrt(2) } , (char*)cartesian };
    CplxNum s2 = { {2, 3 * M_PI_4 } , (char*)polar };
    CplxNum s1_expected = { {0.0, 2.8284271 } , (char*)cartesian };

    complexsum(&s1, s2);

    ASSERT_TRUE(ComplexNumberNear(s1_expected, s1, tolerance));
}

TEST(ComplexSum, S1polarS2CartesianoCheckOutputS1) {
    CplxNum s1 = { {1, M_PI } , (char*)polar };
    CplxNum s2 = { {-1, -1 } , (char*)cartesian };
    CplxNum s1_expected = { {2.2360680, -2.6779451 } , (char*)polar };

    complexsum(&s1, s2);

    ASSERT_TRUE(ComplexNumberNear(s1_expected, s1, tolerance));
}

// probs
TEST(ComplexSum, S1polarInfinityAngleS2CartesianoCheckReturnValue) {
    CplxNum s1 = { {1, INFINITY } , (char*)polar };
    CplxNum s2 = { {-1, -1 } , (char*)cartesian };
    CplxNum s1_expected = { {INFINITY, INFINITY } , (char*)polar };

    unsigned ret = complexsum(&s1, s2);

    ASSERT_EQ(2, ret);
}

TEST(ComplexSum, S1polarzeroS2CartesianoCheckOutputS1) {
    CplxNum s1 = { {0, M_PI } , (char*)polar };
    CplxNum s2 = { {-1, -1 } , (char*)cartesian };
    CplxNum s1_expected = { {sqrt(2), -3 * M_PI_4 } , (char*)polar };

    complexsum(&s1, s2);

    ASSERT_TRUE(ComplexNumberNear(s1_expected, s1, tolerance));
}

TEST(ComplexMultiply, S1polarzeroS2CartesianoCheckOutputS1) {
    CplxNum s1 = { {0, M_PI } , (char*)polar };
    CplxNum s2 = { {-1, -1 } , (char*)cartesian };
    CplxNum s1_expected = { {0, 0 } , (char*)polar };

    complexmultiply(&s1, s2);

    ASSERT_TRUE(ComplexNumberNear(s1_expected, s1, tolerance));
}

TEST(ComplexMultiply, S1polarS2cartInfinityArgumentCheckReturnValue) {
    CplxNum s1 = { {1, 1 } , (char*)polar };
    CplxNum s2 = { {-1, INFINITY } , (char*)cartesian };
    CplxNum s1_expected = { {INFINITY, INFINITY } , (char*)polar };

    unsigned ret = complexmultiply(&s1, s2);

    ASSERT_EQ(2, ret);
}

#if 0
// complexmultiply não testa para ângulos infinitos, somente módulos infinitos
TEST(ComplexMultiply, S1polarInfinityAngleS2CartesianoCheckReturnValue) {
    CplxNum s1 = { { 1, INFINITY } , (char*)polar };
    CplxNum s2 = { {-1, -1 } , (char*)cartesian };
    CplxNum s1_expected = { {INFINITY, INFINITY } , (char*)polar };

    unsigned ret = complexmultiply(&s1, s2);

    ASSERT_EQ(2, ret);
}

#endif

TEST(ComplexMultiply, S1CartesianoS2CartesianoCheckOutputS1) {
    CplxNum s1 = { {sqrt(2), sqrt(2) } , (char*)cartesian };
    CplxNum s2 = { {-sqrt(2), sqrt(2) } , (char*)cartesian };
    CplxNum s1_expected = { {-4.0, 0.0 } , (char*)cartesian };

    complexmultiply(&s1, s2);

    ASSERT_TRUE(ComplexNumberNear(s1_expected, s1, tolerance));
}

TEST(ComplexMultiply, S1PolarS2PolarCheckOutputS1) {
    CplxNum s1 = { {sqrt(2), M_PI_2 } , (char*)polar };
    CplxNum s2 = { {sqrt(2), -M_PI / 6 } , (char*)polar };
    CplxNum s1_expected = { {2.0, M_PI / 3 } , (char*)polar };

    complexmultiply(&s1, s2);

    ASSERT_TRUE(ComplexNumberNear(s1_expected, s1, tolerance));
}

TEST(ComplexMultiply, S1CartesianoS2PolarCheckOutputS1) {
    CplxNum s1 = { {-sqrt(2), -sqrt(2) } , (char*)cartesian };
    CplxNum s2 = { {2, 3 * M_PI_4 } , (char*)polar };
    CplxNum s1_expected = { {4.0, 0.0 } , (char*)cartesian };

    complexmultiply(&s1, s2);

    ASSERT_TRUE(ComplexNumberNear(s1_expected, s1, tolerance));
}

TEST(ComplexMultiply, S1polarS2CartesianoCheckOutputS1) {
    CplxNum s1 = { {2, M_PI } , (char*)polar };
    CplxNum s2 = { {-1, 0 } , (char*)cartesian };
    CplxNum s1_expected = { {2.0, 0.0 } , (char*)polar };

    complexmultiply(&s1, s2);

    ASSERT_TRUE(ComplexNumberNear(s1_expected, s1, tolerance));
}
