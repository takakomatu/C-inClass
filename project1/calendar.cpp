#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std; 

// Function prototypes
void readInput(string &startMY, string &endMY);
void initTM(tm &DTM);
void extractDate(string MY, int &Month, int &Year);
void openDocument();
void Header();
void outputHeader();
void outputOpenTable();
void outputOpenMonthTable(string Month, int year);
void outputCloseMonthTable();
void processYears(string startMY, string endMY);
int processMonths(int beginMonth, int stopMonth, int year, 
                                  int firstDayOfFirstWeek, int febDays); 
void printMonth(int month, int year, int firstDayOfFirstWeek, int days);
int extractStartDayOfFirstWeek(int startMonth, int startYear);
void outputCloseTable();
void Footer();
void closeDocument();

// -------------------------------------------------------------------
int main() {
   string startMY, endMY;

   readInput(startMY, endMY);
   openDocument();
   Header();
   outputHeader();
   outputOpenTable();
   processYears(startMY, endMY);
   outputCloseTable();
   Footer();
   closeDocument();
}

// -------------------------------------------------------------------
void processYears(string startMY, string endMY) {
   int startYear, startMonth;
   int endYear, endMonth;
   int num_months;
   int febDays;
   int daysOfYear;
   
   extractDate(startMY, startMonth, startYear);
   extractDate(endMY, endMonth, endYear);

   int startDayOfFirstWeek = extractStartDayOfFirstWeek(startMonth, startYear);
   int firstDayOfFirstWeek = startDayOfFirstWeek+1; 

   for (int years = startYear; years <= endYear; years++) {
      int beginMonth, stopMonth, beginYear, stopYear, Days;
      if ((years%4)==0) {
         febDays = 29;
      }
      else {
         febDays = 28;
      }
      if (years == startYear) {
         beginMonth = startMonth;
      }
      else {
         beginMonth = 1;
      }
      if (years == endYear) {
         stopMonth = endMonth;
      }
      else {
         stopMonth = 12;
      }
      daysOfYear = processMonths(beginMonth, stopMonth, years, firstDayOfFirstWeek, febDays); 
      startDayOfFirstWeek = extractStartDayOfFirstWeek(1, years+1);
      firstDayOfFirstWeek = startDayOfFirstWeek+1;
   }
}

// -------------------------------------------------------------------
int extractStartDayOfFirstWeek(int startMonth, int startYear) {
   // The following code creates a string stream which is a stream (like cout or cin) which
   // is associated with a string.  As a stream, the extraction >> and insertion << operators are
   // supported
   stringstream ss;
   string date;
   if (startMonth < 10) ss << "0";
   ss << startMonth << "/01/" << startYear;
   // convert the stream to a string
   date = ss.str();
   tm startTM;
   initTM(startTM);
   strptime(date.c_str(), "%m/%d/%Y", &startTM); 
   return startTM.tm_wday; 
}

// -------------------------------------------------------------------
int processMonths(int beginMonth, int stopMonth, int year, 
                                  int firstDayOfFirstWeek, int febDays) {
   int days;
   int sumDays = 0;
   for (int months = beginMonth; months <= stopMonth; months++) {
      switch(months) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            days = 31;
            break;
        case 4: case 6: case 9: case 11:
            days = 30;
            break;
        case 2:
            days = febDays;
            break;
      }
      sumDays += days;

      printMonth(months, year, firstDayOfFirstWeek, days);
      firstDayOfFirstWeek = firstDayOfFirstWeek + days - 28; 
      if (firstDayOfFirstWeek > 7) firstDayOfFirstWeek -= 7;
   }
   return sumDays;
}

// -------------------------------------------------------------------
string convertMonth(int month) {
   string Month; 
   switch(month) {
      case 1: Month="January"; break;
      case 2: Month="February"; break;
      case 3: Month="March"; break;
      case 4: Month="April"; break;
      case 5: Month="May"; break;
      case 6: Month="June"; break;
      case 7: Month="July"; break;
      case 8: Month="August"; break;
      case 9: Month="September"; break;
      case 10: Month="October"; break;
      case 11: Month="November"; break;
      case 12: Month="December"; break;
   }
   return Month;
}

