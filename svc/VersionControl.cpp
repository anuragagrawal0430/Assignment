
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <queue>
using namespace std;


#define new_c cout<<"\n--------------------------------------------------------------------\n";

// structure to store data on stack
typedef struct node
{
	string line;
	char command[10];
	int lineno;
}node;


class svc
{

public:
	queue <node> S;
	int op;
	//..............................................................Function to add line.........................................................
	void addline(string line)
	{
		fstream fp("test.txt",ios::app);
		fp<<line<<endl;
		node temp;
		temp.line=line;
		strcpy(temp.command,"add\0");
		temp.lineno=-1;
		S.push(temp);
	}
	//end of addline function...........................................................................................................

	//.............................................................Function to delete line..............................................
	void deleteline(string d)
	{
		int lineno=-1,i=0;
		string l;
		fstream tempf("temp.txt",ios::app);
		fstream fp("test.txt");
		while(getline(fp,l,'\n'))
		{
			i++;
			if(l!=d)
			{
				tempf<<l<<endl;
			}
			else
			{
				lineno=i;
			}
		}
		fp.close();
		tempf.close();
		remove("test.txt");
		rename("temp.txt","test.txt");
		if(lineno>0)
		{
			node temp;
			temp.line=d;
			strcpy(temp.command,"delete\0");
			temp.lineno=lineno;
			S.push(temp);
		}
	}
	//end of deleteline function.............................................................................................................

	//.................................................Function to Display the version asked..........................................
	void display(int vr)
	{
		int itoken,dispnoline;
		fstream fv("version.txt",ios::in);
		string line;

		//find the version asked exist and the details of the version
		getline(fv,line,'\n');
		do
		{
			istringstream ss(line);
			ss>>itoken;
		}while(itoken!=vr && getline(fv,line,'\n'));
		if(itoken!=vr)
		{
			cout<<"\nThe version you want does not exist !!";
			return;
		}
		fv.close();
		//version found

		//now place every line as per the details of the version
		string output[20];
		bool out[20];
		for(int g=0;g<10;g++)
			out[g]=false;
		int n1,n2,n2c;
		istringstream ss(line);
		ss>>itoken;
		ss>>dispnoline;
		ss>>itoken;

		int prev=-1,inc=0;
		//read backup lines as per the version requires
		while(!ss.eof())
		{
			int k,ln;
			string bline,copy;
			ss>>n1;
			ss>>n2;
			fstream fb("backup.txt",ios::in);
			do
			{
				getline(fb,bline,'\n');
				istringstream bs(bline);
				bs>>itoken;
				bs>>ln;
			}while(itoken!=n1);
			while(ln!=n2)
			{
				getline(fb,bline,'\n');
				istringstream bs(bline);
				bs>>copy;
				bs>>ln;
			}
			istringstream bs(bline);
			bs>>copy;
			bs>>copy;
			bs>>copy;
			n2c=n2;
			if(prev<n2)
			{
				n2+=inc;
				inc++;
			}
			for(k=(n2-1);out[k]==true;k++)
			{
				//do nothing just get the next empty line as per required
			}
			while(!bs.eof())
			{
				bs>>copy;
				output[k]+=copy+" ";
			}
			out[k]=true;
			prev=n2c;
			fb.close();
		}//end of while to take lines needed from backup file
		string copy;
		fstream ft("test.txt",ios::in);
		for(int k=0;k<dispnoline;k++)
		{
			if(out[k]==false)
			{
				getline(ft,copy,'\n');
				output[k]=copy;
			}
		}
		cout<<"\n->|test.txt version-"<<vr<<"|<-\n";
		for(int k=0;k<dispnoline;k++)
		{
			cout<<"\n"<<output[k];
		}
		if(dispnoline==0)
			cout<<"\nThis version is an empty file";
	}
	//end of display function................................................................................................

