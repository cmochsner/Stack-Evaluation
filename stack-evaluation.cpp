#include <iostream>
#include <string>
#include <stdio.h> 
#include <sstream>

using namespace std;

bool isBalanced(string exp);


template<class T>
struct node
{
	T item;
	struct node<T> *next;
};
template<class T>
class stack
{
	private:
		struct node<T> *top;
	public:
		stack()
		{
			top = NULL;
		}
		T getTop();
		T pop();
		void push(T el);
		bool isEmpty();
		void print();
};
template<class T>
T stack<T>::getTop()
{
	if (top != NULL)
	{
		return top->item;
	}
}
template<class T>
T stack<T>::pop()
{
	if (top == NULL)
	{
		cout << "Stack is empty. Cannot delete." << endl;
		return ' ';
	}
	T item=top->item;

	struct node<T>* temp = top;
	top = top->next;

	//free(temp);

	return item;
}
template<class T>
void stack<T>::push(T el)
{
	if (top == NULL)
	{
		top = new node<T>;
		top->item = el;
		top->next = NULL;
		return;
	}
	struct node<T> * newnode = new node<T>;

	newnode->item = el;
	newnode->next = top;
	top = newnode;
}
template<class T>
bool stack<T>::isEmpty()
{
	if (top == NULL)
	{
		return true;
	}
	return false;
}
template<class T>
void stack<T>::print()
{
	struct node<T>* current = top;
	while (current != NULL)
	{
		cout << current->item << " ";
		current=current->next;
	}
	cout << endl;
}
int calculate(stack<int>& s, stack<char>& s2);
void parse(string exp, stack<int>& s, stack<char>& s2, int& i);
void calc(string exp);
int main()
{
	//(1+2-(4+18+[7)])
	string exp;
	int choice=0;
	cout << "Welcome to the isBalanced stack program!" << endl;
	while (choice != 3)
	{
		cout << "1: Check if an expression is balanced" << endl;
		cout << "2: Evaluate a simple expression with only + and -" << endl;
		cout << "3: Exit" << endl;
		cin >> choice;
		switch (choice)
		{
			case 1:
			{
				cout << "Enter your expression: " << endl;
				cin >> exp;
				if (isBalanced(exp))
				{
					cout << "It is balanced!" << endl;
					cout << endl;
				}
				else
				{
					cout << "It is not balanced!" << endl;
				}
			}
			break;
			case 2:
			{
				cout << "\nEnter your expression: " << endl;
				cin >> exp;
				if (!isBalanced(exp))
				{
					cout << "It not is balanced!" << endl;
					cout << endl;
					break;
				}
				cout << "Your result is: ";
				calc(exp);
				cout << endl;
			}
			break;
			case 3:
			{
				cout << "Exiting..." << endl;
				return 0;
			}
			break;
			default:
			{
				cout << "Invalid input. Try again" << endl;
				cin >> choice;
			}
			break;
		}
	}
	//system("pause");
	return 0;
}
void calc(string exp)
{
	stack<int> s;
	stack<char> s2;
	stack<int> s3;
	stack<char> s4;
	int i = exp.length() - 1;
	int j= exp.length() - 1;
	int count[50];
	int paren = -1;

	while (i >= 0)
	{
		if (exp[i] == ')')
		{
			while (exp[i] != '(')
			{
				parse(exp, s3, s4, i);
				i--;
			}
			s.push(calculate(s3, s4));
			i--;
		}
		parse(exp, s, s2, i);
		i--;
	}
	cout<<calculate(s, s2);
}
void parse(string exp, stack<int>& s, stack<char>& s2, int& i)
{
	string str;
	switch (exp[i])
	{
		case '+':
		{
			if (i == 0)
			{
				break;
			}
			s2.push(exp[i]);
		}
		break;
		case '-':
		{
			if (i == 0)
			{
				int neg = (-1)*s.pop();
				s.push(neg);
				break;
			}
			s2.push(exp[i]);
		}
		break;
		case ')':
		case '(':
			break;
		default:
		{
			int num;
			while (i >= 0 && exp[i] != '+'&&exp[i] != '-'&&exp[i] != ')'&&exp[i] != '('&&exp[i] != ']'&&exp[i] != '['&&exp[i] != '{'&&exp[i] != '}')
			{
				str = exp[i] + str;
				i--;
			}
			istringstream ss(str);
			ss >> num;
			s.push(num);
			i++;
		}
		break;
	}
}
int calculate(stack<int>& s, stack<char>& s2)
{
	int sol = 0, num1, num2;
	if (s2.isEmpty()&&!s.isEmpty())
	{
		sol = s.pop();
	}
	while (!s2.isEmpty())
	{
		char op = s2.pop();
		switch (op)
		{
			case '+':
				num1=s.pop();
				num2 = 0;
				if (!s.isEmpty())
				{
					num2 = s.pop();
				}
				sol = num1 + num2;
				s.push(sol);
				break;
			case '-':
				num1 = s.pop();
				num2 = 0;
				if (!s.isEmpty())
				{
					num2 = s.pop();
				}
				sol = num1-num2;
				s.push(sol);
				break;
			default:
				break;
		}
	}
	return sol;
}
bool isBalanced(string exp)
{
	stack<char> s;
	int i = 0;
	while (i < exp.length())
	{
		switch (exp[i])
		{
			case '(':
			case '{':
			case '[':
				s.push(exp[i]);
				break;
			case ')':
				if ('(' == s.getTop())
				{
					s.pop();
				}
				else
				{
					return false;
				}
				break;
			case '}':
				if ('{' == s.getTop())
				{
					s.pop();
				}
				else
				{
					return false;
				}
				break;
			case ']':
				if ('[' == s.getTop())
				{
					s.pop();
				}
				else
				{
					return false;
				}
				break;
			default:
				break;
		}
		i++;
	}
	if (s.isEmpty())
	{
		return true;
	}

	return false;
}