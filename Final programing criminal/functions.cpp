
#include<iostream>      
#include<fstream>       
#include<string>        
#include<conio.h>      
#include<stdlib.h>
#include"functions.h"
#include"structs.h"
using namespace std;



void Read()
{
	string admin_email, admin_pass, admin_ID;
	ifstream Admin("admins.txt");
	if (Admin.is_open())
	{
		while ((Admin.peek()) != EOF) //end of the file
		{
			getline(Admin, admin_email);
			getline(Admin, admin_pass);
			getline(Admin, admin_ID);

			admin[num_of_admins].username = admin_email;
			admin[num_of_admins].password = admin_pass;
			admin[num_of_admins].ID = admin_ID;

			num_of_admins++;
		}
		Admin.close();
	}

	string officer_email, officer_pass, officer_id, number_of_assignedcases, crime_ID, number_of_ongoing;
	ifstream Officer("Officer.txt");
	if (Officer.is_open())
	{
		while (Officer.peek() != EOF)
		{
			getline(Officer, officer_email);
			getline(Officer, officer_pass);
			getline(Officer, officer_id);
			getline(Officer, number_of_assignedcases);

			officer[num_of_officers].username = officer_email;
			officer[num_of_officers].password = officer_pass;
			officer[num_of_officers].officerID = officer_id;
			officer[num_of_officers].num_assignedcases = stoi(number_of_assignedcases);
			for (int i = 0; i < stoi(number_of_assignedcases); i++)
			{
				getline(Officer, crime_ID);
				officer[num_of_officers].Crime_ID[i] = stoi(crime_ID);
			}
			getline(Officer, number_of_ongoing);
			officer[num_of_officers].num_of_ongoingcrimes = stoi(number_of_ongoing);

			num_of_officers++;
		}
		Officer.close();
	}

	string criminalID, criminal_name, criminal_gender, criminal_age, criminal_height, ID, criminal_nationality, criminal_country, criminal_address;
	string day_of_criminal, month_of_criminal, year_of_criminal;
	ifstream Criminal("Criminal.txt");
	if (Criminal.is_open())
	{
		while (Criminal.peek() != EOF)
		{
			getline(Criminal, criminalID);
			getline(Criminal, criminal_name);
			getline(Criminal, criminal_gender);
			getline(Criminal, criminal_age);
			getline(Criminal, criminal_height);
			getline(Criminal, ID);
			getline(Criminal, criminal_nationality);
			getline(Criminal, criminal_country);
			getline(Criminal, criminal_address);
			getline(Criminal, day_of_criminal);
			getline(Criminal, month_of_criminal);
			getline(Criminal, year_of_criminal);

			criminals[num_of_criminals].criminal_ID = criminalID;
			criminals[num_of_criminals].name = criminal_name;
			criminals[num_of_criminals].gender = criminal_gender;
			criminals[num_of_criminals].age = stoi(criminal_age);
			criminals[num_of_criminals].height = stoi(criminal_height);
			criminals[num_of_criminals].national_ID = ID;
			criminals[num_of_criminals].nationality = criminal_nationality;
			criminals[num_of_criminals].country = criminal_country;
			criminals[num_of_criminals].address = criminal_address;
			criminals[num_of_criminals].birthofcriminal.DAY = stoi(day_of_criminal);
			criminals[num_of_criminals].birthofcriminal.month = stoi(month_of_criminal);
			criminals[num_of_criminals].birthofcriminal.year = stoi(year_of_criminal);

			num_of_criminals++;
		}
		Criminal.close();
	}

	string crime_no, numofcriminals, criminalid, typeofcrime, status, day, month, year;
	ifstream Crime("Crime.txt");

	if (Crime.is_open())
	{
		while (Crime.peek() != EOF)
		{
			getline(Crime, crime_no);
			getline(Crime, numofcriminals);

			crimes[num_of_crimes].crimeID = stoi(crime_no);
			crimes[num_of_crimes].num_of_criminals_involved = stoi(numofcriminals);
			for (int i = 0; i < stoi(numofcriminals); i++)
			{
				getline(Crime, criminalid);
				crimes[num_of_crimes].criminal_ID[i] = criminalid;
			}
			getline(Crime, typeofcrime);
			getline(Crime, status);
			getline(Crime, day);
			getline(Crime, month);
			getline(Crime, year);

			crimes[num_of_crimes].crimetype = typeofcrime;
			crimes[num_of_crimes].status = status;
			crimes[num_of_crimes].DMY.DAY = stoi(day);
			crimes[num_of_crimes].DMY.month = stoi(month);
			crimes[num_of_crimes].DMY.year = stoi(year);

			num_of_crimes++;
		}
		Crime.close();
	}
}

void login()
{
	int num, index;
	cout << "THE CRIMINAL INVESTIGATION SYSTEM" << endl;
	cout << " Admin press 1" << endl;
	cout << "Officer press 2" << endl;


	cin >> num;
	while (num != 1 && num != 2)
	{
		cout << " wrong access ";  cin >> num;
		break;
	}
	system("cls");
	if (num == 1)
	{
		bool verified = checkadmin();

		if (verified == false)
		{
			string adminid;
			cout << "  Please enter your ID to search for your account:   ";     cin >> adminid;
			for (int i = 0; i < 10; i++)
			{
				if (adminid == admin[i].ID)
				{
					cout << " YOUR ID IS CORRECT ,SO WE WILL RESET YOUR PASSWORD" << endl;
					string newpassword;
					cout << "\n  Enter your new password:   ";    cin >> newpassword;
					admin[i].password = newpassword;
					system("cls");
					output_admin();
					verified = true;
					break;
				}
			}
			if (verified == false)
			{
				cout << "\n false access" << endl;
			}
		}
	}
	else if (num == 2)
	{
		bool verified = checkofficer();

		if (verified == false)
		{
			string officerid;
			cout << "  last trial" << endl;
			cout << " enter ID";   cin >> officerid;
			for (int i = 0; i < 10; i++)
			{
				if (officerid == officer[i].officerID)
				{
					cout << "    YOUR ID IS CORRECT, SO WE WILL RESET YOUR PASSWORD" << endl;
					string newpassword;
					cout << "\n  Enter your new password:";    cin >> newpassword;
					officer[i].password = newpassword;
					system("cls");
					index = i;
					output_officer(index);
					verified = true;
					break;
				}
			}
			if (verified == false)
			{
				cout << "wrong ID" << endl;
			}
		}
	}
}

