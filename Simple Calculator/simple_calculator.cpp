#include<iostream>
#include<cmath>

using namespace std;

void add(double num1, double num2) {
    double result = num1 + num2;
    cout<< endl << "Addition of " << num1 << " and " << num2 << " is: " << result << endl;
}
void subtract(double num1, double num2) {
    double result = num1 - num2;
    cout<< endl << "Substraction of " << num1 << " and " << num2 << " is: " << result << endl;
}
void multiply(double num1, double num2) {
    double result = num1 * num2;
    cout<< endl << "Multiplication of " << num1 << " and " << num2 << " is: " << result << endl;
}
void divide(double num1, double num2) {
   if(num2 == 0) {
        cout<< endl << "Number can not divide by zero" << endl;
    } else {
        double result = num1 / num2;
        cout<< endl << "Divison of " << num1 << " and " << num2 << " is: " << result << endl;
    }
}
void remainder(int num1, int num2) {
    if(num2 == 0) {
        cout<< endl << "Number can not modulus by zero" << endl;
    } else {
        int result = num1 % num2;
        cout<< endl << "Modulus of " << num1 << " and " << num2 << " is: " << result << endl;
    }
}
void power(double num1, double num2) {
    double result = pow(num1, num2);
    cout<< endl << "Power of " << num1 << " by " << num2 << " is: " << result << endl;
}
void square_root(double num1) {
    double result = sqrt(num1);
    cout<< endl << "Sqyare Root of " << num1 << " is: " << result << endl;
}

int main() {
    int choice;
    double num1, num2;
    
    cout<< endl << "\t------Welcome To Simple Calculator------" << endl;

    do {
        start:
        cout<< endl << "Choose one of the following Operator." << endl;
        cout<< "1 for Addition(+)" << endl;
        cout<< "2 for Substraction(-)" << endl;
        cout<< "3 for Multiplication(*)" << endl;
        cout<< "4 for Divison(/)" << endl;
        cout<< "5 for Modulus(%)" << endl;
        cout<< "6 for Power(^)" << endl;
        cout<< "7 for Sqaure Root()" << endl;
        cout<< "8 for EXIT" << endl;

        cout<< endl << "Please enter your choice: ";
        cin>> choice;

        if(choice < 1 || choice > 8) {
            cout<< endl << "Invalid choice, enter valid choice." << endl;
            goto start;
        }

        if(choice == 8) {
            cout<< endl << "\tThank You" << endl;
            return 0;
        } else if(choice == 7) {
            cout<< "Enter the value of number: ";
            cin>> num1;
        } else {
            cout<< "Enter the value of first number: ";
            cin>> num1;
            cout<< "Enter the value of second number: ";
            cin>> num2;
        }
        
        switch (choice)
        {
        case 1: add(num1, num2);
            break;
        case 2: subtract(num1, num2);
            break;
        case 3: multiply(num1, num2);
            break;
        case 4: divide(num1, num2);
            break;
        case 5: remainder((int)num1, (int)num2); //Cast into int for modulus
            break;
        case 6: power(num1, num2);
            break;
        case 7: square_root(num1);
            break;
        }
    } while(true);
}
