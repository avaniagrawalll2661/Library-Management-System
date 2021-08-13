# include<bits/stdc++.h>
using namespace std;
# include<conio.h>
# include<iostream>
# include<stdlib.h>
# include<iomanip>
# include<string.h>
class book
{
	char bno[6];
	char bname[50];
	char aname[20];
	public:
		void createbook()
		{
			cout<<"\nNEW BOOK ENTRY:..\n";
			cout<<"Enter the book no.\n";
			cin>>bno;
			cout<<"Enter the book name:\n";
			gets(bname);
			cout<<"Enter the author name:\n";
			gets(aname);
			cout<<"\n\nBook created...\n";
		}
		
		void showbook()
		{
			cout<<"Book Number: "<<bno<<endl;
			cout<<"Book Name: ";
			puts(bname);
			cout<<"Author Name: ";
			puts(aname);
		}
		
		void modifybook()
		{
			cout<<"\nBook Number"<<bno;
			cout<<"Modify Book Name: ";
			gets(bname);
			cout<<"Modify Authors Name: ";
			gets(aname);
		}
		
		char *retbno()
		{
			return bno;
		}
		
		void report()
		{
			cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
		}
};


class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
	public:
		void createstudent()
		{
			cout<<"NEW STUDENT ENTRY...\n";
			cout<<"Enter the Admission Number...\n";
			cin>>admno;
			cout<<"Enter the student's name: \n";
			gets(name);
			token=0;
			stbno[0]="\0";
			cout<<"\n\nStudent Record Created..."<<endl;
		}
		
		void showstudent().
		{
			cout<<"Admission Number: "<<admno;
			cout<<"Student name:  ";
			puts(name);
			cout<<"No. of book issued: "<<token;
			if(token==1)
			cout<<"Book Number: "<<stbno;
		}
		
		void modifystudent()
		{
			cout<<"Admission Number:  "<<admno;
			cout<<"Modify Student Name: \n";
			gets(name);
		}
		char *retadmno()
		{
			return admno;
		}
		char *retstbno()
		{
			return stbno;
		}
		int rettoken()
		{
			return token;
		}
		void addtoken()
		{
			token=1;
		}
		void resettoken()
		{
			token=0;
		}
		
		void getstbno(char t[])
		{
			strcpy(stbno,t);
		}
		void report(char t[])
		{
			cout<<admno<<setw(30)<<name<<setw(20)<<token<<endl;
		}
		
};

fstream fp,fp1;
book bk;
student st;

void writebook()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		bk.createbook();
		fp.write((char*)&bk,sizeof(book));
		cout<<"Do you want to add more record...(y/n)?...";
		cin>>ch;
	}
	while(ch=='y'||ch=='Y');
	fp.close();
}


void writestudent()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.createstudent();
		fp.write((char*)&st,sizeof(student));
		cout<<"Do you want to add more record...(y/n)?...";
		cin>>ch;
	}
	while(ch=='y'||ch=='Y');
	fp.close();
}

void displayspb(char n[])
{
	cout<<"\nBOOK DETAILS: \n";
	int flag=0;
	fp.open("book.dat",ios::in);
	
	while(fp.read((char *)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.showbook();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	cout<<"\n\nBook does not exist:";
	
}


void displaysps(char n[])
{
	cout<<"\nSTUDENT DETAILS: \n";
	int flag=0;
	fp.open("student.dat",ios::in);
	
	while(fp.read((char *)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.showstudent();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	cout<<"\n\nStudent does not exist:";
}

void modifybook()
{
	char n[6];
	int found=0;
	cout<<"\nModify book records:...\n";
	cout<<"Enter book number: \n";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.showbook();
			cout<<"\nEnter the new details of book:...\n";
			bk.modifybook();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::curr);
			fp.write((char*)&bk,sizeof(book)); 
			cout<<"Record updated.."<<endl;
			found=1;
		}
	}
	fp.close();
	if(found==0)
	cout<<"Book not found:"<<endl;
}

void modifystudent()
{
	char n[6];
	int found=0;
	cout<<"\nModify student records:...\n";
	cout<<"Enter admission number: \n";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(bk.retadmno(),n)==0)
		{
			st.showstudent();
			cout<<"\nEnter the new details of student:...\n";
			st.modifystudent();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::curr);
			fp.write((char*)&st,sizeof(student)); 
			cout<<"Record updated.."<<endl;
			found=1;
		}
	}
	fp.close();
	if(found==0)
	cout<<"Student not found:"<<endl;
}

void deletestudent()
{
	char n[6];
	int flag=0;
	cout<<"Delete student on the basis of adm. no.:.."<<endl;
	cout<<"Enter the admission number..\n";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
		{
			fp2.write((char*)&st,sizeof(student));
			
		}
		else
		{
			flag=1;
		}
	}
	fp2.close();
	fp.close();
	remove("student.dat");
	rename("temp.dat","student.dat");
	if(flag==1)
	cout<<"\n\n\tRecord Deleted...\n";
	else
	cout<<"\n\nRecord Not Found...\n";
}

void deletebook()
{
	char n[6];
	int flag=0;
	cout<<"Delete book on the basis of book no.:.."<<endl;
	cout<<"Enter the book number..\n";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(st.retbno(),n)!=0)
		{
			fp2.write((char*)&bk,sizeof(book));
			
		}
		else
		{
			flag=1;
		}
	}
	fp2.close();
	fp.close();
	remove("book.dat");
	rename("temp.dat","book.dat");
	if(flag==1)
	cout<<"\n\n\tRecord Deleted...\n";
	else
	cout<<"\n\nRecord Not Found...\n";
}