// -------------------------------------------------------------------
void printMonth(int month, int year, int firstDayOfFirstWeek, int days) {
   string Month;
   int day = 1;
   int dayofweek;

   Month = convertMonth(month);

   // generate the first week of the month
   cout << "<tr><td>";
   outputOpenMonthTable(Month, year);
   cout << "<tr>";
   for (dayofweek = 1; dayofweek <= 7; dayofweek++) {
      cout << "<td>";
      if (dayofweek >= firstDayOfFirstWeek) {
         cout << day;
         day++;
      }
      cout << "</td>";
   }
   cout << "</tr>" << endl;

   // generate remaining days of the month
   dayofweek = 1;
   cout << "<tr>";
   while (day <= days) {
      cout << "<td>";
      cout << day;
      cout << "</td>";
      day++;
      if ((dayofweek%7)==0) {
         cout << "</tr>" << endl << "<tr>";
         dayofweek = 1;
      }
      else
         dayofweek++;
   }
   
   // generate the rest of the last week of the month
   while(dayofweek <= 7) {
      cout << "<td>";
      cout << "</td>";
      dayofweek++;
   }
   cout << "</tr>" << endl;

   outputCloseMonthTable();
   cout << "</td></tr>" << endl;
}

// -------------------------------------------------------------------
void extractDate(string MY, int &Month, int &Year) {
   int pos;
   pos = MY.find("/");
   if (pos >= 0) {
      stringstream ss(MY.substr(0, pos));
      ss >> Month;
      MY = MY.substr(pos+1, MY.length());
      stringstream ss2(MY.substr(0, MY.length()));
      ss2 >> Year;
   }
   else {
      cout << "format of date is invalid" << endl;
      cout << "format of date is invalid" << endl;
      return;
   }
}

// -------------------------------------------------------------------
void readInput(string &startMonthYear, string &endMonthYear) {
   cerr << "Please enter the starting Month and Year: ";
   cin >> startMonthYear;
   cerr << "Please enter the ending Month and Year: ";
   cin >> endMonthYear;
   return;
}

// -------------------------------------------------------------------
void initTM(tm &DTM) {
   DTM.tm_sec=0;
   DTM.tm_min=0;
   DTM.tm_hour=0;
   DTM.tm_mday=0;
   DTM.tm_mon=0;
   DTM.tm_year=0;
   DTM.tm_wday=0;
   DTM.tm_yday=0;
   DTM.tm_isdst=0;
}

// -------------------------------------------------------------------
void openDocument() {
   cout << "<!DOCTYPE html>" << endl;
   cout << "<head>" << endl;
   cout << "<title> Calendar </title>" << endl;
   cout << "</head>" << endl;
   cout << "<body>" << endl;
}

// -------------------------------------------------------------------
void Header() {
   cout << "Lawrence Miller CSC 24400 Section 21 <br>" << endl;
   cout << "Spring 2018 Assignment Example 1 <br>" << endl;
   cout << "<br><hr><br><br>" << endl;
}

// -------------------------------------------------------------------
void outputHeader() {
   cout << "<h1>Calendar</h1><br><br>" << endl;
}

// -------------------------------------------------------------------
void outputOpenTable() {
   cout << "<table>" << endl; // border=" << '"' << "1" << '"' << ">" << endl;
}

// -------------------------------------------------------------------
void outputOpenMonthTable(string Month, int year) {
   cout << "<table border=" << '"' << 1 << '"' << ">" << endl;
   cout << "<tr><th colspan=" << '"' << "7" << '"' << ">" << Month << " " << year << "</th></tr>" << endl;
   cout << "<tr><td>Sun</td> <td>Mon</td> <td>Tue</td> <td>Wed</td> <td>Thu</td> <td>Fri</td> <td>Sat</td> </tr>" << endl; 
}

// -------------------------------------------------------------------
void outputCloseMonthTable() {
   cout << "</table>" << endl;
}

// -------------------------------------------------------------------
void outputCloseTable() {
   cout << "</table>" << endl;
}

// -------------------------------------------------------------------
void Footer() {
   cout << "<br><br><hr><br>" << endl;
   cout << "END OF PROGRAM OUTPUT" << endl;
   cout << "<br><hr>" << endl;
}

// -------------------------------------------------------------------
void closeDocument() {
   cout << "</body>" << endl;
   cout << "</html>" << endl;
}
