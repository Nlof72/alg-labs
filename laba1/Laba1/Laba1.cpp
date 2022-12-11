#include <iostream>
#include <fstream>
#include "../single_include/nlohmann/json.hpp"
#include <math.h>

using json = nlohmann::json;

struct SaveData
{
    int currentTurn;

    int citizensNumber;
    int cityAcreSize;
    float wheatBushelAmount;

    int producedWheatBushel;
    int arrivedPeopleNumber;
    int destroyedByRatsWheatBushel;
    int diedPeopleNumber;

    int wheatFromField;
    int acreCost;

    bool wasPlague;

    int sumPercentDiedPeople;

    SaveData() {
        currentTurn = 1;

        citizensNumber = 100;
        cityAcreSize = 1000;
        wheatBushelAmount = 2800;

        diedPeopleNumber = 0;
        arrivedPeopleNumber = 0;
        producedWheatBushel = 0;
        destroyedByRatsWheatBushel = 0;

        wheatFromField = 0;
        acreCost = 0;

        sumPercentDiedPeople = 0;

        wasPlague = false;
    }

    void FillData(int turn, int citizens, int citySize, float wheatBushel, int diedPeople, 
        int arrivePeople, int produedWheatBush, int destroyedByRats, int wFromField, int aCost, int sumDiedPeoplePercent,bool hasPlague) {

        currentTurn = turn;

        citizensNumber = citizens;
        cityAcreSize = citySize;
        wheatBushelAmount = wheatBushel;

        diedPeopleNumber = diedPeople;
        arrivedPeopleNumber = arrivePeople;
        producedWheatBushel = produedWheatBush;
        destroyedByRatsWheatBushel = destroyedByRats;

        wheatFromField = wFromField;
        acreCost = aCost;

        sumPercentDiedPeople = sumDiedPeoplePercent;

        wasPlague = hasPlague;
    }

    json GetJSONData() {
        return {
            {"currentTurn", currentTurn},

            {"citizensNumber", citizensNumber},
            {"cityAcreSize", cityAcreSize},
            {"wheatBushelAmount", wheatBushelAmount},

            {"diedPeopleNumber", diedPeopleNumber},
            {"arrivedPeopleNumber", arrivedPeopleNumber},
            {"producedWheatBushel", producedWheatBushel},
            {"destroyedByRats", destroyedByRatsWheatBushel},

            {"wheatFromField", wheatFromField},
            {"acreCost", acreCost},

            {"sumPercentDiedPeople", sumPercentDiedPeople},

            {"hasPlague", wasPlague},
        };
    }

    void ReadJsonData(json& data) {
        data.at("currentTurn").get_to(currentTurn);

        data.at("citizensNumber").get_to(citizensNumber);
        data.at("cityAcreSize").get_to(cityAcreSize);
        data.at("wheatBushelAmount").get_to(wheatBushelAmount);

        data.at("diedPeopleNumber").get_to(diedPeopleNumber);
        data.at("arrivedPeopleNumber").get_to(arrivedPeopleNumber);
        data.at("producedWheatBushel").get_to(producedWheatBushel);
        data.at("destroyedByRats").get_to(destroyedByRatsWheatBushel);

        data.at("wheatFromField").get_to(wheatFromField);
        data.at("acreCost").get_to(acreCost);

        data.at("sumPercentDiedPeople").get_to(sumPercentDiedPeople);

        data.at("hasPlague").get_to(wasPlague);
    }
};

void SaveGameData(json data) 
{
    std::ofstream saveFile("save.json");
    if (saveFile.is_open())
    {
        saveFile << data.dump(4);
    }
    saveFile.close();
}


