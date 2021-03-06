// Banking-Management-System

#include<bits/stdc++.h>

using namespace std;

class Crypt {

    string encryptedString, decryptedString;
    int i;

    public:

    // Encryption algorithm for encrypting aadhar number
    string encryptText(string textString) {

        encryptedString = "";
        i = 0;

        for(char c : textString) {

            if(i >= 0 && i <= 3) {
                encryptedString += c + 5;
                i++;
            }
            else if(i >= 4 && i <= 7) {
                encryptedString += c - 5;
                i++;
            }
            else if(i >=8 && i <= 11) {
                encryptedString += c + 10;
                i++;
            }
            else {
                encryptedString += c - 10;
                i++;
            }
            
        }
        return encryptedString;     
    }

    // Decryption algorithm for decrypting aadhar number
    string decryptText(string textString) {

        decryptedString = "";
        i = 0;

        for(char c : textString) {

            if(i >= 0 && i <= 3) {
                decryptedString += c - 5;
                i++;
            }
            else if(i >= 4 && i <= 7) {
                decryptedString += c + 5;
                i++;
            }
            else if(i >=8 && i <= 11) {
                decryptedString += c - 10;
                i++;
            }
            else {
                decryptedString += c + 10;
                i++;
            }       
        }
        return decryptedString;     
    }

};

bool isPasswordValid(string pass) {

    int alphabetCount = 0, digitCount = 0, specialCharacterCount = 0;

    if(pass.length() < 10) {
        cout<<pass.length()<<endl;
        return false;
    }
    else {
        for(char c : pass) {
        
            if(c >= 65 && c <= 90 || c >= 97 && c <= 122) {
                alphabetCount++;
            }
            else if(c >= 48 && c <= 57){
                digitCount++;
            }
            else {
                specialCharacterCount++;
            }
        }

        if(alphabetCount >= 5 && digitCount >= 3 && specialCharacterCount >= 2 )
            return true;
        else 
            return false;
        
    }
    
}

// Function that returns the current balance of an account
string getCurrentBalance(string accountNumber) {

    ifstream DatabaseFile("data.txt", ios :: in);
    Crypt c;

    string inp_line, balance = "";
    accountNumber = c.encryptText(accountNumber);

    while(getline(DatabaseFile, inp_line)) {

        if(inp_line.substr(13, 12) == accountNumber) {

            for(int i = 0, j = inp_line.length() - 1; i < j; i++, j--) {
                char temp = inp_line[i];
                inp_line[i] = inp_line[j];
                inp_line[j] = temp;
            }

            int i = 0;

            while(inp_line[i] != ';') {
                balance += inp_line[i];
                i++;
            }

            for(int i = 0, j = balance.length() - 1; i < j; i++, j--) {
                char temp = balance[i];
                balance[i] = balance[j];
                balance[j] = temp;
            }

            return balance;
            
        }
        
    }

    return "\nAccount number not found";
    
}


string getAccountNumber(string aadharNumber) {

    Crypt c;

    ifstream DatabaseFile("data.txt", ios :: in);
    string inpLine;
    aadharNumber = c.encryptText(aadharNumber);

    while(getline(DatabaseFile, inpLine)) {

        if(inpLine.substr(0, 12) == aadharNumber) {
            DatabaseFile.close();
            return c.decryptText(inpLine.substr(13, 12));   
        }
    }
    DatabaseFile.close();
    return "\nAccount not found";
    
}

// Function to convert the provided string in lowercase
char to_lowercase(char c) {

    if(c >= 'A' && c <= 'Z') {
        return c + 32;
    }

    return c;
    
}

// Check whether the given file exists
bool fileExists(const string &name) {
    ifstream File(name.c_str());
    return File.good();    
}

 bool aadharNumberExists(string Id) {

    Crypt c;

    ifstream ReadDatabase("data.txt", ios :: in);

    string inpLine, tempString = "";

    while(getline(ReadDatabase, inpLine)) {

        for(int i = 0; i < 12; i++) {
            tempString += inpLine[i];
        }

        if(c.decryptText(tempString) == Id){
            ReadDatabase.close();
            return true;
        }

        tempString = "";

    }
    ReadDatabase.close();
    return false;
     
}

