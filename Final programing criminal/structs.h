#include<iostream>   
#include<string>  
#include<vector>




using namespace std;

const int num_of_casesofcriminals = 200;
const int num_of_casesofcrimes = 300;

int num_of_officers{ 0 };
int num_of_criminals{ 0 };
int num_of_crimes{ 0 };

bool Verification = false;
int choice{ 0 };
char a;

struct admin_login
{
	string username;
	string password;
	string ID;
};

struct officer_login
{
	string username;
	string password;
	string officerID;
	int num_assignedcases{ 0 };
	int Crime_ID[num_of_casesofcrimes] = { 0 };
	int num_of_ongoingcrimes{ 0 };
};

struct date
{
	int DAY{ 0 };
	int month{ 0 };
	int year{ 0 };
};

struct Criminal_Data
{
	string criminal_ID{ 0 };
	string name{ 0 };
	string gender{ 0 };
	int age{ 0 };
	float height{ 0 };
	string national_ID{ 0 };
	string nationality{ 0 };
	string country{ 0 };
	string address{ 0 };
	date birthofcriminal{ 0 };
};

struct crime
{
	int crimeID{ 0 };
	int criminals_incase{ 0 };
	string criminal_ID[num_of_casesofcriminals];
	string crimetype;
	string status;
	date DAY_MONTH_YEAR;
};

vector<admin_login> admin1;
officer_login officer[10];
Criminal_Data criminals[num_of_casesofcriminals];
crime crimes[num_of_casesofcrimes];
int check = 0;