void displayalls()
{
	fp.open("student.dat",ios::in);
	if(!fp)
	{
		cout<<"File could not be opened:"<<endl;
		return;
	}
	cout<<"\n\n\t\tStudent List\n\n";
	cout<<"===================================\n";
	cout<<"Admission No."<<setw(10)<<"Name"<<setw(20)<<"Book issued\n";
	cout<<"===================================\n";
	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}
	fp.close();
}

void displayallb()
{
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"\nFile could not be opened\n";
		return;
	}
	cout<<"\n\n\t\tBOOK LIST:\n\n";
	cout<<"=====================================\n";
	cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author Name\n";
	cout<<"================================================\n";
	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.report(); 	 	
	}
	fp.close();
}

void bookissue()
{
	char sn[6],bn[6];
	int found =0,flag=0;
	cout<<"BOOK ISSUE:\n\n";
	cout<<"============================================\n";
	cout<<"\n\nEnter Admission number of student\n";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student))&& found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
				cout<<"\n\n\tEnter the book number...\n";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
					if(strcmpi(bk.retbno(),bn)==0)
					{
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
						int pos=-1*sizeof(st);
						fp.seekg(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\tBOOK ISSUED SUCCESSFULLY:\n";
						
					}
				}
				if(flag==0)
				{
					cout<<"Book no. does not exist..\n";
				}
			}
			else
			{
				cout<<"You have not returned the last book:\n";
			}
		}
	} 
	if(found==0)
	{
		cout<<"\n\nstudent Record Not exist...\n";
	}
	fp.close();
	fp1.close();
}

void bookdeposit()
{
	char sn[6],bn[6];
	int found =0,flag=0,day,fine;
	cout<<"BOOK DEPOSIT:\n\n";
	cout<<"============================================\n";
	cout<<"\n\nEnter Admission number of student\n";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student))&& found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==1)
			{
				
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
					if(strcmpi(bk.retbno(),st.retstbno())==0)
					{
						flag=1;
						bk.showbook();
						cout<<"\n\nBook deposited in no. of days:\n\n";
						cin>>day;
						if(day>15)
						{
							fine=(day-15)*1;
							cout<<"\n\nFine has to be deposited Rs. "<<fine<<endl;
						}
						st.resettoken();
						int pos=-1*sizeof(st);
						fp.seekg(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\tBOOK DEPOSITED SUCCESSFULLY:\n";
						
					}
				}
				if(flag==0)
				{
					cout<<"Book no. does not exist..\n";
				}
			}
			else
			{
				cout<<"No Book is Issued:\n";
			}
		}
	} 
	if(found==0)
	{
		cout<<"\n\nstudent Record Not exist...\n";
	}
	fp.close();
	fp1.close();
}




void start()
{
	cout<<"\t\t\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
	cout<<"\n\nDEVELOPER: AVINASH";
	getch();
}

void admin()
{
	int ch2;
	cout<<"\t\t\tADMINISTARTION MENU:";
	cout<<"\n\n\t\t1.CREATE STUDENT RECORD:";
	cout<<"\n\n\t\t2.DISPLAY ALL STUDENT RECORD:";
	cout<<"\n\n\t\t3.DISPLAY SPECIFIC STUDENT RECORD:";
	cout<<"\n\n\t\t4.MODIFY STUDENT RECORD:";
    cout<<"\n\n\t\t5.DELETE STUDENT RECORD:";
 	cout<<"\n\n\t\t6.CREATE BOOK:";
	cout<<"\n\n\t\t7.DISPLAY ALL BOOKS:";
	cout<<"\n\n\t\t8.DISPLAY SPECIFIC BOOK:";
	cout<<"\n\n\t\t9.MODIFY BOOK RECORD:";
	cout<<"\n\n\t\t10.DELETE BOOK RECORD:";
	cout<<"\n\n\t\t11.BACK TO MAIN MENU:";
	cout<<"\n\n\t\t PLEASE SELECT YOUR OPERATION(1-11):";
	cin>>ch2;
	switch(ch2)
	{  
		case 1:
			writestudentrecord();
			break;
		case 2:
			displayalls();
			break;
		case 3:
			char num[6];
			cout<<"Enter your Admission no.";
			cin>>num;
			displayspecifics(num);
			break;
		case 4:
			modifystudent();
			break;
		case 5:
			deletestudent();
			break;
		case 6:
		    writebook();
			 break;
		case 7:
		    displayallb();
			break;
		case 8:
		    {
			char num[6];
			cout<<"Please Enter the book no.";
			cin>>num;
			displayspecificb(num);
		    }
			break;
		case 9:
		    modifybook();
			break;
		case 10:
		    deletebook();
			break;
		case 11:
		     return;
		default:
		    cout<<"Invalid choice, Try Again:";
					
	}
    admin();
}
void main()
{
	int ch;
	start();
	do{
		cout<<"\n\n\t\t\t\t\t\tMAIN MENU\n";
		cout<<"01. BOOK ISSUE\n";
		cout<<"02. BOOK RETURN\n";
		cout<<"03. ADMINNISTARTOR MENU\n";
		cout<<"04. EXIT\n";
		cout<<"Please select  number between 1 to 4";
		cin>>ch;
		switch(ch)
		{
			case 1:
				bookissue();
				break;
			case 2:
				bookreturn();
				break;
			case 3:
				admin();
				break;
			case 4:
				exit(0);
				break;
			default:
				cout<<"Invalid Choice:";
				break;
		    
			   	
		}
	}
	while(ch!=4)
	
		
	
;}
