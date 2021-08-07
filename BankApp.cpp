// Banking-Management-System

#include<bits/stdc++.h>

using namespace std;

class Crypt {

    public:

    // Encryption algorithm for encrypting aadhar number
    string encryptText(string textString) {

        string encryptedString = "";
        int i = 0;

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

        string decryptedString = "";
        int i = 0;

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

// Check whether the given file exists
bool fileExists(string &name) {
    ifstream File(name.c_str());
    return File.good();    
}

 bool idExists(string Id) {

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

        for(int i = 0; i < inpLine.length()/2; i++) {
            swap(inpLine[i], inpLine[inpLine.length() - i - 1]);
        }

        for(int i = 0; i < 12; i++) {
            tempString += inpLine[i];
        }

        for(int i = 0; i < tempString.length()/2; i++) {
            swap(tempString[i], tempString[tempString.length() - i - 1]);
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

        for(int i = 0; i < inpLine.length()/2; i++) {
            swap(inpLine[i], inpLine[inpLine.length() - i - 1]);
        }

        for(int i = 13; i < 23; i++) {
            tempString += inpLine[i];
        }

        for(int i = 0; i < tempString.length()/2; i++) {
            swap(tempString[i], tempString[tempString.length() - i - 1]);
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
    else if(!idExists(aadharNumber)) {

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

        string accountNumber = generateAccountNumber();

        WriteFile << c.encryptText(aadharNumber) << ";" << name << ";" << surname << ";" << c.encryptText(phoneNumber) << ";" << c.encryptText(accountNumber) << ";";

        cout<<"\nNew Account Successfully created!!"<<endl;
        cout<<"\nYour account number is -> "<<accountNumber<<endl<<endl;

        system("pause");

        system("cls");

        cout<<"\n--- Set UPI pin for your account ---"<<endl;
        cout<<"\n(Pin must contain all 6 digits)"<<endl;
        cout<<"\nEnter the pin -> ";
        string UpiId;
        cin>>UpiId;

        while(UpiId.length() != 6) {
            cout<<"\nEnter the pin properly as mentioned -> ";
            cin>>UpiId;
        }

        WriteFile << c.encryptText(UpiId) << endl;
    }
    else {
        cout<<"\nYou already have an account in our bank!!"<<endl;
        return;
    }
}


// main function
int main() {

    bool check_termination = false;

    while(true) {

        system("cls");

        cout<<"------ Welcome ------"<<endl;

        cout<<"\n1. Create a new account"<<endl;
        cout<<"0. Exit"<<endl;

        cout<<"\nEnter your choice -> ";
        int choice;
        cin>>choice;

        switch (choice)
        {
        case 0:
            break;
        
        case 1:
            {
                createNewAccount();
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
