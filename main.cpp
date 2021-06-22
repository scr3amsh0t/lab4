#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

#define MAX_LENGTH 4096
#define PATH_DEP "db_dep.txt"
#define PATH_CR "db_cr.txt"

class Fio { // ����� ���

private: // ��������� ����������
	char *surname;
	char *name;
	char *patronymic;

public:
	Fio() { // ����������� �� ���������
		set_surname((char *) "I");
		set_name((char *) "I");
		set_patronymic((char *) "I");
	}

	Fio(const Fio &fio) { // ����������� �����������
		set_surname(fio.surname);
		set_name(fio.name);
		set_patronymic(fio.patronymic);
	}

	Fio &operator=(const Fio &fio) { // �������� ������������
		set_surname(fio.surname);
		set_name(fio.name);
		set_patronymic(fio.patronymic);
		return *this;
	}

	// ������� � �������
	void set_surname(char *surname) {
		this->surname = new char[strlen(surname) + 1];
		strcpy_s(this->surname, strlen(surname) + 1, surname);
	}

	void set_name(char *name) {
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	void set_patronymic(char *patronymic) {
		this->patronymic = new char[strlen(patronymic) + 1];
		strcpy_s(this->patronymic, strlen(patronymic) + 1, patronymic);
	}

	char *get_surname() {
		return surname;
	}

	char *get_name() {
		return name;
	}

	char *get_patronymic() {
		return patronymic;
	}

	// ������������� �������� ���������� ������ (�����)
	friend ostream &operator<<(ostream &out, const Fio &fio);

	friend Fio enter_fio(); // ������������� (������� ����������� �����) ������� ����� � ����� ���
};

class Account {
private:
	float sum;
	Fio client;

public:
	Account() {
		sum = 100;
	}

	Account(const Account& account) {
		sum = account.sum;
		client = account.client;
	}

	Account& operator+(float amount) {
		this->sum += amount;
		return *this;
	}

	float get_sum() const {
		return sum;
	}

	Fio get_client() const {
		return client;
	}

	void set_client(Fio client) {
		this->client = client;
	}

	void set_sum(float sum) {
		this->sum = sum;
	}

};

class Credit : public Account {
private:
	int ccn;
	float percent;

public:
	static int count; // ����������� �������

	Credit() : Account() { // ����������� �� ���������
		ccn = 1234;
		percent = 1;
	}

	Credit(const Credit& credit) : Account(credit) { // ����������� �����������
		set_ccn(credit.ccn);
		set_percent(credit.percent);
	}

	Credit& operator=(const Credit& credit) { // �������� ������������
		set_client(credit.get_client());
		set_sum(credit.get_sum());
		set_ccn(credit.ccn);
		set_percent(credit.percent);
		return *this;
	}

	Credit& operator+(float amount) {
		set_sum(get_sum() + amount);
		return *this;
	}

	int get_ccn() const {
		return ccn;
	}

	float get_percent() const {
		return percent;
	}

	void set_ccn(int ccn) {
		this->ccn = ccn;
	}

	void set_percent(float percent) {
		this->percent = percent;
	}

	friend Credit enter_credit(); // ������� ����� ����� � ����������

	friend ostream& operator<<(ostream& out, const Credit& credit);

	friend void save(Credit* list); // ���������� ������� ����������

	friend Credit* read_credits(); // ���������� ������� ������ �� �����

	friend Credit* sort_by_sum(Credit* list, int& am); // ���������� ���������� �� ������� �� �����

	friend void print_list(Credit* list, int size); // ���������� ������� ������ ����� ���������
};

class Deposit : public Account {

private:
	int id;

public:
	static int count; // ����������� �������

	Deposit() : Account() { // ����������� �� ���������
		id = 1;
	}

	Deposit(const Deposit &bank) : Account(bank) { // ����������� �����������
		set_id(bank.id);
	}

	Deposit &operator=(const Deposit &bank) { // �������� ������������
		set_client(bank.get_client());
		set_sum(bank.get_sum());
		set_id(bank.id);
		return *this;
	}