bool accountNumberExists(string num) {

    Crypt c;

    ifstream ReadDatabase("data.txt", ios :: in);

    string inpLine, tempString = "";

    while(getline(ReadDatabase, inpLine)) {

        for(int i = 13; i < 25; i++) {
            tempString += inpLine[i];
        }

        if(c.decryptText(tempString) == num){
            ReadDatabase.close();
            return true;
        }

        tempString = ""; 

    }
    ReadDatabase.close();
    return false;
}

bool phoneNumberExists(string number) {

    Crypt c;

    ifstream ReadDatabase("data.txt", ios :: in);

    string inpLine, tempString = "";

    while(getline(ReadDatabase, inpLine)) {

        for(int i = 26; i < 36; i++) {
            tempString += inpLine[i];
        }

        if(c.decryptText(tempString) == number){
            ReadDatabase.close();
            return true;
        }

        tempString = ""; 

    }
    ReadDatabase.close();
    return false;
    
}


// Generate random account number
string generateAccountNumber() {

    string accountNumber = "";

    jumpHere:

    srand(time(0));

    for(int i = 0; i < 12; i++) {

        accountNumber += to_string(rand() % 10);
        
    }

    if(accountNumberExists(accountNumber)) {
        accountNumber = "";
        goto jumpHere;
    }

    return accountNumber;
    
}


// Function to create a new account
void createNewAccount() {

    Crypt c;

    ofstream WriteFile("data.txt", ios :: app);

    system("cls");

    cout<<"---- Create a new account ----"<<endl;

    cout<<"\nEnter your aadhar number -> ";
    string aadharNumber;
    cin>>aadharNumber;
    
    if(aadharNumber.length() != 12) {
        cout<<"\nAadhar number is not valid"<<endl;
    }
    else if(!aadharNumberExists(aadharNumber)) {

        cout<<"\nEnter your Name -> ";
        string name;
        cin>>name;

        cout<<"\nEnter your Surname -> ";
        string surname;
        cin>>surname;

        cout<<"\nEnter your phone number -> ";
        string phoneNumber;

        jumpHereForPhoneNumber:
        
        cin>>phoneNumber;

        if(phoneNumber.length() != 10) {
            cout<<"\nInvalid Phone Number!!"<<endl;
            cout<<"\nTry again..."<<endl;
            return;
        }
        else if(phoneNumberExists(phoneNumber)) {
            cout<<"\nYour number is already registered in our bank with another account"<<endl;
            cout<<"\nPlease enter another number..."<<endl;
            return;
        }

        for(char &c : name) {
            c = to_lowercase(c);
        }

        for(char &c : surname) {
            c = to_lowercase(c);
        }

        string accountNumber = generateAccountNumber();

        cout<<"\nNew Account Successfully created!!"<<endl;
        cout<<"\nYour account number is -> "<<accountNumber<<endl<<endl;

        system("pause");

        system("cls");

        cout<<"\n--- Set UPI pin for your account ---"<<endl;
        cout<<"\n(Pin must contain all 6 digits)"<<endl;
        cout<<"\nEnter the pin -> ";
        string UpiPin;
        cin>>UpiPin;

        while(UpiPin.length() != 6) {
            cout<<"\nEnter the pin properly as mentioned -> ";
            cin>>UpiPin;
        }

        string reEnterUpiPin;
        cout<<"\nReEnter the upi pin -> ";
        cin>>reEnterUpiPin;

        if(UpiPin != reEnterUpiPin) {
            cout<<"\nPin doesn't match!!"<<endl;
            return;
        }

        WriteFile <<  c.encryptText(aadharNumber) << ";" << c.encryptText(accountNumber) << ";" << c.encryptText(phoneNumber) << ";" << c.encryptText(UpiPin) << ";" << name << ";" << surname << ";" << "0" << endl;
        WriteFile.close();

        cout<<"\nUPI Pin registered Successfully!!"<<endl;
        cout<<"\nYour UPI Id is -> "<<name<<aadharNumber.substr(6, aadharNumber.length()-1 )<<"@Sbank"<<endl;

    }
    else {
        cout<<"\nThis details are already registered in an account!!"<<endl;
        WriteFile.close();
        return;
    }
}

