#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

#include "Enum.h" // enum ��� ���� ����.
#include "Member.h" // ȸ�� ���� Ŭ���� ���� ����.
#include "Car.h" // �� Ŭ���� ���� ����.
#include "User.h" // ����� Ŭ���� ���� ����.
#include "TowerManager.h" // ���� ���� ���� ���� ����.

Member::Member(string id, string password, string name, string phone) {
	this->id = id;
	this->password = password;
	this->name = name;
	this->phone = phone;
}
void Member::setPassword(string password) { this->password = password; }
void Member::setName(string name) { this->name = name; }
void Member::setPhone(string phone) { this->phone = phone; }
string Member::getId() { return id; }
string Member::getPassword() { return password; }
string Member::getName() { return name; }
string Member::getPhone() { return phone; }

Car::Car(int location, string id, string number, time_t parkingTime) {
	this->location = location;
	this->id = id;
	this->number = number;
	this->parkingTime = parkingTime;
}
int Car::getLocation() { return location; }
string Car::getId() { return id; }
string Car::getNumber() { return number; }
time_t Car::getTime() { return parkingTime; }

User::User() {
	total = 0; // ���� ���� �� �ʱ�ȭ.
	for (int i = 0; i < SPACE; i++)
		car[i] = NULL; // ���� Ŭ���� �迭 �ʱ�ȭ.
	loadFile(); // ������ ȣ�� ��� ����� ���� �ҷ�����.
}
User::~User() {
	saveFile(); // �Ҹ��� ȣ�� ��� ���� �����ϱ�.
	for (unsigned int i = 0; i < member.size(); i++) { // ���� �Ҵ�� ��� ��� ����.
		delete member[i];
		member[i] = NULL;
	}
	for (int i = 0; i < total; i++) { // ���� �Ҵ�� ���� ��� ����.
		delete car[i];
		car[i] = NULL;
	}
	cout << "�̿����ּż� �����մϴ�." << endl;
}
void User::saveFile() { // ���� ���� �Լ�.
	ofstream fout;
	fout.open("member.txt"); // member.txt ���� ����.
	for (unsigned int i = 0; i < member.size(); i++) // ������ '$'�� �̿��� ������ ���� �ε�.
		fout << member[i]->getId() << '$' << member[i]->getPassword() << '$' << member[i]->getName() << '$' << member[i]->getPhone() << '$' << endl;
	fout.close(); // member.txt ���� Ŭ����.
	fout.open("car.txt"); // car.txt ���� ����.
	for (int i = 0; i < total; i++) // ������ '$'�� �̿��� ������ ���� ����.
		fout << car[i]->getLocation() << '$' << car[i]->getId() << '$' << car[i]->getNumber() << '$' << car[i]->getTime() << '$' << endl;
	fout.close(); // car.txt ���� Ŭ����.
}
void User::loadFile() { // ���� �ҷ����� �Լ�.
	char c;
	int i = 0;
	ifstream fin;
	fin.open("member.txt"); // ȸ�� ���� ���� ����.
	while (true) {
		string id = "", password = "", name = "", phone = "";
		while ((c = fin.get()) != EOF) { // ���̵� ��������.
			if (c == '\n') continue; // ���� ���ڴ� ����.
			if (c == '$') break; // �����ڷ� ����.
			id += c; // id ��Ʈ���� �ش� ���� ����.
		}
		if (c == EOF) break;
		while ((c = fin.get()) != EOF) { // ��й�ȣ ��������.
			if (c == '\n') continue; // ���� ���ڴ� ����.
			if (c == '$') break; // �����ڷ� ����.
			password += c; // password ��Ʈ���� �ش� ���� ����.
		}
		if (c == EOF) break;
		while ((c = fin.get()) != EOF) { // �̸� ��������.
			if (c == '\n') continue; // ���� ���ڴ� ����.
			if (c == '$') break; // �����ڷ� ����.
			name += c; // name ��Ʈ���� �ش� ���� ����.
		}
		if (c == EOF) break;
		while ((c = fin.get()) != EOF) { // ��ȭ��ȣ ��������.
			if (c == '\n') continue; // ���� ���ڴ� ����.
			if (c == '$') break; // �����ڷ� ����.
			phone += c; // phone ��Ʈ���� �ش� ���� ����.
		}
		if (c == EOF) break;
		member.push_back(new Member(id, password, name, phone)); // �ҷ��� �����ͷ� Member Ŭ������ ���� �Ҵ� �� member ������ ���Ϳ� ����.
	}
	fin.close();
	fin.open("car.txt"); // ���� ���� ���� ����.
	while (i < SPACE) {
		string location = "", id = "", number = "", time = "";
		while ((c = fin.get()) != EOF) { // ������ ��ġ ���� ��������.
			if (c == '\n') continue;
			if (c == '$') break;
			location = c;
		}
		while ((c = fin.get()) != EOF) { // ������ ȸ�� ���̵� ��������.
			if (c == '\n') continue;
			if (c == '$') break;
			id += c;
		}
		if (c == EOF) break;
		while ((c = fin.get()) != EOF) { // ���� ��ȣ ��������.
			if (c == '\n') continue;
			if (c == '$') break;
			number += c;
		}
		if (c == EOF) break;
		while ((c = fin.get()) != EOF) { // ���� �ð� ���� ��������.
			if (c == '\n') continue;
			if (c == '$') break;
			time += c;
		}
		if (c == EOF) break;
		car[i++] = new Car(stoi(location), id, number, stoi(time)); // �ҷ��� �����ͷ� Car Ŭ������ ���� �Ҵ� �� car ������ �迭�� ����.
		total++; // ���� ���� �� ����.
	}
	fin.close();
}

