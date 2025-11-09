#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int BoardSize = 30;
const int MaxPlayers = 8;
int ActivePlayers = MaxPlayers;

//TT = Total Tiles
const int TTPlus3 = 1;
const int TTMinus3 = 1;
const int TTSkipTurn = 1;
const int TTExtraTurn = 1;
const int TTPass = 1;

enum TileType{
    NORMAL,
    MINUS3,
    PLUS3,
    SKIPTURN,
    EXTRATURN,
    PASS,
    END,
    START,
};

TileType Tabuleiro[30];

TileType Board[BoardSize];

class Player{
    public:

    int Position = 0;
    TileType Effect = NORMAL;
    int PlayerNumber = 1;
    string Name = "ERROR";
    string Color = "\033[1;37m";
    bool Turn = false;
};

Player Players[MaxPlayers];

//--General Functions---------------------------------------------------||
void clear(){
    #ifdef WIN32
	    system("CLS");
    #else
	    system("clear");
    #endif
}
void Enter(string Phrase){
    cout << Phrase << ":";
    cin.get();
	clear();
}

int PlayerInput(int& Action){
    string PlayerInput;
    
    getline (cin, PlayerInput);
    cout << endl;

    if (PlayerInput == "0"){
        Action = 0;
    }else if (PlayerInput == "1" || PlayerInput == "01"){
        Action = 1;
    }else if (PlayerInput == "2" || PlayerInput == "02"){
        Action = 2;
    }else if (PlayerInput == "3" || PlayerInput == "03"){
        Action = 3;
    }else if (PlayerInput == "4" || PlayerInput == "04"){
        Action = 4;
    }else if (PlayerInput == "5" || PlayerInput == "05"){
        Action = 5;
    }else if (PlayerInput == "6" || PlayerInput == "06"){
        Action = 6;
    }else if (PlayerInput == "7" || PlayerInput == "07"){
        Action = 7;
    }else if (PlayerInput == "8" || PlayerInput == "08"){
        Action = 8;
    }else if (PlayerInput == "9" || PlayerInput == "09"){
        Action = 9;
    }else if (PlayerInput == "10" || PlayerInput == "010"){
        Action = 10;
    }else if (PlayerInput == "11" || PlayerInput == "011"){
        Action = 11;
    }else if (PlayerInput == "12" || PlayerInput == "012"){
        Action = 12;
    }else if (PlayerInput == "13" || PlayerInput == "013"){
        Action = 13;
    }else if (PlayerInput == "14" || PlayerInput == "014"){
        Action = 14;
    }else if (PlayerInput == "15" || PlayerInput == "015"){
        Action = 15;
    }else if (PlayerInput == "16" || PlayerInput == "016"){
        Action = 16;
    }else if (PlayerInput == "17" || PlayerInput == "017"){
        Action = 17;
    }else if (PlayerInput == "18" || PlayerInput == "018"){
        Action = 18;
    }else if (PlayerInput == "19" || PlayerInput == "019"){
        Action = 19;
    }else if (PlayerInput == "20" || PlayerInput == "020"){
        Action = 20;
    }else if (PlayerInput == "Random" || PlayerInput == "random"){
        Action = 33;
    }else if(PlayerInput == "Hole" || PlayerInput == "hole"){
        Action = 69;
    }else{
        Action = -1;
    }

    return Action;
}

//--Menus and Interfaces--------------------------------------------------------------------||

string PlayerTileTypeCheckUI(Player player){
    switch (player.Effect){
        case NORMAL:
        return "--";
        break;

        case MINUS3:
        return "-3 Spaces";
        break;

        case PLUS3:
        return "+3 Spaces";
        break;

        case SKIPTURN:
        return "Skip a Turn";
        break;

        case EXTRATURN:
        return "Extra Turn";
        break;

        case PASS:
        return "Imobile until everyone passes";
        break;

        case END:
        return "Winner";
        break;

        case START:
        return "Start";
        break;
    }
    return "Normal";
}

