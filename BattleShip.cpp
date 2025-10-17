#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int ShipParts = 17;

struct BoardSlot {
    bool Ship = false;
    bool Shot = false;
};

class Player {
    public:

    string Name = "";
    int ShipPoints = 0;

    BoardSlot Board[10][10];

}Player1,Player2;

//--General Functions---------------------------------------------------||
void clear(){
    #ifdef WIN32
	    system("CLS");
    #else
	    system("clear");
    #endif
}
void Enter(){
    cout << "PRESS ENTER:";
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
    }else if (PlayerInput == "Random" || PlayerInput == "random"){
        Action = 33;
    }else if (PlayerInput == "Starwalker" || PlayerInput == "starwalker"){
        Action = 1225;
    }else{
        Action = -1;
    }

    return Action;
}

bool boolSwitch(bool& Boolean){
    if (Boolean == true){
        return false;
    }else{
        return true;
    }

    return true;
}

void BattleInput(int& Xaim, int& Yaim){

    string input;

    cout << "You: ";
    getline (cin, input);

    if (input[0] == 'A' || input[0] == 'a'){
        Yaim = 0;
    }else if (input[0] == 'B' || input[0] == 'b'){
        Yaim = 1;
    }else if (input[0] == 'C' || input[0] == 'c'){
        Yaim = 2;
    }else if (input[0] == 'D' || input[0] == 'd'){
        Yaim = 3;
    }else if (input[0] == 'E' || input[0] == 'e'){
        Yaim = 4;
    }else if (input[0] == 'F' || input[0] == 'f'){
        Yaim = 5;
    }else if (input[0] == 'G' || input[0] == 'g'){
        Yaim = 6;
    }else if (input[0] == 'H' || input[0] == 'h'){
        Yaim = 7;
    }else if (input[0] == 'I' || input[0] == 'i'){
        Yaim = 8;
    }else if (input[0] == 'J' || input[0] == 'j'){
        Yaim = 9;
    }else{
        Yaim = -1;
    }

    switch (size(input)){
        case 2:

        if (input[1] == '1'){
            Xaim = 0;
        } else if (input[1] == '2'){
            Xaim = 1;
        } else if (input[1] == '3'){
            Xaim = 2;
        } else if (input[1] == '4'){
            Xaim = 3;
        } else if (input[1] == '5'){
            Xaim = 4;
        } else if (input[1] == '6'){
            Xaim = 5;
        } else if (input[1] == '7'){
            Xaim = 6;
        } else if (input[1] == '8'){
            Xaim = 7;
        } else if (input[1] == '9'){
            Xaim = 8;
        } else{
            Xaim = -1;
        }
        break;

        case 3:

        if (input[1] == '1' && input[2] == '0'){
            Xaim = 9;
        } else{
            Xaim = -1;
        }
        break;

        default:
        Yaim = -1;
        Xaim = -1;
        break;
    }
}

void BoardCleaning(Player& User){
    for (int l = 0; l <= 10; l++){
        for (int i = 0; i <= 10; i++){
            User.Board[l][i].Ship = false;
            User.Board[l][i].Shot = false;
        }
    }
}

void GameStartup(Player& User1, Player& User2){
    BoardCleaning(User1);
    BoardCleaning(User2);

    User1.ShipPoints = User2.ShipPoints = ShipParts;
}


