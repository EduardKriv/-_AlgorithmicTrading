#include "gtest/gtest.h"
#include "model/interpolator.h"
#include "model/approximator.h"

using namespace s21;

TEST(tests_inter, test1) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    auto table = inter.CalcPoints(9);

    EXPECT_NEAR(table.Y_[0], 12.850000, 1e-6);
    EXPECT_NEAR(table.Y_[1], 12.210000, 1e-6);
    EXPECT_NEAR(table.Y_[2], 12.140000, 1e-6);
    EXPECT_NEAR(table.Y_[3], 12.320000, 1e-6);
    EXPECT_NEAR(table.Y_[4], 12.300000, 1e-6);
    EXPECT_NEAR(table.Y_[5], 12.132862, 1e-6);
    EXPECT_NEAR(table.Y_[6], 12.015710, 1e-6);
    EXPECT_NEAR(table.Y_[7], 12.150000, 1e-6);
    EXPECT_NEAR(table.Y_[8], 12.460000, 1e-6);
}

TEST(tests_inter, test2) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    auto date_value = inter.GetValueByDateTime("2021-03-26-17-43");

    EXPECT_NEAR(date_value, 12.179978, 1e-6);
}

TEST(tests_inter, test3) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    auto date_value = inter.GetValueByDateTime("2021-03-22-00-00");

    EXPECT_NEAR(date_value, 12.85, 1e-6);
}

TEST(tests_inter, test4) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    inter.CalcPoints(10);
    auto date_value = inter.GetValueByDateTime("2021-03-23-00-00");

    EXPECT_NEAR(date_value, 12.21, 1e-6);
}

TEST(tests_inter, test5) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    inter.CalcPoints(50);
    auto date_value = inter.GetValueByDateTime("2021-03-24-00-00");

    EXPECT_NEAR(date_value, 12.14, 1e-6);
}

TEST(tests_inter, test6) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    inter.CalcPoints(77);
    auto date_value = inter.GetValueByDateTime("2021-03-25-00-00");

    EXPECT_NEAR(date_value, 12.32, 1e-6);
}

TEST(tests_inter, test7) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    inter.CalcPoints(111);
    auto date_value = inter.GetValueByDateTime("2021-03-26-00-00");

    EXPECT_NEAR(date_value, 12.3, 1e-6);
}

TEST(tests_inter, test8) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    inter.CalcPoints(111);
    auto date_value = inter.GetValueByDateTime("2021-03-29-00-00");

    EXPECT_NEAR(date_value, 12.15, 1e-6);
}

TEST(tests_inter, test9) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    inter.CalcPoints(111);
    auto date_value = inter.GetValueByDateTime("2021-03-30-00-00");

    EXPECT_NEAR(date_value, 12.46, 1e-6);
}

TEST(tests_inter, test10) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    inter.CalcPoints(1110);
    auto date_value = inter.GetValueByDateTime("2021-03-31-00-00");

    EXPECT_NEAR(date_value, 12.25, 1e-6);
}

TEST(tests_inter, test11) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Interpolator inter(&loader);
    inter.Interpolate();
    inter.CalcPoints(777);
    auto date_value = inter.GetValueByDateTime("2021-04-01-00-00");

    EXPECT_NEAR(date_value, 12.179999, 1e-6);
}

TEST(tests_approx, test1) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Approximator approx(&loader);
    approx.Approximate(2);
    auto date_value = approx.GetValueByDateTime("2021-03-26-17-43");

    EXPECT_NEAR(date_value, 12.201887, 1e-6);
}

TEST(tests_approx, test2) {
    Loader loader;
    loader.LoadData("resources/F_test.csv");

    Approximator approx(&loader);
    approx.Approximate(4);
    auto date_value = approx.GetValueByDateTime("2021-03-26-17-43");

    EXPECT_NEAR(date_value, 12.343984, 1e-6);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