void NameCollumnUI(){
    cout << endl;
    for (int l = 0; l < ActivePlayers; l++){
        if (Players[l].Turn == true){
            cout << Players[l].Color << "\033[4m";
        }
        cout << "   Player " << Players[l].PlayerNumber << ": " << Players[l].Name << " (" << PlayerTileTypeCheckUI(Players[l]) << ")   \033[0m" << endl;
    }
}

void TileUI(int number, bool Top, bool PlayerShow){
    int TotalPlayersin = 0;
    bool Playerin = false;

    for (int l = 0; l < ActivePlayers; l++){
        if (Players[l].Position == number){
            Playerin = true;
            TotalPlayersin++;
        }
    }

    if (Top == true){
        if (PlayerShow == false){// "bool Playershow" is being used to choose between showing the number or "ceiling" to avoid having more bool's
            if (Playerin == true){
            for (int l = 0; l < TotalPlayersin-3; l++){

                cout << "  ";
            }

            }
            if (number < 9){
                cout << " " << number+1;
            }else{
                cout << number+1;
            }
            return;
        }else{
            if (Playerin == true){
                for (int l = 0; l < TotalPlayersin-3; l++){

                    cout << "  ";
                }
            }
            cout << "  ";
            return;
        }
    }


    if (PlayerShow == true){
        for (int l = 0; l < ActivePlayers; l++){
        if (Players[l].Position == number){
            cout << Players[l].Color << "P" << l + 1 << "\033[0m";
        }
        }
        if (TotalPlayersin == 1){
            cout << "    ";
        }else if (TotalPlayersin == 2){
            cout << "  ";
        }else if (TotalPlayersin == 0){
            cout << "      ";
        }
        // cout << boardplayers;
        return;
    }

    if (Playerin == true){
        for (int l = 0; l < TotalPlayersin-3; l++){
            cout << "\033[4m" << "  ";
        }
    }

    cout << "\033[4m";
    switch(Board[number]){
        case NORMAL:
        cout << "      ";
        break;

        case MINUS3:
        cout << "\033[91m";
        cout << "  -3  ";
        break;

        case PLUS3:
        cout << "\033[92m";
        cout << "  +3  ";
        break;

        case SKIPTURN:
        cout << "\033[95m";
        cout << " SKIP ";
        break;

        case EXTRATURN:
        cout << "\033[92m";
        cout << "+1TURN";
        break;

        case PASS:
        cout << "\033[91m";
        cout << " PASS ";
        break;

        case END:
        cout << "\033[93m";
        cout << "  END ";
        break;

        case START:
        cout << "\033[93m";
        cout << "START ";
        break;
    }
    cout << "\033[0m";
}

void BoardUI(){
    clear();
    int RowSize = 6;
    int Spaces = BoardSize;
    int SpaceDose = 0;
    int DoseStart = 0;

    NameCollumnUI();

    if (Spaces >= RowSize){// Board "Ceiling"
            SpaceDose = RowSize;
    }else{
        SpaceDose = Spaces;
        Spaces = 0;
    }
    for (int l = DoseStart; l <= SpaceDose + DoseStart - 1; l++){// Board "Ceiling"
            cout << "\033[4m   ";
            TileUI(l, true, true);
            cout << "   \033[0m";
    }

    while (Spaces > 0){// Board
        if (Spaces >= RowSize){
            SpaceDose = RowSize;
            Spaces -= RowSize;
        }else{
            SpaceDose = Spaces;
            Spaces = 0;
        }

        cout << endl;
        for (int l = DoseStart; l <= SpaceDose + DoseStart - 1; l++){
            cout << "|  ";
            TileUI(l, true, false);
            cout << "  |";
        }
        cout << endl;
        for (int l = DoseStart; l <= SpaceDose + DoseStart - 1; l++){
            cout << "|";
            TileUI(l, false,true);
            cout << "|";
        }
        cout << endl;
        for (int l = DoseStart; l <= SpaceDose + DoseStart - 1; l++){
            cout << "|";
            TileUI(l, false,false);
            cout << "|";
        }

        DoseStart += SpaceDose;
    }
    cout << endl;
}