bool checkadmin()
{
	int  trials = 1;
	do
	{
		string useremail, userpassword;
		char pass;
		int i = 0;
		cout << "  Enter your username: ";     cin >> useremail;
		cout << "  Enter your password: ";
		while (true)
		{
			pass = _getch();
			if ((pass >= 'a' && pass <= 'z') || (pass >= 'A' && pass <= 'Z') || (pass >= '0' && pass <= '9'))
			{
				userpassword += pass;
				++i;
				cout << "*";
			}
			if (pass == '\b')
			{
				cout << "\b \b";
				if (userpassword.size() > 0)
				{
					userpassword.resize(userpassword.size() - 1);
					--i;
				}
			}
			if (pass == '\r')
			{
				break;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if ((useremail == admin[i].username) && (userpassword == admin[i].password))
			{

				trials = 4;
				system("cls");
				output_admin();
				Verification = true;
				break;
			}
		}
		if (Verification == false)
		{
			if (i > 8)
			{
				cout << "\n  only 8 char\n";
			}
			else
			{
				cout << "wrong" << endl;
			}
			cout << " \n";
			trials++;
		}
	} while (trials <= 3);

	return Verification;
}

void output_admin()
{
	cout << "LOGIN IS SUCCESSFULLY DONE AS ADMIN" << ">>" << endl;
	cout << "   CRIMINAL INVESTIGATION SYSTEM   " << endl;
	do
	{
		cout << "  1 add new criminal or officer or a crime" << endl << endl;
		cout << "  2 update database" << endl << endl;
		cout << "  3 search for data" << endl << endl;
		cout << "  4 display alll data" << endl << endl;
		cout << "  5 delete data" << endl << endl;
		cout << "  6 assign a crime to officer" << endl << endl;
		cout << "  7 exit after saving data" << endl;
		cout << "choose a function";
		cin >> choice;
		system("cls");

		switch (choice)
		{
		case 1:
		{
			addcrime();
			break;
		}
		case 2:
		{
			updatecrime();
			break;
		}
		case 3:
		{
			search();
			break;
		}
		case 4:
		{
			display_all();
			break;
		}
		case 5:
		{
			deletecrime();
			break;
		}
		case 6:
		{
			assigncrime_officer();
			break;
		}

		case 7:
		{
			Write();
			cout << " done and saved " << endl;
			break;
		}
		default:
		{
			cout << "choose again" << endl;
			output_admin();
			break;
		}
		}
	} while (choice != 7);
}

void addcrime()
{
	do
	{
		cout << "  ADD NEW CRIMINAL/CRIME/OFFICER???" << endl;
		cout << "  Press 1. to add new Criminal or 2. to add new Crime or 3.to add new officer";
		cin >> choice;
		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "wrong choice";  cin >> choice;
			addcrime();
			break;
		}
		system("cls");
		if (choice == 1)
		{
			cout << "DESCRIPTION FOR THE NEW CRIMINAL" << endl;

			cout << "ID"; cin >> criminals[num_of_criminals].criminal_ID;
			cout << endl;
			cout << " name"; cin >> criminals[num_of_criminals].name;
			cout << endl;
			cout << " gender (f or m)"; cin >> criminals[num_of_criminals].gender;
			cout << endl;
			cout << " age"; cin >> criminals[num_of_criminals].age;
			cout << endl;
			cout << "height"; cin >> criminals[num_of_criminals].height;
			cout << endl;
			cout << "national ID"; cin >> criminals[num_of_criminals].national_ID;
			cout << endl;
			cout << "nationality"; cin >> criminals[num_of_criminals].nationality;
			cout << endl;
			cout << "country "; cin >> criminals[num_of_criminals].country;
			cout << endl;
			cout << " address "; cin >> criminals[num_of_criminals].address;
			cout << endl;
			cout << " date of birth"; cin >> criminals[num_of_criminals].birthofcriminal.DAY;
			cout << endl;
			cout << " month of birth"; cin >> criminals[num_of_criminals].birthofcriminal.month;
			cout << endl;
			cout << "year of birth"; cin >> criminals[num_of_criminals].birthofcriminal.year;
			cout << endl;
			num_of_criminals++;

		}
		else if (choice == 2)
		{
			int cnt = 0;
			cout << "PLEASE ENTER THE DESCRIPTION FOR THE NEW CRIME" << endl;
			cout << " Enter the crime ID(int):                           |"; cin >> crimes[num_of_crimes].crimeID;
			cout << endl;
			cout << " Enter the num_of_criminals_involved:               |"; cin >> crimes[num_of_crimes].num_of_criminals_involved;
			cout << endl;
			for (int i = 0; i < crimes[num_of_crimes].num_of_criminals_involved; i++)
			{
				cout << " Enter the ID of criminal num [" << ++cnt << "]:\t\t    |"; cin >> crimes[num_of_crimes].criminal_ID[i];
				cout << endl;
			}
			cout << " Enter the type of crime:                           |"; cin >> crimes[num_of_crimes].crimetype;
			cout << endl;
			cout << " Enter Case status[closed/ongoing/cold/unassigned]: |"; cin >> crimes[num_of_crimes].status;
			cout << endl;
			cout << " PLEASE ENTER THE CRIME DATE" << endl;
			cout << " Enter the crime day(int):                          |"; cin >> crimes[num_of_crimes].DMY.DAY;
			cout << endl;
			cout << " Enter the crime month(int):                        |"; cin >> crimes[num_of_crimes].DMY.month;
			cout << endl;
			cout << " Enter the crime year(int):                         |"; cin >> crimes[num_of_crimes].DMY.year;
			cout << endl;
			cout << " The date is:" << crimes[num_of_crimes].DMY.DAY << "/" << crimes[num_of_crimes].DMY.month << "/" << crimes[num_of_crimes].DMY.year << endl;
			num_of_crimes++;

		}
		else
		{
			addofficer();
		}
		system("cls");
		cout << "\n\n  Press [Y/y] to add another Criminal/Crime/officer or [N/n] to go to main menu...";  cin >> a;
		while (a != 'Y' && a != 'y' && a != 'N' && a != 'n')
		{
			cout << "  Invalid character, Please choose character from the options:  ";
			cin >> a;
		}
		if (a == 'Y' || a == 'y')
		{
			Verification = true;
			system("cls");
		}
		else if (a == 'n' || a == 'N')
		{
			Verification = false;
			system("cls");
			break;
		}
		system("cls");
	} while (Verification);
}

