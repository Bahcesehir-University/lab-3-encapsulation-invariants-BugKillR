// ============================================================
// CMP1002 - Lab: Encapsulation and Invariants
// Student Version - MainProgram.cpp
// ============================================================
// Instructions:
//   Complete all TODO sections below.
//   Do NOT modify function signatures or class interfaces.
//   All logic must remain in this single file.
// ============================================================

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

// ================================
// CLASS DEFINITIONS
// ================================

// --------------------------------------------------
// Class: Temperature
// Represents a temperature in Celsius.
// Invariant: temperature must be >= -273.15 (absolute zero)
// --------------------------------------------------
class Temperature {
private:
    double celsius_;

public:
    explicit Temperature(double celsius) {
        if (celsius < -273.15)
            throw std::invalid_argument("Invalid celsius value!\n");
        celsius_ = celsius;
    }

    double getCelsius() const {
        return celsius_;
    }

    double getFahrenheit() const {
        return ((celsius_ * 9/5) + 32);
    }

    void setCelsius(double celsius) {
        if (celsius < -273.15)
            throw std::invalid_argument("Can't set to this value!\n");
        celsius_ = celsius;
    }
};

// --------------------------------------------------
// Class: BankAccount
// Represents a simple bank account.
// Invariants:
//   - balance must never be negative
//   - owner name must not be empty
// --------------------------------------------------
class BankAccount {
private:
    string owner_;
    double balance_;

public:
    BankAccount(const string& owner, double initialBalance) {
        if (owner.empty() || initialBalance < 0)
            throw std::invalid_argument("Owner name is empty or balance is lower than 0!\n");
        owner_ = owner;
        balance_ = initialBalance;
    }

    string getOwner() const {
        return owner_;
    }

    double getBalance() const {
        return balance_;
    }

    void deposit(double amount) {
        if (amount <= 0)
            throw std::invalid_argument("Amount must be greater or equal to zero!\n");
        balance_ += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0)
            throw std::invalid_argument("Cannot withdraw money less or equal than 0!\n");
        if (balance_ - amount < 0)
            throw std::runtime_error("Insufficient funds!\n");
        balance_ -= amount;
    }

    void transfer(BankAccount& other, double amount) {
        withdraw(amount);
        other.deposit(amount);
    }
};

// --------------------------------------------------
// Class: Password
// Represents a password with strength rules.
// Invariants:
//   - password length must be >= 8
//   - password must contain at least one digit
// --------------------------------------------------
class Password {
private:
    string password_;

    // Helper: check if a string contains at least one digit
    static bool hasDigit(const string& s) {
        int i = 0;

        while (s[i])
        {
            if ('0' <= s[i] && s[i] <= '9')
                return true;
            i++;
        }
        return false;
    }

    // Helper: validate password against all rules
    static void validate(const string& pwd) {
        // TODO: Check length >= 8 and hasDigit
        // Throw std::invalid_argument with descriptive message if invalid
        if (!hasDigit(pwd) || pwd.length() < 8)
            throw std::invalid_argument("Invalid password!\n");
    }

public:
    // Constructor: create a password.
    // Must pass validation.
    explicit Password(const string& pwd) {
        validate(pwd);
        password_ = pwd;
    }

    // Change password: old password must match, new must be valid.
    // Throw std::invalid_argument if oldPassword doesn't match
    // Throw std::invalid_argument if newPassword fails validation
    void change(const string& oldPassword, const string& newPassword) {
        if (!matches(oldPassword))
            throw std::invalid_argument("Old password doesn't match!\n");
        validate(newPassword);
        password_ = newPassword;
    }

    // Check if a given string matches the stored password.
    bool matches(const string& attempt) const {
        return (password_ == attempt);
    }

    // Return the length of the password (safe to expose)
    size_t getLength() const {
        return password_.length();
    }

    // NOTE: There is deliberately NO getPassword() method.
    // Exposing the raw password would break encapsulation.
};


// ================================
// MAIN FUNCTION
// ================================
int main() {
    cout << "=== Encapsulation and Invariants Lab ===" << endl;
    cout << endl;

    // --- Temperature Demo ---
    cout << "--- Temperature ---" << endl;
    try {
        Temperature t(100.0);
        cout << "Celsius: " << t.getCelsius() << endl;
        cout << "Fahrenheit: " << t.getFahrenheit() << endl;
        t.setCelsius(-40.0);
        cout << "Updated Celsius: " << t.getCelsius() << endl;
        cout << "Updated Fahrenheit: " << t.getFahrenheit() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // Try invalid temperature
    try {
        Temperature bad(-300.0);
        cout << "This should not print!" << endl;
    } catch (const invalid_argument& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }
    cout << endl;

    // --- BankAccount Demo ---
    cout << "--- BankAccount ---" << endl;
    try {
        BankAccount alice("Alice", 1000.0);
        BankAccount bob("Bob", 500.0);
        cout << alice.getOwner() << " balance: " << alice.getBalance() << endl;

        alice.deposit(200.0);
        cout << "After deposit: " << alice.getBalance() << endl;

        alice.transfer(bob, 300.0);
        cout << "After transfer:" << endl;
        cout << "  Alice: " << alice.getBalance() << endl;
        cout << "  Bob:   " << bob.getBalance() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    // --- Password Demo ---
    cout << "--- Password ---" << endl;
    try {
        Password pw("Secure99");
        cout << "Password length: " << pw.getLength() << endl;
        cout << "Matches 'wrong': " << pw.matches("wrong") << endl;
        cout << "Matches 'Secure99': " << pw.matches("Secure99") << endl;
        pw.change("Secure99", "NewPass1");
        cout << "Password changed successfully." << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << endl;
    cout << "=== Lab Complete ===" << endl;
    return 0;
}
