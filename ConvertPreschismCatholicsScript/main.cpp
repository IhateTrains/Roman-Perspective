#include <stdio.h>  /* defines FILENAME_MAX */
#define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>

#include <windows.h> /// for DWORD

#include <conio.h>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <regex>

using namespace std;

const string OperatorsAndBrackets = "><={}";
bool ExcludeCommentedLines = true;

string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}

bool ToBool (string value)
{
    if(value == "1") return true;
    return false;
}

void Menu (void)
{
    cout << "============================================================" << endl;
    cout << " This script converts pre-schism Catholics to Orthodoxy" << endl;
    cout << "============================================================" << endl;
    cout << "C - initiate new conversion"<<endl;
    cout << "ESC - exit"<<endl;
    cout << "============================================================"<<endl;
    cout<<endl;
}

void ConvertFile ()
{
    ifstream File;
    ofstream ConvertedFile;
    string FileDirectory;
    string SingleLine = "";

    int CatholicYear;
    int CatholicMonth;
    int CatholicDay;

    int YearInCurrentBlock;
    int MonthInCurrentBlock;
    int DayInCurrentBlock;

    string tekst;
    smatch wynik;
    regex wzorzec("\\d*.\\d*.\\d*");

    cout<<"Specify the file directory (example: C:\\MyMod\\events\\MyEvent.txt): ";
    getline(cin, FileDirectory);
    string ConvertedFileDirectory = GetCurrentWorkingDir()+"\\FILEBEINGCLEANEDBYILIKETRAINS.txt"; /// lul name but at least almost ensures no such file exists already (yeah too lazy to add proper safety checks...)
    File.open(FileDirectory.c_str());
    ConvertedFile.open(ConvertedFileDirectory.c_str());

    if (File.good())
    {

                            while(getline(File, SingleLine))
                            {
                                if (SingleLine.find("#")) SingleLine = SingleLine.substr(0, SingleLine.find("#"));

                                if (regex_search(tekst, wynik, wzorzec) ) cout<<"Jakaœ data znaleziona"<<endl;


                                ConvertedFile<<SingleLine;
                                cout<<wynik[0]; ///test

                                if (!File.eof()) ConvertedFile<<endl;

                            }

                        cout<<"Conversion finished."<<endl;



        File.close();
        ConvertedFile.close();

        remove( FileDirectory.c_str() ); /// removes the old version of the file

        if (!MoveFile(ConvertedFileDirectory.c_str(), FileDirectory.c_str())) /// move the cleaned version in place of the old one
        {
            cout << "File moving failed." << endl;
            system("pause");
        }
        else {
            cout << "File saved." << endl<<endl;
        }
    }
    else
    {
        cout<<"Specified file couldn't be opened."<<endl<<endl;
    }
    Menu();
}

int main()
{
    char d;

    GetCurrentWorkingDir();
    Menu();

    do
    {
        cin.clear();
        cin.sync();
        d = toupper(getch());

        switch(d)
        {
            case 'C': ConvertFile(); break;
            case 27: cout<<"Closing the program..."<<endl; break;
            default: cout<<"You pressed a wrong key."<<endl;
        }
    }
    while (d!=char(27));

    return 0;
}
