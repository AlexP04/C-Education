#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

string FindNameByYear(const map<int, string>& names, int year) {
	string name;

	for (const auto& item : names) {
		if (item.first <= year) {
			name = item.second;
		}
		else {
			break;
		}
	}

	return name;
}
string FindAllNamesByYear(const map<int, string>& names, int year) {
	string name = " (";
	vector<string> temp;
	for (const auto& item : names) {
		if (item.first <= year) {
			temp.push_back(item.second);
		}
		else {
			break;
		}
	}
	if (temp.empty()) return "";
	else
	{
		string last = temp[temp.size() - 1];
		temp.pop_back();
		bool all = true;
		for (int i = 0; i < temp.size(); i++) if (temp[i] != last) all = false;
		if (all) 
		{ 
			temp.clear();
			return "";
		}
		reverse(temp.begin(), temp.end());
		name += temp[0];
		for (int i = 1; i < temp.size(); i++) name += ", " + temp[i];
		name += ")";
	}
	return name;
}

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		first_names[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		last_names[year] = last_name;
	}
	string GetFullName(int year) {

		const string first_name = FindNameByYear(first_names, year);
		const string last_name = FindNameByYear(last_names, year);

		if (first_name.empty() && last_name.empty()) {
			return "Incognito";

		}
		else if (first_name.empty()) {
			return last_name + " with unknown first name";

		}
		else if (last_name.empty()) {
			return first_name + " with unknown last name";

		}
		else {
			return first_name + " " + last_name;
		}
	}
	string GetFullNameWithHistory(int year) {

		const string first_name = FindNameByYear(first_names, year) + FindAllNamesByYear(first_names, year);
		const string last_name = FindNameByYear(last_names, year) + FindAllNamesByYear(last_names, year);

		if (first_name.empty() && last_name.empty()) {
			return "Incognito";

		}
		else if (first_name.empty()) {
			return last_name + " with unknown first name";

		}
		else if (last_name.empty()) {
			return first_name + " with unknown last name";

		}
		else {
			return first_name + " " + last_name;
		}
	}
private:
	map<int, string> first_names;
	map<int, string> last_names;
};

int main() {
	Person person;

	person.ChangeFirstName(1900, "Eugene");
	person.ChangeLastName(1900, "Sokolov");
	person.ChangeLastName(1910, "Sokolov");
	person.ChangeFirstName(1920, "Evgeny");
	person.ChangeLastName(1930, "Sokolov");
	cout << person.GetFullNameWithHistory(1940) << endl;
	for (int i = 0; i < 4; i++)cout << endl;

	Person person2;

	person2.ChangeFirstName(1965, "Polina");
	person2.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person2.GetFullNameWithHistory(year) << endl;
	}

	person2.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person2.GetFullNameWithHistory(year) << endl;
	}

	person2.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person2.GetFullNameWithHistory(year) << endl;
	}

	person2.ChangeFirstName(1990, "Polina");
	person2.ChangeLastName(1990, "Volkova-Sergeeva");
	cout << person2.GetFullNameWithHistory(1990) << endl;

	person2.ChangeFirstName(1966, "Pauline");
	cout << person2.GetFullNameWithHistory(1966) << endl;

	person2.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		cout << person2.GetFullNameWithHistory(year) << endl;
	}

	person2.ChangeLastName(1961, "Ivanova");
	cout << person2.GetFullNameWithHistory(1967) << endl;
	for (int i = 0; i < 4; i++)cout << endl;


	Person person3;

	person3.ChangeFirstName(1965, "Polina");
	person3.ChangeFirstName(1965, "Appolinaria");

	person3.ChangeLastName(1965, "Sergeeva");
	person3.ChangeLastName(1965, "Volkova");
	person3.ChangeLastName(1965, "Volkova-Sergeeva");

	for (int year : {1964, 1965, 1966}) {
		cout << person3.GetFullNameWithHistory(year) << endl;
	}

	return 0;
}
