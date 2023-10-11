#include <iostream>
#include <string>
#include <random>
#include <regex>


using namespace std;

class Password {
private:
    string characters;
    bool strong;
    int length;
public:
    // Set up object
    // Option 1
    Password(int x) {
        characters = generatePassword(x);
        length = x;
    };
    // Option 2
    // Constructor overloading / polymorphism
    Password(int x, string s) {
        characters = generatePassword(x);
        length = x;
        // after valid password is found
        characters = appendToString(s);
    };
    bool checkStrength(string s, int x) {
        // Determine password strength, "strong" is 1/true when it contains one of each character type
        strong = (regex_match(s, regex("^.*(?=.{8,})(?=.*[a-zA-Z])(?=.*\\d)(?=.*[!#$%&? \"]).*$")));
        return strong;
    }
    string generatePassword(int x) {
        const string allowableChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^<>,.&*()_";
        const int passwordLength = x;
        // Create a random device
        std::random_device rd;

        // Initialize a random number generator engine with the random device
        std::default_random_engine engine(rd());

        // Create a uniform distribution in the range of allowable characters
        std::uniform_int_distribution<int> dist(0, allowableChars.size() - 1);

        // Choose characters randomly from string
        string password;
        for (int i = 0; i < passwordLength; ++i) {
            password += allowableChars[dist(engine)];
        }

        // Initiate string validation
        checkStrength(password, length);

        // Recursively call generatePassword until it finds a strong combo
        if (!strong) {
            return generatePassword(x);
        } else {
            // update private "character" member
            characters = password;
            return password;
        }
    }
    string appendToString(string s) {
        string temp = characters + s;
        characters = temp;
        return characters;
    }
    void printPassword() {
        cout << "Generated Strong Password: " << characters << endl;
    }
};

int main() {
    // (int, string)
    // (desired character length, insert phrase into password)
    Password newPassword1(22);
    Password newPassword2(8, "meow");

    newPassword1.printPassword();
    newPassword2.printPassword();
}

