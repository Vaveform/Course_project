#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <cmath>
#include <exception>
#include <iomanip>

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
  void AddEvent(const Date& date, const string& event)
  {
	  pair[date].insert(event);
  };
  bool DeleteEvent(const Date& date, const string& event)
  {
	  if(pair.count(date) > 0 && pair.at(date).count(event) > 0)
	  {
		  pair.at(date).erase(pair.at(date).find(event));
		  return true;
	  }
	  else{
		  return false;
	  }
  };
  int  DeleteDate(const Date& date)
  {
	  auto finder = pair.find(date);
	  int result = 0;
	  if(finder != pair.end())
	  {
		  result = pair.at(date).size();
		  pair.erase(finder);
	  }
	  else{
		  throw runtime_error("Unknown signal 6");
	  }
	  return result;
  };

  void Find(const Date& date) const
  {
	  if(pair.count(date) > 0){
		  for(const auto& event: pair.at(date)){
			  cout << event << endl;
		  }
	  }
	  else{
		  throw runtime_error("Unknown signal 6");
	  }
  };

  void Print() const
  {
	  for(const auto& item: pair)
	  {
		  for(const auto& event: item.second)
		  {
			  cout << setfill('0') << setw(4) << item.first.GetYear() << "-"
					  << setw(2) << item.first.GetMonth()
					  << setw(2) << item.first.GetDay()
					  << " " << event << endl;
		  }
	  }
  };
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
