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
	explicit Date(const string& input_date)
	{
		istringstream inp(input_date);
		int new_year, new_month, new_day;
		int symbol1 , symbol2;
		inp >> new_year;
		symbol1 = inp.get();
		inp >> new_month;
		symbol2 = inp.get();
		inp >> new_day;
		if(inp.peek() != -1 || symbol1 == -1 || symbol2 == -1){
			throw runtime_error("Wrong format date");
		}
		else{
			if(new_month > 12 || new_month < 1){
				throw runtime_error("Month value is invalid: " + to_string(new_month));
			}
			else{
				if(new_day > 31 || new_day < 1){
					throw runtime_error("Day value is invalid: " + to_string(new_day));
				}
				else{
					year = new_year;
					month = new_month;
					day = new_day;
				}
			}
		}

	};
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
  };

  void Print() const
  {
	  for(const auto& item: pair)
	  {
		  for(const auto& event: item.second)
		  {
			  cout << setfill('0') << setw(4) << item.first.GetYear() << "-"
					  << setw(2) << item.first.GetMonth() << "-"
					  << setw(2) << item.first.GetDay()
					  << " " << event << endl;
		  }
	  }
  };
};

int main()
{
  Database db;
  set<string> all_commands = {"Del", "Find", "Print", "Add",""};
  string command;
  while (getline(cin, command))
  {
	  stringstream inp(command);
	  string activity, date;
	  inp >> activity;
	  if(all_commands.find(activity) != all_commands.end())
	  {
		  try
		  {
			  if(activity == "Del"){
				  string date, event;
				  inp >> date >> event;
				  if(event.size() != 0){
					  if(db.DeleteEvent(Date(date), event)){
						  cout << "Deleted successfully" << endl;
					  }
					  else{
						  cout << "Event not found" << endl;
					  }
				  }
				  else{
					  int deleted = db.DeleteDate(Date(date));
					  cout << "Deleted " << deleted << " events" << endl;
				  }
			  }
			  else if(activity == "Find")
			  {
				  string date;
				  inp >> date;
				  db.Find(Date(date));
			  }
			  else if(activity == "Print")
			  {
				  db.Print();
			  }
			  else if(activity == "Add")
			  {
				  string date, event;
				  inp >> date >> event;
				  db.AddEvent(Date(date), event);
			  }
			  else{
				  continue;
			  }
		  }catch(exception& ex){
			  cout << ex.what() << endl;
			  break;
		  }
	  }
	  else
	  {
		  cout << "Unknown command: " << activity << endl;
		  break;
	  }
  }

  return 0;
}
