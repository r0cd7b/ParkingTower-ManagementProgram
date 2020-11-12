#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

#include "Enum.h" // enum 상수 정의 파일.
#include "Member.h" // 회원 정보 클래스 정의 파일.
#include "Car.h" // 차 클래스 정의 파일.
#include "User.h" // 사용자 클래스 정의 파일.
#include "TowerManager.h" // 주차 관리 도구 정의 파일.

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
	total = 0; // 현재 차량 수 초기화.
	for (int i = 0; i < SPACE; i++)
		car[i] = NULL; // 차량 클래스 배열 초기화.
	loadFile(); // 생성자 호출 즉시 저장된 정보 불러오기.
}
User::~User() {
	saveFile(); // 소멸자 호출 즉시 정보 저장하기.
	for (unsigned int i = 0; i < member.size(); i++) { // 동적 할당된 멤버 모두 해제.
		delete member[i];
		member[i] = NULL;
	}
	for (int i = 0; i < total; i++) { // 동적 할당된 차량 모두 해제.
		delete car[i];
		car[i] = NULL;
	}
	cout << "이용해주셔서 감사합니다." << endl;
}
void User::saveFile() { // 파일 저장 함수.
	ofstream fout;
	fout.open("member.txt"); // member.txt 파일 오픈.
	for (unsigned int i = 0; i < member.size(); i++) // 구분자 '$'를 이용한 데이터 구분 로딩.
		fout << member[i]->getId() << '$' << member[i]->getPassword() << '$' << member[i]->getName() << '$' << member[i]->getPhone() << '$' << endl;
	fout.close(); // member.txt 파일 클로즈.
	fout.open("car.txt"); // car.txt 파일 오픈.
	for (int i = 0; i < total; i++) // 구분자 '$'를 이용한 데이터 구분 저장.
		fout << car[i]->getLocation() << '$' << car[i]->getId() << '$' << car[i]->getNumber() << '$' << car[i]->getTime() << '$' << endl;
	fout.close(); // car.txt 파일 클로즈.
}
void User::loadFile() { // 파일 불러오기 함수.
	char c;
	int i = 0;
	ifstream fin;
	fin.open("member.txt"); // 회원 정보 파일 오픈.
	while (true) {
		string id = "", password = "", name = "", phone = "";
		while ((c = fin.get()) != EOF) { // 아이디 가져오기.
			if (c == '\n') continue; // 개행 문자는 무시.
			if (c == '$') break; // 구분자로 구분.
			id += c; // id 스트링에 해당 문자 삽입.
		}
		if (c == EOF) break;
		while ((c = fin.get()) != EOF) { // 비밀번호 가져오기.
			if (c == '\n') continue; // 개행 문자는 무시.
			if (c == '$') break; // 구분자로 구분.
			password += c; // password 스트링에 해당 문자 삽입.
		}
		if (c == EOF) break;
		while ((c = fin.get()) != EOF) { // 이름 가져오기.
			if (c == '\n') continue; // 개행 문자는 무시.
			if (c == '$') break; // 구분자로 구분.
			name += c; // name 스트링에 해당 문자 삽입.
		}
		if (c == EOF) break;
		while ((c = fin.get()) != EOF) { // 전화번호 가져오기.
			if (c == '\n') continue; // 개행 문자는 무시.
			if (c == '$') break; // 구분자로 구분.
			phone += c; // phone 스트링에 해당 문자 삽입.
		}
		if (c == EOF) break;
		member.push_back(new Member(id, password, name, phone)); // 불러온 데이터로 Member 클래스를 동적 할당 후 member 포인터 벡터에 삽입.
	}
	fin.close();
	fin.open("car.txt"); // 차량 정보 파일 오픈.
	while (i < SPACE) {
		string location = "", id = "", number = "", time = "";
		while ((c = fin.get()) != EOF) { // 차량의 위치 정보 가져오기.
			if (c == '\n') continue;
			if (c == '$') break;
			location = c;
		}
		while ((c = fin.get()) != EOF) { // 차량의 회원 아이디 가져오기.
			if (c == '\n') continue;
			if (c == '$') break;
			id += c;
		}
		if (c == EOF) break;
		while ((c = fin.get()) != EOF) { // 차량 번호 가져오기.
			if (c == '\n') continue;
			if (c == '$') break;
			number += c;
		}
		if (c == EOF) break;
		while ((c = fin.get()) != EOF) { // 입차 시간 정보 가져오기.
			if (c == '\n') continue;
			if (c == '$') break;
			time += c;
		}
		if (c == EOF) break;
		car[i++] = new Car(stoi(location), id, number, stoi(time)); // 불러온 데이터로 Car 클래스를 동적 할당 후 car 포인터 배열에 삽입.
		total++; // 현재 차량 수 증가.
	}
	fin.close();
}