GeneralUser::GeneralUser() {
	step = 1; // �⺻ �۾� �ܰ� 1
	signedMember = NULL; // ���ӵ� ��� NULL �ʱ�ȭ.
}
void GeneralUser::run() { // �Ϲ� ����� ��� ���� �Լ�.
	while (step) { // step �÷���, ��, �۾� �ܰ谡 0�̸� ���α׷� ����.
		system("cls");
		switch (step) { // step�� �÷��׿� ���� �۾� �ܰ� ����.
		case 1:
			firstScreen(); // ù ��° �ܰ� ����. (�α���, ȸ������, ���̵� ã��)
			break;
		case 2:
			secondScreen(); // �� ��° �ܰ� ����. (���� ���� ȭ��)
			break;
		case 3:
			thirdScreen(); // �� ��° �ܰ� ����. (ȸ�� ���� ���� ȭ��)
			break;
		}
	}
}
void GeneralUser::firstScreen() { // ù ��° �۾� �ܰ� �Լ�.
	char select;
	cout << "������������ ���� Ÿ��  ������������" << endl;
	cout << "��                                ��" << endl;
	cout << "��                                ��" << endl;
	cout << "��1. �α���                       ��" << endl;
	cout << "��2. ȸ������                     ��" << endl;
	cout << "��3. ���̵� ã��                  ��" << endl;
	cout << "��                                ��" << endl;
	cout << "��0. ����                         ��" << endl;
	cout << "������������������������������������" << endl;
	cout << ">>";
	cin >> select; // �޴� ����.
	while (cin.get() != '\n');
	switch (select) {
	case '1':
		logIn(); // �α���.
		break;
	case '2':
		signUp(); // ȸ������.
		break;
	case '3':
		findId(); // ���̵� ã��.
		break;
	case '0':
		step = 0; // ���� ���� �� �۾� �ܰ� 0 ����.
		return;
	default:
		cout << "������ �� ���� �۾��Դϴ�." << endl;
	}
	system("pause");
}
void GeneralUser::logIn() { // �α��� �Լ�.
	string id, password;
	cout << "���̵�" << endl << ">>";
	cin >> id;
	cout << "��й�ȣ" << endl << ">>";
	cin >> password;
	for (unsigned int i = 0; i < member.size(); i++) // ȸ�� ���� ����ŭ �ݺ�.
		if (id == member[i]->getId() && password == member[i]->getPassword()) { // ���̵�� ��й�ȣ�� ��ġ�� ���.
			signedMember = member[i]; // ���ӵ� ȸ�� �����Ϳ� ��ġ�ϴ� ȸ�� Ŭ���� �ּҸ� ����.
			cout << id << "(��)�� �α��� �Ǿ����ϴ�." << endl;
			step = 2; // �۾� �ܰ� 2�� ����.
			return;
		}
	cout << "��ϵ��� ���� ���̵��̰ų�, ���̵� �Ǵ� ��й�ȣ�� �߸� �Է��ϼ̽��ϴ�." << endl;
}
void GeneralUser::signUp() { // ȸ������ �Լ�.
	string id, password, name, phone;
	unsigned int i;
	while (true) { // ��ȿ�� ���̵� �Է±��� �ݺ�.
		cout << "���̵�" << endl << ">>";
		cin >> id;
		if (id.length() < 4 || id.length() > 10) { // ��ȿ�� �ڸ��� �˻�.
			cout << "4�ڸ� �̻� 10�ڸ� ������ ���̵� �Է����ּ���." << endl;
			continue;
		}
		for (i = 0; i < member.size(); i++) // ���̵� �ߺ� �˻�.
			if (id == member[i]->getId()) {
				cout << "�̹� ��� ���� ���̵��Դϴ�." << endl;
				break;
			}
		if (i == member.size())
			break;
	}
	while (true) { // ��ȿ�� ��й�ȣ �Է±��� �ݺ�.
		cout << "��й�ȣ" << endl << ">>";
		cin >> password;
		if (password.length() >= 4 && password.length() <= 8) // ��ȿ�� �ڸ��� �˻�.
			break;
		cout << "4�ڸ� �̻� 8�ڸ� ������ ��й�ȣ�� �Է����ּ���." << endl;
	}
	while (true) { // ��ȿ�� �̸� �Է±��� �ݺ�.
		cout << "�̸�" << endl << ">>";
		cin >> name;
		if (name.length() > 0 && name.length() <= 6) // ��ȿ�� �ڸ��� �˻�.
			break;
		cout << "6�ڸ�(�ѱ� 3�ڸ�) ������ �̸��� �Է����ּ���." << endl;
	}
	while (true) { // ��ȿ�� �޴���ȭ��ȣ �Է±��� �ݺ�.
		cout << "�޴���ȭ��ȣ" << endl << ">>";
		cin >> phone;
		if (phone.length() > 0 && phone.length() <= 11) // ��ȿ�� �ڸ��� �˻�.
			break;
		cout << "11�ڸ� ������ �޴���ȭ��ȣ�� �Է����ּ���." << endl;
	}
	member.push_back(new Member(id, password, name, phone)); // ȸ�� ���Ϳ� ���ο� ȸ�� Ŭ���� �߰�.
	cout << name << "���� ������ ȯ���մϴ�!" << endl;
}
void GeneralUser::findId() { // ���̵� ã�� �Լ�.
	string name, phone;
	cout << "�̸�" << endl << ">>";
	cin >> name;
	cout << "�޴���ȭ��ȣ" << endl << ">>";
	cin >> phone;
	for (unsigned int i = 0; i < member.size(); i++)
		if (name == member[i]->getName() && phone == member[i]->getPhone()) { // �Է��� �̸��� �޴���ȭ��ȣ�� ��ġ�ϴ��� �˻�.
			cout << name << "���� ���̵�: " << member[i]->getId() << endl;
			return;
		}
	cout << name << "���� ���̵� �������� �ʽ��ϴ�." << endl;
}
void GeneralUser::secondScreen() { // �� ��° �۾� �ܰ� �Լ�. (���� ���� ȭ��)
	char select;
	int i, count = 0;
	cout << "������������ ���� Ÿ��  ������������" << endl;
	cout << "�����̵�: ";
	cout.width(24);
	cout << left << signedMember->getId() << "��" << endl; // ���ӵ� ȸ���� ���̵� ���
	cout << "��                                ��" << endl;
	cout << "������������ ���� ���  ������������" << endl;
	cout << "��������  ���� ��ȣ  ���� ��ġ  ����" << endl;
	for (i = 0; i < total; i++) {
		int loaction;
		if (car[i]->getId() == signedMember->getId()) { // ���ӵ� ȸ���� ���̵�� ������ �Էµ� ���̵� ��ġ�� ��� ���.
			cout << "����";
			cout.width(4);
			cout << right << ++count << "  "; // ���� ���� ���.
			cout.width(9);
			cout << right << car[i]->getNumber() << "  "; // ���� ��ȣ ���.
			loaction = car[i]->getLocation(); // ������ ��ġ ���� ��������.
			cout << loaction / (COLUMN * ROW) + 1 << "�� " << (char)(loaction / COLUMN % ROW + 65) << "�� " << (char)(loaction % COLUMN + 65) << "������" << endl; // ���� ��ġ ���� ���.
		}
	}
	if (count == 0) { // ������ ���� ��� ���� ���.
		cout << "����                            ����" << endl;
		cout << "����  ������ ������ �����ϴ�.   ����" << endl;
		cout << "����                            ����" << endl;
	}
	cout << "������������������������������������" << endl;
	cout << "�����: ";
	cout.width(2);
	cout << right << FEE << "��/��                   ��" << endl; // ���� ��� FEE�� �Էµ� ��� ���.
	cout << "��                                ��" << endl;
	cout << "��                                ��" << endl;
	cout << "��1. ����                         ��" << endl;
	cout << "��2. ����                         ��" << endl;
	cout << "��3. ȸ�� ���� ����               ��" << endl;
	cout << "��                                ��" << endl;
	cout << "��0. �α׾ƿ�                     ��" << endl;
	cout << "������������������������������������" << endl;
	cout << ">>";
	cin >> select;
	while (cin.get() != '\n');
	switch (select) {
	case '1':
		income(); // ���� ����.
		break;
	case '2':
		outgo(); // ���� ����.
		break;
	case '3':
		step = 3; // ȸ�� ���� ���� �ܰ�(3)���� step �÷��� ����.
		system("cls");
		return;
	case '0':
		cout << "�α׾ƿ� �Ǿ����ϴ�." << endl;
		step = 1; // �α׾ƿ� �� �α��� �ܰ�(1)���� step �÷��� ����.
		break;
	default:
		cout << "������ �� ���� �۾��Դϴ�." << endl;
	}
	system("pause");
}
void GeneralUser::income() { // ���� ���� �Լ�.
	int i = 0, location;
	string number;
	if (total == SPACE) { // �� ���� ���� �ִ� ������ �������� ���.
		cout << "���� ������ ���� á���ϴ�!" << endl;
		cout << "������ �ٽ� �̿����ּ���." << endl;
		return;
	}
	while (true) { // ��ȿ�� ���� �Է±��� �ݺ�.
		cout << "���� ��ȣ" << endl << ">>";
		cin >> number;
		if (number.length() > 8 || number.length() <= 0) { // ���� ��ȣ �ڸ��� ����.
			cout << "8�ڸ� ������ ���� ��ȣ�� �Է����ּ���." << endl;
			continue;
		}
		for (i = 0; i < total; i++)
			if (number == car[i]->getNumber()) { // ���� ��ȣ �ߺ� �˻�.
				cout << "�̹� ������ ���� ��ȣ�Դϴ�." << endl;
				break;
			}
		if (i == total)
			break;
	}
	for (i = 0; i < SPACE; i++) { // �� ���� ������ ã�� �˰���.
		int j = 0;
		for (j = 0; j < total; j++)
			if (i == car[j]->getLocation()) // �̹� ������ �����̸� break;
				break;
		if (j == total) {
			location = i; // �������� ���� �����̸� i�� location�� ����.
			break;
		}
	}
	car[total++] = new Car(location, signedMember->getId(), number, time(NULL)); // ���� Ŭ������ car Ŭ���� ������ �迭�� ���� �Ҵ�.
	cout << number << " ������ " << location / (COLUMN * ROW) + 1 << "�� " << (char)(location / COLUMN % ROW + 65) << "�� " << (char)(location % COLUMN + 65) << "���� �����Ǿ����ϴ�." << endl;
}
void GeneralUser::outgo() { // ���� ���� �Լ�.
	int index, count;
	if (total == 0) { // ������ ������ ���� ���.
		cout << "������ ������ �����ϴ�!" << endl;
		return;
	}
	do { // ��ȿ�� ������ �Էµ� ������ �ݺ�.
		int i;
		count = 0;
		cout << "������ ������ ����" << endl << ">>";
		cin >> index;
		for (i = 0; i < total; i++) {
			int fee, totalCash = 0, j;
			if (car[i]->getId() == signedMember->getId()) // ������ ȸ�� ���̵�� ���ӵ� ȸ���� ���̵� ��ġ�Ѵٸ� ī��Ʈ +1.
				count++;
			if (index == count && count > 0) { // ī��Ʈ�� 0 �ʰ��̰� �Է� ���� ���ΰ� ī��Ʈ�� ���ٸ� ����.
				fee = (int)((time(NULL) - car[i]->getTime()) * FEE); // ���� �ð��� ������ ��� �ð��� ���� ���ϰ� ���� ����� ����.
				cout << "����� " << fee << "�� �Դϴ�." << endl;
				do { // ��ݿ� �´� ������ ���Ե� ������ �ݺ�.
					int cash;
					cout << "�� ���Ե� �ݾ�: " << totalCash << "��" << endl;
					cout << "���� �ݾ�: " << fee - totalCash << "��" << endl;
					cout << "���� ����" << endl << ">>";
					cin >> cash;
					if (cash <= 0) { // �ٸ��� ���� ���� ������ ����.
						cout << "�������� ������ �������ֽʽÿ�." << endl;
						continue;
					}
					totalCash += cash;
				} while (totalCash < fee);
				delete car[i]; // ���� �Ҵ�� ���� Ŭ���� ����.
				car[i] = NULL; // ������ �ʱ�ȭ.
				for (j = i; j < total - 1; j++) // ���� Ŭ���� ������ �迭 ����. (������ ���� �޿��.)
					car[j] = car[j + 1];
				car[j] = NULL; // ������ ���Ҹ� NULL�� �ʱ�ȭ.
				total--; // ���� ������ ���� �� -1.
				cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
				if (totalCash > fee) // ���Ե� ������ ��ݺ��� Ŭ ��� �Ž����� ��ȯ.
					cout << "�Ž��� �� " << totalCash - fee << "���� �����ʽÿ�." << endl;
				cout << "�̿����ּż� �����մϴ�." << endl;
				return;
			}
		}
		cout << "�ٸ� ������ �Է��ϼ���." << endl;
		cin.clear();
		while (cin.get() != '\n');
	} while (index != count);
}
void GeneralUser::thirdScreen() { // �� ��° �۾� �ܰ�. (ȸ�� ���� ���� ȭ��.)
	char select;
	cout << "������������ ���� Ÿ��  ������������" << endl;
	cout << "�����̵�: ";
	cout.width(24);
	cout << left << signedMember->getId() << "��" << endl;
	cout << "���̸�: ";
	cout.width(26);
	cout << left << signedMember->getName() << "��" << endl;
	cout << "���޴���ȭ��ȣ: ";
	cout.width(18);
	cout << left << signedMember->getPhone() << "��" << endl;
	cout << "��                                ��" << endl;
	cout << "��1. ��й�ȣ ����                ��" << endl;
	cout << "��2. �̸� ����                    ��" << endl;
	cout << "��3. �޴���ȭ��ȣ ����            ��" << endl;
	cout << "��4. ȸ�� Ż��                    ��" << endl;
	cout << "��                                ��" << endl;
	cout << "��0. ����                         ��" << endl;
	cout << "������������������������������������" << endl;
	cout << ">>";
	cin >> select;
	while (cin.get() != '\n');
	switch (select) {
	case '1':
		editPassword(); // ��й�ȣ ���� ����.
		break;
	case '2':
		editName(); // �̸� ���� ����.
		break;
	case '3':
		editPhone(); // �޴���ȭ��ȣ ���� ����.
		break;
	case '4':
		withdrawal(); // ȸ�� Ż�� ����.
		break;
	case '0':
		step = 2; // �� ��° �ܰ�� ���ư���. (���� ���� ȭ��)
		system("cls");
		return;
	default:
		cout << "������ �� ���� �۾��Դϴ�." << endl;
	}
	system("pause");
}
void GeneralUser::editPassword() { // ��й�ȣ ���� �Լ�.
	string password;
	while (true) { // ���� ��й�ȣ�� �ٸ� ��й�ȣ �Է±��� �ݺ�.
		cout << "������ ��й�ȣ" << endl << ">>";
		cin >> password;
		if (password != signedMember->getPassword())
			break;
		cout << "���� ��й�ȣ�� �����մϴ�!" << endl;
	};
	signedMember->setPassword(password); // ���ӵ� ȸ���� ��й�ȣ ����.
	cout << "ȸ������ ��й�ȣ�� ����Ǿ����ϴ�." << endl;
}
void GeneralUser::editName() { // �̸� ���� �Լ�.
	string name;
	while (true) { // ���� �̸��� �ٸ� �̸� �Է±��� �ݺ�.
		cout << "������ �̸�" << endl << ">>";
		cin >> name;
		if (name != signedMember->getName())
			break;
		cout << "���� �̸��� �����մϴ�!" << endl;
	};
	signedMember->setName(name); // ���ӵ� ȸ���� �̸� ����.
	cout << "ȸ������ �̸��� ����Ǿ����ϴ�." << endl;
}
void GeneralUser::editPhone() { // �޴���ȭ��ȣ ���� �Լ�.
	string phone;
	while (true) { // ���� ��ȣ�� �ٸ� ��ȣ �Է±��� �ݺ�.
		cout << "������ �޴���ȭ��ȣ" << endl << ">>";
		cin >> phone;
		if (phone != signedMember->getPhone())
			break;
		cout << "���� �޴���ȭ��ȣ�� �����մϴ�!" << endl;
	};
	cout << "ȸ������ �޴���ȭ��ȣ�� ����Ǿ����ϴ�." << endl;
	signedMember->setPhone(phone); // ���ӵ� ȸ���� �޴���ȭ��ȣ ����.
}
void GeneralUser::withdrawal() { // ȸ�� Ż�� �Լ�.
	string password;
	int i = 0;
	for (i = 0; i < SPACE; i++) { // ������ ������ �����ϴ��� �˻�.
		if (car[i] == NULL)
			continue;
		if (car[i]->getId() == signedMember->getId()) // ���ӵ� ȸ�� ���̵�� ��ġ�ϴ� ���� ���� Ȯ�εǸ� break;
			break;
	}
	if (i < SPACE) { // ���� ���� ���� �䱸.
		cout << "���� ������ ������ ��� �����Ͻʽÿ�." << endl;
		return; // �Ʒ� ������ �������� �ʰ� ����.
	}
	while (1) { // �´� ��й�ȣ �Է±��� �ݺ�.
		cout << "��й�ȣ Ȯ��" << endl << ">>";
		cin >> password;
		if (password != signedMember->getPassword()) { // �ٸ� ��� ��ȣ�� �Է��� ���.
			cout << "Ʋ�� ��й�ȣ�Դϴ�." << endl;
			cout << "�ٽ� �Է����ֽʽÿ�." << endl;
			continue;
		}
		for (it = member.begin(); it != member.end(); it++)
			if ((*it)->getId() == signedMember->getId()) { // ���ӵ� ȸ���� ���̵�� ��ġ�ϴ� ���̵� ����.
				it = member.erase(it);
				break;
			}
		delete signedMember; // �ش� ȸ�� Ŭ���� ���� �Ҵ� ����.
		signedMember = NULL; // ���ӵ� ȸ�� ������ �ʱ�ȭ.
		step = 1; // ù��° �۾� �ܰ�� �̵�.
		break;
	}
}

