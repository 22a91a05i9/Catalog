#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Convert string from given base to decimal
long long decodeValue(const string& value, int base) {
    long long result = 0;
    for (char c : value) {
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        }
        result = result * base + digit;
    }
    return result;
}

class PolynomialSolver {
private:
    struct Point {
        long long x;
        long long y;
    };
    
    vector<Point> points;
    
    // Lagrange interpolation to find f(0)
    long long lagrangeInterpolation() {
        long long result = 0;
        int n = points.size();
        
        for (int i = 0; i < n; i++) {
            long long numerator = points[i].y;
            long long denominator = 1;
            
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    numerator *= (-points[j].x);
                    denominator *= (points[i].x - points[j].x);
                }
            }
            
            // Ensure denominator is positive
            if (denominator < 0) {
                numerator *= -1;
                denominator *= -1;
            }
            
            result += numerator / denominator;
        }
        
        return result;
    }
    
public:
    void addPoint(long long x, long long y) {
        points.push_back({x, y});
    }
    
    void clearPoints() {
        points.clear();
    }
    
    long long findSecret() {
        if (points.empty()) {
            cerr << "Error: No points loaded" << endl;
            return 0;
        }
        
        return lagrangeInterpolation();
    }
    
    void printPoints() {
        cout << "Decoded points:" << endl;
        for (const auto& p : points) {
            cout << "(" << p.x << ", " << p.y << ")" << endl;
        }
    }
};

// Test case 1 data
void testCase1(PolynomialSolver& solver) {
    solver.clearPoints();
    
    // Point 1: base 10, value 4
    solver.addPoint(1, 4);
    
    // Point 2: base 2, value 111 = 7
    solver.addPoint(2, 7);
    
    // Point 3: base 10, value 12
    solver.addPoint(3, 12);
    
    // Point 6: base 4, value 213 = 2*16 + 1*4 + 3 = 39
    solver.addPoint(6, 39);
}

// Test case 2 data
void testCase2(PolynomialSolver& solver) {
    solver.clearPoints();
    
    // Point 1: base 6, value 13444211440455345511
    solver.addPoint(1, decodeValue("13444211440455345511", 6));
    
    // Point 2: base 15, value aed7015a346d63
    solver.addPoint(2, decodeValue("aed7015a346d63", 15));
    
    // Point 3: base 15, value 6aeeb69631c227c
    solver.addPoint(3, decodeValue("6aeeb69631c227c", 15));
    
    // Point 4: base 16, value e1b5e05623d881f
    solver.addPoint(4, decodeValue("e1b5e05623d881f", 16));
    
    // Point 5: base 8, value 316034514573652620673
    solver.addPoint(5, decodeValue("316034514573652620673", 8));
    
    // Point 6: base 3, value 2122212201122002221120200210011020220200
    solver.addPoint(6, decodeValue("2122212201122002221120200210011020220200", 3));
    
    // Point 7: base 3, value 20120221122211000100210021102001201112121
    solver.addPoint(7, decodeValue("20120221122211000100210021102001201112121", 3));
}

int main() {
    cout << "=== Polynomial Solver - Secret Sharing ===" << endl;
    cout << "Using Lagrange interpolation to find secret C" << endl;
    
    PolynomialSolver solver;
    
    // Test Case 1
    cout << "\nTest Case 1 (k=3, using first 3 points):" << endl;
    testCase1(solver);
    solver.printPoints();
    long long secret1 = solver.findSecret();
    cout << "Secret C: " << secret1 << endl;
    
    // Test Case 2
    cout << "\nTest Case 2 (k=7, using first 7 points):" << endl;
    testCase2(solver);
    solver.printPoints();
    long long secret2 = solver.findSecret();
    cout << "Secret C: " << secret2 << endl;
    
    return 0;
}
