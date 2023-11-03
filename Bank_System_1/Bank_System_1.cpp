#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <iomanip>

using namespace std;

const string fileName = "Client.txt";

struct strClientInfo
{

	string AccountNumber;
	string PinCode;
	string ClientName;
	string PhoneNumber;
	double AccountBalance;
	bool DeleteData = false;
};

strClientInfo EnterClientInfo() {
	strClientInfo ClientInfo;

	cout << "Enter Account Number: ";
	//getline(cin, ClientInfo.AccountNumber);
	cin >> ClientInfo.AccountNumber;

	cout << "Enter Pin Code: ";
	cin >> ClientInfo.PinCode;

	cout << "Enter Client Name: ";
	getline(cin >> ws, ClientInfo.ClientName);

	cout << "Enter Phone Number: ";
	cin >> ClientInfo.PhoneNumber;

	cout << "Enter Account Balance: ";
	cin >> ClientInfo.AccountBalance;

	return ClientInfo;
}

vector <string> SplitString(string Word, string Separator = "#//#") {

	short Pos = 0;
	string sWord;
	vector <string> SaveSplitWord;

	while ((Pos = Word.find(Separator)) != string::npos) {

		sWord = Word.substr(0, Pos);

		if (sWord != "") {
			SaveSplitWord.push_back(sWord);
		}

		Word.erase(0, Pos + Separator.length());
	}

	if (Word != "") {
		SaveSplitWord.push_back(Word);
	}
	return SaveSplitWord;
}

string ConvertRecordToOneLine(strClientInfo ClientInfo, string Separator = "#//#") {
	string Line;

	Line += ClientInfo.AccountNumber + Separator;
	Line += ClientInfo.PinCode + Separator;
	Line += ClientInfo.ClientName + Separator;
	Line += ClientInfo.PhoneNumber + Separator;
	Line += to_string(ClientInfo.AccountBalance);

	return Line;
}

strClientInfo ConvertVectorToString(string LineData) {

	strClientInfo ClientInfo;

	vector <string> SaveClientData;
	SaveClientData = SplitString(LineData);

	ClientInfo.AccountNumber = SaveClientData[0];
	ClientInfo.PinCode = SaveClientData[1];
	ClientInfo.ClientName = SaveClientData[2];
	ClientInfo.PhoneNumber = SaveClientData[3];
	ClientInfo.AccountBalance = stod(SaveClientData[4]);

	return ClientInfo;
}

void PrintHeaderClintData(vector <strClientInfo> vClientData) {

	cout << "\t\t\t\tClient List (" << vClientData.size() << ") Client(s).\n";
	cout << "__________________________________________________________________________________________________________________\n";
	cout << "|  " << left << setw(15) << "Account Number";
	cout << "|  " << left << setw(10) << "Pin Code";
	cout << "|  " << left << setw(45) << "Client Name";
	cout << "|  " << left << setw(12) << "Phone Number";
	cout << "|  " << left << setw(12) << "Account Balance";
	cout << "\n__________________________________________________________________________________________________________________\n";
}

vector <strClientInfo> ShowDataOnFile(string fileName) {

	fstream MyFile;
	string Data;
	strClientInfo Line;
	vector <strClientInfo> SaveClientData;
	short Counter = 0;

	MyFile.open(fileName, ios::in);

	if (MyFile.is_open()) {

		while (getline(MyFile, Data)) {

			Line = ConvertVectorToString(Data);

			SaveClientData.push_back(Line);


		}
		MyFile.close();
	}

	return SaveClientData;
}

void PrintAllClientData() {

	vector <strClientInfo> vClientData;
	vClientData = ShowDataOnFile(fileName);

	PrintHeaderClintData(vClientData);

	for (strClientInfo& Client : vClientData) {
		cout << "|  " << left << setw(15) << Client.AccountNumber;
		cout << "|  " << left << setw(10) << Client.PinCode;
		cout << "|  " << left << setw(45) << Client.ClientName;
		cout << "|  " << left << setw(12) << Client.PhoneNumber;
		cout << "|  " << left << setw(12) << Client.AccountBalance;
		cout << endl;
	}
	cout << "\n__________________________________________________________________________________________________________________\n";
	cout << "\nPress any key to go back to Main Menu..." << endl;
	system("pause > 0");
}

// ADD DATA

string AddHeaderClient() {

	string AccountNumber;
	vector <strClientInfo> ifSameAccountNumber;

	ifSameAccountNumber = ShowDataOnFile(fileName);

	cout << "\n------------------------------\n";
	cout << "\tAdd New Client Screen\n";
	cout << "------------------------------\n";
	cout << "Adding New Clients:\n\n";
	cout << "Enter Account Number: ";
	cin >> AccountNumber;

	for (strClientInfo& ClientAccountNumber : ifSameAccountNumber) {
		while (ClientAccountNumber.AccountNumber == AccountNumber) {
			cout << "Client With [" << AccountNumber << "] already exists, Enter another account number: \n";
			cin >> AccountNumber;
		}
	}
	return AccountNumber;
}

