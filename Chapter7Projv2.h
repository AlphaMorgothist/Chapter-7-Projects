#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;

//Random initializations
void printSlow(string &string);

//Classes
class Enemy {
public:
	Enemy(string name);
	void DisplayTactics();
	void debug();
	int m_Num = 0;
private:
	
};
class Critter {
public:
	Critter(string name, int hunger, int boredom);
	void Talk();
	void Feed();
	void Play();
	void Passtime();
	void Trick();
private:
	string name;
	int m_Hunger;
	int m_Boredom;
	int GetMood();
};
class Alien {
public:
	Alien(int health = 5);
	void Takedamage();
	void Regenerate();
private:
	int m_Health;
};
class Player {
public:
	Player(int ammo = 3);
	void Blast(Alien &anAlien);
	void Reload();
private:
	int m_Ammo;
};
class Stickpile {
public:
	Stickpile(int numsticks);
	void Remove(int sticks);
	void Display();
	int Checkwon();
private:
	int m_Numsticks;
};
class Stickplayer {
public:
	Stickplayer(string &name);
	string name;
	int Getinput();
};
class Stickgame {
public:
	Stickgame(Stickplayer &p1, Stickplayer &p2, Stickpile &sticks);
};
class RPSplayer{
public:
	RPSplayer(string &name);
	const vector<string> hand = { "void", "Rock", "Paper", "Scissors", "void" };
	string curhand;
	string name;
	int wins = 0;
	int GetInput();
};
class RPS {
public:
	RPS(RPSplayer &p1, RPSplayer &p2);
	void Options();
	bool won = false;
};

//Class funct defs

//RPS
RPSplayer::RPSplayer(string & name) :
	name(name) {}
int RPSplayer::GetInput()
{
	int hand[1];
	cout << "\n" << name << "'s selection: ";
	for (int i = 0; i < 1; i++)
	{
		hand[0] = _getch() - '0';

		cout << "*";
	}
	if (hand[0] <= 4 && hand[0] != 0) {
		return hand[0];
	}
	else { return 4; }
}
RPS::RPS(RPSplayer &p1, RPSplayer &p2) {
	while (won != true) {
		if (p1.wins >= 5) {
			cout << "\n" << p1.name << " has won the game!" << endl;
			Sleep(2000);
			won = true;
			break;
		}
		if (p2.wins >= 5) {
			cout << "\n" << p2.name << " has won the game!" << endl;
			Sleep(2000);
			won = true;
			break;
		}
		Options();
		p1.curhand = p1.hand[p1.GetInput()];
		p2.curhand = p2.hand[p2.GetInput()];
		system("CLS");
		if (p1.curhand == "void") {
			srand(time(NULL));
			int num = rand() % 2 + 1;
			p1.curhand = p1.hand[num];
		}
		if (p2.curhand == "void") {
			srand(time(NULL));
			int num = rand() % 2 + 1;
			p2.curhand = p2.hand[num];
		}
		cout << p1.name << "'s hand: " << p1.curhand << endl;
		cout << p2.name << "'s hand: " << p2.curhand << endl;
		cout << "\nThe winner of this round is...";
		if (p1.curhand == "Rock") {
			if (p2.curhand == "Paper") {
				cout << p2.name << "!" << endl; \
					p2.wins++;
			}
			else if (p2.curhand == "Rock") {
				cout << "\nTie Game!\n" << endl;
			}
			else if (p2.curhand == "Scissors") {
				cout << p1.name << "!" << endl;
				p1.wins++;
			}
		}
		if (p1.curhand == "Paper") {
			if (p2.curhand == "Scissors") {
				cout << p2.name << "!" << endl; \
					p2.wins++;
			}
			else if (p2.curhand == "Paper") {
				cout << "\nTie Game!\n" << endl;
			}
			else if (p2.curhand == "Rock") {
				cout << p1.name << "!" << endl;
				p1.wins++;
			}
		}
		if (p1.curhand == "Scissors") {
			if (p2.curhand == "Rock") {
				cout << p2.name << "!" << endl; \
					p2.wins++;
			}
			else if (p2.curhand == "Scissors") {
				cout << "\nTie Game!\n" << endl;
			}
			else if (p2.curhand == "Paper") {
				cout << p1.name << "!" << endl;
				p1.wins++;
			}
		}
	}
}
void RPS::Options() {
	cout << "\n\tChoose your hand!\n\tOr input '4' for a random one!" << endl;
	cout << "\n1: Rock\n2: Paper\n3: Scissors" << endl;
}

