
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;
string stitch;

void Stitcher(int rst, int mode, string DT, string DDC, string CT, string CDC)
{
    stitch = std::to_string(rst) + std::to_string(mode) + DT + DDC + CT + CDC;

    cout << "String = " << stitch << endl;

}

string message()
{
    return stitch;
}

int main()
{
    int    reset = 0, modeFlag = 0;
    int    modeSTATE, dogtimerFlag;
    char   mode, resetHolder;

    string timeInterval_dog, dutyCycle_dog,
           timeInterval_cat, dutyCycle_cat,
           stitch, DogTimer;

    ostringstream timeInterval_dog_String, dutyCycle_dog_String,
                  timeInterval_cat_String, dutyCycle_cat_String;
    while (1)
    {
        modeSTATE = 0;
        reset = 0;
       
        while (modeSTATE != 1)
        {
         
            cout << "-----------------------------------------------------------------" << endl;
            cout << "                WELCOME TO THE FOOD DISPENSER                    " << endl;
            cout << "        Enter feeding mode : (a = Automatic, m = manual)         " << endl;
            cin >> mode;

            switch (mode)
            {
            case 'a':
            {
                cout << "-----------------------------------------------------------------" << endl;
                cout << "You are now in Automatic mode" << endl;
                cout << "-----------------------------------------------------------------" << endl;
                cout << "Enter feeding time interval for DOG (0 - 999) minute(s):" << endl;

                cin >> timeInterval_dog;

                timeInterval_dog_String.str("");
                timeInterval_dog_String << setfill('0') << setw(3) << timeInterval_dog;
                DogTimer = timeInterval_dog_String.str();

                cout << "DT value: " << DogTimer << endl;

                if(DogTimer.size() == 3)
                {
                    
                    cout << "-----------------------------------------------------------------" << endl;
                    cout << "Enter amount of DOG food released (0 - 99) %:" << endl;

                    cin >> dutyCycle_dog;

                    dutyCycle_dog_String.str("");
                    dutyCycle_dog_String << setfill('0') << setw(2) << dutyCycle_dog;
                    std::string DogDutyCycle = dutyCycle_dog_String.str();

                    if (DogDutyCycle.size() == 2)
                    {
                        cout << "-----------------------------------------------------------------" << endl;
                        cout << dutyCycle_dog << "% of the DOG food will be released every " << timeInterval_dog << " minute(s)." << endl;
                        cout << "-----------------------------------------------------------------" << endl;

                        cout << "Enter feeding time interval for CAT (0 - 999) minute(s):" << endl;

                        cin >> timeInterval_cat;

                        timeInterval_cat_String.str("");
                        timeInterval_cat_String << setfill('0') << setw(3) << timeInterval_cat;
                        std::string CatTimer = timeInterval_cat_String.str();

                        if (CatTimer.size() == 3)
                        {

                            cout << "-----------------------------------------------------------------" << endl;
                            cout << "Enter amount of CAT food released (1 - 99) %:" << endl;

                            cin >> dutyCycle_cat;

                            dutyCycle_cat_String.str("");
                            dutyCycle_cat_String << setfill('0') << setw(2) << dutyCycle_cat;
                            std::string CatDutyCycle = dutyCycle_cat_String.str();

                            if (CatDutyCycle.size() == 2)
                            {
                                cout << "-----------------------------------------------------------------" << endl;
                                cout << dutyCycle_cat << "% of the CAT food will be released every " << timeInterval_cat << " minute(s)." << endl;
                                cout << "-----------------------------------------------------------------" << endl;

                                cout << "PRESS r TO RETURN TO MODE MENU." << endl;
                                cout << "-----------------------------------------------------------------" << endl;

                                dogtimerFlag = 1;
                                modeFlag = 1;
                                reset = 0;

                                Stitcher(reset, modeFlag, DogTimer, DogDutyCycle, CatTimer, CatDutyCycle);

                                cout << "modeState = " << modeSTATE << endl;

                                cin >> resetHolder;

                                if (resetHolder == 'r')
                                {
                                    resetHolder = '0';
                                    reset = 1;
                                    modeFlag = 0;

                                    DogTimer.clear();
                                    DogDutyCycle.clear();
                                    CatTimer.clear();
                                    CatDutyCycle.clear();

                                    DogTimer = "000";
                                    DogDutyCycle = "00";
                                    CatTimer = "000";
                                    CatDutyCycle = "00";

                                    stitch = std::to_string(reset) + std::to_string(modeFlag) + DogTimer + DogDutyCycle + CatTimer + CatDutyCycle;
                                    cout << "String = " << stitch;

                                    modeSTATE = 1;

                                    cout << endl << "modeState = " << modeSTATE << endl;
                                }
                            }
                            else
                            {
                                cout << endl << "Value Limit has been exceeded, returning to main menu..." << endl;
                            }
                        }
                        else
                        {
                            cout << endl << "Value Limit has been exceeded, returning to main menu..." << endl;
                        }
                    }
                    else
                    {
                        cout << endl << "Value Limit has been exceeded, returning to main menu..." << endl;
                    }
                }
                else
                {
                    cout << endl << "Value Limit has been exceeded, returning to main menu..." << endl;
                    
                    modeSTATE = 1;
                    
                }

                break;
            }
            case 'm':
            {

                cout << "-----------------------------------------------------------------" << endl;
                cout << "Manual Mode" << endl;
                cout << "-----------------------------------------------------------------" << endl;
                cout << "PRESS r TO RETURN TO MODE MENU." << endl;
                cout << "-----------------------------------------------------------------" << endl;

                reset = 0;

                cin >> resetHolder;

                if (resetHolder == 'r')
                {
                    resetHolder = '0';
                    modeSTATE = 1;
                }

                break;
            }
            default:
            {
                    cout << endl << "Incorrect key entered, returning to main menu..." << endl; 
                    modeSTATE = 1;
                break;
            }
            }
        }
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
