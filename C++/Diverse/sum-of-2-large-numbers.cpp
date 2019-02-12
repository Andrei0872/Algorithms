
/* 
Sum of 2 large numbers
str1 = "3333311111111111", 
str2 = "44422222221111"

Output : 3377733333332222
*/

#include <iostream>
#include <cstring>
#define MAXDIGITS 10000
using namespace std;

struct BigNumber
{
    unsigned int len;
    int *digits;

    BigNumber(unsigned int _len, char number[])
    {
        this->len = _len;
        this->digits = new int[_len];
        unsigned int digits_index = 0;

        // Store in reverse order
        while (digits_index != this->len)
        {
            this->digits[digits_index++] = number[--_len] - '0';
        }
    }
};

struct BigNumber *readNumber(char number[])
{
    return new BigNumber(strlen(number), number);
}

int minValue(int num1, int num2)
{
    return num1 < num2 ? num1 : num2;
}

void computeSum(BigNumber *num1, BigNumber *num2)
{
    int result[MAXDIGITS];
    int result_index = 0;
    int minLength = minValue(num1->len, num2->len);
    int carry = 0, sum;

    for (int i = 0; i < minLength; i++)
    {
        sum = num1->digits[i] + num2->digits[i] + carry;
        result[result_index++] = sum % 10;
        carry = sum / 10;
    }

    // Add what's left
    for (int i = minLength; i < num1->len; i++)
    {
        result[result_index++] = num1->digits[i];
    }

    for (int i = minLength; i < num2->len; i++)
    {
        result[result_index++] = num2->digits[i];
    }

    for (int i = result_index - 1; i >= 0; i--)
    {
        cout << result[i];
    }
}

int main()
{

    char str1[] = "3333311111111111";
    char str2[] = "44422222221111";

    BigNumber *num1 = readNumber(str1);
    BigNumber *num2 = readNumber(str2);

    computeSum(num1, num2);

    return 0;
}