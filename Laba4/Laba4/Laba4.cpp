#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int RollDice(string diceInfo)
{
    int repeatTime;
    int cubeValue;

    int randomCubeValue;
    int deleteSymbNumber;

    int sumCubesValue = 0;

    while (diceInfo.find_first_of("d") <= diceInfo.length())
    {
        deleteSymbNumber = 3;

        repeatTime = diceInfo[diceInfo.find("d") - 1] - '0';
        cubeValue = diceInfo[diceInfo.find("d") + 1] - '0';

        if ((int)diceInfo[diceInfo.find("d") + 2] > 47 && (int)diceInfo[diceInfo.find("d") + 2] < 58)
        {
            cubeValue = cubeValue * 10 + (diceInfo[diceInfo.find("d") + 2] - '0');
            deleteSymbNumber += 1;
        }

        for (int i = 0; i < repeatTime; i++)
        {
            randomCubeValue = rand() % cubeValue + 1;
            sumCubesValue += randomCubeValue;
            //cout << randomCubeValue << "\n";
        }

        //cout << "\n";

        diceInfo.replace(diceInfo.find("d") - 1, deleteSymbNumber, "");
    }

    while (diceInfo.find_first_of("+") <= diceInfo.length() || diceInfo.find_first_of("-") <= diceInfo.length() ||
        diceInfo.find_first_of("*") <= diceInfo.length() || diceInfo.find_first_of("/") <= diceInfo.length())
    {
        deleteSymbNumber = 2;

        int symbPos = diceInfo.find_first_of("+");
        if (symbPos <= diceInfo.length())
        {
            int tempValue = diceInfo[symbPos + 1] - '0';
            if ((int)diceInfo[symbPos + 2] > 47 && (int)diceInfo[symbPos + 2] < 58)
            {
                tempValue = tempValue * 10 + diceInfo[symbPos + 2] - '0';
                deleteSymbNumber += 1;
            }

            sumCubesValue += tempValue;
            diceInfo.replace(symbPos, deleteSymbNumber, "");
            deleteSymbNumber = 2;
        }

        symbPos = diceInfo.find_first_of("-");
        if (symbPos <= diceInfo.length())
        {
            int tempValue = diceInfo[symbPos + 1] - '0';
            if ((int)diceInfo[symbPos + 2] > 47 && (int)diceInfo[symbPos + 2] < 58)
            {
                tempValue = tempValue * 10 + diceInfo[symbPos + 2] - '0';
                deleteSymbNumber += 1;
            }

            sumCubesValue -= tempValue;
            diceInfo.replace(symbPos, deleteSymbNumber, "");
            deleteSymbNumber = 2;
        }

        symbPos = diceInfo.find_first_of("*");
        if (symbPos <= diceInfo.length())
        {
            int tempValue = diceInfo[symbPos + 1] - '0';
            if ((int)diceInfo[symbPos + 2] > 47 && (int)diceInfo[symbPos + 2] < 58)
            {
                tempValue = tempValue * 10 + diceInfo[symbPos + 2] - '0';
                deleteSymbNumber += 1;
            }

            sumCubesValue *= tempValue;
            diceInfo.replace(symbPos, deleteSymbNumber, "");
            deleteSymbNumber = 2;
        }

        symbPos = diceInfo.find_first_of("/");
        if (symbPos <= diceInfo.length())
        {
            int tempValue = diceInfo[symbPos + 1] - '0';
            if ((int)diceInfo[symbPos + 2] > 47 && (int)diceInfo[symbPos + 2] < 58)
            {
                tempValue = tempValue * 10 + diceInfo[symbPos + 2] - '0';
                deleteSymbNumber += 1;
            }

            sumCubesValue /= tempValue;
            diceInfo.replace(symbPos, deleteSymbNumber, "");
            deleteSymbNumber = 2;
        }
    }

    return sumCubesValue;
}

void TestDice(string dice, int repeatTime)
{
    ofstream f(dice + ".txt");

    for (int i = 0; i < repeatTime; i++)
    {
        f << RollDice(dice) << "\n";
    }

    f.close();
}


int main()
{
    srand(time(nullptr));

    string diceInfo = "2d6";
    string _1d6 = "1d6";
    string _2d6 = "2d6";
    string _3d6 = "3d6";
    string _1d10 = "1d10";
    string _2d10 = "2d10";
    string _3d10 = "3d10";

    TestDice(_1d6, 100000);
    TestDice(_2d6, 100000);
    TestDice(_3d6, 100000);
    TestDice(_1d10,100000);
    TestDice(_2d10, 100000);
    TestDice(_3d10, 100000);
    
    cout << "\n" << RollDice(diceInfo) << "\nHello World!\n";
}