void PlayerWinUI(Player player){
    int Spacing = 46 - (size(player.Name)/2);

    clear();
    cout << player.Color;
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << "\033[0m" << endl;
    cout << "                         Q  U  E  S  T     F  O  R     G  L  O  R  Y                         " << player.Color << endl;
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << "\n\n";

    cout << "                                           Player " << player.PlayerNumber << endl;
    for (int l = 0; l < Spacing; l++){
        cout << " ";
    }
    cout << player.Name << "\n\n";

    cout << "       ___          __          ___  ______________   _____       __    __________                         " << endl;
    cout << "       \\  \\        /  \\        /  / |_____    _____| |     \\     |  |  /  ________\\                               " << endl;
    cout << "        \\  \\      /    \\      /  /        |  |       |  |\\  \\    |  | /  /                            " << endl;
    cout << "         \\  \\    /  /\\  \\    /  /         |  |       |  | \\  \\   |  | \\  \\_______             " << endl;
    cout << "          \\  \\  /  /  \\  \\  /  /          |  |       |  |  \\  \\  |  |  \\_______  \\           " << endl;
    cout << "           \\  \\/  /    \\  \\/  /           |  |       |  |   \\  \\ |  |          \\  \\         " << endl;
    cout << "            \\    /      \\    /       _____|  |_____  |  |    \\  \\|  |  ________/  /                          " << endl;
    cout << "             \\__/        \\__/       |______________| |__|     \\_____| |__________/                                " << endl;
    cout << "                                                                                             " << "\n\n";
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << "\033[0m" << endl;
    cout << "                         Q  U  E  S  T     F  O  R     G  L  O  R  Y                         " << player.Color << endl;
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << "\033[0m" << "\n\n";

    sleep(2);
    Enter("PRESS ENTER");
    clear();
}

void D6Roll(int& number, bool board, string color6){
    string spacing = "\t\t  ";
    for (int l = 0; l < 20; l++){
        number = rand() % 6 + 1;
        clear();
        if (board == true){
            BoardUI();
        }
        cout << "\n\n";
        switch (number){

            case 1:
            cout <<spacing<<".---------." << endl;
            cout <<spacing<<"|         |" << endl;
            cout <<spacing<<"|\033[30m    *    \033[0m|" << endl;
            cout <<spacing<<"|         |" << endl;
            cout <<spacing<<"'---------'" << endl;
            break;

            case 2:
            cout <<spacing<<".---------." << endl;
            cout <<spacing<<"|       * |" << endl;
            cout <<spacing<<"|         |" << endl;
            cout <<spacing<<"| *       |" << endl;
            cout <<spacing<<"'---------'" << endl;
            break;

            case 3:
            cout <<spacing<<".---------." << endl;
            cout <<spacing<<"|       * |" << endl;
            cout <<spacing<<"|    *    |" << endl;
            cout <<spacing<<"| *       |" << endl;
            cout <<spacing<<"'---------'" << endl;
            break;

            case 4:
            cout <<spacing<<".---------." << endl;
            cout <<spacing<<"| *     * |" << endl;
            cout <<spacing<<"|         |" << endl;
            cout <<spacing<<"| *     * |" << endl;
            cout <<spacing<<"'---------'" << endl;
            break;

            case 5:
            cout <<spacing<<".---------." << endl;
            cout <<spacing<<"| *     * |" << endl;
            cout <<spacing<<"|    *    |" << endl;
            cout <<spacing<<"| *     * |" << endl;
            cout <<spacing<<"'---------'" << endl;
            break;

            case 6:
            cout <<spacing<<".---------." << endl;
            cout <<spacing<<"|"<<color6<<" *     * \033[0m|" << endl;
            cout <<spacing<<"|"<<color6<<" *     * \033[0m|" << endl;
            cout <<spacing<<"|"<<color6<<" *     * \033[0m|" << endl;
            cout <<spacing<<"'---------'" << endl;
            break;
        }
        usleep(10000 + (2500 * l));
    }
}

