#include <gtest/gtest.h>

// Declare the add function to be tested
extern "C" {
    int add(const char *input);
}

// Test case for empty input string
TEST(StringCalculatorAddTests, ExpectZeroForEmptyInput) {
    int expectedresult = 0;
    const char* input = "";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for input string with a single zero
TEST(StringCalculatorAddTests, ExpectZeroForSingleZero) {
    int expectedresult = 0;
    const char* input = "0";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for input string with two numbers
TEST(StringCalculatorAddTests, ExpectSumForTwoNumbers) {
    int expectedresult = 3;
    const char* input = "1,2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for input string with newline as delimiter
TEST(StringCalculatorAddTests, ExpectSumWithNewlineDelimiter) {
    int expectedresult = 6;
    const char* input = "1\n2,3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for ignoring numbers greater than 1000
TEST(StringCalculatorAddTests, IgnoreNumbersGreaterThan1000) {
    int expectedresult = 2;
    const char* input = "1,1001,1";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for input string with custom delimiter
TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter) {
    int expectedresult = 6;
    const char* input = "//;\n1;2;3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for input string with custom delimiter and negative number
TEST(StringCalculatorAddTests, ExpectErrorForNegativeNumbers) {
    const char* input = "1,-2,3";
    testing::internal::CaptureStderr();
    add(input);
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_NE(output.find("negatives not allowed"), std::string::npos);
}

// Test case for input string with invalid characters
TEST(StringCalculatorAddTests, ExpectZeroForInvalidCharacters) {
    int expectedresult = 0;
    const char* input = "1,a,2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for empty input string with custom delimiter notation
TEST(StringCalculatorAddTests, ExpectZeroForEmptyInputWithCustomDelimiter) {
    int expectedresult = 0;
    const char* input = "//;\n";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for single number with custom delimiter
TEST(StringCalculatorAddTests, ExpectNumberForSingleNumberWithCustomDelimiter) {
    int expectedresult = 3;
    const char* input = "//;\n3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for handling large input
TEST(StringCalculatorAddTests, HandleLargeInput) {
    char input[MAX_INPUT_LENGTH];
    memset(input, '1', MAX_INPUT_LENGTH - 1);
    input[MAX_INPUT_LENGTH - 1] = '\0';
    int result = add(input);
    ASSERT_GT(result, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
