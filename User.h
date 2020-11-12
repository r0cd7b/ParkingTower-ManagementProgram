#ifndef USER_H
#define USER_H
class User {
protected:
	int total;
	vector <Member *> member;
	vector <Member *>::iterator it;
	Car *car[SPACE];
public:
	User();
	~User();
	virtual void run() = 0;
	virtual void firstScreen() = 0;
	virtual void secondScreen() = 0;
	virtual void thirdScreen() = 0;
	void saveFile();
	void loadFile();
};
class GeneralUser : public User {
	int step;
	Member *signedMember;
public:
	GeneralUser();
	virtual void run();
	virtual void firstScreen();
	virtual void logIn();
	void signUp();
	void findId();
	virtual void secondScreen();
	virtual void income();
	virtual void outgo();
	virtual void thirdScreen();
	void editName();
	void editPhone();
	void editPassword();
	void withdrawal();
};
class Administrator : public User {
	int step, total, tIndex, tId, tNumber, tLocation;
	Car *searchedCar;
	Car *sortedCar[SPACE];
public:
	Administrator();
	void run();
	void firstScreen();
	void logIn();
	void secondScreen();
	void outputCarList(Car *car[]);
	void searchCarByIndex();
	void searchCarById();
	void searchCarByNumber();
	void sortId(int order);
	void sortNumber(int order);
	void sortLocation(int order);
	void thirdScreen();
	void outCar();
};
#endif