void depositMoney(string accountNumber) {

    Crypt c;

    ifstream DatabaseFile("data.txt", ios :: in);
    string moneyToBeAdded, inpLine;
    bool found = false;
    int lineNumber = 0;

    while(getline(DatabaseFile, inpLine)) {
        string subStr = inpLine.substr(13, 12);
        lineNumber++;
        if(c.decryptText(subStr) == accountNumber) {
            found = true;
            break;
        }
    }

    DatabaseFile.close();

    if(!found) {
        cout<<"\nAccount number not registered in the bank"<<endl;
        return;
    }

    // If account number exists, code below to deposit money 
    // (rewrite the whole file)

    ifstream DBFILE("data.txt", ios :: in);
    ofstream TempFile("temp.txt", ios :: out);

    string lineToStore;

    while(--lineNumber) {
        getline(DBFILE, lineToStore);
        TempFile << lineToStore << endl;
    }

    getline(DBFILE, lineToStore);

    DBFILE.close();
    DatabaseFile.close();

    string lineToChange = "";

    cout<<"\nEnter the amount to be deposited in the account -> ";
    int amount;
    cin>>amount;

    lineToChange += lineToStore.substr(0, 43);

    TempFile << lineToChange << ";";

    int j = 44;

    while(lineToStore[j] != ';') {
        TempFile << lineToStore[j];
        j++;
    }
    
    TempFile << ";";

    j++;

    while(lineToStore[j] != ';') {
        TempFile << lineToStore[j];
        j++;
    }

    TempFile << ";";
    j++;

    string currentAmount = "";

    while(j != lineToStore.length()) {
        currentAmount += lineToStore[j];
        j++;
    }

    int newAmount = stoi(currentAmount) + amount;

    TempFile << newAmount << endl;

    ifstream DataFile("data.txt", ios :: in);

    lineNumber = 0;

    while(getline(DataFile, inpLine)) {
        string subStr = inpLine.substr(13, 12);
        if(c.decryptText(subStr) == accountNumber) {
            break;
        }
    }

    while(getline(DataFile, inpLine)) {
        TempFile << inpLine << endl;
    }

    DataFile.close();
    TempFile.close();

    remove("data.txt");
    rename("temp.txt", "data.txt");

    cout<<"\nTransaction Successful!!"<<endl;
    cout<<"\nYour current balance is -> "<<getCurrentBalance(accountNumber)<<endl;
}


