#include <iostream>
#include <stack>
#include <string>

using namespace std;


class Priority {
public:
	virtual int GivePriority() = 0;
};
class HighPriority : public Priority {
public:
	int GivePriority() override {
		return 2;
	}
};
class LowPriority : public Priority {
public:
	int GivePriority() override {
		return 1;
	}
};
class LeftPriority : public Priority {
public:
	int GivePriority() override {
		return 0;
	}
};
class RightPriority : public Priority {
public:
	int GivePriority() override {
		return -1;
	}
};
class NumPriority : public Priority {
public:
	int GivePriority() override {
		return -2;
	}
};

class GetP {
private:
	Priority* _priority;
public:
	void changeOP(Priority* p) {
		_priority = p;
	}
	int Operation() {
		return _priority->GivePriority();
	}
};

static int getPriority(char word) {
	GetP* _getP = new GetP();
	switch (word)
	{
	case '*':
	case '/':
		_getP->changeOP(new HighPriority());
		return _getP->Operation();
	case '+':
	case '-':
		_getP->changeOP(new LowPriority());
		return _getP->Operation();
	case '(':
		_getP->changeOP(new LeftPriority());
		return _getP->Operation();
	case ')':
		_getP->changeOP(new RightPriority());
		return _getP->Operation();
	default:
		_getP->changeOP(new NumPriority());
		return _getP->Operation();
	}
}
stack<char> operation;
stack<int> num;

static void cal() {
	int a, b, result;
	if (num.size() < 2) {
		throw string("잘못된 입력입니다.");
	}
	else {
		b = num.top();
		num.pop();
		a = num.top();
		num.pop();
	}

	char oper = operation.top();
	operation.pop();

	if (oper == '+') {
		result = a + b;
	}
	else if (oper == '-') {
		result = a - b;
	}
	else if (oper == '*') {
		result = a * b;
	}
	else if (oper == '/') {
		result = a / b;
	}
	num.push(result);

}

int main() {
	string line;
	getline(cin, line);
	char word;
	int count = 0;
	
	try {
		for (int i = 0; i < line.length(); i++) {
			word = (char)line[i];

			int code = getPriority(word);
			switch (code)
			{
			case -2:
				if (getPriority(line[i + 1]) == -2) {
					string nword;
					int setting;
					if (line[i + 1] == 'b') {
						setting = 2;
						for (int j = i + 2; j < line.length(); j++) {
							if ((line[j] == '+') || (line[j] == '-') || (line[j] == '*') || (line[j] == '/') || (line[j] == '(') || (line[j] == ')')) {
								i = j - 1;
								break;
							}
							else {
								nword += line[j];
							}
						}
					}
					else if (line[i + 1] == 'x') {
						setting = 16;
						for (int j = i + 2; j < line.length(); j++) {
							if ((line[j] == '+') || (line[j] == '-') || (line[j] == '*') || (line[j] == '/') || (line[j] == '(') || (line[j] == ')')) {
								i = j - 1;
								break;
							}
							else {
								nword += line[j];
							}
						}
					}
					else {

						setting = 10;
						int j = i;
						for (j = i; j < line.length(); j++) {
							if ((line[j] == '+') || (line[j] == '-') || (line[j] == '*') || (line[j] == '/') || (line[j] == '(') || (line[j] == ')')) {
								break;
							}
							else {
								nword += line[j];
							}
						}
						i = j - 1;
					}
					num.push(stoi(nword, 0, setting));
				}
				else { num.push(word - '0'); }
				break;
			case 2:
			case 1:
 				while ((!operation.empty()) && code <= getPriority(operation.top())) {
					cal();
				}
				operation.push(word);
				break;
			case 0:
				operation.push(word);
				break;
			case -1:
				while (operation.top() != '(') {
					if (operation.size() <= 1) {
						throw string("잘못된 입력입니다.");
					}
					else {
						cal();
					}
				}
				operation.pop();
				break;
			default:
				break;
			}
		}

		while (!operation.empty()) {
			cal();
		}

		cout << num.top();
	}
	catch (string& s) {
		cout << s;
	}


	return 0;
}