void TitleScreenUI(bool hole){
    clear();
cout<<"\t"<<"\033[1;93m                                                                           .                  " << endl;
    cout<< "\t"  << "                                                                           :'       \033[0m" << endl;
    cout<< "\t"  << "+-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'\033[1;93m: '.\033[0m--+\033[1;92m" << endl;
    cout<< "\t"  << "         __________     __        __   __________    _________   ________\033[1;93m.'_   '-....-     \033[1;92m" << endl;
    cout<< "\t"  << "        /  ______  \\   |  |      |  | |   _______|  /   ______| |___\033[1;93m...-:___|    .-''       \033[1;92m" << endl;
    cout<< "\t"  << "       /  /      \\  \\  |  |      |  | |  |         |  /             |\033[1;93m '' .     .'           \033[1;92m" << endl;
    cout<< "\t"  << "      |  |        |  | |  |      |  | |  |______   |  \\_____        |  |\033[1;93m   ' . .           \033[1;92m" << endl;
    cout<< "\t"  << "      |  |        |  | |  |      |  | |   ______|   \\______  \\      |  |    \033[1;93m  ':        \033[1;92m" << endl;
    cout<< "\t"  << "      |  |  ___   |  | |  |      |  | |  |                 \\  |     |  |      \033[1;93m '.       \033[1;92m" << endl;
    cout<< "\t"  << "       \\  \\/  /__/  /   \\  \\____/  /  |  |_______   _______/  |     |  |                " << endl;
    cout<< "\t"  << "        \\_   ______/     \\________/   |__________| |_________/      |__|           " << endl;
    cout<< "\t"  << "         :__/                                                                   " << "\033[0m" << endl;
    cout<< "\t"  << "  \033[1;92m      .'.\033[0m                               FOR                                     " << "\033[1;93m" << endl;
    cout<< "\t"  << "  \033[1;92m     .'_'.\033[1;93m_______    __             _________     __________    ___    ___            " << endl;
    cout<< "\t"  << " \033[1;92m_...-' /  _'-..._\033[1;93m_\\  |  |           /  _____  \\   |   ____   \\  \\   \\  /   /         " << endl;
    cout<< "\t"  << "  \033[1;92m ''-./  / .-''\033[1;93m      |  |          /  /     \\  \\  |  |    \\   |  \\   \\/   /        " << endl;
    cout<< "\t"  << "      |\033[1;92m: | :'\033[1;93m         |  |         |  |       |  | |  |____/   |   \\      /         " << endl;
    cout<< "\t"  << "      | \033[1;92m'.'\033[1;93m    _____  |  |         |  |       |  | |   ___   _/     \\    /           " << endl;
    cout<< "\t"  << "      |  \033[1;92m|\033[1;93m    |___  | |  |         |  |       |  | |  |   \\  \\       /  /              " << endl;
    cout<< "\t"  << "       \\  \\_______/ | |  |________  \\  \\_____/  /  |  |    \\  \\     /  /               " << endl;
    cout<< "\t"  << "        \\__________/  |___________|  \\_________/   |__|     \\__\\   /__/               \033[0m" << "\n\n";
    if (hole == true){
    cout<< "\t" << "\033[1;91m                  |         |  -----------  -          ---------    " << endl;
    cout<< "\t" << "                  |         |  |         |  |          |           " << endl;
    cout<< "\t" << "                  |         |  |         |  |          |            " << endl;
    cout<< "\t" << "                  |---------|  |         |  |          |--------    " << endl;
    cout<< "\t" << "                  |         |  |         |  |          |             " << endl;
    cout<< "\t" << "                  |         |  |         |  |          |             " << endl;
    cout<< "\t" << "                  |         |  |_________|  |________  |________     \033[0m" << endl;
    }
    cout<< "\t"  << "+-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'--.-'-+  \033[0m" << "\n\n";
    
    cout<< "\t"  << "                       +-----------+          +-----------+          " << endl;
    cout<< "\t"  << "                       |   Play    |          |   Quit    |        " << endl;
    cout<< "\t"  << "                       +----(1)----+          +----(0)----+         " << "\n\n";
}

