#include<iostream>
#include"HW2_lkd.h"
#include<ctime>
using namespace std;
int main()
{
	time_t tt=time(NULL);
	tm* t=localtime(&tt);
	srand(unsigned(time(NULL)));
	DATEYMD today(t->tm_year+1900,t->tm_mon+1,t->tm_mday),ddl(today);
	ddl.Add(100);
	Cursor.background();
	vector<BOOKIND> book;
	vector<ACCOUNT> user;
	if(READ(book,user))
		for(unsigned int i=0;i<user.size();i++)
			user[i].booked(book);
	else
		user.push_back(ACCOUNT(10000,"12345678",1));
	unsigned int id,ind;
	unsigned short kind(32767);
	char pass[50];
	while(kind==32767)
	{
		id=Cursor.numberscan(11,37);
		Cursor.strscan(15,37,pass,true);
		for(unsigned int i=0;i<user.size();i++)
			if(kind=user[i].pass(id,pass),kind!=32767)
			{
				ind=i;
				break;
			}
		if(kind==32767)
		{
			Cursor.Wrong("�û��������ڻ����벻��ȷ");
			Cursor.backgroun();
		}
	}
	if(kind)
	{
		unsigned int kind,id,idf,idt;
		unsigned short isbn[13];
		char password[60],name[60],publisher[60];
		bool flag,flag2,flag3;
		while(kind=Cursor.Teabackground(),kind!=6)
		{
			Cursor.cls();
			switch(kind)
			{
			case 0://��
				Cursor.Norprint(4,"�������룺",12,0);
				Cursor.Norprint(11,"ѧ��ѧ�ţ�",13,0,29);
				Cursor.Norprint(15,"13λISBN��",13,0,29);
				id=Cursor.numberscan(11,39);
				Cursor.isbnscan(15,39,isbn);
				flag=true;
				for(unsigned int k,j,i=0;i<user.size();i++)
					if(user[i].testid(id))
					{
						flag=false;
						flag2=true;
						for(j=0;j<book.size();j++)
							if(book[j].echo(isbn))
							{
								flag2=false;
								if(!user[i].ok())
								{
									Cursor.Wrong("ѧ�����鳬��5��");
									break;
								}
								if(book[j].booked())
								{
									Cursor.Wrong("��ͼ���ѽ��");
									break;
								}
								user[i].bor();
								for(k=0;k<book[j].n;k++)
									if(!book[j].time[k].booked())
									{
										book[j].time[k].set(ddl,id);
										break;
									}
								SAVE(book,user);
								Cursor.Rright();
								break;
							}
						if(flag2)
							Cursor.Wrong("δ�ҵ�ͼ����Ϣ��ISBN��������");
						break;
					}
				if(flag)
					Cursor.Wrong("�˻�δ��ͨ������Ա�ʺŲ��ܽ��飩");
				break;
			case 1://��
				Cursor.Norprint(4,"�������룺",12,0);
				Cursor.Norprint(11,"ѧ��ѧ�ţ�",15,0,29);
				Cursor.Norprint(15,"13λISBN��",15,0,29);
				id=Cursor.numberscan(11,39);
				Cursor.isbnscan(15,39,isbn);
				flag=true;
				for(unsigned int k,j,i=0;i<user.size();i++)
					if(user[i].testid(id))
					{
						flag=false;
						flag2=true;
						for(j=0;j<book.size();j++)
							if(book[j].echo(isbn))
							{
								flag2=false;
								flag3=true;
								for(k=0;k<book[j].n;k++)
									if(book[j].time[k].BOR(id))
									{
										flag3=false;
										book[j].time[k].set(0,0,0,0);
										user[i].ret();
										SAVE(book,user);
										Cursor.Rright();
										break;
									}
								if(flag3)
									Cursor.Wrong("��ͬѧδ���Ĺ����飬��������");
								break;
							}
							if(flag2)
							Cursor.Wrong("δ�ҵ�ͼ����Ϣ��ISBN��������");
						break;
					}
				if(flag)
					Cursor.Wrong("�˻�δ��ͨ������Ա�ʺŲ��ܽ��飩");
				break;
			case 2://��
				Cursor.Norprint(5,"�������룺",9,0);
				Cursor.Norprint(9,"ͼ�����ƣ�",15,0,26);
				Cursor.Norprint(12," ������ ��",15,0,26);
				Cursor.Norprint(15,"ͼ�����ߣ�",15,0,26);
				Cursor.Norprint(18,"13λISBN��",15,0,26);
				Cursor.Norprint(21,"ͼ�������",15,0,26);
				Cursor.strscan(9,36,name);
				Cursor.strscan(12,36,publisher);
				Cursor.strscan(15,36,password);
				Cursor.isbnscan(18,36,isbn);
				id=Cursor.numberscan(21,36);
				flag=true;
				for(unsigned int i=0;i<book.size();i++)
					if(book[i].echo(isbn))
					{
						flag=false;
						break;
					}
				if(id==0)
				{
					Cursor.Wrong("��������Ϊ��");
					break;
				}
				if(flag)
				{
					book.push_back(BOOKIND(name,publisher,password,isbn,id));
					SAVE(book,user);
					Cursor.Rright();
				}
				else
					Cursor.Wrong("ͼ��ISBN���ͻ����������");
				break;
			case 3://��
				{
					char *s[2]={"   �鿴ͼ������   ","   �鿴����ͼ��   "};
					unsigned char pos[2]={9,16};
					if(Cursor.Chose(2,'[',s,']',pos,14,11))
						Show2(book,today);
					else
						Show1(book);
				}
				break;
			case 4://��
				Cursor.Norprint(4,"������ʼĩѧ�ţ�������ͳһ��ʼ����",10,0);
				Cursor.Norprint(6,"ʼĩѧ����ͬ����������룬�����ѿ�ͨ�ʺ����벻��",10,0);
				Cursor.Norprint(10,"��ʼѧ�ţ�",15,0,29);
				Cursor.Norprint(13,"��ֹѧ�ţ�",15,0,29);
				Cursor.Norprint(16,"�趨���룺",15,0,29);
				Cursor.Norprint(19,"��0Ϊѧ��������Ϊ����Ա���˺����ͣ�",15,0,4);
				idf=Cursor.numberscan(10,39);
				idt=Cursor.numberscan(13,39);
				Cursor.strscan(16,39,password);
				id=Cursor.numberscan(19,39);
				if(idf==0)
				{
					Cursor.Wrong("�Ƿ�ѧ��0");
					break;
				}
				if(idf==idt)
				{
					flag=true;
					for(unsigned int i=0;i<user.size();i++)
						if(user[i].echo(idf))
						{
							user[i].passwordize(password);
							flag=false;
							SAVE(book,user);
							Cursor.Rright();
							break;
						}
					if(flag)
						Cursor.Wrong("δ��ͨ�ʺŲ�����������");
					break;
				}
				else
				{
					if(idf>idt)
					{
						Cursor.Wrong("��ʼѧ�Ų���С����ֹѧ��");
						break;
					}
					for(unsigned int j,i=idf;i<=idt;i++)
					{
						flag=true;
						for(j=0;j<user.size();j++)
							if(user[j].echo(i))
							{
								flag=false;
								break;
							}
						if(flag)
							user.push_back(ACCOUNT(i,password,(unsigned short)id));
					}
					SAVE(book,user);
					Cursor.Rright();
				}
				break;
			case 5://password
				if(user[ind].recrypt())
				{
					SAVE(book,user);
					Cursor.Rright();
				}
				else
					Cursor.Wrong("���벻��ȷ �� �������������벻һ��");
				break;
			}
		}
	}
	else
	{
		unsigned short kind;
		while(kind=Cursor.Stubackground(),kind!=3)
		{
			Cursor.cls();
			switch(kind)
			{
			case 0:
				user[ind].own(book,today);
				break;
			case 1:
				if(user[ind].search(book,ddl,today))
				{
					SAVE(book,user);
					Cursor.Rright();
				}
				break;
			case 2:
				if(user[ind].recrypt())
				{
					SAVE(book,user);
					Cursor.Rright();
				}
				else
					Cursor.Wrong("���벻��ȷ �� �������������벻һ��");
				break;
			}
		}
	}
	Cursor.end();
	return 0;
}