GeneralUser::GeneralUser() {
	step = 1; // 기본 작업 단계 1
	signedMember = NULL; // 접속된 멤버 NULL 초기화.
}
void GeneralUser::run() { // 일반 사용자 모드 실행 함수.
	while (step) { // step 플래그, 즉, 작업 단계가 0이면 프로그램 종료.
		system("cls");
		switch (step) { // step의 플래그에 따라 작업 단계 변경.
		case 1:
			firstScreen(); // 첫 번째 단계 수행. (로그인, 회원가입, 아이디 찾기)
			break;
		case 2:
			secondScreen(); // 두 번째 단계 수행. (차량 관리 화면)
			break;
		case 3:
			thirdScreen(); // 세 번째 단계 수행. (회원 정보 수정 화면)
			break;
		}
	}
}
void GeneralUser::firstScreen() { // 첫 번째 작업 단계 함수.
	char select;
	cout << "┏━━━━━ 주차 타워  ━━━━━┓" << endl;
	cout << "┃                                ┃" << endl;
	cout << "┃                                ┃" << endl;
	cout << "┃1. 로그인                       ┃" << endl;
	cout << "┃2. 회원가입                     ┃" << endl;
	cout << "┃3. 아이디 찾기                  ┃" << endl;
	cout << "┃                                ┃" << endl;
	cout << "┃0. 이전                         ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━┛" << endl;
	cout << ">>";
	cin >> select; // 메뉴 선택.
	while (cin.get() != '\n');
	switch (select) {
	case '1':
		logIn(); // 로그인.
		break;
	case '2':
		signUp(); // 회원가입.
		break;
	case '3':
		findId(); // 아이디 찾기.
		break;
	case '0':
		step = 0; // 종료 선택 시 작업 단계 0 설정.
		return;
	default:
		cout << "수행할 수 없는 작업입니다." << endl;
	}
	system("pause");
}
void GeneralUser::logIn() { // 로그인 함수.
	string id, password;
	cout << "아이디" << endl << ">>";
	cin >> id;
	cout << "비밀번호" << endl << ">>";
	cin >> password;
	for (unsigned int i = 0; i < member.size(); i++) // 회원 벡터 수만큼 반복.
		if (id == member[i]->getId() && password == member[i]->getPassword()) { // 아이디와 비밀번호가 일치할 경우.
			signedMember = member[i]; // 접속된 회원 포인터에 일치하는 회원 클래스 주소를 전달.
			cout << id << "(으)로 로그인 되었습니다." << endl;
			step = 2; // 작업 단계 2로 설정.
			return;
		}
	cout << "등록되지 않은 아이디이거나, 아이디 또는 비밀번호를 잘못 입력하셨습니다." << endl;
}
void GeneralUser::signUp() { // 회원가입 함수.
	string id, password, name, phone;
	unsigned int i;
	while (true) { // 유효한 아이디 입력까지 반복.
		cout << "아이디" << endl << ">>";
		cin >> id;
		if (id.length() < 4 || id.length() > 10) { // 유효한 자릿수 검사.
			cout << "4자리 이상 10자리 이하의 아이디를 입력해주세요." << endl;
			continue;
		}
		for (i = 0; i < member.size(); i++) // 아이디 중복 검사.
			if (id == member[i]->getId()) {
				cout << "이미 사용 중인 아이디입니다." << endl;
				break;
			}
		if (i == member.size())
			break;
	}
	while (true) { // 유효한 비밀번호 입력까지 반복.
		cout << "비밀번호" << endl << ">>";
		cin >> password;
		if (password.length() >= 4 && password.length() <= 8) // 유효한 자릿수 검사.
			break;
		cout << "4자리 이상 8자리 이하의 비밀번호를 입력해주세요." << endl;
	}
	while (true) { // 유효한 이름 입력까지 반복.
		cout << "이름" << endl << ">>";
		cin >> name;
		if (name.length() > 0 && name.length() <= 6) // 유효한 자릿수 검사.
			break;
		cout << "6자리(한글 3자리) 이하의 이름을 입력해주세요." << endl;
	}
	while (true) { // 유효한 휴대전화번호 입력까지 반복.
		cout << "휴대전화번호" << endl << ">>";
		cin >> phone;
		if (phone.length() > 0 && phone.length() <= 11) // 유효한 자릿수 검사.
			break;
		cout << "11자리 이하의 휴대전화번호을 입력해주세요." << endl;
	}
	member.push_back(new Member(id, password, name, phone)); // 회원 벡터에 새로운 회원 클래스 추가.
	cout << name << "님의 가입을 환영합니다!" << endl;
}
void GeneralUser::findId() { // 아이디 찾기 함수.
	string name, phone;
	cout << "이름" << endl << ">>";
	cin >> name;
	cout << "휴대전화번호" << endl << ">>";
	cin >> phone;
	for (unsigned int i = 0; i < member.size(); i++)
		if (name == member[i]->getName() && phone == member[i]->getPhone()) { // 입력한 이름과 휴대전화번호가 일치하는지 검사.
			cout << name << "님의 아이디: " << member[i]->getId() << endl;
			return;
		}
	cout << name << "님의 아이디가 존재하지 않습니다." << endl;
}
void GeneralUser::secondScreen() { // 두 번째 작업 단계 함수. (차량 관리 화면)
	char select;
	int i, count = 0;
	cout << "┏━━━━━ 주차 타워  ━━━━━┓" << endl;
	cout << "┃아이디: ";
	cout.width(24);
	cout << left << signedMember->getId() << "┃" << endl; // 접속된 회원의 아이디 출력
	cout << "┃                                ┃" << endl;
	cout << "┃┌──── 차량 목록  ────┐┃" << endl;
	cout << "┃│색인  차량 번호  주차 위치  │┃" << endl;
	for (i = 0; i < total; i++) {
		int loaction;
		if (car[i]->getId() == signedMember->getId()) { // 접속된 회원의 아이디와 차량에 입력된 아이디가 일치할 경우 출력.
			cout << "┃│";
			cout.width(4);
			cout << right << ++count << "  "; // 색인 정보 출력.
			cout.width(9);
			cout << right << car[i]->getNumber() << "  "; // 차량 번호 출력.
			loaction = car[i]->getLocation(); // 차량의 위치 정보 가져오기.
			cout << loaction / (COLUMN * ROW) + 1 << "층 " << (char)(loaction / COLUMN % ROW + 65) << "행 " << (char)(loaction % COLUMN + 65) << "열│┃" << endl; // 차량 위치 정보 출력.
		}
	}
	if (count == 0) { // 차량이 없을 경우 예외 출력.
		cout << "┃│                            │┃" << endl;
		cout << "┃│  주차된 차량이 없습니다.   │┃" << endl;
		cout << "┃│                            │┃" << endl;
	}
	cout << "┃└──────────────┘┃" << endl;
	cout << "┃요금: ";
	cout.width(2);
	cout << right << FEE << "원/초                   ┃" << endl; // 현재 상수 FEE에 입력된 요금 출력.
	cout << "┃                                ┃" << endl;
	cout << "┃                                ┃" << endl;
	cout << "┃1. 입차                         ┃" << endl;
	cout << "┃2. 출차                         ┃" << endl;
	cout << "┃3. 회원 정보 수정               ┃" << endl;
	cout << "┃                                ┃" << endl;
	cout << "┃0. 로그아웃                     ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━┛" << endl;
	cout << ">>";
	cin >> select;
	while (cin.get() != '\n');
	switch (select) {
	case '1':
		income(); // 입차 수행.
		break;
	case '2':
		outgo(); // 출차 수행.
		break;
	case '3':
		step = 3; // 회원 정보 수행 단계(3)으로 step 플래그 설정.
		system("cls");
		return;
	case '0':
		cout << "로그아웃 되었습니다." << endl;
		step = 1; // 로그아웃 시 로그인 단계(1)으로 step 플래스 설정.
		break;
	default:
		cout << "수행할 수 없는 작업입니다." << endl;
	}
	system("pause");
}
void GeneralUser::income() { // 차량 입차 함수.
	int i = 0, location;
	string number;
	if (total == SPACE) { // 총 차량 수가 최대 공간에 도달했을 경우.
		cout << "주차 공간이 가득 찼습니다!" << endl;
		cout << "다음에 다시 이용해주세요." << endl;
		return;
	}
	while (true) { // 유효한 차량 입력까지 반복.
		cout << "차량 번호" << endl << ">>";
		cin >> number;
		if (number.length() > 8 || number.length() <= 0) { // 차량 번호 자릿수 제한.
			cout << "8자리 이하의 차량 번호를 입력해주세요." << endl;
			continue;
		}
		for (i = 0; i < total; i++)
			if (number == car[i]->getNumber()) { // 차량 번호 중복 검사.
				cout << "이미 주차된 차량 번호입니다." << endl;
				break;
			}
		if (i == total)
			break;
	}
	for (i = 0; i < SPACE; i++) { // 빈 주차 공간을 찾는 알고리즘.
		int j = 0;
		for (j = 0; j < total; j++)
			if (i == car[j]->getLocation()) // 이미 주차된 공간이면 break;
				break;
		if (j == total) {
			location = i; // 주차되지 않은 공간이면 i를 location에 삽입.
			break;
		}
	}
	car[total++] = new Car(location, signedMember->getId(), number, time(NULL)); // 차량 클래스를 car 클래스 포인터 배열에 동적 할당.
	cout << number << " 차량이 " << location / (COLUMN * ROW) + 1 << "층 " << (char)(location / COLUMN % ROW + 65) << "행 " << (char)(location % COLUMN + 65) << "열에 주차되었습니다." << endl;
}
void GeneralUser::outgo() { // 차량 출차 함수.
	int index, count;
	if (total == 0) { // 주차된 차량이 없을 경우.
		cout << "출차할 차량이 없습니다!" << endl;
		return;
	}
	do { // 유효한 색인이 입력될 때까지 반복.
		int i;
		count = 0;
		cout << "출차할 차량의 색인" << endl << ">>";
		cin >> index;
		for (i = 0; i < total; i++) {
			int fee, totalCash = 0, j;
			if (car[i]->getId() == signedMember->getId()) // 차량의 회원 아이디와 접속된 회원의 아이디가 일치한다면 카운트 +1.
				count++;
			if (index == count && count > 0) { // 카운트가 0 초과이고 입력 받은 색인과 카운트가 같다면 수행.
				fee = (int)((time(NULL) - car[i]->getTime()) * FEE); // 현재 시간과 주차한 당시 시간의 차를 구하고 단위 요금을 곱함.
				cout << "요금은 " << fee << "원 입니다." << endl;
				do { // 요금에 맞는 현금이 삽입될 때까지 반복.
					int cash;
					cout << "총 삽입된 금액: " << totalCash << "원" << endl;
					cout << "남은 금액: " << fee - totalCash << "원" << endl;
					cout << "현금 삽입" << endl << ">>";
					cin >> cash;
					if (cash <= 0) { // 바르지 않은 현금 삽입은 무시.
						cout << "정상적인 현금을 삽입해주십시오." << endl;
						continue;
					}
					totalCash += cash;
				} while (totalCash < fee);
				delete car[i]; // 동적 할당된 차량 클래스 해제.
				car[i] = NULL; // 포인터 초기화.
				for (j = i; j < total - 1; j++) // 차량 클래스 포인터 배열 정리. (삭제된 공간 메우기.)
					car[j] = car[j + 1];
				car[j] = NULL; // 마지막 원소를 NULL로 초기화.
				total--; // 현재 주차된 차량 수 -1.
				cout << "출차가 완료되었습니다." << endl;
				if (totalCash > fee) // 삽입된 현금이 요금보다 클 경우 거스름돈 반환.
					cout << "거스름 돈 " << totalCash - fee << "원을 받으십시오." << endl;
				cout << "이용해주셔서 감사합니다." << endl;
				return;
			}
		}
		cout << "바른 색인을 입력하세요." << endl;
		cin.clear();
		while (cin.get() != '\n');
	} while (index != count);
}
void GeneralUser::thirdScreen() { // 세 번째 작업 단계. (회원 정보 수정 화면.)
	char select;
	cout << "┏━━━━━ 주차 타워  ━━━━━┓" << endl;
	cout << "┃아이디: ";
	cout.width(24);
	cout << left << signedMember->getId() << "┃" << endl;
	cout << "┃이름: ";
	cout.width(26);
	cout << left << signedMember->getName() << "┃" << endl;
	cout << "┃휴대전화번호: ";
	cout.width(18);
	cout << left << signedMember->getPhone() << "┃" << endl;
	cout << "┃                                ┃" << endl;
	cout << "┃1. 비밀번호 변경                ┃" << endl;
	cout << "┃2. 이름 변경                    ┃" << endl;
	cout << "┃3. 휴대전화번호 변경            ┃" << endl;
	cout << "┃4. 회원 탈퇴                    ┃" << endl;
	cout << "┃                                ┃" << endl;
	cout << "┃0. 이전                         ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━┛" << endl;
	cout << ">>";
	cin >> select;
	while (cin.get() != '\n');
	switch (select) {
	case '1':
		editPassword(); // 비밀번호 변경 수행.
		break;
	case '2':
		editName(); // 이름 변경 수행.
		break;
	case '3':
		editPhone(); // 휴대전화번호 변경 수행.
		break;
	case '4':
		withdrawal(); // 회원 탈퇴 수행.
		break;
	case '0':
		step = 2; // 두 번째 단계로 돌아가기. (차량 관리 화면)
		system("cls");
		return;
	default:
		cout << "수행할 수 없는 작업입니다." << endl;
	}
	system("pause");
}
void GeneralUser::editPassword() { // 비밀번호 변경 함수.
	string password;
	while (true) { // 현재 비밀번호와 다른 비밀번호 입력까지 반복.
		cout << "변경할 비밀번호" << endl << ">>";
		cin >> password;
		if (password != signedMember->getPassword())
			break;
		cout << "현재 비밀번호와 동일합니다!" << endl;
	};
	signedMember->setPassword(password); // 접속된 회원의 비밀번호 변경.
	cout << "회원님의 비밀번호가 변경되었습니다." << endl;
}
void GeneralUser::editName() { // 이름 변경 함수.
	string name;
	while (true) { // 현재 이름과 다른 이름 입력까지 반복.
		cout << "변경할 이름" << endl << ">>";
		cin >> name;
		if (name != signedMember->getName())
			break;
		cout << "현재 이름과 동일합니다!" << endl;
	};
	signedMember->setName(name); // 접속된 회원의 이름 변경.
	cout << "회원님의 이름이 변경되었습니다." << endl;
}
void GeneralUser::editPhone() { // 휴대전화번호 변경 함수.
	string phone;
	while (true) { // 현재 번호와 다른 번호 입력까지 반복.
		cout << "변경할 휴대전화번호" << endl << ">>";
		cin >> phone;
		if (phone != signedMember->getPhone())
			break;
		cout << "현재 휴대전화번호와 동일합니다!" << endl;
	};
	cout << "회원님의 휴대전화번호가 변경되었습니다." << endl;
	signedMember->setPhone(phone); // 접속된 회원의 휴대전화번호 변경.
}
void GeneralUser::withdrawal() { // 회원 탈퇴 함수.
	string password;
	int i = 0;
	for (i = 0; i < SPACE; i++) { // 주차된 차량이 존재하는지 검사.
		if (car[i] == NULL)
			continue;
		if (car[i]->getId() == signedMember->getId()) // 접속된 회원 아이디와 일치하는 차량 존재 확인되면 break;
			break;
	}
	if (i < SPACE) { // 주차 차량 출차 요구.
		cout << "먼저 주차된 차량을 모두 출차하십시오." << endl;
		return; // 아래 과정을 수행하지 않고 리턴.
	}
	while (1) { // 맞는 비밀번호 입력까지 반복.
		cout << "비밀번호 확인" << endl << ">>";
		cin >> password;
		if (password != signedMember->getPassword()) { // 다른 비밀 번호를 입력할 경우.
			cout << "틀린 비밀번호입니다." << endl;
			cout << "다시 입력해주십시오." << endl;
			continue;
		}
		for (it = member.begin(); it != member.end(); it++)
			if ((*it)->getId() == signedMember->getId()) { // 접속된 회원의 아이디와 일치하는 아이디 제거.
				it = member.erase(it);
				break;
			}
		delete signedMember; // 해당 회원 클래스 동적 할당 해제.
		signedMember = NULL; // 접속된 회원 포인터 초기화.
		step = 1; // 첫번째 작업 단계로 이동.
		break;
	}
}