void slowPrint(string text, int interval, string color){

    cout << color;

    for (int l = 0; l < size(text); l++){
        cout << text[l];
        usleep(interval);
    }

    cout << "\033[0m";

}
string RandomColor(){
    int Chance = rand() % 5 + 1;

    switch (Chance){
        case 1:
        return "\033[91m";
        break;

        case 2:
        return "\033[92m";
        break;

        case 3:
        return "\033[93m";
        break;

        case 4:
        return "\033[95m";
        break;

        case 5:
        return "\033[96m";
        break;

        default:
        break;
    }

    return "\033[0m";
}
//--Board Interface--------------------------------------------------||
string Slot(BoardSlot slot, bool enemy){
    if (slot.Shot == true && slot.Ship == true){
        return "\033[1;90m[\033[0;91mX\033[1;90m]\033[0m";
    }
    
    if (slot.Shot == true){
        return "\033[37;46m(O)\033[0m";
    }
    
    if (slot.Ship == true && enemy == false){
        return "\033[100m + \033[0m";
    }
    
    return "\033[34;46m ~ \033[0m";
}
string SlotLine(Player User, int y, bool enemy){
    string Line = "";
    Line += Slot(User.Board[0][y],enemy);
    Line += Slot(User.Board[1][y],enemy);
    Line += Slot(User.Board[2][y],enemy);
    Line += Slot(User.Board[3][y],enemy);
    Line += Slot(User.Board[4][y],enemy);
    Line += Slot(User.Board[5][y],enemy);
    Line += Slot(User.Board[6][y],enemy);
    Line += Slot(User.Board[7][y],enemy);
    Line += Slot(User.Board[8][y],enemy);
    Line += Slot(User.Board[9][y],enemy);
    return Line;
}

string HealthBar(int MaxHealth, int Health){
    string HPbar = "{";

    for (int l = 1; l <= MaxHealth; l++){
        if (l <= Health){
            HPbar += "\033[1;91m=\033[0m";
        }else{
            HPbar += "\033[90m-\033[0m";
        }
    }

    HPbar += "}";
    return HPbar;
}

void BoardUI(Player User,Player Target, bool OnlyUser){
    clear();

    if (OnlyUser == false){
    cout << "\t\t\t" << "                ENEMY" << "\n\n";

    cout << "\t\t\t" << "     1  2  3  4  5  6  7  8  9  10                   " << endl;
    cout << "\t\t\t" << "    ._.._.._.._.._.._.._.._.._.._.                   " << endl;
    cout << "\t\t\t" << "A  |"<<SlotLine(Target,0,true )<<"|                  " << endl;
    cout << "\t\t\t" << "B  |"<<SlotLine(Target,1,true )<<"|                  " << endl;
    cout << "\t\t\t" << "C  |"<<SlotLine(Target,2,true )<<"|   Armada Health: " << endl;
    cout << "\t\t\t" << "D  |"<<SlotLine(Target,3,true )<<"|  " << HealthBar(ShipParts,Target.ShipPoints) << endl;
    cout << "\t\t\t" << "E  |"<<SlotLine(Target,4,true )<<"|                  " << endl;
    cout << "\t\t\t" << "F  |"<<SlotLine(Target,5,true )<<"|                  " << endl;
    cout << "\t\t\t" << "G  |"<<SlotLine(Target,6,true )<<"|                  " << endl;
    cout << "\t\t\t" << "H  |"<<SlotLine(Target,7,true )<<"|                  " << endl;
    cout << "\t\t\t" << "I  |"<<SlotLine(Target,8,true )<<"|                  " << endl;
    cout << "\t\t\t" << "J  |"<<SlotLine(Target,9,true )<<"|                  " << endl;
    cout << "\t\t\t" << "    ''''''''''''''''''''''''''''''                   " << endl;
    }
    cout << "___________________________________________________________________________________________" << endl;
    cout << "___________________________________________________________________________________________" << "\n\n";

    cout << "\t\t\t" << "     1  2  3  4  5  6  7  8  9  10                   " << endl;
    cout << "\t\t\t" << "    ._.._.._.._.._.._.._.._.._.._.                   " << endl;
    cout << "\t\t\t" << "A  |" <<SlotLine(User,0,false)<< "|                  " << endl;
    cout << "\t\t\t" << "B  |" <<SlotLine(User,1,false)<< "|                  " << endl;
    cout << "\t\t\t" << "C  |" <<SlotLine(User,2,false)<< "|                  " << endl;
    cout << "\t\t\t" << "D  |" <<SlotLine(User,3,false)<< "|                  " << endl;
    cout << "\t\t\t" << "E  |" <<SlotLine(User,4,false)<< "|                  " << endl;
    cout << "\t\t\t" << "F  |" <<SlotLine(User,5,false)<< "|                  " << endl;
    cout << "\t\t\t" << "G  |" <<SlotLine(User,6,false)<< "|                  " << endl;
    cout << "\t\t\t" << "H  |" <<SlotLine(User,7,false)<< "|   Armada Health: " << endl;
    cout << "\t\t\t" << "I  |" <<SlotLine(User,8,false)<< "|  " << HealthBar(ShipParts,User.ShipPoints) << endl;
    cout << "\t\t\t" << "J  |" <<SlotLine(User,9,false )<<"|                  " << endl;
    cout << "\t\t\t" << "    ''''''''''''''''''''''''''''''                   " << endl;
    cout << "\t\t\t" << "                 YOU                                 " << endl;
    cout << "\t\t\t" << "" << endl;
    cout << "\t\t\t" << "" << endl;
    cout << "\t\t\t" << "" << endl;

}