strClientInfo AddNewClientData() {

	strClientInfo ClientInfo;

	ClientInfo.AccountNumber = AddHeaderClient();

	cout << "Enter Pin Code: ";
	cin >> ClientInfo.PinCode;

	cout << "Enter Client Name: ";
	getline(cin >> ws, ClientInfo.ClientName);

	cout << "Enter Phone Number: ";
	cin >> ClientInfo.PhoneNumber;

	cout << "Enter Account Balance: ";
	cin >> ClientInfo.AccountBalance;

	return ClientInfo;
}

void AddNewClient() {

	fstream MyFile;
	strClientInfo EnterClientData;
	string Data;
	char Answer = 'n';

	MyFile.open(fileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		do {
			system("cls");
			EnterClientData = AddNewClientData();
			Data = ConvertRecordToOneLine(EnterClientData);
			MyFile << Data << endl;

			cout << "Client Addes Successfully, do you want to add more clients: Y/N?";
			cin >> Answer;

		} while (tolower(Answer) == 'y');
		MyFile.close();
	}
	cout << "\nPress any key to go back to Main Menu..." << endl;
	system("pause > 0");
}

// DELETE DATA

void printClintDataWantDelete(strClientInfo Client) {

	cout << "\n-------------------------------------------\n";
	cout << "\nAccount Number: " << Client.AccountNumber << endl;
	cout << "Pin Code: " << Client.PinCode << endl;
	cout << "Client Name: " << Client.ClientName << endl;
	cout << "Phone Number: " << Client.PhoneNumber << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
	cout << "\n-------------------------------------------\n";


}

void DeleteScreenHeader() {
	cout << "\n-----------------------------------------------\n";
	cout << "\t\tDelete Client Screen";
	cout << "\n-----------------------------------------------\n";

}

string EnterClientAccountNumber() {
	string Answer;
	cout << "Enter Client Account Number: ";
	cin >> Answer;

	return Answer;
}

bool FindClientAccountNumberIsSame(vector <strClientInfo> vAllClientData, strClientInfo& ClientAccountNumber, string AccountNumber) {



	for (strClientInfo& Data : vAllClientData) {

		if (Data.AccountNumber == AccountNumber) {

			ClientAccountNumber = Data;
			return true;

		}
	}
	return false;
}

char AnswerForDelete() {
	char A;
	cout << "Are you sure want delete this client: y/n?";
	cin >> A;
	return A;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <strClientInfo>& vAllClientData) {

	for (strClientInfo& Data : vAllClientData) {

		if (Data.AccountNumber == AccountNumber) {
			Data.DeleteData = true;
			return true;
		}

	}

}

vector <strClientInfo> SaveClientFileAreDeleted(string fileName, vector <strClientInfo> vAllClientData) {

	fstream MyFile;
	string Line;

	MyFile.open(fileName, ios::out);

	if (MyFile.is_open()) {

		for (strClientInfo& Client : vAllClientData) {

			if (Client.DeleteData == false) {
				Line = ConvertRecordToOneLine(Client);
				MyFile << Line << endl;
			}

		}
		MyFile.close();
	}
	return vAllClientData;
}

bool DeleteClintData() {

	system("cls");
	vector <strClientInfo> vAllClientData;
	vAllClientData = ShowDataOnFile(fileName);
	strClientInfo ClientAccountNumber;
	char MyAnswer;

	DeleteScreenHeader();
	string AccountNumber = EnterClientAccountNumber();

	if (FindClientAccountNumberIsSame(vAllClientData, ClientAccountNumber, AccountNumber)) {

		printClintDataWantDelete(ClientAccountNumber);

		MyAnswer = AnswerForDelete();
		if (tolower(MyAnswer) == 'y') {
			MarkClientForDeleteByAccountNumber(AccountNumber, vAllClientData);

			SaveClientFileAreDeleted(fileName, vAllClientData);
			vAllClientData = SaveClientFileAreDeleted(fileName, vAllClientData);

			cout << "\nClient Deleted Successfully.\n";
		}
		cout << "\nPress any key to go back to Main Menu..." << endl;
		system("pause > 0");
		return true;

	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		system("pause > 0");
		return false;
	}

}

//UpdateClientData

void PrintUpdateHeader() {
	cout << "\n-----------------------------------------------\n";
	cout << "\t\"Update Client Screen";
	cout << "\n-----------------------------------------------\n";
}