	//..................................................Function to make COMMIT .............................................
	void commit()
	{
		int count,v,itoken,vr,dc;
		string lookahead,line;
		vr=findlatestversion();
		count=0;
		fstream tfile("test.txt",ios::in);
		while(getline(tfile,lookahead,'\n'))
			count++;
		tfile.close();
		ostringstream vs,cs;
		vr++;
		cs<<count;
		vs<<vr;
		line=vs.str()+" "+cs.str()+" "+cs.str();
		fstream f("version.txt",ios::app);
		f<<line<<endl;
		f.close();

		//connecting the deleted lines with their respective versions
		vr--;
		node temp;
		int nooflines,diff;
		string vline;
		dc=0;
		while(S.empty()!=1)
		{
			v=vr;
			temp=S.front();
			S.pop();
			if(strcmp(temp.command,"delete\0")==0)
			{

				//to create the backup file to store deleted lines

				fstream bf("backup.txt",ios::app);
				ostringstream bvr,bl;
				string backup;
				bvr<<(vr+1);
				bl<<temp.lineno;
				backup=bvr.str()+" "+bl.str()+" - "+temp.line;
				bf<<backup<<endl;
				bf.close();

				//end of creating backup file

				//to connected the respective versions with their deleted lines
				while(v>0)
				{
					fstream fv("version.txt",ios::in);
					for(int k=1;k<=v;k++)
						getline(fv,vline,'\n');

					istringstream ss(vline);
					ss>>itoken;
					ss>>nooflines;
					ss>>diff;

					//update version line
					if(temp.lineno<=diff)
					{
						diff--;
						ostringstream os1,os2,os3,os4,os5;
						os1<<itoken;
						os2<<nooflines;
						os3<<diff;
						string vupdate;
						vupdate=os1.str()+" "+os2.str()+" "+os3.str();
						int dv=-1,dl=-1;
						while(1)
						{
							ss>>dv;
							ss>>dl;
							if(ss.eof() && dl<0)
							{
								os4<<(vr+1);
								os5<<temp.lineno;
								vupdate+=" "+os4.str()+" "+os5.str();
								dc++;
								break;
							}
							else
							{
								ostringstream s1,s2;
								s1<<dv;
								s2<<dl;
								vupdate+=" "+s1.str()+" "+s2.str();
								dl=-1;
								dv=-1;
							}
						}
						fv.close();
						string l;
						int index;
						fstream fv1("tempv.txt",ios::app);
						fstream ofv("version.txt",ios::in);
						index=0;
						while(getline(ofv,l,'\n'))
						{
							index++;
							if(index!=v)
							{
								fv1<<l<<endl;
							}
							else
							{
								fv1<<vupdate<<endl;
							}
						}
						ofv.close();
						fv1.close();
						remove("version.txt");
						rename("tempv.txt","version.txt");
						v--;
					}
					//end of update version line


					else
					{
						break;
					}
					fv.close();
				}//end of while to connect the respective versions
			}//end of if command is "delete"
		}//end of stack while
	}
	//end of commit function........................................................................................................

	//..............................................Find the latest version..........................................................
	int findlatestversion()
	{
		int itoken,v=0;
		string lookahead,line;
		fstream fp("version.txt",ios::in);
		if(fp!=NULL)
		{
			fstream temp("version.txt",ios::in);
			while(getline(temp,lookahead,'\n'))
				getline(fp,line,'\n');
			if(line!="")
			{
				istringstream ss(line);
				ss>>itoken;
			}
			v=itoken;
			temp.close();
		}
		return v;
	}
	//end of latest version......................................................................................
};