void PlayerTitleCard(bool player1){
    if (player1 == true){
    cout << "  _________    __           __________  ___      ___  _________   _________       ____       " << endl;
    cout << " |   ____  \\  |  |         |   ____   | \\  \\    /  / |   ______| |   ____  \\     /    |      " << endl;
    cout << " |  |    |  | |  |         |  |    |  |  \\  \\  /  /  |  |        |  |    |  |   /  /  |      " << endl;
    cout << " |  |____|  | |  |         |  |____|  |   \\  \\/  /   |  |_____   |  |____|  |  |__/|  |      " << endl;
    cout << " |   ______/  |  |         |   ____   |    \\    /    |   _____|  |   ___   /       |  |      " << endl;
    cout << " |  |         |  |         |  |    |  |     |  |     |  |        |  |   \\  \\       |  |      " << endl;
    cout << " |  |         |  |_______  |  |    |  |     |  |     |  |______  |  |    \\  \\   ___|  |___   " << endl;
    cout << " |__|         |__________| |__|    |__|     |__|     |_________| |__|     \\__\\ |__________|  " << endl;
    cout << "                                                                                             " << "\n\n\n\n";
    }else{
    cout << "  _________    __           __________  ___      ___  _________   _________      ________      " << endl;
    cout << " |   ____  \\  |  |         |   ____   | \\  \\    /  / |   ______| |   ____  \\    /  ____  \\      " << endl;
    cout << " |  |    |  | |  |         |  |    |  |  \\  \\  /  /  |  |        |  |    |  |  |  |    |  |    " << endl;
    cout << " |  |____|  | |  |         |  |____|  |   \\  \\/  /   |  |_____   |  |____|  |  |__|  ./ ./   " << endl;
    cout << " |   ______/  |  |         |   ____   |    \\    /    |   _____|  |   ___   /       ./ ./   " << endl;
    cout << " |  |         |  |         |  |    |  |     |  |     |  |        |  |   \\  \\     ./ ./    " << endl;
    cout << " |  |         |  |_______  |  |    |  |     |  |     |  |______  |  |    \\  \\   /  /______   " << endl;
    cout << " |__|         |__________| |__|    |__|     |__|     |_________| |__|     \\__\\ |__________|  " << endl;
    cout << "                                                                                             " << "\n\n\n\n";
    }
}

void PlayerChangeUI(bool player1){
    clear();
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << endl;
    cout << "                   B     A     T     T     L     E     S     H     I     P                   " << endl;
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << "\n\n\n" << RandomColor();
    PlayerTitleCard(player1);
    cout << "                \\    /  ___            ____     _______         ____                      " << endl;
    cout << "                 \\  /  /   \\  |     | |    \\       |   |     | |    \\ |\\   |          " << endl;
    cout << "                  \\/  |     | |     | |____/       |   |     | |____/ | \\  |             " << endl;
    cout << "                  /   |     | |     | |   \\        |   |     | |   \\  |  \\ |            " << endl;
    cout << "                 /     \\___/   \\___/  |    \\       |    \\___/  |    \\ |   \\|         " << endl;
    cout << "                                                                                             \033[0m" << "\n\n";
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << endl;
    cout << "                   B     A     T     T     L     E     S     H     I     P                   " << endl;
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << "\n\n";

    Enter();
    clear();
}

