#include"Stack.h"

//flag为1时表示栈内优先级  flag为0表示栈外优先级
int GetPriority(char ch, int flag)
{
	if (ch == '+' || ch == '-')
	{
		if (flag)
		{
			return 3;
		}
		else
		{
			return 2;
		}
	}
	else if (ch == '*' || ch == '/' || ch == '%')
	{
		if (flag)
		{
			return 5;
		}
		else
		{
			return 4;
		}
	}
	else if (ch == '(')
	{
		if (flag)
		{
			return 1;
		}
		return 6;
	}
	else if (ch == ')')
	{
		if (flag)
		{
			return 6;
		}
		else
		{
			return 1;
		}
	}
}

bool IsOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '(' || ch == ')')
	{
		return true;
	}
	return false;
}

//中缀表达式转后缀表达式
void prefixionToSuffix(char* dst, char* src)
{
	assert(dst);
	assert(src);
	Stack<char> s;
	char * cur = src;
	char* tmp = dst;
	while (*cur != '\0')
	{
		if (*cur >= '0' && *cur <= '9')
		{
			*tmp++ = *cur;
			cur++;
			continue;
		}
		else if (IsOperator(*cur))
		{
			if (s.Empty())//如果栈为空，直接入栈
			{
				s.Push(*cur);
				cur++;
			}
			else//如果栈不空，则需要判断栈顶元素和当前操作符的优先级
			{
				if (*cur == ')')
				{
					while (*cur == ')' && s.Top() != '(')
					{
						*tmp++ = s.Top();
						s.Pop();
					}
					s.Pop();
					cur++;
				}
				if (GetPriority(*cur, 0) > GetPriority(s.Top(), 1))
				{
					s.Push(*cur);
					cur++;
				}
				else
				{
					while (!s.Empty() && GetPriority(*cur, 0) < GetPriority(s.Top(), 1))
					{
						*tmp++ = s.Top();
						s.Pop();
					}
					s.Push(*cur);
					cur++;
				}
				
			}
		}
		else
		{
			*tmp++ = *cur++;
		}
	}
	while(!s.Empty())
	{
		*tmp++ = s.Top();
		s.Pop();
	}
}
                           
