#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <vector>

using namespace std;

class ElectricityBill {
private:
    double costPerKWh; 
    string date;       
    double totalKWh;   
    double amountPaid;

public:

    ElectricityBill(double cost, const string& billDate, double kWh)
        : costPerKWh(cost), date(billDate), totalKWh(kWh), amountPaid(cost* kWh) {
        if (cost < 0 || kWh < 0) {
            throw invalid_argument("Cost and kWh must be non-negative.");
        }
    }

 
    void operator++() {
        costPerKWh++;
        amountPaid = costPerKWh * totalKWh; 
    }

    
    void operator-=(double value) {
        if (value < 0) {
            throw invalid_argument("Value to decrease must be non-negative.");
        }
        costPerKWh -= value;
        amountPaid = costPerKWh * totalKWh; 
    }

   
    bool searchByDate(const string& searchDate) const {
        return date == searchDate;
    }

    
    void displayInfo() const {
        cout << "Date: " << date << endl;
        cout << "Cost per kWh: " << fixed << setprecision(2) << costPerKWh << " UAH" << endl;
        cout << "Total kWh consumed: " << fixed << setprecision(2) << totalKWh << " kWh" << endl;
        cout << "Amount paid: " << fixed << setprecision(2) << amountPaid << " UAH" << endl;
    }
};

int main() {
    try {
        
        vector<ElectricityBill> bills = {
            ElectricityBill(4.32, "2024-10-06", 320.0),
            ElectricityBill(3.85, "2024-09-28", 250.5),
            ElectricityBill(5.10, "2024-10-10", 400.0)
        };

        
        for (const auto& bill : bills) {
            bill.displayInfo();
            cout << endl;
        }

      
        string searchDate;
        cout << "Enter the date to search for the bill (format: YYYY-MM-DD): ";
        cin >> searchDate;

        bool found = false;
        for (const auto& bill : bills) {
            if (bill.searchByDate(searchDate)) {
                cout << "\nBill found for date: " << searchDate << endl;
                bill.displayInfo();
                found = true;
                break; 
            }
        }

        if (!found) {
            cout << "\nBill not found for date: " << searchDate << endl;
        }
    }
    catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}