char AnswerForUpdate() {
	char A;
	cout << "Are you sure want update this client: y/n?";
	cin >> A;
	return A;
}

strClientInfo UpdateClientData(string AccountNumber) {

	strClientInfo ClientInfo;

	ClientInfo.AccountNumber = AccountNumber;
	cout << "\nEnter Pin Code: ";
	cin >> ClientInfo.PinCode;

	cout << "Enter Client Name: ";
	getline(cin >> ws, ClientInfo.ClientName);

	cout << "Enter Phone Number: ";
	cin >> ClientInfo.PhoneNumber;

	cout << "Enter Account Balance: ";
	cin >> ClientInfo.AccountBalance;

	return ClientInfo;
}

vector <strClientInfo> SaveClientFileToUpdate(string fileName, vector <strClientInfo> vAllClientData) {

	fstream MyFile;
	string Line;
	MyFile.open(fileName, ios::out);

	if (MyFile.is_open()) {

		for (strClientInfo& Data : vAllClientData) {

			if (Data.DeleteData == false) {

				Line = ConvertRecordToOneLine(Data);

				MyFile << Line << endl;

			}

		}
		MyFile.close();

	}
	return vAllClientData;
}

void UpdateClientData() {

	system("cls");
	PrintUpdateHeader();

	string EnterData = EnterClientAccountNumber();
	vector <strClientInfo> vAllClientData;
	vAllClientData = ShowDataOnFile(fileName);
	strClientInfo strClient;
	char Answer;

	if (FindClientAccountNumberIsSame(vAllClientData, strClient, EnterData)) {
		printClintDataWantDelete(strClient);

		Answer = AnswerForUpdate();

		if (toupper(Answer) == 'Y') {

			for (strClientInfo& Client : vAllClientData) {

				if (Client.AccountNumber == EnterData) {

					Client = UpdateClientData(EnterData);
					break;
				}

			}
			SaveClientFileToUpdate(fileName, vAllClientData);
			cout << "\nClient Updated Successfully." << endl;
		}

	}
	else {
		cout << "\nClient with Account Number (" << EnterData << ") is Not Found!";
		system("pause > 0");

	}
	cout << "\nPress any key to go back to Main Menu..." << endl;
	system("pause > 0");

}

//Find Client Data

void PrintClientDataHeaderToFindData() {

	cout << "\n-----------------------------------------------\n";
	cout << "\t\tFind Client Screen";
	cout << "\n-----------------------------------------------\n";

}

bool FindClinetData() {
	system("cls");

	PrintClientDataHeaderToFindData();
	vector <strClientInfo> FindClient;
	FindClient = ShowDataOnFile(fileName);

	string AccountNumber = EnterClientAccountNumber();

	for (strClientInfo& Client : FindClient) {

		if (Client.AccountNumber == AccountNumber) {
			printClintDataWantDelete(Client);
			cout << "\nPress any key to go back to Main Menu..." << endl;
			system("pause > 0");
			return true;
		}

	}

	cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";

	cout << "\nPress any key to go back to Main Menu..." << endl;
	system("pause > 0");
	return false;

}

void ExitFromProgram() {
	system("cls");
	cout << "\n-----------------------------------------------\n";
	cout << "\t\tProgram Ends :-)";
	cout << "\n-----------------------------------------------\n";
	cout << "\nPress any key to go back to Main Menu..." << endl;
	system("pause > 0");
}

void MainMenu() {

	cout << "==================================================================\n";
	cout << "\t\t\t" << "Main Menu Screen\n";
	cout << "==================================================================\n";
	cout << "\t\t[1]Show Client List.\n";
	cout << "\t\t[2]Add New Client.\n";
	cout << "\t\t[3]Delete Client.\n";
	cout << "\t\t[4]Update Client Info.\n";
	cout << "\t\t[5]Find Client.\n";
	cout << "\t\t[6]Exit.\n";
	cout << "==================================================================\n";


}

void MainScreen() {
	system("cls");
	MainMenu();

	short Number;
	cout << "Choose what do you want to do? [1 to 6]? " << endl;
	cin >> Number;

	switch (Number) {

	case 1:
		system("cls");
		PrintAllClientData();
		MainScreen();
		break;

	case 2:
		AddNewClient();
		MainScreen();
		break;

	case 3:
		DeleteClintData();
		MainScreen();
		break;

	case 4:
		UpdateClientData();
		MainScreen();
		break;

	case 5:
		FindClinetData();
		MainScreen();
		break;
	case 6:
		ExitFromProgram();
		break;
	default:
		MainScreen();

	}

}

int main() {

	MainScreen();

	system("pause > 0");
	return 0;
}