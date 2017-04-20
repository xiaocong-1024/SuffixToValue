#include"Stack.h"

//12 3 4 + * 6 - 8 2 / +
int  SuffixToValue(char *suffix, char *prefixion)
{
	prefixionToSuffix(suffix, prefixion);

	Stack<int> s;
	char* cur = suffix;
	int res = 0;
	int tmp = 0;
    while (*cur != '\0')
	{
		if (*cur == '+' || *cur == '-' || *cur == '*' || *cur == '/' || *cur == '%')
		{
			char ch = *cur;
			int right = s.Top();
			s.Pop();
			int left = s.Top();
			s.Pop();
			switch (ch)
			{
			case '+':
				s.Push(left + right);
				break;
			case '-':
				s.Push(left - right);
				break;
			case '*':
				s.Push(left * right);
				break;
			case '%':
				s.Push(left % right);
				break;
			case '/':
				if (right)
				{
					s.Push(left / right);
				}
				break;
			}
			cur++;
		}
		else if (*cur >= '0' && *cur <= '9')
		{
			res = 0;
			while (!isspace(*cur) && *cur >= '0' && *cur <= '9')
			{
				tmp = *cur - '0';
				res = res * 10 + tmp;
				cur++;
			}
			s.Push(res);
			//cur++;
		}
		else
		{
			cur++;
		}
	}
	if (!s.Empty())
	{
		res = s.Top();
		return res;
	}
}

