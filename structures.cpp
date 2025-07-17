#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstring>

using namespace std;

const int MENU_1 = 49;
const int MENU_2 = 50;
const int MENU_3 = 51;
const int MENU_4 = 52;
const int MENU_5 = 53;
const int MENU_6 = 54;
const int MENU_7 = 55;
const int MENU_EXIT = 27;

struct serial {
	int number;                 //�����
	char name[30];             //��������
	int start_year;           //��� ������
	int number_of_seasons;   //���-�� �������
	char genre[30];         //����
	double rating;         //�������
	char country[30];     //������
	char language[30];   //���� ���������
	serial *next;
	serial *prev;
};

enum direction { to_forward, to_reverse };

void add_to_list(serial**, serial**);
void show_list(serial*, direction);
void delete_el(serial**, serial**);
void edit_serial(char*, serial*);
void save_to_file(serial*);
void load_from_file(serial**, serial**);
//void show_all_authors(serial*);
//void show_sublist_years(serial*);

int main(int argc, char** argv) {
	
	serial *first = NULL;
	serial *last = NULL;
	int req = 0;
	
	setlocale(LC_CTYPE, "Russian");
	
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	do {
		system("cls");
		cout << "  1. �������� ������� � ������.\n";	
		cout << "  2. �������� ������.\n";
		cout << "  3. ������� �������.\n";
		cout << "  4. ������ ����� ��������.\n";	
		cout << "  5. ��������� � ����.\n";
		cout << "  6. ��������� �� �����.\n";	
		cout << "  7. �������������� �������.\n";		
		cout << "ESC. �����.\n";
		req = getch();
		switch(req) {
			case MENU_1: {
				system("cls");
				add_to_list(&first, &last);
				getch();
				break;
			}			
			case MENU_2: {
				system("cls");
				show_list(first, to_forward);
				getch();
				break;
			}
			case MENU_3: {
				system("cls");
				delete_el(&first, &last);
				getch();
				break;
			}			
			case MENU_4: {
				system("cls");
				if(first == NULL) {
					cout << "������ ����." << endl;
					getch();
					break;
				}
				char name[30];
				cout << "������� �������� ������� ��� ��������������: ";
				cin.sync();
				gets(name);
				edit_serial(name, first);
				getch();
				break;
			}			
			case MENU_5: {
				system("cls");
				save_to_file(first);
				getch();
				break;
			}
			case MENU_6: {
				system("cls");
				load_from_file(&first, &last);
				getch();
				break;
			}		
		/*	case MENU_7: {
				system("cls");
				cout << "1. ������� �������� ���� �������.\n";	
				cout << "2. ������� ����� �� ��������� ���������� ��������� ���� �������.\n";
				int nf = getch();
				system("cls");
				switch(nf) {
					case MENU_1: {
						show_all_authors(first);
						getch();
						break;
					}			
					case MENU_2: {
						show_sublist_years(first);
						getch();
						break;
					}				
				}
				break;
			}*/	
	  }
	} while(req != MENU_EXIT);	
	return 0;
}

void add_to_list(serial **ph, serial **pl) {
	serial *new_el = new serial;
	serial *h = *ph;
	serial *l = *pl;
	cin.sync();
	srand(time(0));
	new_el->number = 99999 + ((2 * rand() * rand()) + 1) % 900000;
	cout << "������� �������� �������: ";
	gets(new_el->name);
	cout << "������� ����: ";	
	gets(new_el->genre);
	cout << "������� ������ �������: ";	
	gets(new_el->country);
	cout << "������� ���� ���������: ";	
	gets(new_el->language);
	cout << "������� ��� ������: ";
	cin >> new_el->start_year;
	cout << "������� ���-�� �������: ";
	cin >> new_el->number_of_seasons;
	cout << "������� �������: ";	
	cin >> new_el->rating;
	new_el->next = NULL;
	new_el->prev = NULL;	
	if(h == NULL) {
		*ph = new_el;
	} 
	if(l == NULL) {
		*pl = new_el;
	} 
	else {
		l->next = new_el;
		new_el->prev = l;
		*pl = new_el;
	}
}

void show_list(serial *pb, direction d) {
	serial *p = pb;
	if(p == NULL) {
		cout << "������ ����." << endl;
		return;
	}	
	while(p != NULL) {
		cout << "�����: ";
		cout << p->number << endl;
		cout << "��������: ";
		cout << p->name << endl;
		cout << "��� ������: ";
		cout << p->start_year << endl;
		cout << "���-�� �������: ";
		cout << p->number_of_seasons << endl;
		cout << "����: ";
		cout << p->genre << endl;
		cout << "�������: ";
		cout << p->rating << endl;
		cout << "������: ";
		cout << p->country << endl;
		cout << "���� ���������: ";
		cout << p->language << endl;
		cout << "----------------" << endl;
		if(d == to_forward) {
			p = p->next;	
		}
		else {
			p = p->prev;	
		}
	}
}

