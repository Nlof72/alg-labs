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
    std::cout << "Вы хотите продолжить старую игру?(Y/N)";
    std::cin >> ans;

    if (ans == "y" || ans == "Y" || ans == "д" || ans == "Д")
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
    const std::string plagueTextValue = "Чума уничтожила половину населения;\n";
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

        std::cout << "Мой повелитель, соизволь поведать тебе\n" << "в году " << currentData.currentTurn<< " твоего высочайшего правления\n" <<
            currentData.diedPeopleNumber << " человек умерли с голоду, и " << currentData.arrivedPeopleNumber << " человек прибыли в наш великий город;\n" <<
            plagueText << "Население города сейчас составляет " << currentData.citizensNumber << " человек;\n" <<
            "Мы собрали " << currentData.producedWheatBushel << " бушелей пшеницы, по " << currentData.wheatFromField << " бушеля с акра;\n" <<
            "Крысы истребили " << currentData.destroyedByRatsWheatBushel << " бушелей пшеницы, оставив " << currentData.wheatBushelAmount << " бушеля в амбарах;\n" <<
            "Город сейчас занимает " << currentData.cityAcreSize << " акров;\n" << "1 акр земли стоит сейчас " << currentData.acreCost << " бушель.";

        std::cout << "\n\nЧто пожелаешь, повелитель?\n";

        while (!isValueValid)
        {
            std::cout << "Сколько акров земли повелеваешь купить?";
            std::cin >> buyAcreValue;
            std::cout << "Сколько акров земли повелеваешь продать?";
            std::cin >> sellAcreValue;
            std::cout << "Сколько бушелей пшеницы повелеваешь съесть?";
            std::cin >> eatBushelValue;
            std::cout << "Сколько акров земли повелеваешь засеять?";
            std::cin >> plantWheatValue;
            if (currentData.wheatBushelAmount - (buyAcreValue * currentData.acreCost) +
                (sellAcreValue * currentData.acreCost) - eatBushelValue - plantWheatValue * 0.5 < 0)
            {
                isValueValid = false;
                std::cout << "О, повелитель, пощади нас! У нас только " << currentData.citizensNumber
                    << " человек, " << currentData.wheatBushelAmount << " бушелей пшеницы и " <<
                    currentData.cityAcreSize << " акров земли!\n";
            }
            else
            {
                if (buyAcreValue < 0 || sellAcreValue < 0 || eatBushelValue < 0 || plantWheatValue < 0)
                {
                    std::cout << "О, повелитель, должно быть ты опечатался!\nМы не понимаем эти значения" << buyAcreValue
                        << " акров при покупке, " << sellAcreValue << " акров при продаже,\n" <<
                        eatBushelValue << " бушелей зерна для еды, " << plantWheatValue
                        << " акров земли для посадки,\nпо неомпаримым законам, установленных тобой, значения должны быть >= 0\n";
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
                std::cout << "\nПогибло слишком много жителей\n";
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
        std::cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. Теперь вы вынуждены влачить жалкое существование в изгнании»";
    }
    else if (avgDeadPeoplePerRound >= 10 && acrePerPeople < 9)
    {
        std::cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному.Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем";
    }
    else if (avgDeadPeoplePerRound >= 3 && acrePerPeople < 10)
    {
        std::cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова";
    }
    else
    {
        std::cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше";
    }
}