//.........................Main function.........................................................................
int main()
{
	svc T;
	int i=0,g;
	T.op=0;
	bool disp;
	char input[10],c;
	string in;
	cout<<"\n->|Program for version control started|<-\n'svc test.txt' is to commit\n'svc n' is to display nth version\n"
			"'add' is to add(append) new line\n'delete' is to delete a line\n'exit' to close the program";
	new_c;
	while(1)
	{
		disp=false;
		i=0;
		fstream fp("test.txt",ios::in);
		if(fp==NULL)
		{
			fstream fp("test.txt",ios::out);
			string svc;
			svc="hello";
			fp<<svc<<endl;
			fp.close();
		}
		cout<<"\n>";
		g=0;
		while((c=getc(stdin))!='\n')
			input[i++]=c;
		input[i]='\0';
		in=input;
		string f;
		int s;
		istringstream ds(in);
		ds>>f;
		ds>>s;
		if(f=="svc" && s!=0)
			disp=true;
		if(f=="svc" && input[4]=='0')
		{
			cout<<"\n->|test.txt version-"<<0<<"|<-\n\nhello";
			new_c;
			continue;
		}
		//to add a line
		if(strcmp(input,"add")==0)
		{
			string line;
			int count;
			fstream tf("test.txt",ios::in);
			count=0;
			while(getline(tf,line,'\n'))
				count++;
			if(count>20)
			{
				cout<<"\nFile test.txt has reached its max line numbers. Delete few lines to add new ones";
				new_c;
				continue;
			}
			T.op++;
			do
			{
				cout<<"\nEnter the line you want to add :: ";
				getline(cin,line);
				g=line.size();
				if(g>10)
				{
					cout<<"\nInput can have max character 10. Try again.";
				}
			}while(g>10);
			T.addline(line);
			new_c;
		}

		//to delete a line
		else if(strcmp(input,"delete")==0)
		{
			string d;
			T.op++;
			cout<<"\nEnter the line you want to delete :: ";
			getline(cin,d);
			T.deleteline(d);
			new_c;
		}
		else if(strcmp(input,"exit")==0)
		{
			node temp;
			cout<<"\nClosing version control....";

			int prev=-1,inc=0;
			//reverting back the changes if the "commit" command is not executed before "exit"
			while(T.S.empty()!=1)
			{
				temp=T.S.front();
				T.S.pop();
				if(strcmp(temp.command,"add\0")==0)
				{
					string l;
					fstream tempf("temp.txt",ios::app);
					fstream fp("test.txt");
					while(getline(fp,l,'\n'))
					{
						if(l!=temp.line)
						{
							tempf<<l<<endl;
						}
					}
					fp.close();
					tempf.close();
					remove("test.txt");
					rename("temp.txt","test.txt");
				}
				else if(strcmp(temp.command,"delete\0")==0)
				{
					int j;
					string l;
					fstream tempf("temp.txt",ios::app);
					fstream fp("test.txt");
					j=0;
					while(getline(fp,l,'\n') || j<(temp.lineno+inc))
					{
						j++;
						if(j!=temp.lineno+inc)
						{
							tempf<<l<<endl;
						}
						else
						{
							tempf<<temp.line<<endl;
							if(l!="")
								tempf<<l<<endl;
						}
					}
					if(prev<temp.lineno)
					{
						inc++;
					}
					prev=temp.lineno;
					fp.close();
					tempf.close();
					remove("test.txt");
					rename("temp.txt","test.txt");
				}
			}
			//stack is empty all the changes are reverted back
			new_c;
			break;
		}

		//do nothing
		else if(strcmp(input,"\n")==0 || strcmp(input,"")==0)
		{
			//do nothing
		}

		//to commit the work done
		else if(strcmp(input,"svc test.txt")==0)
		{
			if(T.op==0)
			{
				cout<<"\nNo operation done to create a new version";
				new_c;
			}
			else
			{
				T.commit();
				cout<<"\nNew version of the file is saved";
				T.op=0;
				new_c;
			}
		}

		//to display a particular version
		else if(disp)
		{
			T.display(s);
			new_c;
		}

		//Input taken is not what is expected
		else
		{
			cout<<"\n***INVALID INPUT***.....try again";
			new_c;
		}
	}
	return 0;
}