void withdrawMoney(string accountNumber) {

    Crypt c;

    ifstream DatabaseFile("data.txt", ios :: in);
    string moneyToBeAdded, inpLine;
    bool found = false;
    int lineNumber = 0;
    string upiId = "", upiPin;

    while(getline(DatabaseFile, inpLine)) {
        string subStr = inpLine.substr(13, 12);
        lineNumber++;
        if(c.decryptText(subStr) == accountNumber) {
            int j = 44;
            while(inpLine[j] != ';') {
                upiId += inpLine[j];
                j++;
            }

            string aadharNum = inpLine.substr(0, 12);
            aadharNum = c.decryptText(aadharNum);
            upiId += aadharNum.substr(6, 6) + "@Sbank";

            upiPin = inpLine.substr(37, 6);
            upiPin = c.decryptText(upiPin);

            found = true;
            break;
        }
    }

    DatabaseFile.close();

    if(!found) {
        cout<<"\nAccount number not registered in the bank"<<endl;
        return;
    }

    jumpHere:
    
    cout<<"\nEnter the amount to withdraw from the account -> ";
    int amount;
    cin>>amount;

    int currentBalance = stoi(getCurrentBalance(accountNumber));

    if(amount < 0) {
        cout<<"\nPlease enter some valid amount"<<endl;
        goto jumpHere;
    }

    else if(amount <= currentBalance) {

        string enteredUpiId, enteredUpiPin;

        cout<<"\nEnter your Upi Id -> ";
        cin>>enteredUpiId;
        cout<<"\nEnter your Upi Pin -> ";
        cin>>enteredUpiPin;

        if(upiId == enteredUpiId && upiPin == enteredUpiPin) {

            ifstream DBFILE("data.txt", ios :: in);
            ofstream TempFile("temp.txt", ios :: out);

            string lineToStore;

            while(--lineNumber) {
                getline(DBFILE, lineToStore);
                TempFile << lineToStore << endl;
            }

            getline(DBFILE, lineToStore);

            DBFILE.close();
            DatabaseFile.close();

            string lineToChange = "";

            lineToChange += lineToStore.substr(0, 43);

            TempFile << lineToChange << ";";

            int j = 44;

            while(lineToStore[j] != ';') {
                TempFile << lineToStore[j];
                j++;
            }
            
            TempFile << ";";

            j++;

            while(lineToStore[j] != ';') {
                TempFile << lineToStore[j];
                j++;
            }

            TempFile << ";";
            j++;

            string currentAmount = "";

            while(j != lineToStore.length()) {
                currentAmount += lineToStore[j];
                j++;
            }

            int newAmount = stoi(currentAmount) - amount;

            TempFile << newAmount << endl;

            ifstream DataFile("data.txt", ios :: in);

            lineNumber = 0;

            while(getline(DataFile, inpLine)) {
                string subStr = inpLine.substr(13, 12);
                if(c.decryptText(subStr) == accountNumber) {
                    break;
                }
            }

            while(getline(DataFile, inpLine)) {
                TempFile << inpLine << endl;
            }

            DataFile.close();
            TempFile.close();

            remove("data.txt");
            rename("temp.txt", "data.txt");

            cout<<"\nTransaction Successful!!"<<endl;
            cout<<"\nYour current balance is -> "<<getCurrentBalance(accountNumber)<<endl;

        }

        else {
            cout<<"\nIncorrect Credentials!!"<<endl;
            return;
        }
        
    }
    
    else {
        cout<<"\nNot enough money to withdraw!!"<<endl;
        cout<<"\nYour current balance is -> "<<getCurrentBalance(accountNumber)<<endl;
    }
}

void deleteAccount(const string aadharNumber) {

    ifstream ReadFile("data.txt", ios :: in);
    ofstream WriteFile("temp.txt", ios :: out);

    bool numberReached = false;
    string checkingLine, checkingNumber;
    Crypt c;

    while(getline(ReadFile, checkingLine)) {

        checkingNumber = checkingLine.substr(0, 12);
        checkingNumber = c.decryptText(checkingNumber);

        if(checkingNumber != aadharNumber) 
            WriteFile << checkingLine << endl;
        else
            break;
    } 

    while(getline(ReadFile, checkingLine))
        WriteFile << checkingLine << endl;
    
    cout<<"\nAccount successfully deleted from the database!!"<<endl;

    ReadFile.close();
    WriteFile.close();

    remove("data.txt");
    rename("temp.txt", "data.txt");
    
}

