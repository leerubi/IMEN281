#include <iostream>
using namespace std;
bool isBinary(int num);
long binary_to_decimal_by_recursive(int num);
long binary_to_decimal_by_non_recursive(int num);
long decimal_to_binary_by_recursive(int num);
long decimal_to_binary_by_non_recursive(int num);

int main(int argc, const char * argv[]) {
	int mainMenu, subMenu, num;
	while (true) {
		cout << "menu�� �Է��ϼ���.(1: 10����->2����, 2: 2����->10����, 0: ������)" << endl;
		cout << "menu: "; cin >> mainMenu;
		if (mainMenu == 0)
			break;
		switch (mainMenu) {
		case 1:
			cout << "sub_menu�� �Է��ϼ���.(1: recursive, 2: non-recursive)" << endl;
			cout << "sub_menu: "; cin >> subMenu;
			cout << "��ȯ�� ���ڸ� �Է��ϼ���: ";
			cin >> num;
			if (subMenu == 1)
				cout << decimal_to_binary_by_recursive(num);
			else
				cout << decimal_to_binary_by_non_recursive(num);
			break;
		case 2:
			cout << "sub_menu�� �Է��ϼ���.(1: recursive, 2: non-recursive)" << endl;
			cout << "sub_menu: "; cin >> subMenu;
			while (true) {
				cout << "��ȯ�� ���ڸ� �Է��ϼ���: ";
				cin >> num;
				if (!isBinary(num))
					continue;
				if (subMenu == 1)
					cout << binary_to_decimal_by_recursive(num);
				else
					cout << binary_to_decimal_by_non_recursive(num);
				break;
			}
			break;
		default:
			cout << "Input 1 or 2 please!";
			break;
		}
		cout << endl << endl;
	}

	return 0;
}
bool isBinary(int num) {
	while ((num % 10 == 0 || num % 10 == 1)) {
		num /= 10;
		if (num == 0 || num == 1)
			return true;
	}
	return false;
}
long binary_to_decimal_by_recursive(int num) {
	if (num < 2)
		return num;
	else
		return (num % 10) + 2 * binary_to_decimal_by_recursive(num / 10);
}
long binary_to_decimal_by_non_recursive(int num) {
	long a = 1;
	long val = 0;
	while (true) {
		if (num == 0)
			break;
		if (num % 10 == 1 || num == 1)
			val += a;
		num /= 10;
		a *= 2;
	}
	return val;
}
long decimal_to_binary_by_recursive(int num) {
	if (num < 2)
		return num;
	else
		return decimal_to_binary_by_recursive(num / 2) * 10 + num % 2;
}
long decimal_to_binary_by_non_recursive(int num) {
	long a = 1;
	long val = 0;
	while (true) {
		if (num == 0)
			break;
		if (num % 2 == 1 || num == 1)
			val += a;
		num /= 2;
		a *= 10;
	}
	return val;
}