void PlayerWinUI(bool player1){
    clear();
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << endl;
    cout << "                   B     A     T     T     L     E     S     H     I     P                   " << endl;
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << "\n\n\n" << RandomColor();
    PlayerTitleCard(player1);
    cout << "       ___          __          ___  ______________   _____       __    __________                         " << endl;
    cout << "       \\  \\        /  \\        /  / |_____    _____| |     \\     |  |  /  ________\\                               " << endl;
    cout << "        \\  \\      /    \\      /  /        |  |       |  |\\  \\    |  | /  /                            " << endl;
    cout << "         \\  \\    /  /\\  \\    /  /         |  |       |  | \\  \\   |  | \\  \\_______             " << endl;
    cout << "          \\  \\  /  /  \\  \\  /  /          |  |       |  |  \\  \\  |  |  \\_______  \\           " << endl;
    cout << "           \\  \\/  /    \\  \\/  /           |  |       |  |   \\  \\ |  |          \\  \\         " << endl;
    cout << "            \\    /      \\    /       _____|  |_____  |  |    \\  \\|  |  ________/  /                          " << endl;
    cout << "             \\__/        \\__/       |______________| |__|     \\_____| |__________/                                " << endl;
    cout << "                                                                                             \033[0m" << "\n\n";
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << endl;
    cout << "                   B     A     T     T     L     E     S     H     I     P                   " << endl;
    cout << "+-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-+" << "\n\n";

    sleep(2);
    Enter();
    clear();
}


//--Ship Placement-------------------------------------------------------||

void ShipShow(int ShipSize, bool vertical, string Name){
    string Ship = "\033[100m + \033[0m";
    string ShipCentre = "\033[1;33;100m + \033[0m";

    string Vspace = "";
    string Hspace = "   ";

    for (int l = 0; l < (ShipSize / 2); l++){
        Vspace += "\n";
    }

    if (vertical == true){

        for(int l = 1; l <= ShipSize; l++){
            if ((l == 1)){
                cout << "\t\t\t\t     ";
                cout << Hspace << ShipCentre << endl;
            }else{
                cout << "\t\t\t\t     ";
                cout << Hspace << Ship << endl;
            }
        }
    }else{
        cout << Vspace;
        cout << "\t\t\t\t     ";
        for(int l = 1; l <= ShipSize; l++){
            if ((l == 1)){
                cout << ShipCentre;
            }else{
                cout << Ship;
            }
        }
        cout << Vspace;
    }
    cout << "\n\t\t\t\t     " << Name << "\n\n";
}

void ShipPlacement(Player& User, Player& Target, int ShipSize, bool& vertical, string Name){
    int X, Y;

    while (true){
    bool valid = true;

        BoardUI(User,Target,true);
        ShipShow(ShipSize,vertical,Name);
        cout << "\nPlace your Ship:" << endl;
        cout << "(The Yellow mark is the position from where it will be positioned)" << endl;
        cout << "" << "\n\n";
        

        BattleInput(X,Y);

        if (X < 0 || Y < 0){
            cout << "There's no such area";
            usleep(500000);
            continue;
        }else if (User.Board[X][Y].Ship == true){
            cout << "There's already a ship placed there";
            usleep(500000);
            continue;
        }

        for (int l = 1; l <= ShipSize; l++){
            if (vertical == true){
                if (Y + l > 10){
                    cout << "That goes over the border";
                    usleep(800000);
                    valid = false;
                    break;
                }else if (User.Board[X][Y + l - 1].Ship == true){
                    cout << "That overlaps with a ship";
                    usleep(800000);
                    valid = false;
                    break;
                }
            }else{
                if (X + l > 10){
                    cout << "That goes over the border";
                    usleep(800000);
                    valid = false;
                    break;
                }else if (User.Board[X + l - 1][Y].Ship == true){
                    cout << "That overlaps with a ship";
                    valid = false;
                    usleep(800000);
                    break;
                }
            }
        }
//--
        if (vertical == true && valid == true){

                for (int l = Y; l < Y + ShipSize; l++){
                    User.Board[X][l].Ship = true;
                }
                break;

        }else if (valid == true){

                for (int l = X; l < X + ShipSize; l++){
                    User.Board[l][Y].Ship = true;
                }
                break;

        }
    }
}