	Deposit& operator+(float amount) {
		set_sum(get_sum() + amount);
		return *this;
	}

	// ������� � �������
	int get_id() const {
		return id;
	}

	void set_id(int id) {
		this->id = id;
	}

	// ������������� ��������� ����� (�����)
	friend ostream &operator<<(ostream &out, const Deposit &bank);

	friend Deposit enter_deposit(); // ������� ����� ����� � ����������

	friend bool find_by_id(Deposit *list, Deposit &bank, int id); // ���������� ������ �� ������ �����

	friend Deposit *sort_by_sum(Deposit *list, int &am); // ���������� ���������� �� ������� �� �����

	friend void save(Deposit *list); // ���������� ������� ����������

	friend Deposit *read_deposits(); // ���������� ������� ������ �� �����

	friend void print_list(Deposit *list, int size); // ���������� ������� ������ ����� ���������
};

void print_list(Deposit *list, int size) { // ����� ����� ������������� �������
	for (int i = 0; i < size; i++) {
		cout << list[i];

		if (i != size - 1) {
			cout << endl << endl;
		}
	}
}

void print_list(Credit *list, int size) { // ����� ����� ������������� �������
	for (int i = 0; i < size; i++) {
		cout << list[i];

		if (i != size - 1) {
			cout << endl << endl;
		}
	}
}

ostream &operator<<(ostream &out, const Fio &fio) { // ����� ���
	out << "Person: " << fio.surname << " " << fio.name << " " << fio.patronymic;
	return out;
}

ostream &operator<<(ostream &out, const Deposit &bank) { // ����� �����
	out << "Client - " << bank.get_client() << endl <<
		"Account ID - " << bank.get_id() << endl << "Account sum - " << bank.get_sum();
	return out;
}

ostream &operator<<(ostream &out, const Credit &credit) { // ����� �������
	out << "Client - " << credit.get_client() << endl <<
		"CCN - " << credit.get_ccn() << endl << "Credit sum - " << credit.get_sum() << endl <<
		"Credit percent - " << credit.get_percent();
	return out;
}

Fio enter_fio() { // ���� ��� � �����
	Fio fio;

	char *buff = new char[MAX_LENGTH];

	cout << "Enter surname: ";
	cin.getline(buff, MAX_LENGTH);
	fio.set_surname(buff);

	cout << "Enter name: ";
	cin.getline(buff, MAX_LENGTH);
	fio.set_name(buff);

	cout << "Enter patronymic: ";
	cin.getline(buff, MAX_LENGTH);
	fio.set_patronymic(buff);

	delete[] buff;
	return fio;
}

Deposit enter_deposit() { // ���� ����� � �����
	Deposit bank;

	cout << "Enter client" << endl;
	bank.set_client(enter_fio());

	cout << "Enter id: ";
	cin >> bank.id;

	cout << "Enter sum: ";
	float t;
	cin >> t;
	bank.set_sum(t);

	return bank;
}

Credit enter_credit() { // ���� ����� � �����
	Credit credit;

	cout << "Enter client" << endl;
	credit.set_client(enter_fio());

	cout << "Enter CCN: ";
	int i_t;
	cin >> i_t;
	credit.set_ccn(i_t);

	cout << "Enter sum: ";
	float t;
	cin >> t;
	credit.set_sum(t);

	cout << "Enter percent: ";
	cin >> t;
	credit.set_percent(t);

	return credit;
}

bool find_by_id(Deposit *list, Deposit &bank, int id) { // ����� �� ������ ��������
	for (int i = 0; i < Deposit::count; ++i) {
		if (list[i].id == id) {
			bank = list[i];
			return true;
		}
	}
	return false;
}

bool find_by_ccn(Credit *list, Credit &credit, int ccn) { // ����� �� ������ �������
	for (int i = 0; i < Credit::count; ++i) {
		if (list[i].get_ccn() == ccn) {
			credit = list[i];
			return true;
		}
	}
	return false;
}

Deposit *sort_by_sum(Deposit *list, int &am) { // ���������� ��������� �������� �� �������
	for (int i = 1; i < Deposit::count; ++i) {
		for (int j = i - 1; j >= 0 && list[j].get_sum() < list[j + 1].get_sum(); --j) {
			std::swap<Deposit>(list[j], list[j + 1]);
		}
	}
	return list;
}

Credit *sort_by_sum(Credit *list, int &am) { // ���������� �������� �������� �� �������
	for (int i = 1; i < Credit::count; ++i) {
		for (int j = i - 1; j >= 0 && list[j].get_sum() < list[j + 1].get_sum(); --j) {
			std::swap<Credit>(list[j], list[j + 1]);
		}
	}
	return list;
}

void save(Deposit *list) { // ���������� ��������� � ���� � ��������� "db_dep.txt"
	remove(PATH_DEP);
	ofstream file(PATH_DEP);

	file << Deposit::count << endl;
	for (int i = 0; i < Deposit::count; ++i) {
		Deposit t = list[i]; // surname;name;patr;id;sum
		file << t.get_client().get_surname() << ';' << t.get_client().get_name() << ';' << t.get_client().get_patronymic() << ';'
			<< t.id << ';' << t.get_sum() << ';' << endl;
	}
	file.close();
}

void save(Credit *list) { // ���������� �������� � ���� � ��������� "db_cr.txt"
	remove(PATH_CR);
	ofstream file(PATH_CR);

	file << Credit::count << endl;
	for (int i = 0; i < Credit::count; ++i) {
		Credit t = list[i]; // surname;name;patr;ccn;sum;percent
		file << t.get_client().get_surname() << ';' << t.get_client().get_name() << ';' << t.get_client().get_patronymic() << ';'
			<< t.ccn << ';' << t.get_sum() << ';' << t.percent << ';' << endl;
	}
	file.close();
}

Deposit *read_deposits() { // ������ �� �����
	Deposit *list = new Deposit[100];

	ifstream file(PATH_DEP);
	if (!file) {
		cout << "File isn't open" << endl;
		return list;
	}

	file >> Deposit::count;

	// surname;name;patr;id;sum
	for (int i = 0; i < Deposit::count; ++i) {
		if (file.eof()) {
			Deposit::count = i;
			cout << "Something went wrong";
			return list;
		}
		Deposit t;
		Fio fio;

		file.ignore();

		char *buff = new char[MAX_LENGTH + 1];

		file.getline(buff, MAX_LENGTH, ';'); // ������ surname
		fio.set_surname(buff);

		file.getline(buff, MAX_LENGTH, ';'); // ������ name
		fio.set_name(buff);

		file.getline(buff, MAX_LENGTH, ';'); // ������ patronymic
		fio.set_patronymic(buff);

		int temp_int;
		file >> temp_int; // ������ ����� �����
		t.set_id(temp_int);
		file.ignore();

		float sum;
		file >> sum; // ������ ����� �� �����

		t.set_sum(sum);
		t.set_client(fio);
		file.ignore();

		list[i] = t;

		delete[] buff;
	}

	file.close();
	return list;
}

Credit *read_credits() { // ������ �� �����
	Credit*list = new Credit[100];

	ifstream file(PATH_CR);
	if (!file) {
		cout << "File isn't open" << endl;
		return list;
	}

	file >> Credit::count;

	// surname;name;patr;ccn;sum;percent
	for (int i = 0; i < Credit::count; ++i) {
		if (file.eof()) {
			Credit::count = i;
			cout << "Something went wrong";
			return list;
		}
		Credit t;
		Fio fio;

		file.ignore();

		char *buff = new char[MAX_LENGTH + 1];

		file.getline(buff, MAX_LENGTH, ';'); // ������ surname
		fio.set_surname(buff);

		file.getline(buff, MAX_LENGTH, ';'); // ������ name
		fio.set_name(buff);

		file.getline(buff, MAX_LENGTH, ';'); // ������ patronymic
		fio.set_patronymic(buff);

		int temp_int;
		file >> temp_int; // ������ ����� �������
		t.set_ccn(temp_int);
		file.ignore();

		float temp_float;
		file >> temp_float; // ������ ����� �������
		t.set_sum(temp_float);
		file.ignore();

		file >> temp_float; // ������ ������� �������
		t.set_percent(temp_float);
		file.ignore();


		t.set_client(fio);

		list[i] = t;

		delete[] buff;
	}

	file.close();
	return list;
}

int menu() { // ����� ������ � ����
	int opt;
	cout << "1. Enter new bank account" << endl;
	cout << "2. Enter new credit" << endl;
	cout << "3. Print all the deposits" << endl;
	cout << "4. Print all the credits" << endl;
	cout << "5. Print all the elements" << endl;
	cout << "6. Sort deposits by decreasing sum" << endl;
	cout << "7. Sort credits by decreasing sum" << endl;
	cout << "8. Search deposit by ID" << endl;
	cout << "9. Search credit by CCN" << endl;
	cout << "10. Exit and save" << endl << endl;

	do {
		cout << "Enter option: ";
		cin >> opt;
		if (opt >= 1 && opt <= 10) {
			break;
		}
		cout << "Wrong option, try again" << endl;
	} while (true);
	cin.ignore();

	return opt;
}

int Deposit::count = 0; // ������������� ����������� ����������
int Credit::count = 0; // ������������� ����������� ����������

int main() {
	int opt;
	int am;
	int temp;
	Deposit bank;
	Deposit *list = read_deposits();
	Credit credit;
	Credit *cr_list = read_credits();

	Deposit banker = Deposit();
	cout << "Was" << endl << banker << endl << endl;

	banker = banker + 205; // �������� ����������������� ���������� �������� ��������

	cout << "Became" << endl << banker << endl << endl;

	while (true) {
		opt = menu();
		cout << endl;
		switch (opt) {
		case 1: { // ���� ������ ����� � �����
			list[Deposit::count] = enter_deposit();
			++Deposit::count;
			cout << endl << endl;
			break;
		}
		case 2: { // ���� ������ ������� � �����
			cr_list[Credit::count] = enter_credit();
			++Credit::count;
			cout << endl << endl;
			break;
		}
		case 3: { // ���������� ��� ��������
			print_list(list, Deposit::count);
			cout << endl << endl;
			break;
		}
		case 4: { // ���������� ��� �������
			print_list(cr_list, Credit::count);
			cout << endl << endl;
			break;
		}
		case 5: { // ���������� ��
			cout << "Deposits:" << endl;
			print_list(list, Deposit::count);
			cout << endl << endl;
			cout << "Credits:" << endl;
			print_list(cr_list, Credit::count);
			cout << endl << endl;
			break;
		}
		case 6: { // ���������� �� ����� �������� (�� �������� � ��������, �� ����������)
			sort_by_sum(list, am);
			print_list(list, Deposit::count);
			cout << endl << endl;
			break;
		}
		case 7: { // ���������� �� ����� ������� (�� �������� � ��������, �� ����������)
			sort_by_sum(cr_list, am);
			print_list(cr_list, Credit::count);
			cout << endl << endl;
			break;
		}
		case 8: { // ����� �� �������
			cout << "Enter id: ";
			cin >> temp;
			if (find_by_id(list, bank, temp)) {
				cout << "Has found an account!" << endl << endl << bank << endl;
			}
			else {
				cout << "Nothing has found!" << endl;
			}
			cout << endl << endl;
			break;
		}
		case 9: { // ����� �� ������ �������
			cout << "Enter ccn: ";
			cin >> temp;
			if (find_by_ccn(cr_list, credit, temp)) {
				cout << "Has found a credit!" << endl << endl << credit << endl;
			}
			else {
				cout << "Nothing has found!" << endl;
			}
			cout << endl << endl;
			break;
		}
		case 10: { // ����� � ����������
			save(list);
			save(cr_list);
			return 0;
		}
		default: {
			break;
		}
		}
	}
}