void PlayerPieceLineRepeater(string line){
    string inicialspacing = " ";

    for (int l = 0; l < MaxPlayers - ActivePlayers; l++){
        inicialspacing += "    ";
    }

    cout << inicialspacing;
    for (int l = 0; l < ActivePlayers; l++){
        cout << Players[l].Color << " " << line << " \033[0m";
    }
    cout << endl;
}
void PlayerPiecesUI(){
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.'-+" << "\n\n";
    PlayerPieceLineRepeater("  ___  ");
    PlayerPieceLineRepeater(" /   \\ ");
    PlayerPieceLineRepeater(" \\   / ");
    PlayerPieceLineRepeater("  | |  ");
    PlayerPieceLineRepeater(" /   \\ ");
    PlayerPieceLineRepeater("|_____|");
    cout << endl;
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.'-+" << "\n\n";
}

//--Main Game--------------------------------------------------------------------||

void EffectRandomPlacement(int tiletypenumber, TileType Effect){
    int Chance;
    for (int l = 0; l < tiletypenumber; l++){// Extra Turn
        while(true){
            Chance = rand() % (BoardSize-4) + 3;
            if (Effect == MINUS3){// To avoid a +3 -> -3 loop situation
                if (Board[Chance] == NORMAL && Board[Chance - 3] != PLUS3){
                    Board[Chance] = Effect;
                    break;
                }
            }else{
                if (Board[Chance] == NORMAL){
                    Board[Chance] = Effect;
                    break;
                }
            }
        }
    }
}
void BoardEffectsRandomizer(){
    int AllTT = TTExtraTurn + TTMinus3 + TTPass + TTPlus3 + TTSkipTurn;

    if (BoardSize - 4 < AllTT){
        return;
    }

    EffectRandomPlacement(TTExtraTurn,EXTRATURN);
    EffectRandomPlacement(TTPlus3,PLUS3);
    EffectRandomPlacement(TTMinus3,MINUS3);
    EffectRandomPlacement(TTPass,PASS);
    EffectRandomPlacement(TTSkipTurn,SKIPTURN);

}

void ActivePlayerChanging(){
    int Action;
    bool Valid = false;

    while (Valid == false){
        ActivePlayers = 0;
        clear();
        cout << "\n\n";
        cout << "\t\t"  << "  +-------------------------------+   " << endl;
        cout << "\t\t"  << "  |  How many Players will play?  |   " << endl;
        cout <<"\t\t  +------\033[90m(Max of "<<MaxPlayers<<" Players)\033[0m-------+" << "\n\n";

        PlayerPiecesUI();

        cout << "You: ";
        PlayerInput(Action);
        ActivePlayers = Action;

        if (ActivePlayers <= 1 || ActivePlayers > MaxPlayers){
            cout << "Invalid";
            usleep(300000);
            continue;
        }
       
        confirmation:
        clear();
        cout << "\t\t"  << "\n\n";
        cout << "\t\t"  << "  +-------------------------------+   " << endl;
        cout << "\t\t"  << "  |  Start Game with "<<ActivePlayers<<" Players?   |   " << endl;
        cout << "\t\t"  << "  +-------------------------------+   " << "\n\n";

        PlayerPiecesUI();

        cout << "\t\t"  << "    (1 - Yes)            (0 - No) " << "\n\n";

        cout << "You: ";
        PlayerInput(Action);
        switch (Action){
            case 0:
            continue;
            break;

            case 1:
            Valid = true;
            break;

            default:
            goto confirmation;
            break;
        }
    }
}

void PlayerSetup(Player& player){
    int Action;
    bool Valid = false;

    player.Turn = true;
    clear();

    NameCollumnUI();
    cout << endl;
    PlayerPiecesUI();

    cout << "Player " << player.PlayerNumber << ", type your name." << "\n\n";
    cout << "You: ";
    getline(cin,player.Name);

    while (Valid == false){
        clear();

        NameCollumnUI();
        cout << endl;
        PlayerPiecesUI();

        cout << player.Name << ", pick a color." << "\n\n";
        cout << "\t\t\t\033[30m" << "\033[41m 1 \033[42m 2 \033[43m 3 \033[46m 4 \033[45m 5 \033[47m 6 \033[100m 7 \033[0m" << "\n\n";
        cout << "You: ";
        PlayerInput(Action);

        Valid = true;
        switch (Action){
            case 1:
            player.Color = "\033[1;91m";
            break;
            case 2:
            player.Color = "\033[1;92m";
            break;
            case 3:
            player.Color = "\033[1;93m";
            break;
            case 4:
            player.Color = "\033[1;96m";
            break;
            case 5:
            player.Color = "\033[1;95m";
            break;
            case 6:
            player.Color = "\033[1;37m";
            break;
            case 7:
            player.Color = "\033[1;90m";
            break;

            default:
            Valid = false;
            cout << "Invalid";
            usleep(300000);
            continue;
        }
    }
}