int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    json savedData;
    bool haveSaveData = false;

    std::string ans;
    std::cout << "�� ������ ���������� ������ ����?(Y/N)";
    std::cin >> ans;

    if (ans == "y" || ans == "Y" || ans == "�" || ans == "�")
    {
        std::ifstream save("save.json");
        if (save.is_open())
        {
            savedData = json::parse(save);
            std::cout << savedData.dump(4) << "\n";
            haveSaveData = true;
        }

        save.close();
    }

    //clear Console
    std::system("cls");

    const int citizenEatNumberWheatBushel = 20;
    const int citizenHandleNumberAcre = 10;
    const float acreBushelWheatNeedForPlant = 0.5f;
    const std::string plagueTextValue = "���� ���������� �������� ���������;\n";
    std::string plagueText = "";
    
    int endTurnNumber = 10;

    SaveData currentData;

    if (haveSaveData)
    {
        currentData.ReadJsonData(savedData);
        if (currentData.wasPlague)
        {
            plagueText = plagueTextValue;
        }
    }
    else 
    {
        currentData.acreCost = rand() % 10 + 17;
    }

    //input value
    int buyAcreValue;
    int sellAcreValue;
    int eatBushelValue;
    int plantWheatValue;

    int handledAcreValue;
    int feededPeople;

    float percentDiedPeople;
    int needToFeed;

    bool isValueValid = false;

    for (int turnNumber = currentData.currentTurn; turnNumber <= endTurnNumber; turnNumber++)
    { 
        //Save in begin raund
        SaveGameData(currentData.GetJSONData());

        std::cout << "��� ����������, �������� �������� ����\n" << "� ���� " << currentData.currentTurn<< " ������ ����������� ���������\n" <<
            currentData.diedPeopleNumber << " ������� ������ � ������, � " << currentData.arrivedPeopleNumber << " ������� ������� � ��� ������� �����;\n" <<
            plagueText << "��������� ������ ������ ���������� " << currentData.citizensNumber << " �������;\n" <<
            "�� ������� " << currentData.producedWheatBushel << " ������� �������, �� " << currentData.wheatFromField << " ������ � ����;\n" <<
            "����� ��������� " << currentData.destroyedByRatsWheatBushel << " ������� �������, ������� " << currentData.wheatBushelAmount << " ������ � �������;\n" <<
            "����� ������ �������� " << currentData.cityAcreSize << " �����;\n" << "1 ��� ����� ����� ������ " << currentData.acreCost << " ������.";

        std::cout << "\n\n��� ���������, ����������?\n";

        while (!isValueValid)
        {
            std::cout << "������� ����� ����� ����������� ������?";
            std::cin >> buyAcreValue;
            std::cout << "������� ����� ����� ����������� �������?";
            std::cin >> sellAcreValue;
            std::cout << "������� ������� ������� ����������� ������?";
            std::cin >> eatBushelValue;
            std::cout << "������� ����� ����� ����������� �������?";
            std::cin >> plantWheatValue;
            if (currentData.wheatBushelAmount - (buyAcreValue * currentData.acreCost) +
                (sellAcreValue * currentData.acreCost) - eatBushelValue - plantWheatValue * 0.5 < 0)
            {
                isValueValid = false;
                std::cout << "�, ����������, ������ ���! � ��� ������ " << currentData.citizensNumber
                    << " �������, " << currentData.wheatBushelAmount << " ������� ������� � " <<
                    currentData.cityAcreSize << " ����� �����!\n";
            }
            else
            {
                if (buyAcreValue < 0 || sellAcreValue < 0 || eatBushelValue < 0 || plantWheatValue < 0)
                {
                    std::cout << "�, ����������, ������ ���� �� ����������!\n�� �� �������� ��� ��������" << buyAcreValue
                        << " ����� ��� �������, " << sellAcreValue << " ����� ��� �������,\n" <<
                        eatBushelValue << " ������� ����� ��� ���, " << plantWheatValue
                        << " ����� ����� ��� �������,\n�� ����������� �������, ������������� �����, �������� ������ ���� >= 0\n";
                    isValueValid = false;
                }
                else
                {
                    isValueValid = true;
                }
            }
        }
        std::cout << "\n";

        currentData.acreCost = rand() % 10 + 17;
        currentData.wheatFromField = rand() % 6 + 1;

        currentData.arrivedPeopleNumber = 0;
        isValueValid = false;
        percentDiedPeople = 0;
        plagueText = "";
        needToFeed = currentData.citizensNumber * citizenEatNumberWheatBushel;

        //Buy Acre
        currentData.cityAcreSize += buyAcreValue;
        currentData.wheatBushelAmount -= buyAcreValue * currentData.acreCost;

        //Sell Acre
        currentData.cityAcreSize -= sellAcreValue;
        currentData.wheatBushelAmount += sellAcreValue * currentData.acreCost;

        //plant fields
        currentData.wheatBushelAmount -= plantWheatValue * 0.5;


        //feed people
        currentData.wheatBushelAmount -= eatBushelValue;
        if (eatBushelValue < needToFeed)
        {
            //calc dead people percent
            feededPeople = (int)floor(eatBushelValue / 20.0);
            
            currentData.diedPeopleNumber = currentData.citizensNumber - feededPeople;

            percentDiedPeople = 100 - (100.0 * feededPeople) / (float)currentData.citizensNumber;
            //cout << percentDiedPeople << "-------";

            currentData.sumPercentDiedPeople += percentDiedPeople;

            currentData.citizensNumber = feededPeople;

            if (percentDiedPeople >= 45)
            {
                std::cout << "\n������� ������� ����� �������\n";
                return 0;
            }
        }

        //Harvest wheat
        if (currentData.citizensNumber * citizenHandleNumberAcre >= plantWheatValue)
        {
            handledAcreValue = plantWheatValue;
        }
        else
        {
            handledAcreValue = currentData.citizensNumber * citizenHandleNumberAcre;
        }

        currentData.producedWheatBushel = currentData.wheatFromField * handledAcreValue;
        currentData.wheatBushelAmount += currentData.producedWheatBushel;

        //Calc rats value
        currentData.destroyedByRatsWheatBushel = rand() % (int)ceil(0.07 * currentData.wheatBushelAmount);
        currentData.wheatBushelAmount -= currentData.destroyedByRatsWheatBushel;

        //Check on Plague
        if ((rand() % 100) <= 15)
        {
            currentData.citizensNumber = (int)(floor(currentData.citizensNumber / 2.0));
            plagueText = plagueTextValue;
        }

        //calc arrivedPeople
        currentData.arrivedPeopleNumber = (int)floor(currentData.diedPeopleNumber / 2.0) +
            ((5 - currentData.wheatFromField) * currentData.wheatBushelAmount) / 600 + 1;

        //std::cout << currentData.arrivedPeopleNumber << "------";

        if (currentData.arrivedPeopleNumber < 0)
        {
            currentData.arrivedPeopleNumber = 0;
        }
        if (currentData.arrivedPeopleNumber > 50)
        {
            currentData.arrivedPeopleNumber = 50;
        }

        currentData.citizensNumber += currentData.arrivedPeopleNumber;
        currentData.currentTurn = turnNumber+1;
    }

    float avgDeadPeoplePerRound = currentData.sumPercentDiedPeople / 10.0;
    float acrePerPeople = currentData.cityAcreSize / currentData.citizensNumber;

    if (avgDeadPeoplePerRound >= 33 && acrePerPeople < 7)
    {
        std::cout << "��-�� ����� ���������������� � ����������, ����� ������� ����, � ������ ��� �� ������. ������ �� ��������� ������� ������ ������������� � ��������";
    }
    else if (avgDeadPeoplePerRound >= 10 && acrePerPeople < 9)
    {
        std::cout << "�� ������� �������� �����, ������� ������ � ����� ��������.����� �������� � �����������, � ����� ������ �� ������ ������ ��� ����������";
    }
    else if (avgDeadPeoplePerRound >= 3 && acrePerPeople < 10)
    {
        std::cout << "�� ���������� ������ �������, � ���, �������, ���� ���������������, �� ������ ������ �� ������� ��� �� ����� ������ �����";
    }
    else
    {
        std::cout << "����������! ���� �������, �������� � ���������� ������ �� ���������� �� �����";
    }
}

