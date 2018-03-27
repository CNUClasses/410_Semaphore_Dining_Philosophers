//============================================================================
// Name        : 410_Semaphore_Dining_Philosophers.cpp
// Author      : 
// Version     :
// Copyright   : Steal this code!
// Description : Deadlock/starvation solution dining philosophers
//============================================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <string>

#include "../../410_Semaphore_Lib/src/Semaphore.h"

using namespace std;

//how many philosophers in the room at a time
const int NUMB_PHILOSOPHERS = 5;

//number forks in room (1 more than numb philosophers or deadlock)
//const int NUMB_FORKS= NUMB_PHILOSOPHERS-1;	//deadlock
//const int NUMB_FORKS= NUMB_PHILOSOPHERS;		//deadlock

//*******************tip***************************
//wanna see where threads are locked? Enable one of the constants above
//set a breakpoint in philosopher (1st report(...) )
//then debug run, use resume to hit the breakpoint NUMB_PHILOSOPHERS times until resume grays
//goto 'Debug' view, the pause button (probably upper left 2 vertical yellow bars next to resume)
//enables you to break into a thread and see what its up to
//*******************tip***************************

const int NUMB_FORKS= NUMB_PHILOSOPHERS+1;	//success, it works

//how much these pigs eat, make it large enough to force failure
const int NUMB_ROUNDS = 100000;

//Semaphore s_philosophers(NUMB_PHILOSOPHERS);
Semaphore s_forks(NUMB_FORKS);

mutex m;
void report(string s){
	lock_guard<mutex> lck(m);
	cout<<s<<endl;
}

void philosopher(int i){
	int nr = NUMB_ROUNDS;
	
	report(string("Philo" + to_string(i) + " starting"));

	while(nr-- >0){
//		report(string("Philo" + to_string(i) + " thinking"));
		
		s_forks.wait();	//get first fork
		s_forks.wait(); //get second

//		report(string("Philo" + to_string(i) + " has forks eating"));
		
		s_forks.signal();	//put down fork
		s_forks.signal(); //put down fork	

//		report(string("Philo" + to_string(i) + " has put down forks"));
	}	
	report(string("Philo" + to_string(i) + " stopping"));

}

int main() {	
	cout << "Starting to eat"<< endl; //

	thread p1(philosopher, 1);
	thread p2(philosopher, 2);
	thread p3(philosopher, 3);
	thread p4(philosopher, 4);
	thread p5(philosopher, 5);

	p1.join();
	p2.join();
	p3.join();
	p4.join();
	p5.join();
	
	cout <<endl<< "Done Eating" <<endl; //

    return 0;
}