void GameStartup(bool erasename){
    for (int l = 0; l < BoardSize; l++){
        Board[l] = NORMAL;
    }

    Board[BoardSize-1] = END;
    Board[0] = START;

    for (int l = 0; l < MaxPlayers; l++){
        Players[l].Position = 0;
        Players[l].Turn = false;
        Players[l].Effect = NORMAL;
        if (erasename == true){
            Players[l].Name = "<No Name>";
            Players[l].Color = "\033[1;37m";
        }
    }

    BoardEffectsRandomizer();
}

void GameSetup(){
    GameStartup(true);
    
    ActivePlayerChanging();

    for (int l = 0; l < ActivePlayers; l++){
        PlayerSetup(Players[l]);
    }

    clear();
    NameCollumnUI();
    cout << endl;
    PlayerPiecesUI();
    sleep(1);
}

void EffExtraTurn(Player& player){
    usleep(500000);
    cout << endl << player.Name << " gets an extra turn!";
    usleep(1000000);
}
void EffSkipTurn(Player& player){
    usleep(500000);
    cout << endl << player.Name << " skips a turn.";
    usleep(1000000);
    player.Turn = false;
    player.Effect = NORMAL;
}
void EffPlusMinus(Player& player, int amount, bool& win){
    usleep(500000);
    if (amount > 0){
        cout << endl << player.Name << " advances " << amount << " spaces!";
    }else{
        cout << endl << player.Name << " retracts " << amount*(-1) << " spaces.";
    }
    usleep(750000);

    if (amount > 0){
        for (int l = 0; l < amount; l++){
            player.Position++;

            if (player.Position >= BoardSize-1){ //Win Check
                player.Position = BoardSize-1;
                player.Effect = Board[player.Position];
                BoardUI();
                win = true;
                sleep(1);
                PlayerWinUI(player);
                player.Turn = false;
                return;
            }else{
                if (l == amount - 1){
                    player.Effect = Board[player.Position];
                }
                BoardUI();
                usleep(250000);
            }
        }
    }else{
        for (int l = 0; l < amount*(-1); l++){
            player.Position--;
            if (l == amount - 1){
                    player.Effect = Board[player.Position];
            }
            BoardUI();
            usleep(250000);
        }
    }
    player.Effect = Board[player.Position];
    usleep(500000);
}
void EffPass(Player& player, bool& free){
    int PlayersBehind = 0;
    for (int l = 0; l < ActivePlayers; l++){
        if (Players[l].Position < player.Position){
            PlayersBehind++;
        }
    }

    usleep(500000);

    if (PlayersBehind == 1){
        cout << endl << "There is " << PlayersBehind << " Player behind." << "\n\n";
    }else{
        cout << endl << "There are " << PlayersBehind << " Players behind." << "\n\n";
    }

    usleep(500000);
    if (PlayersBehind == 0){
        free = true;
        player.Effect = NORMAL;
        cout << player.Name << " is free!" << endl;
    }else{
        free = false;
        cout << player.Name << " is stuck.";
    }
    usleep(1000000);
}