// main function
int main() {

    string adminPassword;
    Crypt c;
    bool passValid = false;
    int numberOfTries = 1;

    restartPoint:

    system("cls");

    if(!fileExists("shadow.txt")) {

        Here:

        ofstream PasswordFile("shadow.txt", ios :: out);

        cout<<"Please set a password that contains the following:"<<endl;
        cout<<"-> at least 5 alphabets,"<<endl;
        cout<<"-> at least 3 digits,"<<endl;
        cout<<"-> at least 2 special characters."<<endl;
        cout<<"\nEnter the password -> ";
        
        getline(cin, adminPassword);

        if(isPasswordValid(adminPassword)) {
            string password = c.encryptText(adminPassword);

            PasswordFile << password;

            cout<<"\nPassword Registered Successfully!!"<<endl;

            system("pause");
            PasswordFile.close();
            exit(0);
        }
        else {
            system("cls");
            cout<<"\nTry again with a stronger password...\n\n";
            goto Here;
        }
    }
    else {

        ifstream PassFile("shadow.txt", ios :: in);
        string checkPasswordExists;

        getline(PassFile, checkPasswordExists);

        PassFile.close();

        checkPasswordExists = c.decryptText(checkPasswordExists);

        if(!isPasswordValid(checkPasswordExists)) {

            remove("shadow.txt");
            goto restartPoint;
            
        }

        ifstream PasswordFile("shadow.txt", ios :: in);
        
        string adminPassword, enteredPassword;

        getline(PasswordFile, adminPassword);

        PasswordFile.close();

        system("cls");

        jumpHereForAnotherTry:

        cout<<"\nEnter the admin password to access the software -> ";
        cin>>enteredPassword;

        if(enteredPassword == c.decryptText(adminPassword)) {
            passValid = true;
        }
        else {
            system("cls");
            
            if(numberOfTries < 3) {
                numberOfTries++;
                cout<<"\nTry again..."<<endl;
                cout<<4-numberOfTries<<" tries left!!"<<endl;
                goto jumpHereForAnotherTry;
            }
            else if(numberOfTries == 3) {
                cout<<"\nOut of tries!!"<<endl<<endl;
                system("pause");
                return 0;
            }

        }
    }

    if(passValid) {
        bool check_termination = false;

        while(true) {

        system("cls");

        cout<<"------ Welcome ------"<<endl;

        cout<<"\n1. Create a new account"<<endl;
        cout<<"2. Check balance of an account"<<endl;
        cout<<"3. Get to know a registered account's number"<<endl;
        cout<<"4. Deposit money into an account"<<endl;
        cout<<"5. Withdraw money from an account"<<endl;
        cout<<"6. Delete an account"<<endl;
        cout<<"0. Exit"<<endl;

        cout<<"\nEnter your choice -> ";
        int choice;
        cin>>choice;

        switch (choice)
        {
        case 0:
            return 0;
        
        case 1:
            {
                createNewAccount();
                break;
            }

        case 2:
            {
                system("cls");
                cout<<"Enter the account number -> ";
                string accountNumber;
                cin.ignore();
                getline(cin, accountNumber);
                cout<<getCurrentBalance(accountNumber)<<endl;
                break;
            }

        case 3:
            {
                system("cls");
                cout<<"Enter the aadhar number -> ";
                string aadharNumber;
                cin.ignore();
                getline(cin, aadharNumber);
                cout<<getAccountNumber(aadharNumber)<<endl;
                break;
            }

        case 4:
            {
                system("cls");
                cout<<"Enter the account number -> ";
                string accountNumber;
                cin.ignore();
                getline(cin, accountNumber);
                depositMoney(accountNumber);
                break;
            }

        case 5:
            {
                system("cls");
                cout<<"Enter the account number -> ";
                string accountNumber;
                cin.ignore();
                getline(cin, accountNumber);
                withdrawMoney(accountNumber);
                break;
            }
        
        case 6:
            {
                system("cls");
                cout<<"Enter the aadhar number of the account -> ";
                string aadharNumber;
                cin>>aadharNumber;
                if(!aadharNumberExists(aadharNumber)) {
                    cout<<"\nAadhar number -> "<<aadharNumber<<" is not linked with any account!!"<<endl;
                    break;
                }
                deleteAccount(aadharNumber);
                break;
            }
        
        default:
            break;
        }

        cout<<"\nDo you want to continue? Enter yes or no -> ";
        string termination_string;
        cin>>termination_string;

        (termination_string == "y" || termination_string == "yes" || termination_string == "Yes"
            || termination_string == "YES") ? check_termination = true : check_termination = false;

        if(!check_termination) break; 
        
    }

    return 0;
    }
    
}