Administrator::Administrator() {
	step = 1; // 초기 작업 단계는 1로 설정.
	total = 0; // 총 주차 차량 대수 0으로 초기화.
	tIndex = tId = tNumber = tLocation = 1; // 차량 목록 정렬 정보 초기화.
	for (int i = 0; i < SPACE; i++) {
		sortedCar[i] = car[i]; // 정렬된 차량 포인터 배열에 원본 차량 포인터 배열 복사.
		if (car[i] != NULL)
			total++; // 주차된 차량 대수만큼 total 변수 설정.
	}
}
void Administrator::run() { // 관리자 모드 실행 함수.
	while (step) {
		system("cls");
		switch (step) {
		case 1:
			firstScreen(); // 첫 번째 작업 단계 수행.
			break;
		case 2:
			secondScreen(); // 두 번째 작업 단계 수행.
			break;
		case 3:
			thirdScreen(); // 세 번째 작업 단계 수행.
			break;
		}
	}
}
void Administrator::firstScreen() { // 첫 번째 작업 단계 실행 함수.
	char select;
	cout << "┏━━━━━ 주차 타워  ━━━━━┓" << endl;
	cout << "┃관리자 모드                     ┃" << endl;
	cout << "┃                                ┃" << endl;
	cout << "┃1. 관리자 로그인                ┃" << endl;
	cout << "┃                                ┃" << endl;
	cout << "┃0. 이전                         ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━┛" << endl;
	cout << ">>";
	cin >> select;
	while (cin.get() != '\n');
	switch (select) {
	case '1':
		logIn(); // 관리자 로그인 수행.
		break;
	case '0':
		step = 0; // 모드 선택 작업 단계로 돌아가기.
		break;
	default:
		cout << "수행할 수 없는 작업입니다." << endl;
		system("pause");
	}
}
void Administrator::logIn() { // 관리자 로그인 함수.
	string id, password;
	cout << "아이디" << endl << ">>";
	cin >> id;
	cout << "비밀번호" << endl << ">>";
	cin >> password;
	if (id == "admin" && password == "admin") { // 관리자의 아이디, 비밀번호와 일치할 경우.
		step = 2; // 다음 작업 단계로 이동. (차량 관리 화면)
		return;
	}
	cout << "관리자 아이디와 비밀번호가 일치하지 않습니다." << endl;
	system("pause");
}
void Administrator::secondScreen() { // 두 번째 작업 단계 함수. (차량 관리 작업)
	char select;
	cout << "┏━━━━━━━━ 주차 타워  ━━━━━━━━┓" << endl;
	cout << "┃관리자 모드                                 ┃" << endl;
	cout << "┃                                            ┃" << endl;
	cout << "┃┌─────── 차량 목록  ───────┐┃" << endl;
	cout << "┃│색인  아이디      차량 번호  주차 위치  │┃" << endl;
	outputCarList(sortedCar); // 정렬 상태를 반영한 포인터 배열의 차량 목록 출력 함수 실행.
	cout << "┃└────────────────────┘┃" << endl;
	cout << "┃요금: ";
	cout.width(2);
	cout << right << FEE << "원/초                               ┃" << endl;
	cout << "┃                                            ┃" << endl;
	cout << "┃1. 색인으로 검색                            ┃" << endl;
	cout << "┃2. 아이디로 검색                            ┃" << endl;
	cout << "┃3. 차량 번호로 검색                         ┃" << endl;
	cout << "┃                                            ┃" << endl;
	cout << "┃4. 아이디 정렬(오름/내림)                   ┃" << endl;
	cout << "┃5. 차량 번호 정렬(오름/내림)                ┃" << endl;
	cout << "┃6. 주차 위치 정렬(오름/내림)                ┃" << endl;
	cout << "┃                                            ┃" << endl;
	cout << "┃0. 로그아웃                                 ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
	cout << ">>";
	cin >> select;
	while (cin.get() != '\n');
	switch (select) {
	case '1':
		searchCarByIndex(); // 색인으로 검색 수행.
		break;
	case '2':
		searchCarById(); // 아이디으로 검색 수행.
		break;
	case '3':
		searchCarByNumber(); // 차량 번호로 검색 수행.
		break;
	case '4':
		sortId(tId); // 차량 아이디 정렬 수행.
		tId = ~tId + 1; // 차량 아이디 정렬의 오름차/내림차 토글 플래그 반전.
		break;
	case '5':
		sortNumber(tNumber); // 차량 번호 정렬 수행.
		tNumber = ~tNumber + 1; // 차량 번호 정렬의 오름차/내림차 토글 플래그 반전.
		break;
	case '6':
		sortLocation(tLocation); // 차량 위치 정렬 수행.
		tLocation = ~tLocation + 1;// 차량 위치 정렬의 오름차/내림차 토글 플래그 반전.
		break;
	case '0':
		step = 1; // 첫 번째 단계로 이동. (로그인 화면)
		break;
	default:
		cout << "수행할 수 없는 작업입니다." << endl;
		system("pause");
	}
}
void Administrator::outputCarList(Car *car[]) { // 정렬 상태를 반영한 차량 목록 출력 함수.
	if (total == 0) { // 주차된 차량이 없을 경우.
		cout << "┃│                                        │┃" << endl;
		cout << "┃│        주차된 차량이 없습니다.         │┃" << endl;
		cout << "┃│                                        │┃" << endl;
		return;
	}
	for (int i = 0; i < total; i++) {
		int loaction;
		cout << "┃│";
		cout.width(4);
		cout << right << i + 1 << "  "; // 색인 출력.
		cout.width(10);
		cout << right << car[i]->getId() << "  "; // 차량의 회원 아이디 출력.
		cout.width(9);
		cout << right << car[i]->getNumber() << "  "; // 차량 번호 출력.
		loaction = car[i]->getLocation();
		cout << loaction / (COLUMN * ROW) + 1 << "층 " << (char)(loaction / COLUMN % ROW + 65) << "행 " << (char)(loaction % COLUMN + 65) << "열│┃" << endl; // 차량 위치 출력.
	}
}
void Administrator::searchCarByIndex() { // 색인으로 차량 검색.
	int index;
	if (total == 0) { // 주차된 차량이 없을 경우.
		cout << "주차된 차량이 없습니다!" << endl;
		system("pause");
		return;
	}
	while (true) { // 바른 색인을 입력할 때까지 반복.
		cout << "검색할 차량의 색인" << endl << ">>";
		cin >> index;
		if (index - 1 >= 0 && index - 1 < total) // 바른 색인 입력 시 break.
			break;
		cout << "바른 색인을 입력하세요." << endl;
		cin.clear();
		while (cin.get() != '\n');
	}
	searchedCar = sortedCar[index - 1]; // 검색된 차량을 나타내는 searchedCar 포인터에 sortedCar에서 찾아낸 차량 포인터 대입.
	step = 3; // 다음 작업 단계로 이동. (차량 출차 화면)
}
void Administrator::searchCarById() { // 아이디로 차량 검색.
	int i, count = 0;
	string id;
	if (total == 0) { // 주차된 차량이 없을 경우 리턴.
		cout << "주차된 차량이 없습니다!" << endl;
		system("pause");
		return;
	}
	cout << "검색할 차량의 아이디" << endl << ">>";
	cin >> id;
	for (i = 0; i < total; i++) {
		int location;
		if (id == sortedCar[i]->getId()) { // 해당 아이디와 일치하는 모든 차량 목록 출력.
			count++; // 색인 값 증가.
			location = sortedCar[i]->getLocation();
			cout << "색인: " << i + 1 << ", 위치: " << location / (COLUMN * ROW) + 1 << "층 " << (char)(location / COLUMN % ROW + 65) << "행 " << (char)(location % COLUMN + 65) << "열, 차량 번호: " << sortedCar[i]->getNumber() << endl;
		}
	}
	if (count == 0) // 일치하는 차량을 못 찾은 경우.
		cout << "존재하지 않는 차량의 아이디입니다." << endl;
	system("pause");
}
void Administrator::searchCarByNumber() { // 차량 번호로 검색.
	int i;
	string number;
	if (total == 0) { // 현재 차량이 전혀 없을 경우 리턴.
		cout << "주차된 차량이 없습니다!" << endl;
		system("pause");
		return;
	}
	cout << "검색할 차량의 번호" << endl << ">>";
	cin >> number;
	for (i = 0; i < total; i++)
		if (number == car[i]->getNumber()) { // 일치하는 차량 번호를 찾을 경우.
			searchedCar = car[i]; // searchedCar 차량 포인터에 검색된 차량 포인터를 대입.
			step = 3; // 다음 작업 단계로 이동. (차량 출차 화면)
			break;
		}
	if (i == total) // 일치하는 차량을 못 찾을 경우.
		cout << "존재하지 않는 차량 번호입니다." << endl;
}
void Administrator::sortId(int order) { // 아이디로 정렬.
	int i = 0, j = 0;
	if (total == 0) { // 현재 주차된 차량이 전혀 없을 경우.
		cout << "주차된 차량이 없습니다!" << endl;
		system("pause");
		return;
	}
	switch (order) { // 오름차인지 내림차인지 판단.
	case 1: // 오름차순
		for (int i = 0; i < total - 1; i++) // 버블 정렬 수행.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getId().compare(sortedCar[j + 1]->getId()) > 0) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	case -1: // 내림차순
		for (int i = 0; i < total - 1; i++) // 버블 정렬 수행.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getId().compare(sortedCar[j + 1]->getId()) < 0) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	}
}
void Administrator::sortNumber(int order) { // 차량 번호로 정렬.
	int i = 0, j = 0;
	if (total == 0) { // 현재 주차된 차량이 전혀 없을 경우.
		cout << "주차된 차량이 없습니다!" << endl;
		system("pause");
		return;
	}
	switch (order) { // 오름차인지 내림차인지 판단.
	case 1: // 오름차순
		for (int i = 0; i < total - 1; i++) // 버블 정렬 수행.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getNumber().compare(sortedCar[j + 1]->getNumber()) > 0) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	case -1: // 내림차순
		for (int i = 0; i < total - 1; i++) // 버블 정렬 수행.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getNumber().compare(sortedCar[j + 1]->getNumber()) < 0) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	}
}
void Administrator::sortLocation(int order) { // 차량 위치로 정렬.
	int i = 0, j = 0;
	if (total == 0) { // 현재 주차된 차량이 전혀 없을 경우.
		cout << "주차된 차량이 없습니다!" << endl;
		system("pause");
		return;
	}
	switch (order) { // 오름차인지 내림차인지 판단.
	case 1: // 오름차순
		for (int i = 0; i < total - 1; i++) // 버블 정렬 수행.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getLocation() > sortedCar[j + 1]->getLocation()) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	case -1: // 내림차순
		for (int i = 0; i < total - 1; i++) // 버블 정렬 수행.
			for (int j = 0; j < total - 1 - i; j++)
				if (sortedCar[j]->getLocation() < sortedCar[j + 1]->getLocation()) {
					Car *tmp = sortedCar[j];
					sortedCar[j] = sortedCar[j + 1];
					sortedCar[j + 1] = tmp;
				}
		return;
	}
}
void Administrator::thirdScreen() { // 세 번째 작업 단계. (차량 출차 화면)
	char select;
	int i = 0;
	cout << "┏━━━━━━━━ 주차 타워  ━━━━━━━━┓" << endl;
	cout << "┃아이디: ";
	cout.width(36);
	cout << left << searchedCar->getId() << "┃" << endl; // 해당 차량의 회원 아이디 출력.
	cout << "┃위치: ";
	cout.width(2);
	cout << right << i / (COLUMN * ROW) + 1 << "층 " << (char)(i / COLUMN % ROW + 65) << "행 " << (char)(i % COLUMN + 65) << "열                          ┃" << endl; // 해당 차량의 위치 출력.
	cout << "┃차량 번호: ";
	cout.width(33);
	cout << left << searchedCar->getNumber() << "┃" << endl; // 해당 차량의 번호 출력.
	cout << "┃현재 요금: ";
	cout.width(4);
	cout << right << (time(NULL) - searchedCar->getTime()) * FEE << "원                           ┃" << endl; // 해당 차량의 현재 요금 출력.
	cout << "┃                                            ┃" << endl;
	cout << "┃1. 새로고침                                 ┃" << endl;
	cout << "┃2. 출차                                     ┃" << endl;
	cout << "┃                                            ┃" << endl;
	cout << "┃0. 이전                                     ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
	cout << ">>";
	cin >> select;
	while (cin.get() != '\n');
	switch (select) {
	case '1': // 새로고침.
		break;
	case '2':
		outCar(); // 출차 수행.
		break;
	case '0':
		step = 2; // 이전 작업 단계로 이동. (차량 관리 화면)
		break;
	default:
		cout << "잘못된 입력입니다.";
		system("pause");
	}
}
void Administrator::outCar() { // 출차 함수.
	int i, j;
	for (i = 0; i < total; i++) // 검색된 차량의 배열 index를 찾는 과정.
		if (searchedCar->getId() == car[i]->getId())
			break;
	delete car[i]; // 해당 차량의 동적 할당 해제
	car[i] = NULL; // 해당 차량을 가리켰던 car 포인터 배열의 원소를 NULL로 초기화.
	for (j = i; j < total - 1; j++) // 뒤의 원소를 한 칸씩 당겨서 빈 자리를 메우는 과정.
		car[j] = car[j + 1];
	car[j] = NULL; // 마지막 자리를 NULL로 초기화.
	total--; // 현재 주차된 차량 대수 -1.
	cout << "출차가 완료되었습니다." << endl;
	for (int i = 0; i < SPACE; i++) // 변경된 car 포인터 배열을 sortedCar 포인터 배열에 복사.
		sortedCar[i] = car[i];
	step = 2; // 이전 작업 단계로 이동. (차량 관리 화면)
	system("pause");
}

TowerManager::TowerManager() { // TowerManager 생성자. 모든 작업은 이 클래스의 생성자를 호출 시 수행된다.
	while (true) { // 종료를 수행할 때까지 반복.
		char select;
		cout << "┏━━━━━ 주차 타워  ━━━━━┓" << endl;
		cout << "┃                                ┃" << endl;
		cout << "┃                                ┃" << endl;
		cout << "┃1. 사용자 모드                  ┃" << endl;
		cout << "┃2. 관리자 모드                  ┃" << endl;
		cout << "┃                                ┃" << endl;
		cout << "┃0. 종료                         ┃" << endl;
		cout << "┗━━━━━━━━━━━━━━━━┛" << endl;
		cout << ">>";
		cin >> select;
		while (cin.get() != '\n');
		switch (select) {
		case '1':
			user = new GeneralUser(); // 일반 사용자 모드 객체를 동적 할당 및 업캐스팅.
			user->run(); // user 객체의 run 함수 수행.
			delete user; // 동적 할당 해제.
			user = NULL; // user 포인터 NULL로 초기화.
			break;
		case '2':
			user = new Administrator(); // 관리자 모드 객체를 동적 할당 및 업캐스팅.
			user->run(); // user 객체의 run 함수 수행.
			delete user; // 동적 할당 해제.
			user = NULL; // user 포인터 NULL로 초기화.
			break;
		case '0': // 종료 선택 시 리턴.
			return;
		default:
			cout << "수행할 수 없는 작업입니다." << endl;
			system("pause");
		}
		system("cls");
	}
}

int main() {
	TowerManager tm; // TowerManager 선언.
}