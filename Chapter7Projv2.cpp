// Chapter7Projv2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include "Chapter7Projv2.h"

int main()
{
	SetConsoleTitle(_T("Chapter 7 Projects"));
	while (true) {
		chapterOptions();
		int choice = getInput();
		switch (choice) {
		case 1: {spawnEnemy(); }break;
		case 2: {spawnEnemy5(); }break;
		case 3: {playCrit(); }break;
		case 4: {playAlien(); }break;
		case 5: {playNIM(); }break;
		case 6: {playRPS(); }break;
		case 0: {return 0; }break;
		}
	}
}


