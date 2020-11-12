#ifndef MEMBER_H
#define MEMBER_H
class Member {
	string id, password, name, phone;
public:
	Member(string id, string password, string name, string phone);
	void setPassword(string password);
	void setName(string name);
	void setPhone(string phone);
	string getId();
	string getPassword();
	string getName();
	string getPhone();
};
#endif