void PlayerTurn(Player& player, bool& win){
    Start:
    int Spaces;
    player.Turn = true;
    bool Free = false;

        BoardUI();

    switch (player.Effect){//Start of Round Effects
        case SKIPTURN:
        EffSkipTurn(player);
        return;
        break;

        case PASS:
        EffPass(player, Free);
        if (Free == false){
            player.Turn = false;
            return;
        }
        break;

        default:
        break;
    }

    cout << "\n\n";
    Enter("PRESS ENTER TO ROLL");
    D6Roll(Spaces, true, player.Color);
    usleep(200000);
    cout << endl << player.Name << " rolled " << Spaces;
    usleep(750000);

    for (int l = 0; l < Spaces; l++){
        clear();
        player.Position++;
        if (player.Position >= BoardSize-1){ //Win Check
            player.Position = BoardSize-1;
            player.Effect = Board[player.Position];
            BoardUI();
            win = true;
            sleep(1);
            PlayerWinUI(player);
            player.Turn = false;
            return;
        }else{
            if (l == Spaces - 1){
                player.Effect = Board[player.Position];
            }
            BoardUI();
            usleep(250000);
        }
    }

    while (true){//End of round effects
        switch (player.Effect){
            case EXTRATURN:
            EffExtraTurn(player);
            goto Start;
            break;

            case PLUS3:
            EffPlusMinus(player, 3, win);
            continue;
            break;

            case MINUS3:
            EffPlusMinus(player, -3, win);
            continue;
            break;

            default:
            break;
        }
        break;
    }

    player.Turn = false;
    usleep(500000);
}

void Game(){
    bool Win = false;

    GameSetup();
    GameStartup(false);

    while (Win == false){
        for (int l = 0; l < ActivePlayers && Win == false; l++){
            PlayerTurn(Players[l], Win);
        }
    }
}

//----------------------------------------------------------------------||


void RandomStudent(){
int Chance;
    string RandomSpell[]{"",
        "        Vasco        ",//1
        "         Tomas       ",//2
        "       Guilherme     ",//3
        "         Filipe      ",//4
        "       Bernardo      ",//5
        "       Henrique      ",//6
        "       Rodrigo .A    ",//7
        "        Nathan       ",//8
        "         Quin        ",//9
        "         Blud        ",//10
        "        Joana        ",//11
        "      Cookie Pisca   ",//12
        "      Rodrigo .M     ",//13
        "         Mateus      ",//14
        "         Joao        ",//15
        "        Andre        "//Secret 16
    };
    clear();

    for(int l = 0; l < 20; l++){

        int Timer = (5000 + (4000 * l));
        Chance = rand() % 100 + 1;
        if(Chance == 33){//Armageddon Chance
            Chance = 16;
        }else{
            Chance = rand() % 15 + 1;
        }
        cout << "\n\n\n\n\n\n\n";
        cout << "\033[94m";
        cout << "\n\t,~~======~~======~~======~~======~~===," << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t/                                     \\" << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t^~~======~~======~~======~~======~~===^" << endl;
        usleep(Timer);
        clear();

        cout << "\n\n\n\n\n\n\n";
        cout << "\033[95m";
        cout << "\n\t,==~~======~~======~~======~~======~~=," << endl;
        cout << "\t/        " << RandomSpell[Chance] <<"        \\" << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t/                                     \\" << endl;
        cout << "\t^======~~======~~======~~======~~=====^" << endl;
        usleep(Timer);
        clear();

        cout << "\n\n\n\n\n\n\n";
        cout << "\033[91m";
        if (l == 19){
            cout << "\033[93m";
        }
        cout << "\n\t,====~~======~~======~~======~~======~," << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t/        " << RandomSpell[Chance] <<"        \\" << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t^====~~======~~======~~======~~======~^" << "\n\n";
        usleep(Timer);
        if (l == 19){
            cout << "\033[0m";
            break;
        }
        clear();
        
        cout << "\n\n\n\n\n\n\n";
        cout << "\033[92m";
        cout << "\n\t,======~~======~~======~~======~~=====," << endl;
        cout << "\t/                                     \\" << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t/        " << RandomSpell[Chance] <<"        \\" << endl;
        cout << "\t^==~~======~~======~~======~~======~~=^" << endl;
        usleep(Timer);
        clear();
    }
    sleep(2);
}


int main(){
    srand(time(0));
    int Action;
    bool Goof = false;

    for (int l = 1; l <= MaxPlayers; l++){
        Players[l-1].PlayerNumber = l;
    }


    while (true){

        TitleScreenUI(Goof);
        cout << "You: ";
        PlayerInput(Action);

        Goof = false;
        switch (Action){
            case 1:
            Game();
            break;

            case 0:
            return 0;
            break;

            case 33:
            RandomStudent();
            break;

            case 69:
            Goof = true;
            break;
        }


    }


    Game();

    

}