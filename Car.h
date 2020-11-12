#ifndef CAR_H
#define CAR_H
class Car {
	int location;
	string id;
	string number;
	time_t parkingTime;
public:
	Car(int location, string id, string number, time_t parkingTime);
	int getLocation();
	string getId();
	string getNumber();
	time_t getTime();
};
#endif