Administrator::Administrator() {
	step = 1; // �ʱ� �۾� �ܰ�� 1�� ����.
	total = 0; // �� ���� ���� ��� 0���� �ʱ�ȭ.
	tIndex = tId = tNumber = tLocation = 1; // ���� ��� ���� ���� �ʱ�ȭ.
	for (int i = 0; i < SPACE; i++) {
		sortedCar[i] = car[i]; // ���ĵ� ���� ������ �迭�� ���� ���� ������ �迭 ����.
		if (car[i] != NULL)
			total++; // ������ ���� �����ŭ total ���� ����.
	}
}
void Administrator::run() { // ������ ��� ���� �Լ�.
	while (step) {
		system("cls");
		switch (step) {
		case 1:
			firstScreen(); // ù ��° �۾� �ܰ� ����.
			break;
		case 2:
			secondScreen(); // �� ��° �۾� �ܰ� ����.
			break;
		case 3:
			thirdScreen(); // �� ��° �۾� �ܰ� ����.
			break;
		}
	}
}
void Administrator::firstScreen() { // ù ��° �۾� �ܰ� ���� �Լ�.
	char select;
	cout << "������������ ���� Ÿ��  ������������" << endl;
	cout << "�������� ���                     ��" << endl;
	cout << "��                                ��" << endl;
	cout << "��1. ������ �α���                ��" << endl;
	cout << "��                                ��" << endl;
	cout << "��0. ����                         ��" << endl;
	cout << "������������������������������������" << endl;
	cout << ">>";
	cin >> select;
	while (cin.get() != '\n');
	switch (select) {
	case '1':
		logIn(); // ������ �α��� ����.
		break;
	case '0':
		step = 0; // ��� ���� �۾� �ܰ�� ���ư���.
		break;
	default:
		cout << "������ �� ���� �۾��Դϴ�." << endl;
		system("pause");
	}
}
void Administrator::logIn() { // ������ �α��� �Լ�.
	string id, password;
	cout << "���̵�" << endl << ">>";
	cin >> id;
	cout << "��й�ȣ" << endl << ">>";
	cin >> password;
	if (id == "admin" && password == "admin") { // �������� ���̵�, ��й�ȣ�� ��ġ�� ���.
		step = 2; // ���� �۾� �ܰ�� �̵�. (���� ���� ȭ��)
		return;
	}
	cout << "������ ���̵�� ��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
	system("pause");
}
void Administrator::secondScreen() { // �� ��° �۾� �ܰ� �Լ�. (���� ���� �۾�)
	char select;
	cout << "������������������ ���� Ÿ��  ������������������" << endl;
	cout << "�������� ���                                 ��" << endl;
	cout << "��                                            ��" << endl;
	cout << "������������������ ���� ���  ������������������" << endl;
	cout << "��������  ���̵�      ���� ��ȣ  ���� ��ġ  ����" << endl;
	outputCarList(sortedCar); // ���� ���¸� �ݿ��� ������ �迭�� ���� ��� ��� �Լ� ����.
	cout << "������������������������������������������������" << endl;
	cout << "�����: ";
	cout.width(2);
	cout << right << FEE << "��/��                               ��" << endl;
	cout << "��                                            ��" << endl;
	cout << "��1. �������� �˻�                            ��" << endl;
	cout << "��2. ���̵�� �˻�                            ��" << endl;
	cout << "��3. ���� ��ȣ�� �˻�                         ��" << endl;
	cout << "��                                            ��" << endl;
	cout << "��4. ���̵� ����(����/����)                   ��" << endl;
	cout << "��5. ���� ��ȣ ����(����/����)                ��" << endl;
	cout << "��6. ���� ��ġ ����(����/����)                ��" << endl;
	cout << "��                                            ��" << endl;
	cout << "��0. �α׾ƿ�                                 ��" << endl;
	cout << "������������������������������������������������" << endl;
	cout << ">>";
	cin >> select;
	while (cin.get() != '\n');
	switch (select) {
	case '1':
		searchCarByIndex(); // �������� �˻� ����.
		break;
	case '2':
		searchCarById(); // ���̵����� �˻� ����.
		break;
	case '3':
		searchCarByNumber(); // ���� ��ȣ�� �˻� ����.
		break;
	case '4':
		sortId(tId); // ���� ���̵� ���� ����.
		tId = ~tId + 1; // ���� ���̵� ������ ������/������ ��� �÷��� ����.
		break;
	case '5':
		sortNumber(tNumber); // ���� ��ȣ ���� ����.
		tNumber = ~tNumber + 1; // ���� ��ȣ ������ ������/������ ��� �÷��� ����.
		break;
	case '6':
		sortLocation(tLocation); // ���� ��ġ ���� ����.
		tLocation = ~tLocation + 1;// ���� ��ġ ������ ������/������ ��� �÷��� ����.
		break;
	case '0':
		step = 1; // ù ��° �ܰ�� �̵�. (�α��� ȭ��)
		break;
	default:
		cout << "������ �� ���� �۾��Դϴ�." << endl;
		system("pause");
	}
}
void Administrator::outputCarList(Car *car[]) { // ���� ���¸� �ݿ��� ���� ��� ��� �Լ�.
	if (total == 0) { // ������ ������ ���� ���.
		cout << "����                                        ����" << endl;
		cout << "����        ������ ������ �����ϴ�.         ����" << endl;
		cout << "����                                        ����" << endl;
		return;
	}
	for (int i = 0; i < total; i++) {
		int loaction;
		cout << "����";
		cout.width(4);
		cout << right << i + 1 << "  "; // ���� ���.
		cout.width(10);
		cout << right << car[i]->getId() << "  "; // ������ ȸ�� ���̵� ���.
		cout.width(9);
		cout << right << car[i]->getNumber() << "  "; // ���� ��ȣ ���.
		loaction = car[i]->getLocation();
		cout << loaction / (COLUMN * ROW) + 1 << "�� " << (char)(loaction / COLUMN % ROW + 65) << "�� " << (char)(loaction % COLUMN + 65) << "������" << endl; // ���� ��ġ ���.
	}
}
void Administrator::searchCarByIndex() { // �������� ���� �˻�.
	int index;
	if (total == 0) { // ������ ������ ���� ���.
		cout << "������ ������ �����ϴ�!" << endl;
		system("pause");
		return;
	}
	while (true) { // �ٸ� ������ �Է��� ������ �ݺ�.
		cout << "�˻��� ������ ����" << endl << ">>";
		cin >> index;
		if (index - 1 >= 0 && index - 1 < total) // �ٸ� ���� �Է� �� break.
			break;
		cout << "�ٸ� ������ �Է��ϼ���." << endl;
		cin.clear();
		while (cin.get() != '\n');
	}
	searchedCar = sortedCar[index - 1]; // �˻��� ������ ��Ÿ���� searchedCar �����Ϳ� sortedCar���� ã�Ƴ� ���� ������ ����.
	step = 3; // ���� �۾� �ܰ�� �̵�. (���� ���� ȭ��)
}
void Administrator::searchCarById() { // ���̵�� ���� �˻�.
	int i, count = 0;
	string id;
	if (total == 0) { // ������ ������ ���� ��� ����.
		cout << "������ ������ �����ϴ�!" << endl;
		system("pause");
		return;
	}
	cout << "�˻��� ������ ���̵�" << endl << ">>";
	cin >> id;
	for (i = 0; i < total; i++) {
		int location;
		if (id == sortedCar[i]->getId()) { // �ش� ���̵�� ��ġ�ϴ� ��� ���� ��� ���.
			count++; // ���� �� ����.
			location = sortedCar[i]->getLocation();
			cout << "����: " << i + 1 << ", ��ġ: " << location / (COLUMN * ROW) + 1 << "�� " << (char)(location / COLUMN % ROW + 65) << "�� " << (char)(location % COLUMN + 65) << "��, ���� ��ȣ: " << sortedCar[i]->getNumber() << endl;
		}
	}
	if (count == 0) // ��ġ�ϴ� ������ �� ã�� ���.
		cout << "�������� �ʴ� ������ ���̵��Դϴ�." << endl;
	system("pause");
}
void Administrator::searchCarByNumber() { // ���� ��ȣ�� �˻�.
	int i;
	string number;
	if (total == 0) { // ���� ������ ���� ���� ��� ����.
		cout << "������ ������ �����ϴ�!" << endl;
		system("pause");
		return;
	}
	cout << "�˻��� ������ ��ȣ" << endl << ">>";
	cin >> number;
	for (i = 0; i < total; i++)
		if (number == car[i]->getNumber()) { // ��ġ�ϴ� ���� ��ȣ�� ã�� ���.
			searchedCar = car[i]; // searchedCar ���� �����Ϳ� �˻��� ���� �����͸� ����.
			step = 3; // ���� �۾� �ܰ�� �̵�. (���� ���� ȭ��)
			break;
		}
	if (i == total) // ��ġ�ϴ� ������ �� ã�� ���.
		cout << "�������� �ʴ� ���� ��ȣ�Դϴ�." << endl;
}
void Administrator::sortId(int order) { // ���̵�� ����.
	int i = 0, j = 0;
	if (total == 0) { // ���� ������ ������ ���� ���� ���.
		cout << "������ ������ �����ϴ�!" << endl;
		system("pause");
		return;
	}
	switch (order) { // ���������� ���������� �Ǵ�.
	case 1: // ��������
		for (int i = 0; i < total - 1; i++) // ���� ���� ����.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getId().compare(sortedCar[j + 1]->getId()) > 0) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	case -1: // ��������
		for (int i = 0; i < total - 1; i++) // ���� ���� ����.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getId().compare(sortedCar[j + 1]->getId()) < 0) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	}
}
void Administrator::sortNumber(int order) { // ���� ��ȣ�� ����.
	int i = 0, j = 0;
	if (total == 0) { // ���� ������ ������ ���� ���� ���.
		cout << "������ ������ �����ϴ�!" << endl;
		system("pause");
		return;
	}
	switch (order) { // ���������� ���������� �Ǵ�.
	case 1: // ��������
		for (int i = 0; i < total - 1; i++) // ���� ���� ����.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getNumber().compare(sortedCar[j + 1]->getNumber()) > 0) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	case -1: // ��������
		for (int i = 0; i < total - 1; i++) // ���� ���� ����.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getNumber().compare(sortedCar[j + 1]->getNumber()) < 0) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	}
}
void Administrator::sortLocation(int order) { // ���� ��ġ�� ����.
	int i = 0, j = 0;
	if (total == 0) { // ���� ������ ������ ���� ���� ���.
		cout << "������ ������ �����ϴ�!" << endl;
		system("pause");
		return;
	}
	switch (order) { // ���������� ���������� �Ǵ�.
	case 1: // ��������
		for (int i = 0; i < total - 1; i++) // ���� ���� ����.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getLocation() > sortedCar[j + 1]->getLocation()) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	case -1: // ��������
		for (int i = 0; i < total - 1; i++) // ���� ���� ����.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getLocation() < sortedCar[j + 1]->getLocation()) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	}
}
void Administrator::thirdScreen() { // �� ��° �۾� �ܰ�. (���� ���� ȭ��)
	char select;
	int i = 0;
	cout << "������������������ ���� Ÿ��  ������������������" << endl;
	cout << "�����̵�: ";
	cout.width(36);
	cout << left << searchedCar->getId() << "��" << endl; // �ش� ������ ȸ�� ���̵� ���.
	cout << "����ġ: ";
	cout.width(2);
	cout << right << i / (COLUMN * ROW) + 1 << "�� " << (char)(i / COLUMN % ROW + 65) << "�� " << (char)(i % COLUMN + 65) << "��                          ��" << endl; // �ش� ������ ��ġ ���.
	cout << "������ ��ȣ: ";
	cout.width(33);
	cout << left << searchedCar->getNumber() << "��" << endl; // �ش� ������ ��ȣ ���.
	cout << "������ ���: ";
	cout.width(4);
	cout << right << (time(NULL) - searchedCar->getTime()) * FEE << "��                           ��" << endl; // �ش� ������ ���� ��� ���.
	cout << "��                                            ��" << endl;
	cout << "��1. ���ΰ�ħ                                 ��" << endl;
	cout << "��2. ����                                     ��" << endl;
	cout << "��                                            ��" << endl;
	cout << "��0. ����                                     ��" << endl;
	cout << "������������������������������������������������" << endl;
	cout << ">>";
	cin >> select;
	while (cin.get() != '\n');
	switch (select) {
	case '1': // ���ΰ�ħ.
		break;
	case '2':
		outCar(); // ���� ����.
		break;
	case '0':
		step = 2; // ���� �۾� �ܰ�� �̵�. (���� ���� ȭ��)
		break;
	default:
		cout << "�߸��� �Է��Դϴ�.";
		system("pause");
	}
}
void Administrator::outCar() { // ���� �Լ�.
	int i, j;
	for (i = 0; i < total; i++) // �˻��� ������ �迭 index�� ã�� ����.
		if (searchedCar->getId() == car[i]->getId())
			break;
	delete car[i]; // �ش� ������ ���� �Ҵ� ����
	car[i] = NULL; // �ش� ������ �����״� car ������ �迭�� ���Ҹ� NULL�� �ʱ�ȭ.
	for (j = i; j < total - 1; j++) // ���� ���Ҹ� �� ĭ�� ��ܼ� �� �ڸ��� �޿�� ����.
		car[j] = car[j + 1];
	car[j] = NULL; // ������ �ڸ��� NULL�� �ʱ�ȭ.
	total--; // ���� ������ ���� ��� -1.
	cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
	for (int i = 0; i < SPACE; i++) // ����� car ������ �迭�� sortedCar ������ �迭�� ����.
		sortedCar[i] = car[i];
	step = 2; // ���� �۾� �ܰ�� �̵�. (���� ���� ȭ��)
	system("pause");
}

TowerManager::TowerManager() { // TowerManager ������. ��� �۾��� �� Ŭ������ �����ڸ� ȣ�� �� ����ȴ�.
	while (true) { // ���Ḧ ������ ������ �ݺ�.
		char select;
		cout << "������������ ���� Ÿ��  ������������" << endl;
		cout << "��                                ��" << endl;
		cout << "��                                ��" << endl;
		cout << "��1. ����� ���                  ��" << endl;
		cout << "��2. ������ ���                  ��" << endl;
		cout << "��                                ��" << endl;
		cout << "��0. ����                         ��" << endl;
		cout << "������������������������������������" << endl;
		cout << ">>";
		cin >> select;
		while (cin.get() != '\n');
		switch (select) {
		case '1':
			user = new GeneralUser(); // �Ϲ� ����� ��� ��ü�� ���� �Ҵ� �� ��ĳ����.
			user->run(); // user ��ü�� run �Լ� ����.
			delete user; // ���� �Ҵ� ����.
			user = NULL; // user ������ NULL�� �ʱ�ȭ.
			break;
		case '2':
			user = new Administrator(); // ������ ��� ��ü�� ���� �Ҵ� �� ��ĳ����.
			user->run(); // user ��ü�� run �Լ� ����.
			delete user; // ���� �Ҵ� ����.
			user = NULL; // user ������ NULL�� �ʱ�ȭ.
			break;
		case '0': // ���� ���� �� ����.
			return;
		default:
			cout << "������ �� ���� �۾��Դϴ�." << endl;
			system("pause");
		}
		system("cls");
	}
}

int main() {
	TowerManager tm; // TowerManager ����.
}