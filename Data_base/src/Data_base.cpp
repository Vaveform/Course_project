#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

class Date {
	int year;
	int month;
	int day;
public:
  int GetYear() const
  {
	  return year;
  };
  int GetMonth() const
  {
	  return month;
  };
  int GetDay() const
  {
	  return day;
  };
};

bool operator<(const Date& lhs, const Date& rhs)
{
	int summary_day_lhs = 12 * 31 * abs(lhs.GetYear()) + 31 * lhs.GetMonth() + lhs.GetDay();
	int summary_day_rhs = 12 * 31 * abs(rhs.GetYear()) + 31 * rhs.GetMonth() + rhs.GetDay();
	return summary_day_lhs < summary_day_rhs;
};

class Database {
private:
  map<Date, set<string>> pair;
public:
  void AddEvent(const Date& date, const string& event);
  bool DeleteEvent(const Date& date, const string& event);
  int  DeleteDate(const Date& date);

  void Find(const Date& date) const
  {
	  if(pair.count(date) > 0){
		  for(const auto& event: pair.at(date)){
			  cout << event << endl;
		  }
	  }
  };

  void Print() const;
};

int main()
{
  Database db;

  string command;
  while (getline(cin, command))
  {
  }

  return 0;
}
