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
	void UpdateDate(const int& new_year, const int& new_month, const int& new_day){
		year = new_year;
		month = new_month;
		day = new_day;
	}
public:
	Date()
	{
		year = 0;
		month = 0;
		day = 0;
	};
	Date(const int& new_year, const int& new_month, const int& new_day){
		UpdateDate(new_year, new_month, new_day);
	}
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
  friend istream& operator>>(istream& stream, Date& my_date);
};

bool operator<(const Date& lhs, const Date& rhs)
{
	int summary_day_lhs = 12 * 31 * lhs.GetYear() + 31 * lhs.GetMonth() + lhs.GetDay();
	int summary_day_rhs = 12 * 31 * rhs.GetYear() + 31 * rhs.GetMonth() + rhs.GetDay();
	return summary_day_lhs < summary_day_rhs;
};
istream& operator>>(istream& stream, Date& my_date){
	string error,input_date;
	stream >> error;
	input_date = error;
	istringstream inp(input_date);
	int new_year, new_month, new_day;
	char symbol1 , symbol2;
	inp >> new_year >> symbol1 >> new_month >> symbol2;
	if(inp.peek() == -1){
		throw runtime_error("Wrong date format: " + error);
	}
	inp >> new_day;
	if(!inp.eof() || symbol1 != '-' || symbol2 != '-'){
		throw runtime_error("Wrong date format: " + error);
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
				my_date.year = new_year;
				my_date.month = new_month;
				my_date.day = new_day;
				my_date.UpdateDate(my_date.year, my_date.month, my_date.day);
			}
		}
	}
	return stream;
}

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
	  string activity;
	  inp >> activity;
	  if(all_commands.find(activity) != all_commands.end())
	  {
		  try
		  {
			  if(activity == "Del"){
				  string event;
				  Date new_date;
				  inp >> new_date >> event;
				  if(event.size() != 0){
					  if(db.DeleteEvent(new_date, event)){
						  cout << "Deleted successfully" << endl;
					  }
					  else{
						  cout << "Event not found" << endl;
					  }
				  }
				  else{
					  int deleted = db.DeleteDate(new_date);
					  cout << "Deleted " << deleted << " events" << endl;
				  }
			  }
			  else if(activity == "Find")
			  {
				  Date new_date;
				  inp >> new_date;
				  db.Find(new_date);
			  }
			  else if(activity == "Print")
			  {
				  db.Print();
			  }
			  else if(activity == "Add")
			  {
				  string event;
				  Date new_date;
				  inp >> new_date >> event;
				  db.AddEvent(new_date, event);
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
