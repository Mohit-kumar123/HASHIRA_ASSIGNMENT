#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Point {
    int x;
    long long y;
};

// Convert number from any base (2-16) to decimal
long long convertBase(const string& num, int base) {
    const long long MOD = 1000000007LL; // using modular arithmetic for large numbers
    long long decimal = 0;
    long long multiplier = 1;
    
    for (int i = num.length() - 1; i >= 0; i--) {
        char c = num[i];
        int digit_val;
        
        if (c >= '0' && c <= '9') {
            digit_val = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            digit_val = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            digit_val = c - 'A' + 10;
        } else {
            return 0; // invalid character
        }
        
        if (digit_val >= base) return 0; // invalid digit for base
        
        decimal = (decimal + (digit_val * multiplier) % MOD) % MOD;
        multiplier = (multiplier * base) % MOD;
    }
    
    return decimal;
}

// Find secret using Lagrange interpolation
long long findSecret(const vector<Point>& points) {
    int n = points.size();
    long double secret = 0.0L;
    
    // Calculate Lagrange interpolation at x=0
    for (int i = 0; i < n; i++) {
        long double term = 1.0L;
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (long double)(-points[j].x) / (long double)(points[i].x - points[j].x);
            }
        }
        
        secret += (long double)points[i].y * term;
    }
    
    // Round to nearest integer
    return (long long)(secret > 0 ? secret + 0.5L : secret - 0.5L);
}

int main() {
    cout << "Shamir's Secret Sharing Solution" << endl;
    cout << "===============================" << endl << endl;
    
    // Test case 1 
    cout << "Test Case 1:" << endl;
    
    vector<Point> test1_points;
    test1_points.push_back({1, convertBase("4", 10)});     
    test1_points.push_back({2, convertBase("111", 2)});    
    test1_points.push_back({3, convertBase("12", 10)});    
    
    cout << "Points: ";
    cout << "(1, " << test1_points[0].y << "), ";
    cout << "(2, " << test1_points[1].y << "), ";
    cout << "(3, " << test1_points[2].y << ")" << endl;
    
    long long secret1 = findSecret(test1_points);
    cout << "Secret: " << secret1 << endl << endl;
    
    // Test case 2
    cout << "Test Case 2:" << endl;
    
    vector<Point> test2_points;
    
    // Input data from test case 2
    string values[] = {
        "13444211440455345511",
        "aed7015a346d63", 
        "6aeeb69631c227c",
        "e1b5e05623d881f",
        "316034514573652620673",
        "2122212201122002221120200210011020220200",
        "20120221122211000100210021102001201112121"
    };
    
    int bases[] = {6, 15, 15, 16, 8, 3, 3};
    
    for (int i = 0; i < 7; i++) {
        long long y_val = convertBase(values[i], bases[i]);
        test2_points.push_back({i + 1, y_val});
        cout << "Point " << (i+1) << ": (" << (i+1) << ", " << y_val << ")" << endl;
    }
    
    long long secret2 = findSecret(test2_points);
    cout << "Secret: " << secret2 << endl;
    
    return 0;
}