//Nim game
Stickpile::Stickpile(int numsticks) :
	m_Numsticks(numsticks) {}
void Stickpile::Remove(int sticks)
{
	m_Numsticks -= sticks;
}
void Stickpile::Display()
{
	system("CLS");
	cout << "Numer of sticks left: " << m_Numsticks << endl;
}
int Stickpile::Checkwon()
{
	if (m_Numsticks <= 0) { return 1; }
	else { return 0; }
}

Stickplayer::Stickplayer(string &name) :
	name(name) {}
int Stickplayer::Getinput()
{
	while (true) {
		cout << "\n" << name << "'s turn. Please enter a number of sticks between 1-4 to remove from the pile" << endl;
		int choice;
		cout << "Number: ";
		cin >> choice;
		system("CLS");
		if (choice > 4 || choice < 0) {
			cout << "\nPlease enter a valid number" << endl;
		}
		else {
			return choice;
		}
	}
}

Stickgame::Stickgame(Stickplayer &p1, Stickplayer &p2, Stickpile &sticks) {
	string intro = "\n\t\tWelcome to NIM.";
	string instruct = "\nEach player takes a turn removing up to 4 sticks from the pile\nThe player to pick up the last stick wins.\n";
	printSlow(intro);
	Sleep(200);
	printSlow(instruct);
	Sleep(2000);
	bool quit = false;
	while (quit != true) {
		sticks.Display();
		int p1rem = p1.Getinput();
		sticks.Remove(p1rem);
		int ifwon = sticks.Checkwon();
		if (ifwon == 1) {
			cout << "\n" << p1.name << " has won the game of NIM!" << endl;
			Sleep(2000);
			quit = true;
			break;
		}
		sticks.Display();
		int p2rem = p2.Getinput();
		sticks.Remove(p2rem);
		ifwon = sticks.Checkwon();
		if (ifwon == 1) {
			cout << "\n" << p2.name << " has won the game of NIM!" << endl;
			Sleep(2000);
			quit = true;
			break;
		}

	}
}//In progress
//Critter Farm
Critter::Critter(string name, int hunger, int boredom) :
	m_Hunger(hunger), m_Boredom(boredom), name(name) {
	cout << "\nA new critter, named " << name << " is born!" << endl;
}
void Critter::Talk()
{
	int mood = GetMood();
	for (int i = mood; i < mood + 1; i++) {
		if (i > 15) {
			cout << "Your creature, "<<name<<", is angry" << endl;
		}
		else if (i > 10) {
			cout << "Your creature, "<<name<<", is slightly upset" << endl;
		}
		else if (i > 5) {
			cout << "Your creature, "<<name<<", is doing alright" << endl;
		}
		else if (i <= 5) {
			cout << "Your creature, "<<name<<", is feeling fine!" << endl;
		}
	}
}
void Critter::Feed()
{
	cout << "Your creature, "<<name<<", eats and is fully fed" << endl;
	m_Hunger = 0;
	Passtime();
}
void Critter::Play()
{
	cout << "You spend a good amount of time playing with " << name << endl;
	m_Boredom = 0;
	Passtime();
}
void Critter::Passtime()
{
	m_Hunger++;
	m_Boredom++;
}
void Critter::Trick()
{
	cout << "Your creature "<<name<<" performs an awesome-ass trick...with it's ass" << endl;
	Passtime();
}
int Critter::GetMood()
{
	int mood = m_Boredom + m_Hunger;

	return mood;
}
//Alien spawn
Enemy::Enemy(string name)
{
	int id1 = rand() % 10000;
	cout << "\nAn enemy ship has entered the sector:" << endl;
	cout << "The ship's name is " << name << id1 << endl;
}
void Enemy::DisplayTactics()
{
	cout << "\nScans indicate there are "<< m_Num << " ships in this sector\n";
	if (m_Num < 5) {
		cout << "Enemy ships set to DEFENSE" << endl;
	}
	else {
		cout << "Enemy ships set to AGGRESSIVE" << endl;
	}
}
void Enemy::debug()
{
	cout << "\nDebug: " << m_Num << endl;
}
//Alien blaster
Alien::Alien(int health) :
	m_Health(health)
{
	cout << "\nAn alien warrior stands before you!" << endl;
}
void Alien::Takedamage()
{
	if (m_Health > 0) {
		m_Health--;
		if (m_Health <= 0) {
			cout << "The alien takes a direct shot, and falls over dead." << endl;
		}
		cout << "Alien health left: " << m_Health << endl;
	}
	else { cout << "The alien is dead!" << endl; }
}
void Alien::Regenerate()
{
	if (m_Health > 0) {
		m_Health++;
		cout << "The alien has regenerated some health!" << endl;
		cout << "Alien health left: " << m_Health << endl;
	}
	else { cout << "The alien is dead!" << endl; }
}