void addofficer()
{
	int count = 0;
	cout << "Officer desc." << endl;
	cout << "  Enter the officer_username:                       |"; cin >> officer[num_of_officers].username;
	cout << endl;
	cout << "  Enter the officer_password:                       |"; cin >> officer[num_of_officers].password;
	cout << endl;
	cout << "  Enter the officer_ID:                             |"; cin >> officer[num_of_officers].officerID;
	cout << endl;
	cout << "  Enter the officer_num_of_assignedcases:           |"; cin >> officer[num_of_officers].num_assignedcases;
	cout << endl;
	for (int i = 0; i < officer[num_of_officers].num_assignedcases; i++)
	{
		cout << "  Enter the ID of Crime num [" << ++count << "]:\t\t    |"; cin >> officer[num_of_officers].Crime_ID[i];
		cout << endl;
	}
	cout << "  Enter the num_of_ongoing_crimes:                  |"; cin >> officer[num_of_officers].num_of_ongoingcrimes;
	num_of_officers++;
}

void updatecrime()
{
	int updatecriminal, updatecrime, updateofficer, option1;
	do
	{
		cout << " DO YOU WANT TO UPDATE CRIMINAL/CRIME/OFFICER???";
		cout << "  Press [1]. to update Criminal or [2]. to update Crime or [3]. to update officer...";  cin >> choice;

		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "  Invalid option...Please choose from menu....";  cin >> choice;
			break;
		}
		system("cls");
		if (choice == 1)
		{
			string criminalID, newname, criminalgender, newID, newnationality, newcountry, newaddress;
			int criminalage, criminalday{ 0 }, criminalmonth{ 0 }, criminalyear{ 0 };
			float criminalheight;

			updatecriminal = searchcriminal();
			if (updatecriminal == -1)
			{
				break;
			}
			else
			{
				displaycriminal(updatecriminal);
				cout << "  Please enter the number that you want to modify: ";  cin >> option1;
				switch (option1)
				{
				case 1:
				{
					cout << "  Please enter the correct criminal_ID:"; cin >> criminalID; cout << endl;
					criminals[updatecriminal].criminal_ID = criminalID;
					cout << " Data has been modified successfully" << endl;
					break;
				}
				case 2:
				{
					cout << "  Please enter the correct name:"; cin >> newname;  cout << endl;
					criminals[updatecriminal].name = newname;
					cout << " Data has been modified successfully" << endl;
					break;
				}
				case 3:
				{
					cout << "  Please enter the correct gender:"; cin >> criminalgender;  cout << endl;
					criminals[updatecriminal].gender = criminalgender;
					cout << " Data has been modified successfully" << endl;
					break;
				}
				case 4:
				{
					cout << "  Please enter the correct age:"; cin >> criminalage;  cout << endl;
					criminals[updatecriminal].age = criminalage;
					cout << " Data has been modified successfully" << endl;
					break;
				}
				case 5:
				{
					cout << "  Please enter the correct height:"; cin >> criminalheight;  cout << endl;
					criminals[updatecriminal].height = criminalheight;
					cout << " Data has been modified successfully" << endl;
					break;
				}
				case 6:
				{
					cout << "  Please enter the correct national ID:";  cin >> newID;  cout << endl;
					criminals[updatecriminal].national_ID = newID;
					cout << "  Data has been modified successfully" << endl;
					break;
				}
				case 7:
				{
					cout << "  Please enter the correct nationality:";   cin >> newnationality;  cout << endl;
					criminals[updatecriminal].nationality = newnationality;
					cout << " Data has been modified successfully" << endl;
					break;
				}
				case 8:
				{
					cout << "  Please enter the correct country:";  cin >> newcountry;  cout << endl;
					criminals[updatecriminal].country = newcountry;
					cout << "  Data has been modified successfully" << endl;
					break;
				}
				case 9:
				{
					cout << "  Please enter the correct address:"; cin >> newaddress;  cout << endl;
					criminals[updatecriminal].address = newaddress;
					cout << " Data has been modified successfully" << endl;
					break;
				}
				case 10:
				{
					cout << "  Please enter the correct day_of_Birth:"; cin >> criminalday;   cout << endl;
					criminals[updatecriminal].birthofcriminal.DAY = criminalday;
					cout << "  Data has been modified successfully" << endl;
					break;
				}
				case 11:
				{
					cout << "  Please enter the correct month_of_Birth:"; cin >> criminalmonth;  cout << endl;
					criminals[updatecriminal].birthofcriminal.month = criminalmonth;
					cout << " Data has been modified successfully" << endl;
					break;
				}
				case 12:
				{
					cout << "  Please enter the correct year_of_Birth:"; cin >> criminalday;  cout << endl;
					criminals[updatecriminal].birthofcriminal.year = criminalyear;
					cout << "  Data has been modified successfully" << endl;
					break;
				}
				default:
				{
					cout << "Wrong \n";
					displaycriminal(updatecriminal);
				}
				}
			}
		}
		else if (choice == 2)
		{
			string officerid, criminalID, typeofcrime, crimestatus;
			int crime_no, criminalsinvolved = { 0 }, dayofcrime, monthofcrime, yearofcrime;

			updatecrime = searchcrime();
			if (updatecrime == -1)
			{
				break;
			}
			else
			{
				displaycrime(updatecrime);
				cout << "  Please enter the number you want to modify:  "; cin >> option1;
				switch (option1)
				{
				case 1:
				{
					cout << "  Please enter the correct crime_ID:";   cin >> crime_no;    cout << endl;
					crimes[updatecrime].crimetype = crime_no;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 2:
				{
					cout << "  Please enter the correct number of criminals involved:";   cin >> criminalsinvolved;  cout << endl;
					crimes[updatecrime].num_of_criminals_involved = criminalsinvolved;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 3:
				{
					int number;
					cout << "  Please enter the order of criminal ID that you want to modify:";  cin >> number;
					if (number != 0 && number <= crimes[updatecrime].num_of_criminals_involved)
					{
						cout << "  Please enter the correct criminal ID:";   cin >> criminalID;  cout << endl;
						crimes[updatecrime].criminal_ID[number - 1] = criminalID;
						cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					}
					else
					{
						cout << "  invalid order of criminal_ID..." << endl;
					}
					break;
				}
				case 4:
				{
					cout << "  Please enter the correct crime type:";   cin >> typeofcrime;   cout << endl;
					crimes[updatecrime].crimetype = typeofcrime;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 5:
				{
					cout << "  Please enter the correct status:"; cin >> crimestatus;  cout << endl;
					crimes[updatecrime].status = crimestatus;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 6:
				{
					cout << "  Please enter the correct day of crime:";    cin >> dayofcrime;   cout << endl;
					crimes[updatecrime].DMY.DAY = dayofcrime;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 7:
				{
					cout << "  Please enter the correct month of crime:";    cin >> monthofcrime;  cout << endl;
					crimes[updatecrime].DMY.month = monthofcrime;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 8:
				{
					cout << "  Please enter the correct year of crime:";    cin >> yearofcrime;    cout << endl;
					crimes[updatecrime].DMY.year = yearofcrime;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				default:
				{
					cout << "  Invalid option..\n\n";
					displaycrime(updatecrime);
				}
				}
			}
		}
		else
		{
			string officerusername, officerpass, officerid;
			int assigned, crimeid, ongoing;

			updateofficer = searchofficer();
			if (updateofficer == -1)
			{
				break;
			}
			else
			{
				displayofficer(updateofficer);
				cout << "  Please enter the number you want to modify:  "; cin >> option1; cout << endl;
				switch (option1)
				{
				case 1:
				{
					cout << "  Please enter the correct officer_username: ";    cin >> officerusername;  cout << endl;
					officer[updateofficer].username = officerusername;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 2:
				{
					cout << "  Please enter the correct officer_password: ";    cin >> officerpass;  cout << endl;
					officer[updateofficer].password = officerpass;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 3:
				{
					cout << "  Please enter the correct officer_ID: ";    cin >> officerid;  cout << endl;
					officer[updateofficer].officerID = officerid;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 4:
				{
					cout << "  Please enter the correct num_of_assignedcases: ";    cin >> assigned;  cout << endl;
					officer[updateofficer].num_assignedcases = assigned;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 5:
				{
					int num;
					cout << "  please enter the order of the crime that you want to modify:  ";  cin >> num;
					if (num != 0 && num <= officer[updateofficer].num_assignedcases)
					{
						cout << "  Please enter the correct Crime_ID: ";    cin >> crimeid;  cout << endl;
						officer[updateofficer].Crime_ID[num - 1] = crimeid;
						cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					}
					else
					{
						cout << "  Invalid order of crime." << endl;
					}
					break;
				}
				case 6:
				{
					cout << "  Please enter the correct num_of_ongoing crimes: ";    cin >> ongoing;  cout << endl;
					officer[updateofficer].num_of_ongoingcrimes = ongoing;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				default:
				{
					cout << "  Invalid option..\n\n";
					displayofficer(updateofficer);
				}
				}
			}
		}

		cout << "\n\n  Press [Y/y] to modify another Criminal/Crime/officer or [N/n] to go to main menu....";  cin >> a;
		while (a != 'Y' && a != 'y' && a != 'N' && a != 'n')
		{
			cout << "  Invalid character, Please choose character from the options: ";  cin >> a;
		}
		if (a == 'Y' || a == 'y')
		{
			Verification = true;
			system("cls");
		}
		else if (a == 'n' || a == 'N')
		{
			Verification = false;
			system("cls");
			break;
		}
		system("cls");
	} while (Verification);
}

void search()
{
	int displayindex;
	do
	{

		cout << "\t\t\t\t\t\t\t\t\t\t    ARE YOU LOOKING FOR A CRIMINAL/CRIME/OFFICER???";
		cout << "\n\t\t\t\t\t\t\t\t\t\t   ______________________________________________" << endl;
		cout << "  Press [1]. to search for Criminal or [2]. to search for Crime or [3]. to search for officer..."; cin >> choice;
		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "  Invalid option...\nPlease choose from menu....";   cin >> choice;
			break;
		}
		system("cls");
		cout << "---------------------------------------------------------------------------------------------------------";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		if (choice == 1)
		{
			displayindex = searchcriminal();
			if (displayindex == -1)
			{
				break;
			}
			else
			{
				displaycriminal(displayindex);
			}
		}
		else if (choice == 2)
		{
			displayindex = searchcrime();
			if (displayindex == -1)
			{
				break;
			}
			else
			{
				displaycrime(displayindex);
			}
		}
		else
		{
			displayindex = searchofficer();
			if (displayindex == -1)
			{
				break;
			}
			else
			{
				displayofficer(displayindex);
			}
		}
		cout << "\n\n  Press [Y/y] to look for another Criminal/Crime/officer or [N/n] to go to main menu..."; cin >> a;
		while (a != 'Y' && a != 'y' && a != 'N' && a != 'n')
		{
			cout << "  Invalid character, Please choose character from the options:  ";  cin >> a;
		}
		if (a == 'Y' || a == 'y')
		{
			Verification = true;
			system("cls");
		}
		else if (a == 'n' || a == 'N')
		{
			Verification = false;
			system("cls");
			break;
		}
		system("cls");
	} while (Verification);
}

int searchcriminal()
{
	string searchcriminal; int sendback = -1;
	cout << "  Please enter the Criminal_ID: "; cin >> searchcriminal; cout << endl;
	for (int i = 0; i < num_of_criminals; i++)
	{
		if (searchcriminal == criminals[i].criminal_ID)
		{
			Verification = true;
			sendback = i;
		}
	}
	if (sendback == -1)
	{
		cout << "  Invalid ID of criminal" << endl;
	}

	return sendback;
}

int searchcrime()
{
	int scrimeid; int sendback = -1;
	cout << "  Enter Crime ID:  "; cin >> scrimeid;  cout << endl;
	for (int i = 0; i < num_of_crimes; i++)
	{
		if (scrimeid == crimes[i].crimeID)
			sendback = i;
	}
	if (sendback == -1)
	{
		cout << "  Invalid Crime_ID" << endl;
	}
	return sendback;
}

int searchofficer()
{
	string officerid; int sendback = -1;
	cout << "  Enter OFFICER_ID:  "; cin >> officerid; cout << endl;
	for (int i = 0; i < num_of_officers; i++)
	{
		if (officerid == officer[i].officerID)
			sendback = i;
	}
	if (sendback == -1)
	{
		cout << "  Invalid officer_ID" << endl;
	}
	return sendback;
}

void displaycriminal(int criminalindex)
{
	cout << "  [1]. \t" << "Criminal ID:       \t|" << criminals[criminalindex].criminal_ID << endl;
	cout << "  [2]. \t" << "Name:              \t|" << criminals[criminalindex].name << endl;
	cout << "  [3]. \t" << "Gender:            \t|" << criminals[criminalindex].gender << endl;
	cout << "  [4]. \t" << "Age:               \t|" << criminals[criminalindex].age << endl;
	cout << "  [5]. \t" << "Height:            \t|" << criminals[criminalindex].height << endl;
	cout << "  [6]. \t" << "National ID:       \t|" << criminals[criminalindex].national_ID << endl;
	cout << "  [7]. \t" << "Nationality:       \t|" << criminals[criminalindex].nationality << endl;
	cout << "  [8]. \t" << "Country:           \t|" << criminals[criminalindex].country << endl;
	cout << "  [9]. \t" << "Address:           \t|" << criminals[criminalindex].address << endl;
	cout << "  [10].\t" << "Day Of Birth:      \t|" << criminals[criminalindex].birthofcriminal.DAY << endl;
	cout << "  [11].\t" << "Month Of Birth:    \t|" << criminals[criminalindex].birthofcriminal.month << endl;
	cout << "  [12].\t" << "Year Of Birth:     \t|" << criminals[criminalindex].birthofcriminal.year << endl;
	cout << "  _____________________________________________________________\n";
}

void displaycrime(int crimeindex)
{
	int count = 0;
	cout << "  [1].\t" << "Crime_ID:                   |" << crimes[crimeindex].crimeID << endl;
	cout << "  [2].\t" << "Num_of_criminals_involved:  |" << crimes[crimeindex].num_of_criminals_involved << endl;
	for (int i = 0; i < crimes[crimeindex].num_of_criminals_involved; i++)
	{
		cout << "  [3].\t" << "Criminal_ID of order[" << ++count << "].....|" << crimes[crimeindex].criminal_ID[i] << endl;
	}
	cout << "  [4].\t" << "Crime type:                 |" << crimes[crimeindex].crimetype << endl;
	cout << "  [5].\t" << "Crime status:               |" << crimes[crimeindex].status << endl;
	cout << "  [6].\t" << "Crime day:                  |" << crimes[crimeindex].DMY.DAY << endl;
	cout << "  [7].\t" << "Crime month:                |" << crimes[crimeindex].DMY.month << endl;
	cout << "  [8].\t" << "Crime year:                 |" << crimes[crimeindex].DMY.year << endl;
	cout << "  ____________________________________________________\n";
}

void displayofficer(int officerindex)
{
	int count = 0;
	cout << "  [1].\t" << "Officer Username:               |" << officer[officerindex].username << endl;
	cout << "  [2].\t" << "Officer password:               |" << officer[officerindex].password << endl;
	cout << "  [3].\t" << "Officer_ID:                     |" << officer[officerindex].officerID << endl;
	cout << "  [4].\t" << "num_of_assignedcases:           |" << officer[officerindex].num_assignedcases << endl;
	for (int i = 0; i < officer[officerindex].num_assignedcases; i++)
	{
		cout << "  [5].\t" << "Assigned case of number[" << ++count << "]....  |" << endl;
		cout << "              Crime_ID:\t\t        |" << officer[officerindex].Crime_ID[i] << endl;
	}
	cout << "  [6].\t" << "num_of_ongoing_crimes:          |" << officer[officerindex].num_of_ongoingcrimes << endl;
	cout << "  ____________________________________________________\n";
}

void display_all()
{
	do
	{
		cout << "\t\t\t\t\t\t\t\t\t     DO YOU WANT TO DISPLAY ALL CRIMINALS/CRIMES/OFFICERS???";
		cout << "\n\t\t\t\t\t\t\t\t\t   _______________________________________________________" << endl;
		cout << "  press [1] to display all Criminals or [2] Crimes or [3] Both or [4] officers.....";   cin >> choice;
		while (choice != 1 && choice != 2 && choice != 3 && choice != 4)
		{
			cout << "  Invalid option...Please choose from menu....";  cin >> choice;
			display_all();
			break;
		}
		system("cls");
		cout << "---------------------------------------------------------------------------------------------------------";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		if (choice == 1)
		{
			for (int i = 0; i < num_of_criminals; i++)
			{
				displaycriminal(i);
			}
		}
		else if (choice == 2)
		{
			for (int i = 0; i < num_of_crimes; i++)
			{
				displaycrime(i);
			}
		}
		else if (choice == 3)
		{
			for (int i = 0; i < num_of_criminals; i++)
			{
				displaycriminal(i);
			}
			cout << "\n\t\t\t\t\t\t\t\t\t\t" << "********************************************************";
			cout << "\n\t\t\t\t\t\t\t\t\t\t" << "********************************************************" << endl;
			for (int i = 0; i < num_of_crimes; i++)
			{
				displaycrime(i);
			}
		}
		else
		{
			for (int i = 0; i < num_of_officers; i++)
			{
				displayofficer(i);
			}
		}
		cout << "\n\n  Press [Y/y] to display all Criminals/Crimes/officers or [N/n] to go to main menu..."; cin >> a;
		while (a != 'Y' && a != 'y' && a != 'N' && a != 'n')
		{
			cout << "  Invalid character, Please choose character from the options:  ";   cin >> a;
		}
		if (a == 'Y' || a == 'y')
		{
			Verification = true;
			system("cls");
		}
		else if (a == 'n' || a == 'N')
		{
			Verification = false;
			system("cls");
			break;
		}
		system("cls");
	} while (Verification);
}


void deletecrime()
{
	int index;
	do
	{
		cout << "---------------------------------------------------------------------------------------------------------";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		cout << "\t\t\t\t\t\t\t\t\t\t DO YOU WANT TO DELETE CRIMINAL/CRIME/OFFICER???";
		cout << "\n\t\t\t\t\t\t\t\t\t\t _______________________________________________" << endl;
		cout << "  Press [1] to delete a Criminal or [2] Crime or [3] to delete officer....";  cin >> choice;
		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "  Invalid option...\nPlease choose from menu....";  cin >> choice;
			break;
		}
		system("cls");
		cout << "---------------------------------------------------------------------------------------------------------";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		if (choice == 1)
		{
			char d;
			index = searchcriminal();
			if (index == -1)
			{
				break;
			}
			else
			{
				displaycriminal(index);
				cout << "\n\n  Do you want to delete this Criminal's information? (y/n)...."; cin >> d;
				while (d != 'Y' && d != 'y' && d != 'N' && d != 'n')
				{
					cout << "  Invalid character..."; cin >> d;
					break;
				}
				if (d == 'y' || d == 'Y')
				{
					for (int i = index; i < num_of_criminals - 1; i++)
					{
						criminals[i].criminal_ID = criminals[i + 1].criminal_ID;
						criminals[i].name = criminals[i + 1].name;
						criminals[i].gender = criminals[i + 1].gender;
						criminals[i].age = criminals[i + 1].age;
						criminals[i].height = criminals[i + 1].height;
						criminals[i].national_ID = criminals[i + 1].national_ID;
						criminals[i].nationality = criminals[i + 1].nationality;
						criminals[i].country = criminals[i + 1].country;
						criminals[i].address = criminals[i + 1].address;
						criminals[i].birthofcriminal.DAY = criminals[i + 1].birthofcriminal.DAY;
						criminals[i].birthofcriminal.month = criminals[i + 1].birthofcriminal.month;
						criminals[i].birthofcriminal.year = criminals[i + 1].birthofcriminal.year;
					}
					num_of_criminals--;
					cout << "  Data has been deleted successfully..." << endl;
				}
				else
				{
					break;
				}
			}
		}
		else if (choice == 2)
		{
			char e;
			index = searchcrime();
			if (index == -1)
			{
				break;
			}
			else
			{
				displaycrime(index);
				cout << "\n\n  Do you want to delete this Crime's information? (y/n)..."; cin >> e;
				while (e != 'Y' && e != 'y' && e != 'N' && e != 'n')
				{
					cout << "  Invalid character..."; cin >> e;
					break;
				}
				if (e == 'y' || e == 'Y')
				{
					for (int i = index; i < num_of_crimes - 1; i++)
					{
						crimes[i].crimeID = crimes[i + 1].crimeID;
						crimes[i].num_of_criminals_involved = crimes[i + 1].num_of_criminals_involved;
						for (int j = 0; j < crimes[i].num_of_criminals_involved; j++)
						{
							crimes[i].criminal_ID[j] = crimes[i + 1].criminal_ID[j];
						}

						crimes[i].crimetype = crimes[i + 1].crimetype;
						crimes[i].status = crimes[i + 1].status;
						crimes[i].DMY.DAY = crimes[i + 1].DMY.DAY;
						crimes[i].DMY.month = crimes[i + 1].DMY.month;
						crimes[i].DMY.year = crimes[i + 1].DMY.year;
					}
					num_of_crimes--;
					cout << "  Data has been deleted successfully..." << endl;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			char f;
			index = searchofficer();
			if (index == -1)
			{
				break;
			}
			else
			{
				displayofficer(index);
				cout << "\n\n  Do you want to delete this officer's information? (y/n)..."; cin >> f;
				while (f != 'Y' && f != 'y' && f != 'N' && f != 'n')
				{
					cout << "  Invalid character..."; cin >> f;
					break;
				}
				if (f == 'y' || f == 'Y')
				{
					for (int i = index; i < num_of_officers - 1; i++)
					{
						officer[i].username = officer[i + 1].username;
						officer[i].password = officer[i + 1].password;
						officer[i].officerID = officer[i + 1].officerID;
						officer[i].num_assignedcases = officer[i + 1].num_assignedcases;
						for (int j = 0; j < officer[i].num_assignedcases; j++)
						{
							officer[i].Crime_ID[j] = officer[i + 1].Crime_ID[j];
						}
						officer[i].num_of_ongoingcrimes = officer[i + 1].num_of_ongoingcrimes;
					}
					num_of_officers--;
					cout << "  Data has been deleted successfully..." << endl;
				}
				else
				{
					break;
				}
			}

		}
		cout << "\n\n  Press [Y/y] to delete another Criminal/Crime/officer or [N/n] to go to main menu..."; cin >> a;
		while (a != 'Y' && a != 'y' && a != 'N' && a != 'n')
		{
			cout << "  Invalid character, Please choose character from the options:  ";  cin >> a;
		}
		if (a == 'Y' || a == 'y')
		{
			Verification = true;
			system("cls");
		}
		else if (a == 'n' || a == 'N')
		{
			Verification = false;
			system("cls");
			break;
		}
		system("cls");
	} while (Verification);
}

void assigncrime_officer()
{
	string sofficerid;   int scrimeid;
	int count = 0, cnt = 0;
	do
	{
		cout << "---------------------------------------------------------------------------------------------------------";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		cout << "\t\t\t\t\t\t\tDo you want to  [1].View unassigned Crimes ,[2].View free Officers ,[3].Assign a case to an officer???";
		cout << "\n\t\t\t\t\t\t\t_____________________________________________________________________________________________________" << endl;
		cin >> choice;
		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "  Invalid option...Please choose from menu...";  cin >> choice;
			break;
		}
		system("cls");
		cout << "---------------------------------------------------------------------------------------------------------";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		switch (choice)
		{
		case 1:
		{
			for (int i = 0; i < num_of_crimes; i++)
			{
				if (crimes[i].status == "unassigned")
				{
					Verification = true;
					count++;
					cout << "  VIEW UNASSIGNED CRIME NUMBER [" << count << "]..." << endl;
					displaycrime(i);
				}
			}
			if (Verification == false)
			{
				cout << "  All crimes are assigned to the officers....." << endl;
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < num_of_officers; i++)
			{
				if (officer[i].num_of_ongoingcrimes < 5)
				{
					Verification = true;
					cnt++;
					cout << "  VIEW FREE OFFICER NUMBER" << "[" << cnt << "]..." << endl;
					cout << "  Officer'S ID: " << officer[i].officerID << endl;
					cout << "  ============================" << endl;
				}
			}
			if (Verification == false)
			{
				cout << "  All officers aren't free....." << endl;
			}
			break;
		}
		case 3:
		{
			bool verified = false; bool verify = false;
			cout << "  Please Enter officer's ID to assign a case:  "; cin >> sofficerid;
			cout << endl;
			for (int i = 0; i < num_of_officers; i++)
			{
				if (officer[i].officerID == sofficerid)
				{
					verify = true;
					if (officer[i].num_of_ongoingcrimes < 5)
					{
						cout << "  Enter the ID of the Crime you want to assign to  that officer:  "; cin >> scrimeid;
						cout << endl;
						for (int j = 0; j < num_of_crimes; j++)
						{
							if (crimes[j].crimeID == scrimeid)
							{
								verified = true;
								if (crimes[j].status == "unassigned")
								{
									officer[i].num_assignedcases++;
									officer[i].Crime_ID[officer[i].num_assignedcases - 1] = scrimeid;
									crimes[j].status = "ongoing";
									officer[i].num_of_ongoingcrimes++;
									cout << "\n\t\t\t\t\t\t\t\t\t\t\tCRIME IS SUCCESSFULLY ASSIGNED TO OFFICER....\n";
									cout << "\t\t\t\t\t\t\t\t\t\t\t_____________________________________________\n";
								}
								else
								{
									cout << "  Crime is already assigned to another officer or is closed...\n";
									break;
								}
							}
						}
						if (!verified)
						{
							cout << "\n  Invalid Crime ID..\n\n";
							break;
						}
						break;
					}
					else
					{
						cout << "\n  Officer is already assigned to another cases...\n";
						break;
					}
				}
			}
			if (!verify)
			{
				cout << "  Invalid Officer_ID......" << endl;
				break;
			}
			break;
		}
		default:
		{
			cout << "  Invalid option....\n\n";
			break;
		}
		}
		cout << "\n  Press [Y/y] to assign another Crime or [N/n] to go to main menu...."; cin >> a;
		while (a != 'Y' && a != 'y' && a != 'N' && a != 'n')
		{
			cout << "  Invalid character, Please choose character from the options:  ";  cin >> a;
			break;
		}
		if (a == 'Y' || a == 'y')
		{
			Verification = true;
			system("cls");
		}
		else if (a == 'n' || a == 'N')
		{
			Verification = false;
			system("cls");
			break;
		}
		system("cls");
	} while (Verification);
}


void Write()
{
	ofstream Admin("Admin.txt", std::ofstream::trunc); //delete
	Admin.close();

	ifstream Admininput;
	ofstream Adminoutput;

	Admininput.open("Admin.txt");
	Adminoutput.open("Admin.txt", ios::app); //add

	if (Admininput.is_open())
	{
		for (int i = 0; i < num_of_admins; i++)
		{
			Adminoutput << admin[i].username << endl;
			Adminoutput << admin[i].password << endl;
			Adminoutput << admin[i].ID << endl;
		}
	}

	ofstream Officer("Officer.txt", std::ofstream::trunc);
	Officer.close();

	ifstream Officerinput;
	ofstream Officeroutput;

	Officerinput.open("Officer.txt");
	Officeroutput.open("Officer.txt", ios::app); //add

	if (Officerinput.is_open())
	{
		for (int i = 0; i < num_of_officers; i++)
		{
			Officeroutput << officer[i].username << endl;
			Officeroutput << officer[i].password << endl;
			Officeroutput << officer[i].officerID << endl;
			Officeroutput << officer[i].num_assignedcases << endl;

			for (int j = 0; j < officer[i].num_assignedcases; j++)
			{
				Officeroutput << officer[i].Crime_ID[j] << endl;
			}
			Officeroutput << officer[i].num_of_ongoingcrimes << endl;
		}
	}

	ofstream Criminal("Criminal.txt", std::ofstream::trunc);
	Criminal.close();

	ifstream Criminalinput;
	ofstream Criminaloutput;

	Criminalinput.open("Criminal.txt");
	Criminaloutput.open("Criminal.txt", ios::app); //add

	if (Criminalinput.is_open())
	{
		for (int i = 0; i < num_of_criminals; i++)
		{
			Criminaloutput << criminals[i].criminal_ID << endl;
			Criminaloutput << criminals[i].name << endl;
			Criminaloutput << criminals[i].gender << endl;
			Criminaloutput << criminals[i].age << endl;
			Criminaloutput << criminals[i].height << endl;
			Criminaloutput << criminals[i].national_ID << endl;
			Criminaloutput << criminals[i].nationality << endl;
			Criminaloutput << criminals[i].country << endl;
			Criminaloutput << criminals[i].address << endl;
			Criminaloutput << criminals[i].birthofcriminal.DAY << endl;
			Criminaloutput << criminals[i].birthofcriminal.month << endl;
			Criminaloutput << criminals[i].birthofcriminal.year << endl;
		}
	}

	ofstream Crime("Crime.txt", std::ofstream::trunc);
	Crime.close();

	ifstream Crimeinput;
	ofstream Crimeoutput;

	Crimeinput.open("Crime.txt");
	Crimeoutput.open("Crime.txt", ios::app); //add

	if (Crimeinput.is_open())
	{
		for (int i = 0; i < num_of_crimes; i++)
		{
			Crimeoutput << crimes[i].crimeID << endl;
			Crimeoutput << crimes[i].num_of_criminals_involved << endl;
			for (int j = 0; j < crimes[i].num_of_criminals_involved; j++)
			{
				Crimeoutput << crimes[i].criminal_ID[j] << endl;
			}
			Crimeoutput << crimes[i].crimetype << endl;
			Crimeoutput << crimes[i].status << endl;
			Crimeoutput << crimes[i].DMY.DAY << endl;
			Crimeoutput << crimes[i].DMY.month << endl;
			Crimeoutput << crimes[i].DMY.year << endl;
		}
	}
}

bool checkofficer()
{
	int trials = 1;
	do
	{
		string userpassword, useremail;
		int  index;

		cout << "----------------------------------------------------------------------------------------------------------";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		char pass;
		int i = 0;

		cout << "  This is your [" << trials << "] trial(s):\n";
		cout << "  --------------------------\n";
		cout << "  Enter your username: ";     cin >> useremail;
		cout << "  Enter your password: ";
		while (true)
		{
			pass = _getch();
			if ((pass >= 'a' && pass <= 'z') || (pass >= 'A' && pass <= 'Z') || (pass >= '0' && pass <= '9'))
			{
				userpassword += pass;  //34an ygam3 3la l ableha
				++i;
				cout << "*";
			}
			if (pass == '\b')  //if user typed backspace,i should be greater than 1.
			{
				cout << "\b \b";
				if (userpassword.size() > 0)
				{
					userpassword.resize(userpassword.size() - 1);
					--i;
				}
			}
			if (pass == '\r')    //enter.
			{
				break;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if ((useremail == officer[i].username) && (userpassword == officer[i].password))
			{
				Verification = true;
				trials = 4;
				system("cls");
				index = i;
				output_officer(index);
				break;
			}
		}
		if (Verification == false)
		{
			cout << "\n\n  CLICK [1] IF YOU WANT TO SHOW YOUR PASSWORD...";  cin >> choice;
			if (choice == 1)
			{
				cout << "  Your password: " << userpassword << endl;
			}
			if (i > 8)
			{
				cout << "\n  Invalid password,The maximum number of digits are '8' ,Try again...\n";
			}
			else
			{
				cout << "\n  Invalid username or password..." << endl;
			}
			cout << "  ___________________________________________________________________\n\n";
			trials++;
		}

	} while (trials <= 3);

	return Verification;
}

void output_officer(int officerindex)
{
	int crimenumber;
	cout << "---------------------------------------------------------------------------------------------------------";
	cout << "---------------------------------------------------------------------------------------------------------\n";
	cout << "\t\t\t\t\t\t\t\t\t\t\t<<" << "LOGIN IS SUCCESSFULLY DONE AS OFFICER" << ">>" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t  " << "    _____________________________   " << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t  " << "    CRIMINAL INVESTIGATION SYSTEM   " << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t  " << "    _____________________________   " << endl;
	do
	{
		cout << "---------------------------------------------------------------------------------------------------------";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		cout << "  [1].CHECK ASSIGNED TASKS.\n\n";
		cout << "  [2].CHECK CRIMINAL RECORDS.\n\n";
		cout << "  [3].UPDATE CRIME DATA\n\n";
		cout << "  [4].CHECK SALARY.\n\n";
		cout << "  [5].EXIT.\n";
		cout << "  _____________________________________________" << endl;
		cout << "  Please choose the option that you want:  ";   cin >> choice;
		system("cls");
		cout << "---------------------------------------------------------------------------------------------------------";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		switch (choice)
		{
		case 1:
		{
			if (officer[officerindex].num_assignedcases == 0)
			{
				cout << "  No Assigned Cases yet..\n\n";
				break;
			}
			else
			{
				int count = 0;
				cout << "  Num_of_assignedcases:  [" << officer[officerindex].num_assignedcases << "]..." << endl;
				cout << "  ------------------------------" << endl;
				for (int i = 0; i < officer[officerindex].num_assignedcases; i++)
				{
					cout << "  Assigned case of number[" << ++count << "]...." << endl;
					cout << "  [1].\t" << "Crime_ID:    \t\t\t|" << officer[officerindex].Crime_ID[i] << endl;
					for (int j = 0; j < num_of_crimes; j++)
					{
						if (officer[officerindex].Crime_ID[i] == crimes[j].crimeID)
						{
							cout << "  [2].\t" << "Num_OF_Criminals_Involved:\t|" << crimes[j].num_of_criminals_involved << endl;
							for (int k = 0; k < crimes[j].num_of_criminals_involved; k++)
							{
								cout << "  [3].\t" << "Criminal ID:              \t|" << crimes[j].criminal_ID[k] << endl;
							}
							cout << "  [4].\t" << "Crime type:               \t|" << crimes[j].crimetype << endl;
							cout << "  [5].\t" << "Crime status:             \t|" << crimes[j].status << endl;
							cout << "  [6].\t" << "Crime day:                \t|" << crimes[j].DMY.DAY << endl;
							cout << "  [7].\t" << "Crime month:              \t|" << crimes[j].DMY.month << endl;
							cout << "  [8].\t" << "Crime year:               \t|" << crimes[j].DMY.year << endl;
						}
					}
					cout << "***************************************************************" << endl;
				}
			}
			break;
		}
		case 2:
		{
			for (int j = 0; j < num_of_criminals; j++)
			{
				displaycriminal(j);
			}
			break;
		}
		case 3:
		{
			int crimeindex, newnumofcriminals, newcriminalid;
			string newstatus;
			bool found = false;
			crimeindex = searchcrime();
			if (crimeindex == -1)
			{
				break;
			}
			for (int i = 0; i < officer[officerindex].num_assignedcases; i++)
			{
				if (crimes[crimeindex].crimeID == officer[officerindex].Crime_ID[i])
				{
					found = true;
					break;
				}
			}
			if (found)
			{
				displaycrime(crimeindex);
				cout << "  Do you want to update [1].Crime Status, [2].Number Of Criminals involved or [3].Criminal ID.\n\n";
				cout << "  please enter the number you want to modify:"; cin >> choice;
				while (choice != 1 && choice != 2 && choice != 3)
				{
					cout << "  Invalid option...Please choose from menu..."; cin >> choice;
					break;
				}
				switch (choice)
				{
				case 1:
				{
					cout << "  Please enter the new status:"; cin >> newstatus;  cout << endl;
					crimes[crimeindex].status = newstatus;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 2:
				{
					cout << "  Please enter the new number of criminals involved:";   cin >> newnumofcriminals;  cout << endl;
					crimes[crimeindex].num_of_criminals_involved = newnumofcriminals;
					cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					break;
				}
				case 3:
				{
					int number;
					cout << "  Please enter the order of criminal ID that you want to modify:";  cin >> number;
					if (number != 0 && number <= crimes[crimeindex].num_of_criminals_involved)
					{
						cout << "  Please enter the new criminal ID:";   cin >> newcriminalid;  cout << endl;
						crimes[crimeindex].criminal_ID[number - 1] = newcriminalid;
						cout << "\t\t\t\t\t\t\t\t\t\t  Data has been modified successfully" << endl;
					}
					else
					{
						cout << "  Invalid order of criminal_ID..." << endl;
					}
					break;
				}
				default:
				{
					cout << "  Invalid option..\n\n";
				}
				}//end of switch
			}
			else if (!found)
			{
				cout << "  Invalid Crime ID to that officer..\n\n";
				break;
			}
			break;
		}

		case 5:
		{
			Write();
			cout << "\t\t\t\t\t\t\t\t" << "       THANK YOU FOR YOUR SERVICE      " << endl;
			cout << "\t\t\t\t\t\t\t\t" << "---------------------------------------" << endl;
			break;

		}
		default:
		{
			cout << "Invalid option..." << endl;
			output_officer(officerindex);
			break;
		}
		}
	} while (choice != 5);
}