void delete_el(serial **ph, serial **pl) {
	serial *h = *ph;
	serial *l = *pl;	
	serial *p = h;
	serial *del = NULL;
	if(p == NULL) {
		cout << "������ ����." << endl;
		return;
	}	
	char dname[30];
	int k = 0;
	bool to_delete = false;
	cin.sync();
	cout << "������� �������� �������: ";
	gets(dname);
	while(p != NULL) {
		if(strcmp(p->name, dname) == 0) {
			if(p == h) {
				if(p->next != NULL) {
					p->next->prev = NULL;
					*ph = p->next;					
				}
				else {
					*ph = NULL;
				}
			}
			if(p == l) {
				if(p->prev != NULL) {
					p->prev->next = NULL;
					*pl = p->prev;
				}
				else {
					*pl = NULL;
				}
			}
			if(p != h && p != l) {
				p->next->prev = p->prev;
				p->prev->next = p->next;				
			}
			k++;
			to_delete = true;
			del = p;		
		}
		p = p->next;
		if(to_delete) {
			delete del;
			to_delete = false;	
		}
	}
	if(k != 0) {
		cout << "\n������(�) ������(�).\n";	
	}
	else {
		cout << "\n������� � ����� ��������� � ������ ���.\n";	
	}
}

void edit_serial(char *name, serial *pb) {
	serial *p = pb;	
	char key_name[30];
	memcpy(key_name, name, sizeof(key_name));
	int k = 0;
	while(p != NULL) {
		if(strcmp(p->name, key_name) == 0) {
			k++;
			system("cls");
			cout << "������ �" << p->number << ":\n";
	    	cout << p->name << endl;
		    cout << p->start_year << endl;
	    	cout << p->number_of_seasons << endl;
	    	cout << p->genre << endl;
	    	cout << p->rating << endl;
		    cout << p->country << endl;
	    	cout << p->language << endl;
			cout << "-------------------------------------" << endl;
			cout << "1. �������� �������� �������.\n";	
			cout << "2. �������� ��� ������.\n";	
			cout << "3. �������� ���-�� �������.\n";	
			cout << "4. �������� ����.\n";	
			cout << "5. �������� �������.\n";	
			cout << "6. �������� ������.\n";	
			cout << "5. �������� ���� ���������.\n";	
			int choise = getch();
			system("cls");
			cin.sync();
			switch(choise) {
				case MENU_1: {
					char value_name[30];
					cout << "������� ����� �������� �������� �������: ";
					gets(value_name);
					memcpy(p->name, value_name, sizeof(value_name));
					break;
				}		
				case MENU_2: {
					int value_start_year;
					cout << "������� ����� �������� ��� ������: ";
					cin >> value_start_year; 
					p->start_year = value_start_year;
					break;
				}
				case MENU_3: {
					int value_number_of_seasons;
					cout << "������� ����� �������� ���-�� �������: ";
					cin >> value_number_of_seasons; 
					p->number_of_seasons = value_number_of_seasons;
					break;
				}
				case MENU_4: {
					char value_genre[30];
					cout << "������� ����� �������� �����: ";
					gets(value_genre);
					memcpy(p->genre, value_genre, sizeof(value_genre));
					break;
				}
				case MENU_5: {
					int value_rating;	
					cout << "������� ����� �������� ���������� �������: ";
					cin >> value_rating;
					p->rating = value_rating; 
					break;
				}
				case MENU_6: {
					char value_country[30];
					cout << "������� ����� �������� ������: ";
					gets(value_country);
					memcpy(p->country, value_country, sizeof(value_country));
					break;
				}
				case MENU_7: {
					char value_language[30];
					cout << "������� ����� �������� ����� ���������: ";
					gets(value_language);
					memcpy(p->language, value_language, sizeof(value_language));
					break;
				}
			}
		}
		p = p->next;
	}
	if(k == 0) {
		cout << "������� � ����� ��������� � ������ ���." << endl;	
	}
}

void save_to_file(serial *h) {
	FILE *fb;
	char fname[20];
	serial *p = h;
	cout << "������� ��� �����: ";
	cin >> fname;
	fb = fopen(fname, "wb");	
	while(p != NULL) {
		fwrite(&(p->number), 1, sizeof(p->number), fb);
		fwrite(p->name, 1, sizeof(p->name), fb);
		fwrite(&(p->start_year), 1, sizeof(p->start_year), fb);
		fwrite(&(p->number_of_seasons), 1, sizeof(p->number_of_seasons), fb);
		fwrite(p->genre, 1, sizeof(p->genre), fb);
		fwrite(&(p->rating), 1, sizeof(p->rating), fb);
		fwrite(p->country, 1, sizeof(p->country), fb);
		fwrite(p->language, 1, sizeof(p->language), fb);
		p = p->next;
	}
	cout << "\n���� "<< fname <<" ������.\n";
	fclose(fb);	
}

