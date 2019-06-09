#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string.h>
#include<map>

using namespace std;

class user
{
	public: 
		char uid[20],name[20],pno[11];
		int age;
		void input_data();
		void display_data();
		friend void disp();
};

class candidate : public user
{
	public:
		char party_name[20];
		void input_data();
		void display_data();
};

void user::input_data()
{
	user u;
	ofstream fdata;
	fdata.open("user.txt",ios::app|ios::binary);
	
	cout<<"Enter 10 digit UID : ";
	cin>>u.uid;
	if(strlen(u.uid)==10)
	{
		cout<<"Enter your name : ";
		cin>>u.name;
		cout<<"Enter your age : ";
		cin>>u.age;
		if(u.age>=18)
		{
			cout<<"Enter your phone number : ";
			cin>>u.pno;
			if(strlen(u.pno)==10)
			{
				
				fdata.write((char*)&u,sizeof(u));
				cout<<"\nData Saved!";
			}
			else
			{
				cout<<"\n\nInvalid phone number.";
			}
		}
		else
		{
			cout<<"\nBelow 18 years, so cannot vote.";
		}
	}
	else
	{
			cout<<"Invalid UID.";
	}
	
	fdata.close();
}

void user::display_data()
{
	user u;
	ifstream fdata;
	fdata.open("user.txt",ios::in|ios::binary);
	
	cout<<"\n\nUID\t\tName\tAge\tPh. No.\n";
	while(fdata.read((char*)&u,sizeof(u)))
	{
		cout<<"\n"<<u.uid;
		cout<<"\t"<<u.name;
		cout<<"\t"<<u.age;
		cout<<"\t"<<u.pno;
	}
	fdata.close();
}


void candidate::input_data()
{
	candidate c;
	user u;
	char id[20];
	int found=0;
	ofstream fdata;
	ifstream fuser;
	fdata.open("candidate.txt",ios::app|ios::binary);
	fuser.open("user.txt",ios::in|ios::binary);
	
	cout<<"Enter Unique ID : ";
	cin>>id;
	
	while(fuser.read((char*)&u,sizeof(u)))
	{
		if(strcmp(u.uid,id)==0)
		{
			strcpy(c.uid,u.uid);
			cout<<"\nName : "<<u.name;
			strcpy(c.name,u.name);
			cout<<"\nEnter your age : "<<u.age;
			c.age=u.age;
			cout<<"\nPhone number : "<<u.pno;
			strcpy(c.pno,u.pno);
			cout<<"\n\nEnter your Party Name : ";
			cin>>c.party_name;
								
			fdata.write((char*)&c,sizeof(c));
			cout<<"\nData Saved!";
			found=1;
		}
	}
	if(found==0)
	{
		cout<<"UID not found";
	}
		
	fdata.close();
	fuser.close();
}


void candidate::display_data()
{
	candidate c;
	ifstream fdata;
	fdata.open("candidate.txt",ios::in|ios::binary);
	
	cout<<"\n\nUID\t\tName\t\tParty Name\n";
	while(fdata.read((char*)&c,sizeof(c)))
	{
		cout<<"\n"<<c.uid;
		cout<<"\t"<<c.name;
		cout<<"\t\t"<<c.party_name;
	}
	fdata.close();
}

void disp()
{
    char x;
    cout << "**************************************************************************************************************************************" << endl;
    cout << "                                                         W E L C O M E                                                                " << endl;
    cout << "**************************************************************************************************************************************" << endl << endl << endl;
    cout << "**************************************************************************************************************************************" << endl;
	cout << "                                                      ONLINE VOTING SYSTEM                                                             " << endl << endl; 
    cout << "**************************************************************************************************************************************" << endl << endl;
    cout << "\n\n";
    system("pause");
}

void disp (int a)
{	
    user u;
	candidate c;
	int choice;
	map <string,int> m;
	string s;
	while(1)
	{
		system("cls");
		cout<<"Choose an option:";
	    cout<<"\n1. Become a voter";
	    cout<<"\n2. Display the voters list";
	    cout<<"\n3. Become a candidate";
	    cout<<"\n4. Display the candidates list";
	    cout<<"\n5. Cast your vote";
	    cout<<"\n6. Display the results";
	    cout<<"\n7. Exit";
	    cout<<"\n\nEnter your choice : ";
		cin>>choice;
		
		if(choice==1)
		{
			u.input_data();
		}
		else if(choice==2)
		{
			u.display_data();
		}
		else if(choice==3)
		{
			c.input_data();
		}
		else if(choice==4)
		{
			c.display_data();
		}
		else if(choice==5)
		{
			ifstream fdata;
			char id[20];
			fdata.open("user.txt",ios::in|ios::binary);
			int found=0;
			cout<<"Enter 10 digit UID : ";
			cin>>id;
			while(fdata.read((char*)&u,sizeof(u)))
			{
				if(strcmp(u.uid,id)==0)
				{
					cout<<"Enter the Party name : ";
					cin>>s;
					m[s]++;
					found=1;
				}
			}
			if(found==0)
			{
				cout<<"UID not found";
			}
			fdata.close();
		}
		else if(choice==6)
		{
			ifstream fdata;
			char winner[20]={"No one"};
			int total=0,winner_vote=0;
			fdata.open("candidate.txt",ios::in|ios::binary);
			
			cout<<"\n\nParty Name\tNo. of votes\n";
			while(fdata.read((char*)&c,sizeof(c)))
			{
				cout<<c.party_name<<"\t\t\t"<<m[c.party_name]<<"\n";
				total+=m[c.party_name];
				if((total == 0 && m[c.party_name]!=0) || winner_vote < m[c.party_name])
				{
					winner_vote=m[c.party_name];
					strcpy(winner,c.party_name);
				}
			}
			fdata.close();
			cout<<"\n\nTotal number of votes : "<<total;
			cout<<"\n\n\n\nWinner : "<<winner;
			cout<<"\n\nThe Online Voting process has been completed successfully!!";
		}
		else if(choice==7)
		{
			exit(0);
		}
		cout<<"\n\n";
		system("pause");
	}
}

int main()
{
	disp();
	disp(2);
	return 0;
}

