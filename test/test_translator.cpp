#include "translator.h"

#include <gtest.h>


TEST(translator, can_translator) {
	ASSERT_NO_THROW(translator t("1+5/(2-12)"));
};
TEST(translator, throw_sintaksis_analysis) {
	translator t("1+2+3(");
	ASSERT_ANY_THROW(t.sintaksis_analysis());
};
TEST(translator, analisys_is_false) {
	translator t("1+2-/52");
	t.sintaksis_analysis();
	EXPECT_EQ(t.analisys(), false);
};
TEST(translator, analisys_is_true) {
	translator t("1+2-(3*8)");
	t.sintaksis_analysis();
	t.sort_term();
	EXPECT_EQ(t.analisys(), true);
};
TEST(translator, checking_brackets_is_false) {
	translator t("1+(2-5))");
	EXPECT_EQ(t.checking_brackets(), false);
};
TEST(translator, checking_brackets_is_true) {
	translator t("1+(2-5*[4+2])");
	EXPECT_EQ(t.checking_brackets(), true);
};
TEST(translator, throw_computing) {
	translator t("1/(5-5))");
	ASSERT_ANY_THROW(t.translation());
};
TEST(translator, translation_1) {
	string st = "1+5/(2-12)";
	translator t(st);
	EXPECT_EQ(t.translation(), 0.5);
};
TEST(translator, translation_2) {
	translator t("1.5+5/(2-12)");
	EXPECT_EQ(t.translation(), 1.0);
};
TEST(translator, translation_3) {
	translator t("1.5*5/[2-12]");
	EXPECT_EQ(t.translation(), -0.75);
};
TEST(translator, translation_4) {
	translator t("10-7*(1+{8/4})");
	EXPECT_EQ(t.translation(), -11);
};
TEST(translator, translation_5) {
	double e = 0.001;
	translator t("10/{7*(1+{8/4})}");
	EXPECT_EQ((t.translation() - 0.476) < e, true);
};
TEST(translator, translation_6) {
	double e = 0.001;
	translator t("0.55*11.1*91");
	EXPECT_EQ(t.translation() - 555.555 < e, true);
};
TEST(translator, translation_7) {
	double e = 0.001;
	translator t("1+1+1/2+1/2/3+1/2/3/4+1/2/3/4/5");
	EXPECT_EQ(t.translation() - 2.718 < e, true);
};
TEST(translator, translation_8) {
	translator t("1+2+3+4+5+6+7+8+9");
	EXPECT_EQ(t.translation(), 45);
};
TEST(translator, translation_9) {
	translator t("(5*4+7)/3+5*7");
	EXPECT_EQ(t.translation(), 44);
};