void load_from_file(serial **ph, serial **pl) {
	serial *h = *ph;
	serial *l = *pl;
	serial *new_el;
	char fname[20];
	int number;
    char name[30]; 
    int start_year; 
    int number_of_seasons; 
    char genre[30]; 
    double rating; 
    char country[30]; 
    char language[30]; 
	FILE *fb;
	cout << "������� ��� �����: ";
	cin >> fname;
	fb = fopen(fname, "rb");
	if (fb == NULL) {
		cout << "\n����� � ������ "<< fname <<" �� ����������.\n";
		return;
	}
	while(!feof(fb)) {
		new_el = new serial;		
		if(fread(&number, 1, sizeof(number), fb) == sizeof(number)){ 
			new_el->number = number;
			if(fread(name, 1, sizeof(name), fb) == sizeof(name)) {
				memcpy(new_el->name, name, sizeof(name));
			} 
			if(fread(&start_year, 1, sizeof(start_year), fb) == sizeof(start_year)) {
				new_el->start_year = start_year;
			} 
			if(fread(&number_of_seasons, 1, sizeof(number_of_seasons), fb) == sizeof(number_of_seasons)) {
				new_el->number_of_seasons = number_of_seasons;
			}
			if(fread(genre, 1, sizeof(genre), fb) == sizeof(genre)) {
				memcpy(new_el->genre, genre, sizeof(genre));
			} 				
			if(fread(&rating, 1, sizeof(rating), fb) == sizeof(rating)) {
				new_el->rating = rating;	
			}
			if(fread(country, 1, sizeof(country), fb) == sizeof(country)) {
				memcpy(new_el->country, country, sizeof(country));
			}
			if(fread(language, 1, sizeof(language), fb) == sizeof(language)) {
				memcpy(new_el->language, language, sizeof(language));	
			}		
			new_el->next = NULL;
			new_el->prev = NULL;	
			if (h == NULL) {
				*ph = new_el;	
			}
			if (l == NULL) {
				*pl = new_el;
			} 
			else {
				l->next = new_el;
				new_el->prev = l;
				*pl = new_el;
			}	
			h = *ph;
			l = *pl;
		} 
	}
	cout << "\n���� "<< fname <<" ��������.\n";
	fclose(fb);			
}
/*
void show_all_authors(serial *pb) {
	int length = 0, k = 0;
	char** authors;
	bool in;
	serial *p = pb;
	if(p == NULL) {
		cout << "������ ����." << endl;
		return;
	}
	while(p != NULL) {
		length++;
		p = p->next;
	}
	authors = new char*[length];
	for(int i = 0; i < length; i++) {
		authors[i] = new char[30];	
	}
	p = pb;
	while(p != NULL) {
		in = false;
		for(int i = 0; (i < k)&&(i < length); i++) {
			if(strcmp(p->author, authors[i]) == 0) {
				in = true;	
			}
		}
		if(!in) {
			memcpy(authors[k], p->author, sizeof(p->author));
			k++;
		}
		p = p->next;
	}
	bool sorted = false;
	char temp[30];
	while(!sorted) {
		sorted = true;
		for(int i = 0; i < k-1; i++) {
			if(strcmp(authors[i], authors[i+1]) > 0) {
				sorted = false;
				memcpy(temp, authors[i], sizeof(temp));
				memcpy(authors[i], authors[i+1], sizeof(temp));
				memcpy(authors[i+1], temp, sizeof(temp));			
			} 
		}
	}
	cout << "������ �������:" << endl;
	for(int i = 0; i < k; i++) {
		cout << authors[i] << endl;
	}
	for(int i = 0; i < length; i++) {
		delete [] authors[i];	
	}	
	delete [] authors;
}

void show_sublist_years(serial *pb) {
	int lbound, rbound, k = 0;
	serial *p = pb;
	if(p == NULL) {
		cout << "������ ����." << endl;
		return;
	}
	cout << "� ������ ���� ������� ������ �����: ";
	cin >> lbound;
	cout << "�� ������ ���� ������� ����������� �����: ";
	cin >> rbound;
	cout << "��������� ������: " << endl;
	while(p != NULL) {
		if((p->year > lbound) && (p->year < rbound)) {
			cout << p->number << endl;
			cout << p->author << endl;
			cout << p->name << endl;
			cout << p->form << endl;
			cout << p->year << endl;
			cout << p->num_pages << endl;
			cout << "----------------" << endl;
			k++;
		}
		p = p->next;
	}
	if(k == 0) cout << "���� � ������ ������ ������� � ������ ���." << endl;
}
*/