void ArmadaPlacement(Player& User, Player& Target){//An Armada is a group of Ships

    struct Ship{
        int ShipSize;
        bool Placed = false;
        string Name;
    };

    Ship Ships[] = {
        {2,false,"Destroyer"},
        {3,false,"Submarine"},
        {3,false,"Cruiser"},
        {4,false,"Battleship"},
        {5,false,"Carrier"}
    };

    int TotalShips = size(Ships);

    int Action, ShipSelected = 0;
    bool Vertical = true;

    bool Validation = false;

    for (int l = 0; l <= TotalShips - 1; l++){

        Validation = false;

        while(Validation == false){

            BoardUI(User,Target,true);
            ShipShow(Ships[ShipSelected].ShipSize,Vertical,Ships[ShipSelected].Name);
            cout << "\n\t\t     "<<"+---------+    +---------+   +---------+" << endl;
            cout << "\t\t     " << "| Rotate  |    |  Place  |   |  Change |" << endl;
            cout << "\t\t     " << "+---(1)---+    +---(2)---+   +---(0)---+" << "\n\n";

            cout << "You: ";
            Action = PlayerInput(Action);
            
            switch (Action){
                case 0:
                ShipSelected++;
                while (true){
                    if (ShipSelected == TotalShips){
                        ShipSelected = 0;
                    } else if (Ships[ShipSelected].Placed == true){
                        ShipSelected++;
                    }else{
                        break;
                    }
                }
                break;
                

                case 1:
                Vertical = boolSwitch(Vertical);
                break;

                case 2:
                Ships[ShipSelected].Placed = true;
                ShipPlacement(User, Target, Ships[ShipSelected].ShipSize, Vertical,Ships[ShipSelected].Name);
                Validation = true;

                ShipSelected++;
                while (l != TotalShips - 1){
                    if (ShipSelected == TotalShips){
                        ShipSelected = 0;
                    } else if (Ships[ShipSelected].Placed == true){
                        ShipSelected++;
                    }else{
                        break;
                    }
                }
                break;

                default:
                cout << "Invalid Ship";
                usleep(500000);
                break;
            }
        }
    }

    BoardUI(User,Target,true);
    sleep(1);

}

//--BattleShip System----------------------------------------------------||
void RandomBattleStartMessage(){
     //int Chance = rand() % 5 + 1;
     int Chance = 5;

    switch(Chance){
        case 1:
        slowPrint("It's time to BATTLESHIP",75000,"\033[1m");
        break;

        case 2:
        slowPrint("Let us make these ships BATTLE",75000,"\033[1m");
        break;

        case 3:
        slowPrint("Let the battles BEGIN!",75000,"\033[1m");
        break;

        case 4:
        slowPrint("First we battle, then we ship, LET'S BATTLESHIP",75000,"\033[1m");
        break;

        case 5:
        slowPrint("1941, the pearl harbour incident.\n\t\t\t\tThe moment where millions of civilians die\n\t\t\t\tPlayer1 is Japan\n\t\t\t\tPlayer2 is the USA\n\t\t\t\tPride for the eagle",75000,"\033[1m");
        break;
    }
}

void PlayerTurn(Player& User, Player& Target){

    int Xaim, Yaim;

    while(true){
        clear();

        BoardUI(User,Target,false);
        //BoardUI(Target,User);
        
        BattleInput(Xaim,Yaim);

        if (Xaim < 0 || Yaim < 0){
            cout << "There is no such area" << endl;
            sleep(1);
        } else if (Target.Board[Xaim][Yaim].Shot == true){
            cout << "The area has already been Shot" << endl;
            sleep(1);
        }else{
            Target.Board[Xaim][Yaim].Shot = true;
            break;
        }
    }

    if (Target.Board[Xaim][Yaim].Ship == true){
        Target.ShipPoints--;
        BoardUI(User,Target,false);
        usleep(500000);
        cout << "The shot hit a Ship!" << endl;
    }else{
        BoardUI(User,Target,false);
        usleep(500000);
        cout << "The shot sank in the ocean" << endl;
    }
    sleep(2);
}