Player::Player(int ammo) :
	m_Ammo(ammo)
{
}
void Player::Blast(Alien & anAlien)
{
	if (m_Ammo > 0) {
		m_Ammo--;
		cout << "\nYou aim your weapon and fire at the alien menace" << endl;
		Sleep(1000);
		string pew = "Pew pew!\n";
		printSlow(pew);
		srand(time(NULL));
		int chance = rand() % 100;
		if (chance >= 50) {
			cout << "\nYour aim is true, and your shot hits the alien scum" << endl;
			anAlien.Takedamage();
		}
		else {
			cout << "\nYour shot missed!" << endl;
			anAlien.Regenerate();
		}
		cout << "Shots left: " << m_Ammo << endl;
	}
	else {
		cout << "\nYou do not have any ammo to shoot with!" << endl;
	}
}
void Player::Reload()
{
	cout << "\nYou reload your weapon" << endl;
	m_Ammo = 4;
}

//Game-Run Functs
void printSlow(string &string) {
	for (int i = 0; i < string.size(); i++)
	{
		Sleep(100);
		cout << string[i];
	}
}
string getName() {
	string name;
	//cin.ignore();
	cout << "\nInput a name for a player: ";
	getline(cin, name);
	if (name != "" && name != " ") {
		return name;
	}
	else { name = "Derpy Mcderp"; return name; }
}
int getInput() {
	cout << "\nPlease enter an option." << endl;
	cout << "Choice: ";
	int choice;
	cin >> choice;
	system("CLS");
	return choice;
}
void chapterOptions() {
	cout << "\n\t\tChapter 7 Projects" << endl;
	cout << "\n1: [Project 7.1] Two Ship-Class Spawn" << endl;
	cout << "2: [Project 7.1] Five Ship-Class Spawn" << endl;
	cout << "3: [Project 7.2] Critter Farm" << endl;
	cout << "4: [Project 7.3] Alien Blaster" << endl;
	cout << "5: [Project 7.4] OOP NIM!" << endl;
	cout << "6: [Project 7.5] Rock-Paper-Scissors" << endl;
	cout << "0: Quit" << endl;
}
void spawnEnemy5() {
	srand(time(NULL));
	string name = "Eb";
	for (int i = 0; i < 5; i++)
	{
		Enemy en4(name);
		en4.m_Num += 5;
		if (i==4){ en4.DisplayTactics(); }
	}
	Sleep(4000);
	system("CLS");
}
void spawnEnemy() {
	srand(time(NULL));
	string name = "En";
	Enemy en1(name);
	Enemy en2(name);
	en2.m_Num += 2;
	en2.DisplayTactics();
	Sleep(4000);
	system("CLS");
}
void critOption() {
	cout << "\nWhat would you like to do?" << endl;
	cout << "\n1: Talk" << endl;
	cout << "2: Feed" << endl;
	cout << "3: Play" << endl;
	cout << "4: Trick" << endl;
	cout << "5: Quit" << endl;
}
void playCrit() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "Welcome to critter farm" << endl;
	Sleep(1000);
	string intro = "\nYour critters will now be spawned... one moment\n";
	for (int i = 0; i < intro.size(); i++)
	{
		cout << intro[i];
		if (intro[i] == '.') {
			Sleep(1000);
		}
		else { Sleep(100); }
	}
	Sleep(1000);
	srand(time(NULL));
	int num1 = rand() % 10 + 1;
	int num2 = rand() % 11;
	Critter crit1("Cretien", 0, 0);
	Sleep(500);
	Critter crit2("Derek", num1, num2);
	Sleep(500);
	Critter crit3("LeeLee", num1, num2);
	Sleep(500);
	Critter crit4("NeeSee", num1, num2);
	Sleep(500);
	Critter crit5("Joe Dirt", num2, num1);
	bool quitcrit = false;
	while (quitcrit != true) {
		critOption();
		int choice = getInput();
		switch (choice) {
		case 1: {
			SetConsoleTextAttribute(h, 0xF0);
			crit1.Talk();
			crit2.Talk();
			crit3.Talk();
			crit4.Talk();
			crit5.Talk();
			SetConsoleTextAttribute(h, 0x0F);
		}break;
		case 2: {
			SetConsoleTextAttribute(h, 0xF0);
			crit1.Feed();
			crit2.Feed();
			crit3.Feed();
			crit4.Feed();
			crit5.Feed(); 
			SetConsoleTextAttribute(h, 0x0F); }break;
		case 3: {
			SetConsoleTextAttribute(h, 0xF0);
			crit1.Play();
			crit2.Play();
			crit3.Play();
			crit4.Play();
			crit5.Play();
			SetConsoleTextAttribute(h, 0x0F); }break;
		case 4: {
			SetConsoleTextAttribute(h, 0xF0);
			crit1.Trick();
			crit2.Trick();
			crit3.Trick();
			crit4.Trick();
			crit5.Trick();
			SetConsoleTextAttribute(h, 0x0F);
		}break;
		case 5: {quitcrit = true; break; }break;
		}
	}
}
void alienOption() {
	cout << "\nWhat would you like to do?" << endl;
	cout << "\n1: Shoot at the alien" << endl;
	cout << "2: Reload" << endl;
	cout << "3: Quit" << endl;
}
void playAlien() {
	bool quit = false;
	Player play;
	cout << "\n\t\tWelcome to";
	string intro = "...\n\t\tALIEN BLASTERRRR!!!!\n";
	printSlow(intro);
	Alien al;
	while (quit != true) {
		alienOption();
		int choice = getInput();
		switch (choice) {
		case 1: {play.Blast(al); }break;
		case 2: {play.Reload(); }break;
		case 3: {quit = true; }break;
		case 10: {al.Takedamage(); }break;
		}
	}
}
void playNIM() {
	cout << "Before we get started, please enter two player names." << endl;
	cin.ignore();
	string name1 = getName();
	string name2 = getName();
	Stickplayer player1(name1);
	Stickplayer player2(name2);
	cout << "\nHow many sticks would you like to play with?\nEnter number 4 or less to get a random pile of sticks." << endl;
	int num = getInput();
	if (num <= 4) {
		num = (rand() % 100 + 10) % 100;
	}
	Stickpile sticks(num);
	string getready = "Thank you. Now loading the game.";
	printSlow(getready);
	Sleep(3000);
	system("CLS");
	Stickgame game(player1, player2, sticks);
}
void playRPS() {
	string intro = "\n\t\tWelcome to Rock Paper Scissors!\nTo start, please enter two player names.\n";
	printSlow(intro);
	cin.ignore();
	string name1 = getName();
	string name2 = getName();
	RPSplayer player1(name1);
	RPSplayer player2(name2);
	string getready = "Thank you. Now loading the game.";
	printSlow(getready);
	Sleep(3000);
	system("CLS");
	RPS game(player1, player2);
}

