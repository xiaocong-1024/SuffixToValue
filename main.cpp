#include"Stack.h"

void Test()
{
	char prefixion[] = "12 * (3 + 4) - 6 + 8 / 2 ";//保存前缀表达式
	char suffix[25] = {};//保存后缀表达式
	int res = SuffixToValue(suffix, prefixion);
	cout << res << endl;
}

int main()
{
	Test();
	return 0;
}