void BattlePlayer(Player& P1, Player& P2){

    GameStartup(P1,P2);

    cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t";
    slowPrint("Place your Ships",75000,"\033[1m");
    sleep(1);
    clear();

    PlayerChangeUI(true);
    ArmadaPlacement(P1,P2);

    PlayerChangeUI(false);
    ArmadaPlacement(P2,P1);

    clear();
    cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t";
    RandomBattleStartMessage();
    sleep(1);


    while(true){
        PlayerChangeUI(true);
        PlayerTurn(P1,P2);

        if (P2.ShipPoints == 0){
            PlayerWinUI(true);
            break;
        }

        PlayerChangeUI(false);
        PlayerTurn(P2,P1);

        if (P1.ShipPoints == 0){
            PlayerWinUI(false);
            break;
        }

    }
}

void TitleScreenUI(){                                                                  
    clear();
    cout<< "\n\t"<< "+-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-+  \033[1;96m" << endl;
    cout<< "\t"  << "\t" <<  "  _________    __________   _________  _________   __           __________       " << endl;
    cout<< "\t"  << "\t" <<  " |   ___   \\  |   ____   | |___    __||__    ___| |  |         |   _______|      " << endl;
    cout<< "\t"  << "\t" <<  " |  |   \\   | |  |    |  |     |  |      |  |     |  |         |  |            " << endl;
    cout<< "\t"  << "\t" <<  " |  |___/  /  |  |____|  |     |  |      |  |     |  |         |  |______      " << endl;
    cout<< "\t"  << "\t" <<  " |   ___   \\  |   ____   |     |  |      |  |     |  |         |   ______|        " << endl;
    cout<< "\t"  << "\t" <<  " |  |   \\   | |  |    |  |     |  |      |  |     |  |         |  |             " << endl;
    cout<< "\t"  << "\t" <<  " |  |___/   | |  |    |  |     |  |      |  |     |  |_______  |  |_______     " << endl;
    cout<< "\t"  << "\t" <<  " |_________/  |__|    |__|     |__|      |__|     |__________| |__________|   \033[1;90m" << endl;
    cout<< "\t"  << "\t" <<  "                ________    __      __   ______   _________                  " << endl;
    cout<< "\t"  << "\t" <<  "              /   _____ |  |  |    |  | |_    _| |   ____  \\                    " << endl;
    cout<< "\t"  << "\t" <<  "             |   /     \\|  |  |    |  |   |  |   |  |    |  |                 " << endl;
    cout<< "\t"  << "\t" <<  "             |   \\_____    |  |____|  |   |  |   |  |____|  |                " << endl;
    cout<< "\t"  << "\t" <<  "              \\______   \\  |   ____   |   |  |   |   ______/                   " << endl;
    cout<< "\t"  << "\t" <<  "                     \\   | |  |    |  |   |  |   |  |                           " << endl;
    cout<< "\t"  << "\t" <<  "              |\\_____/   | |  |    |  |  _|  |_  |  |                        " << endl;
    cout<< "\t"  << "\t" <<  "              |_________/  |__|    |__| |______| |__|                        \033[0m" << endl;
    cout<< "\t"  << "+-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-+  " << "\n\n";
    
    cout<< "\t"  << "                           +-----------+          +-----------+          " << endl;
    cout<< "\t"  << "                           | 2P Battle |          |   Quit    |        " << endl;
    cout<< "\t"  << "                           +----(1)----+          +----(0)----+         " << "\n\n";
}

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
        "        André        "//Secret 16
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

    while (true){

        TitleScreenUI();

        cout << "You: ";
        Action = PlayerInput(Action);

        switch (Action){
            case 0:
            return 0;
            break;

            case 1:
            clear();
            BattlePlayer(Player1, Player2);
            break;

            case 33:
            RandomStudent();
            break;
        }
    }

}

