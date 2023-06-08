#include <check.h>

#include "s21_calculator.h"

START_TEST(calc_sum_int) {
  ck_assert_int_eq(calc("5 + 9"), 14);
  ck_assert_int_eq(calc("99 + 1"), 100);
  ck_assert_int_eq(calc("99 + 100001"), 100100);
  ck_assert_int_eq(calc("9177 + 15"), 9192);
}
END_TEST

START_TEST(calc_sum_double) {
  ck_assert_double_eq(calc("5.1 + 9.17"), 14.27);
  ck_assert_double_eq(calc("99.0005 + 1.17"), 100.1705);
  ck_assert_double_eq(calc("99.11111114 + 100001.11111114"), 100100.22222228);
  ck_assert_double_eq(calc("9177.5 + 15.5"), 9193);
}
END_TEST

START_TEST(calc_minus_int) {
  ck_assert_int_eq(calc("5 - 9"), -4);
  ck_assert_int_eq(calc("99 - 1"), 98);
  ck_assert_int_eq(calc("99 - 100001"), -99902);
  ck_assert_int_eq(calc("9177 - 15"), 9162);
}
END_TEST

START_TEST(calc_minus_double) {
  ck_assert_double_eq(calc("5.1 - 9.17"), -4.07);
  ck_assert_double_eq(calc("99.0005 - 1.17"), 97.8305);
  ck_assert_double_eq(calc("100001.7000004 - 99.2000002"), 99902.5000002);
  ck_assert_double_eq(calc("9177.5 - 15.31"), 9162.19);
}
END_TEST

START_TEST(calc_umnozh_int) {
  ck_assert_int_eq(calc("5 * 9"), 45);
  ck_assert_int_eq(calc("99 * 1"), 99);
  ck_assert_int_eq(calc("99 * 100001"), 9900099);
  ck_assert_int_eq(calc("9177 * 15"), 137655);
}
END_TEST

START_TEST(calc_umnozh_double) {
  ck_assert_float_eq(calc("5.1 * 9.17"), 5.1 * 9.17);
  ck_assert_float_eq(calc("99.55 * 1.17"), 99.55 * 1.17);
  ck_assert_float_eq(calc("99.1115 * 100001.234"), 9911272.303591);
  ck_assert_float_eq(calc("9177.5 * 15.5"), 142251.25);
}
END_TEST

START_TEST(calc_minus_sqrt_double) {
  // ck_assert_float_eq(calc("sqrt(-7)"), sqrt(-7));  //nan
  ck_assert_float_eq(calc("6 mod (~7)"), 6 % (-7));
  // ck_assert_float_eq(calc("log(-10)"), log10(-10));  //nan
  // ck_assert_float_eq(calc("ln(-7)"), log(-7));  //nan

  ck_assert_float_eq(calc("sin(~7)"), sin(-7));
  ck_assert_float_eq(calc("cos(~7)"), cos(-7));
  ck_assert_float_eq(calc("tan(~7)"), tan(-7));
  // ck_assert_float_eq(calc("asin(-7)"), asin(-7));  //nan
  // ck_assert_float_eq(calc("acos(-7)"), acos(-7));  //nan
  // ck_assert_float_eq(calc("atan(-7)"), atan(-7));  //nan
}
END_TEST

START_TEST(calc_unar_int) {
  ck_assert_int_eq(calc("~5"), -5);
  ck_assert_int_eq(calc("~99 - 1"), -100);
  ck_assert_int_eq(calc("~(99 + 100001)"), -100100);
  ck_assert_int_eq(calc("9177 + (~15)"), 9162);
}
END_TEST

START_TEST(calc_mod_int) {
  ck_assert_int_eq(calc("5 mod 2"), 5 % 2);
  ck_assert_int_eq(calc("~99 mod 5"), -99 % 5);
  ck_assert_int_eq(calc("~(99 mod 10)"), -(99 % 10));
  ck_assert_int_eq(calc("9177 mod (~15)"), 9177 % (-15));
}
END_TEST

START_TEST(hard_tests) {
  ck_assert_float_eq(calc("(5.1 ^ 9.17 - 1)/2"), (pow(5.1, 9.17) - 1) / 2);
  ck_assert_float_eq(calc("log(sin(1)^3.2 + 101.115)/2"),
                     log10(pow(sin(1), 3.2) + 101.115) / 2);
  ck_assert_float_eq(calc("log(cos(1)^3.2 + 10.115)/2"),
                     log10(pow(cos(1), 3.2) + 10.115) / 2);
  ck_assert_float_eq(calc("~(3.45^(log(cos(1)^3.2 + 10.115)/2))"),
                     -pow(3.45, log10(pow(cos(1), 3.2) + 10.115) / 2));
  ck_assert_float_eq(calc("asin(acos(1) ^ tan(1)) * sqrt(7)^ln(10)"),
                     asin(pow(acos(1), tan(1))) * pow(sqrt(7), log(10)));
  ck_assert_float_eq(calc("asin(acos(1) ^ tan(1)) * sqrt(7)^atan(1)"),
                     asin(pow(acos(1), tan(1))) * pow(sqrt(7), atan(1)));
}
END_TEST

START_TEST(credit) {
  double first, last;

  ck_assert_float_eq(annuitet(15, 120000, 12), 10830.997481);
  ck_assert_float_eq(annuitet(15, 120000, 7), 18010.646505);
  ck_assert_float_eq(annuitet(15, 120000, 1), 121500.000000);
  ck_assert_float_eq(annuitet(15, 120000, 600), 1500.869609);
  ck_assert_float_eq(annuitet(48, 2000, 48), 94.361295);

  ck_assert_float_eq(diff(15, 120000, 12, &first, &last), 129616.438356);
  ck_assert_float_eq(diff(15, 120000, 7, &first, &last), 125917.808219);
  ck_assert_float_eq(diff(15, 120000, 1, &first, &last), 121479.452055);
  ck_assert_float_eq(diff(15, 120000, 600, &first, &last), 564575.342466);
  ck_assert_float_eq(diff(48, 2000, 48, &first, &last), 3933.150685);
}
END_TEST

START_TEST(graph) { ck_assert_float_eq(Y_calc("X5+", 3, 5), 10); }
END_TEST

Suite *s21_calc_suite(void) {
  Suite *suite;

  suite = suite_create("s21_calc");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, calc_sum_int);
  tcase_add_test(tcase_core, calc_sum_double);
  tcase_add_test(tcase_core, calc_minus_int);
  tcase_add_test(tcase_core, calc_minus_double);
  tcase_add_test(tcase_core, calc_umnozh_int);
  tcase_add_test(tcase_core, calc_umnozh_double);
  tcase_add_test(tcase_core, calc_unar_int);
  tcase_add_test(tcase_core, hard_tests);
  tcase_add_test(tcase_core, calc_mod_int);
  tcase_add_test(tcase_core, credit);
  tcase_add_test(tcase_core, graph);
  tcase_add_test(tcase_core, calc_minus_sqrt_double);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_calc_suite();
  SRunner *suite_runner = srunner_create(suite);
  // srunner_set_fork_status(suite_runner, CK_NOFORK);
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}