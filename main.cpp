/* 
 * File:   main.cpp
 * Author: habrcmil
 *
 * Created on February 22, 2014, 9:58 AM
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ctime>

using namespace std;
#define inv 12
#define mainhand inventory[0] 
#define offhand inventory[1]
#define head inventory[2]
#define chest inventory[3]
#define necklace inventory[4]
#define mring inventory[5]
#define oring inventory[6]
#define waist inventory[7]
#define legs inventory[8]
#define gloves inventory[9]
#define wrists inventory[10]
#define boots inventory[11]
#define AllItems 41

int maxhealth=5,maxstamina=5,maxmana=5, gold=10, level=1, cl=0, slots=10,nrspell=10;
int Day=1,Hour=0,Minute=0;
unsigned int XP=0;
//slots:main hand 0, offhand 1, head 2,chest 3,necklace 4,mring 5,
//oring 6, waist 7,legs 8, gloves 9,wrists 10, boots 11

//weapons: unarmed 0, 1hand sword 1,2handed sword 2, bow 3, staff 4, shield 5, quiver 6
//head: unarmored 0, light 8, medium 9, heavy 10
//chest: unarmored 0, light 11, medium 12, heavy 13
//legs: unarmored 0, light 14, medium 15, heavy 16
//waist: unarmored 0, light 17, medium 18, heavy 19
//boots: unarmored 0, light 20, medium 21, heavy 22
//gloves: unarmored 0, light 23, medium 24, heavy 25
//wrists: unarmored 0, light 26, medium 27, heavy 28
//necklace: no 0, iron 29, silver 30, gold 31
//mring || oring: no 0, iron 32, silver 33, gold 34
//potions: 35 1health potion, 36 3health potion, 37 1mana potion, 38 3mana potion, 
//         39 1stamina potion, 40 3stamina potion
int inventory[inv], *bag=new int[slots];
int *spellbook=new int[nrspell];
double health=5.0, stamina=5.0, mana=5.0;
void cityMove();
void portMove();
int FreeSlot();
void Status();
bool YesNo(){
    char a;
    cin >> a;
    cin.ignore(100,'\n');
    a=tolower(a);
    if(a=='y')return true;
    else if(a=='n')return false;
    else YesNo();
}
void SleepFor(int n){
    char s[10];
    s[0]='s';
    s[1]='l';
    s[2]='e';
    s[3]='e';
    s[4]='p';
    s[5]=' ';
    if(n<10 && n>0){
        s[6]=48+n;
        s[7]='\0';
    }
   else if(n>9 && n<100){
        s[6]=n/10 +48;
        s[7]=n%10 +48;
        s[8]='\0';
    }
    else if(n>99 && n<1000){
        s[6]=n/100 +48;
        s[7]=n%100 +48;
        s[8]=n%10 +48;
        s[9]='\0';
    }
    system(s);
}
void checkPos(int mapnr){
    Minute+=5;
    if(Minute>59){
        Minute-=60;
        Hour++;
        if(Hour>23){
            Hour-=24;
            Day++;
        }
    }
    if(mapnr == 1){
        cout << "You are in highlands covered with snow." << endl <<
                "In the north and in the west you see high snowy mountains.\n" <<
                "In the south there is a forest.\n" <<
                "And in the east are snow highlands." << endl;
    }
    else if(mapnr== 2){
        cout << "You are in highlands covered with snow." << endl <<
                "In the North you see high snowy mountains.\n" <<
                "In the South there is a forest. You also see tower near the middle of it.\n" <<
                "In the West there are snow highlands.\n"<<
                "In the East are plains covered with snow with small city." << endl;
    }
    else if(mapnr== 3){
        cout << "You are in the city. There is tavern, blacksmith, General Goods store and three houses."<<endl<<
                "In the North and in the East you see high snowy mountains.\n" <<
                "In the South there is a forest.\n" <<
                "In the West there are snow highlands."<<endl;
        cityMove();
    }
    else if(mapnr== 4){
        if(stamina>0){
            cout << "You are in the forest. You don't see anything "<<
                    "so you climbed a tree to look around.(You lost 1 stamina)."<<endl<<
                    "In the North you see snowy highlands.\n"<<
                    "In the South you see a beach and beautiful sight of a sea.\n"<<
                    "In the West you see mountains descending to the sea.\n"<<
                    "In the East you see forest with a fort with tower in the middle of it."<<endl;
            stamina--;
        }
        else{
            cout << "You are in the forest. You don't see anything "<<
                    "but you are exhausted so you can't climb a tree to look around"<<endl;
        }
    }
    else if(mapnr== 5){
        cout << "As you entered this part of forest someone screamed at you. \"Go back or we will kill you!\""<<endl;
    }
    else if(mapnr== 6){
        if(stamina>0){
            cout << "You are in the forest. You don't see anything "<<
                    "so you climbed a tree to look around.(You lost 1 stamina)."<<endl<<
                    "In the North you see snowy plains with city there.\n"<<
                    "In the South you see a beach and beautiful sight of a sea.\n"<<
                    "In the West you see forest with a fort with tower in the middle of it."<<
                    "In the East you see a cliff which is being splashed by the waves from stormy sea.\n"<<endl;
            stamina--;
        }
        else{
            cout << "You are in the forest. You don't see anything "<<
                    "but you are exhausted so you can't climb a tree to look around"<<endl;
        }
    }
    else if(mapnr== 7){
        cout << "You are on the beach."<<endl<<
                "In the North you see a forest."<<endl<<
                "In the South and West you see an ocean."<<endl<<
                "In the East you see a big city with huge port full of merchant ships."<<endl;
    }
    else if(mapnr== 8){
        cout << "You are in the big city. There is a tavern, Jewellery,"<<
                " Weapon merchant, Armor merchant, Food store, Tailor's shop, a wizard,"<<
                " Alchemist,a port and fifteen houses."<<endl<<
                "In the North there is a forest. You also see tower near the middle of it.\n"<<
                "In the South you see ships sailing in and out of the port.\n"<<
                "In the West and East you see beaches."<<endl;
        portMove();
    }
    else if(mapnr== 9){
        cout << "You are on the beach."<<endl<<
                "In the North you see a forest."<<endl<<
                "In the South and East you see an ocean."<<endl<<
                "In the West you see a big city with huge port full of merchant ships."<<endl;
    }
}
int whatItem(int nr){
    string def = "\033[0m";
    string g= "\033[0;32m";
    string r= "\033[0;31m";
    string b= "\033[1;34m";
    switch(nr){
        case 0:return 1;break;
        case 1:cout<<"One-Handed Sword";break;
        case 2:cout<<"Two-Handed Sword";break;
        case 3:cout<<"Bow";break;
        case 4:cout<<"Staff";break;
        case 5:cout<<"Shield";break;
        case 6:cout<<"Quiver";break;
        case 7:cout<<"Gold";break;
        case 8:cout<<"Cloth Helmet";break;
        case 9:cout<<"Leather Helmet";break;
        case 10:cout<<"Steel Helmet";break;
        case 11:cout<<"Cloth Armor";break;
        case 12:cout<<"Leather Armor";break;
        case 13:cout<<"Steel Armor";break;
        case 14:cout<<"Cloth Leggings";break;
        case 15:cout<<"Leather Leggings";break;
        case 16:cout<<"Steel Leggings";break;
        case 17:cout<<"Cloth Belt";break;
        case 18:cout<<"Leather Belt";break;
        case 19:cout<<"Steel Belt";break;
        case 20:cout<<"Cloth Shoes";break;
        case 21:cout<<"Leather Shoes";break;
        case 22:cout<<"Steel Boots";break;
        case 23:cout<<"Cloth Gloves";break;
        case 24:cout<<"Leather Gloves";break;
        case 25:cout<<"Steel Gloves";break;
        case 26:cout<<"Cloth Wrists";break;
        case 27:cout<<"Leather Wrists";break;
        case 28:cout<<"Steel wrists";break;
        case 29:cout<<"Iron Amulet";break;
        case 30:cout<<"Silver Amulet";break;
        case 31:cout<<"Golden Amulet";break;
        case 32:cout<<"Iron Ring";break;
        case 33:cout<<"Silver Ring";break;
        case 34:cout<<"Golden Ring";break;
        case 35:cout<<r<<"Health potion - small"<<def;break;
        case 36:cout<<r<<"Health potion - large"<<def;break;
        case 37:cout<<b<<"Mana potion - small"<<def;break;
        case 38:cout<<b<<"Mana potion - large"<<def;break;
        case 39:cout<<g<<"Stamina potion - small"<<def;break;
        case 40:cout<<g<<"Stamina potion - large"<<def;break;
        case 100:cout<<"FireBall";break;
        case 101:cout<<"Frost Bolt";break;
        case 102:cout<<"Lightning Bolt";break;
        case 103:cout<<"Paralysis";break;
        case 104:cout<<"Sleep";break;
        case 105:cout<<"Healing Touch";break;
        case 106:cout<<"FireBlast";break;
        return 0;
    }
}
int DamageSpell(int nr){
    switch(nr){
        case 100:return 4+level;break;
        case 101:return 3+level;break;
        case 102:return 3+level;break;
        case 103:return -1;break;
        case 104:return -1;break;
        case 105:return 2+level;break;
        case 106:return 1+level;break;
        default: return -99;break;
    }
}
int ManaCost(int nr){
    switch(nr){
        case 100:return 2+level;break;
        case 101:return 1+level;break;
        case 102:return 1+level;break;
        case 103:return 4+level;break;
        case 104:return 4+level;break;
        case 105:return 2+level;break;
        case 106:return 1+level;break;
    }
}
int DamageWeapon(){
    int dmg=0;
    switch(mainhand){
        case 0:dmg= level;break;
        case 1:dmg= 1+level;break;
        case 2:dmg= 4+level;break;
        case 3:dmg= 3+level;break;
        case 4:dmg= 1+level;break;
    }
    if(offhand==0)dmg+=level;
    else if(offhand==1)dmg+=1+level;
    else if(offhand==6)dmg+=level;
    return dmg;
}
int Armor(){
    int armor=0;
    switch(head){
        case 8:armor= 1+level;break;
        case 9:armor= 3+level;break;
        case 10:armor= 6+level;break;
    }
    switch(legs){
        case 14:armor+= 1+level;break;
        case 15:armor+= 3+level;break;
        case 16:armor+= 6+level;break;
    }
    switch(waist){
        case 17:armor+= level;break;
        case 18:armor+= 1+level;break;
        case 19:armor+= 2+level;break;
    }
    switch(boots){
        case 20:armor+= level;break;
        case 21:armor+= 1+level;break;
        case 22:armor+= 2+level;break;
    }
    switch(gloves){
        case 23:armor+= level;break;
        case 24:armor+= 1+level;break;
        case 25:armor+= 2+level;break;
    }
    switch(wrists){
        case 26:armor+= level;break;
        case 27:armor+= 1+level;break;
        case 28:armor+= 2+level;break;
    }
    if(offhand==5)armor+=4+level;
    return armor;
}
bool checkMove(char move, int mapnr){
    if(move=='n'){
        if(mapnr==1 || mapnr==2 || mapnr==3)
            return false;
    }
    else if(move=='s'){
        if(mapnr==7 || mapnr==8 || mapnr==9)
            return false;
    }
    else if(move=='e'){
        if(mapnr==6 || mapnr==9 || mapnr==3)
            return false;
    }
    else if(move=='w'){
        if(mapnr==1 || mapnr==4 || mapnr==7)
            return false;
    }
    else return false;
    return true;
}
bool doMovefrom5(char move, char a,int &mapnr){
        if(move=='n'){
            if(a=='s'){
                mapnr+=3;
                return true;
            }
            else health-=2;
        }
        else if(move=='s'){
            if(a=='n'){
                mapnr-=3;
                return true;
            }
            else health-=2;
        }
        else if(move=='e'){
            if(a=='w'){
                mapnr--;
                return true;
            }
            else health-=2;
        }
        else if(move=='w'){
            if(a=='e'){
                mapnr++;
                return true;
            }
            else health-=2;
        }
        return false;
}
void TavernRest(){
    char tavernmove;
    cout << "Do you want to rent a room for 3 gold?(Y or N)"<< endl;
    cin >> tavernmove;
    cin.ignore(100, '\n');
    tavernmove = tolower(tavernmove);
    if(tavernmove=='y'){
        if(gold>3){
            gold-=3;
            stamina=maxstamina;
            health=maxhealth;
            mana=maxmana;
            cout << "You are well rested."<<endl;
        }
        else{
            cout << "\"Sorry, you need 3 gold coins to rent a room.\""<<endl;
        }
    }
    else if(tavernmove=='n'){
        cout << "\"Come again if you change your mind.\""<<endl;
    }
    else{
        cout << "\"So have you decided yet?\""<<endl;
        TavernRest();
    }
}
void TavernEat(){
    char eat;
    cout << "Do you want to buy food and drink to replenish all health and 3 stamina and 2 mana?(Y or N)"<<endl;
    cin >> eat;
    cin.ignore(100, '\n');
    eat = tolower(eat);
    if(eat=='y'){
        if(gold>2){
            gold-=2;
            if((stamina+=3)>maxstamina)stamina=maxstamina;
            health=maxhealth;
            if(mana+=2>maxmana)mana=maxmana;
            cout << "You ate all food you could."<<endl;
        }
        else {
            cout << "\"Sorry, you need 2 gold coins to buy food and drink.\""<<endl;
        }
    }
    else if(eat=='n'){
        cout << "\"Come again if you change your mind.\""<<endl;
    }
    else {
        cout << "\"So have you decided yet?\""<<endl;
        TavernEat();
    }
}
void Tavern(){
    char tavernmove;
    while(1){
        cout << "\"Greetings traveler, what could I do for you? I have free room for you to rent"<<
                " or I can get you something to eat and drink.\"(R,E,X)"<<endl;
        cin >> tavernmove;
        cin.ignore(100, '\n');
        tavernmove= tolower(tavernmove);
        if(tavernmove=='r'){
            cout << "\"So you want to rent a room, that will be 3 gold coins for a day, please.\""<<endl;
            TavernRest();
        }
        else if(tavernmove=='e'){
            cout << "\"We have plenty of food and drink to fulfill your wishes but it will cost you 2 coins.\""<<endl;
            TavernEat();
        }
        else if(tavernmove=='x'){
            cout << "\"Please come again.\""<<endl;
            break;
        }
    }
}
int randomNumber(int low, int high){
    int random_integer;
    int range = high - low + 1;
    random_integer = low +(rand()%range);
    return random_integer;
}
void ExpGain(int mobnr){
    string def = "\033[0m";
    string green= "\033[1;32m";
    string g= "\033[0;32m";
    string r= "\033[0;31m";
    string b= "\033[1;34m";
    XP+=2*mobnr*level;
    if(mobnr==3)XP-= mobnr * level;
    if(XP>(10+10*level)){
        XP-=10+10*level;
        level++;
        cout<<green<<"You gained a level. You are now level "<<level<<"."<<def<<endl;
        while(1){
            cout<< "Choose what you want to improve. (H for health or S for stamina or M for mana)"<<endl;
            char a;
            cin >> a;
            cin.ignore(100,'\n');
            a=tolower(a);
            if(a=='h'){maxhealth++;health=maxhealth;cout << "You chose "<<r<<"health"<<def<<endl;}
            else if(a=='s'){maxstamina++;stamina=maxstamina;cout << "You chose "<<g<<"stamina"<<def<<endl;}
            else if(a=='m'){maxmana++;mana=maxmana;cout << "You chose "<<b<<"mana"<<def<<endl;}
            else cout<<"Wrong choice."<<endl;
        }
    }
}
void Loot(int mobnr){
    int slot=FreeSlot(), itemnr=randomNumber(1,40);
    //black-30; red-31; green-32; yellow-33; blue-34; magenta-35; cyan-36; light gray-37
    string defaultcol = "\033[0m";//default color in console
    string color = "\033[1;33m";//Color of text 31=red; options [0 text; [1 text is bold;[7 background
    string green= "\033[0;32m";
    if(itemnr==7){
        int g=randomNumber(1,5);
        gold+=g;
        cout<<"You gained "<<color<<g;
        if(g!=1)cout<<" gold coins.";
        else cout<<" gold coin.";
        cout<<defaultcol<<endl;
    }
    else{
        cout <<green<< "You gained ";
        whatItem(itemnr);
        cout<<"."<<defaultcol<<endl;
        bag[slot]=itemnr;
    }
    slot=FreeSlot();
    if(randomNumber(1,100)>50 && slot>=0 && slot<slots){
        cout<<"You found another item."<<endl;
        itemnr=randomNumber(1,40);
        if(itemnr==7){
            int g=randomNumber(1,5);
            gold+=g;
            cout<<"You gained "<<color<<g;
            if(g!=1)cout<<" gold coins.";
            else cout<<" gold coin.";
            cout<<defaultcol<<endl;
        }
        else{
            cout <<green<< "You gained ";
            whatItem(itemnr);
            cout<<"."<<defaultcol<<endl;
            bag[slot]=itemnr;
        }
    }
    ExpGain(mobnr);
}
void combatAttack(int yDmg,int yArmor,int mobnr){
    char a;
    int mDmg;
    bool mStun = false, yStun = false,flagwhile=false;
    double mDmgRed, yDmgRed=yArmor * 2 / 100, mHP;
    //black-30; red-31; green-32; brown-33; blue-34; magenta-35; cyan-36; light gray-37
    string defaultcol = "\033[0m";//default color in console
    string color = "\033[0;31m";//Color of text 31=red; options [0 text; [1 text is bold;[7 background
    string boldcolor= "\033[1;31m";
    string g = "\033[0;32m";
    string y = "\033[1;33m";
    if(mobnr==1){
        mDmg = 2+level;
        mDmgRed=0.15;
        mHP=3+level;
    }
    else if(mobnr==2){
        mDmg = 3+level;
        mDmgRed=0.35;
        mHP=4+level;
    }
    else if(mobnr==3){
        mDmg = 1+level;
        mDmgRed=0.5;
        mHP=5+level;
    }
    while(health>0 || mHP > 0){
        Status();
        system("sleep 2");
        cout << "What do you want to do?(N to normal attack(100% damage) "<<
                "or M for Mighty attack (175% damage, -2stamina) or S to cast spell)"<<endl;
        cin >> a;
        cin.ignore(100,'\n');
        a=tolower(a);
        while(1){
            if(!yStun){
                if(a=='n'){
                    if(randomNumber(1,100)>10){
                        cout<<"You attacked your opponent with normal attack. You dealt "<<color<< 
                                yDmg *(1-mDmgRed)<<" damage."<<defaultcol<<endl;
                        mHP -= yDmg *(1-mDmgRed);
                    }
                    else cout << "You missed."<<endl;
                }
                else if(a=='m'){
                    if(stamina >=2){
                        if(randomNumber(1,100)>20){
                            cout<<"You attacked your opponent with mighty attack. You dealt "<<boldcolor<<
                                    yDmg*1.75 *(1-mDmgRed)<<" damage."<<defaultcol<<endl;
                            mHP-=yDmg*1.75 *(1-mDmgRed);
                            stamina-=2;
                        }
                        else {cout << "You missed."<<endl;stamina-=2;}
                    }else {
                        cout << "You didn't have enough stamina to perform mighty "<<
                                "attack but you still tried to do it."<<endl;
                        if(randomNumber(1,100)>90){
                            cout << "You succeeded, you dealt "<<color<< yDmg*1.75 * 0.9 *(1-mDmgRed)<<
                                    " damage"<<defaultcol<<endl;
                            mHP -= yDmg*1.75 * 0.9 *(1-mDmgRed);
                        }else cout<<"You have missed."<<endl;
                    }
                }
                else if(a=='s'){
                    int spell,asd,index=0;
                    bool flag=false;
                    for(int i=0;i<nrspell;i++){
                        asd=spellbook[i];
                         if(asd>0){
                             cout<<"Spell "<<(i+1)<<": ";
                             whatItem(asd);
                             cout<<" (";
                             if(mana < ManaCost(asd))cout<<color;
                             else cout<<g;
                             cout << ManaCost(asd)<<defaultcol<<" mana) ";
                             index++;
                         }
                    }
                    cout << endl;
                    while(1){
                        cout<<"Which spell do you want to use? Type spell number to cast it, 0 to exit."<<endl;
                        flag=cin >> spell;
                        while(!flag){cin.clear();cin.ignore(100,'\n');flag=cin >> spell;}
                        cin.ignore(100,'\n');
                        if(spell==0){flagwhile=true;break;}
                        else if(spell>0 && spell <= nrspell){
                            spell--;
                            int n=spellbook[spell];
                            if(ManaCost(n)>mana){
                                cout<<"You don't have enough mana to cast that."<<endl;
                                flagwhile=true;
                                break;
                            }
                            if(n>=0){
                                int eff = DamageSpell(n);
                                if(eff>0 && n!=105){
                                    cout<<"You casted ";
                                    whatItem(n);
                                    cout<< ". You dealt "<<color<<eff<<" damage."<<defaultcol<<endl;
                                    mHP -= eff;
                                    mana-=ManaCost(n);
                                    break;
                                }
                                else if(eff==-99){
                                    cout << "You tried to cast unknown spell. And"<<color<<" failed."<<defaultcol<<endl;
                                    break;
                                }
                                else if(eff==-1){
                                    mStun=true;cout << "You "<<y<<"stunned your opponent."<<defaultcol<<endl;
                                    mana -= ManaCost(n);
                                    break;
                                }
                                else if(n==105){
                                    cout << "You used ";
                                    whatItem(n);
                                    cout<< ". You healed yourself for "<<g<<eff<<" health."<<defaultcol<<endl;
                                    health+=eff;
                                    if(health>maxhealth)health=maxhealth;
                                    mana -= ManaCost(n);
                                    break;
                                }
                            }else {
                                cout << "You tried to cast unknown spell. And"<<color<<" failed."<<defaultcol<<endl;
                                break;
                            }
                        }
                    }
                }
            }else {cout << "You are stunned."<<endl; yStun=false;}
            if(!flagwhile)break;
            else flagwhile=false;
        }
        if(mHP<=0)break;
        if(!mStun){
            int attnr = randomNumber(1,10);
            if(attnr<8){
                if(randomNumber(1,100)>25){
                    cout << "Your opponent attacked you for "<<color<<mDmg * (1-yDmgRed)<<" damage"<<defaultcol<<endl;
                    health-=mDmg * (1-yDmgRed);
                }else cout<<"Your opponent attacked you but missed."<<endl;
            }
            else if(attnr<=10){
                if(randomNumber(1,100)>35){
                    cout<< "Your opponent attacked you twice for "<<boldcolor<<mDmg * 2 * 0.75 *(1-yDmgRed)<<" damage"<<defaultcol<<endl;
                    health -= mDmg * 2 * 0.75 *(1-yDmgRed);
                }else cout << "Your opponent missed you."<<endl;
            }
        }else mStun=false;
        if(health<=0)break;
    }
    if(mHP<=0){
        cout<<"You killed your opponent."<<endl;
        Loot(mobnr);
    }
}
void combatRun(int dmg,int armor,int mobnr){
    int det;
    if(mobnr==1){
        det=70;
    }
    else if(mobnr==2){
        det=40;
    }
    else if(mobnr==3){
        det=30;
    }
    if(armor>2+6*level){
        det += armor-2-6*level;
    }
    if(randomNumber(1,100)>det){
        cout<<"You successfully avoided combat."<<endl;
    }
    else {cout << "You tried to avoid combat but the opponent noticed you."<<endl;combatAttack(dmg,armor,mobnr);}
}
void Sneak(int dmg, int armor,int mobnr){
    double det;
    char a;
    if(mobnr==1){
        det=70.0;
    }
    else if(mobnr==2){
        det=40.0;
    }
    else if(mobnr==3){
        det=30.0;
    }
    det+=armor;
    if(armor == 10+6*level)det*=0.75;
    if(randomNumber(1,1000)>det*10){
        cout<<"You successfully sneaked behind your opponent. "<<
              "What do you want to do? (K to kill your opponent or R to avoid combat)"<<endl;
        cin >> a;
        cin.ignore(100,'\n');
        a=tolower(a);
        if(a=='k'){
            if(randomNumber(1,100)>10){
                cout << "You killed your opponent."<<endl;
                Loot(mobnr);
            }
            else {cout<<"Your opponent noticed you before you could kill him."<<endl;
                combatAttack(dmg, armor,mobnr);
            }
        }
        else if(a=='r'){
            cout << "You avoided the combat."<<endl;
        }
        else {
            cout<< "You didn't know what to do and your opponent noticed you."<<endl;
            combatAttack(dmg, armor,mobnr);
        }
    }
    else {cout << "You failed to sneak behind your opponent."<<endl;combatAttack(dmg,armor,mobnr);}
}
void Combat(int percent,int mobnr){
    int r = randomNumber(1,100), Yourdmg = DamageWeapon(), Yourarmor = Armor();
    char a;
    if(r<=percent){
        cout << "You spot a ";
        if(mobnr == 1)cout<<"wolf.";
        else if(mobnr==2)cout<<"bandit.";
        else if(mobnr==3)cout<<"crab.";
        while(1){
            cout <<endl<< "What do you want to do? (A to Attack, R to try to avoid it, S to try to sneak through)"<<endl;
            cin >> a;
            cin.ignore(100,'\n');
            a = tolower(a);
            if(a=='a'){
                combatAttack(Yourdmg,Yourarmor, mobnr);
                break;
            }else if(a=='r'){
                combatRun(Yourdmg,Yourarmor,mobnr);
                break;
            }
            else if(a=='s'){
                Sneak(Yourdmg,Yourarmor,mobnr);
                break;
            }
            else cout<<"You can't do that."<<endl;
        }
    }
}
void rEncounter(int mapnr){
    if(mapnr == 1 || mapnr == 2){
        Combat(60,1);
    }
    else if(mapnr==4 || mapnr==6){
        Combat(50,2);
    }
    else if(mapnr==7 || mapnr == 9){
        Combat(35,3);
    }
}
int Cost(int item, bool buy){
    switch(item){
        case 1:if(buy)return 5; else return 3;break;
        case 2:if(buy)return 7; else return 4;break;
        case 3:if(buy)return 6; else return 3;break;
        case 4:if(buy)return 4; else return 2;break;
        case 5:if(buy)return 5; else return 3;break;
        case 6:if(buy)return 4; else return 2;break;
        //case 7:cout<<"";break;return 
        case 8:if(buy)return 2; else return 1;break;
        case 9:if(buy)return 4; else return 2;break;
        case 10:if(buy)return 6; else return 3;break;
        case 11:if(buy)return 3; else return 2;break;
        case 12:if(buy)return 5; else return 3;break;
        case 13:if(buy)return 8; else return 4;break;
        case 14:if(buy)return 3; else return 2;break;
        case 15:if(buy)return 5; else return 3;break;
        case 16:if(buy)return 8; else return 4;break;
        case 17:if(buy)return 1; else return 1;break;
        case 18:if(buy)return 2; else return 1;break;
        case 19:if(buy)return 4; else return 2;break;
        case 20:if(buy)return 2; else return 1;break;
        case 21:if(buy)return 3; else return 2;break;
        case 22:if(buy)return 5; else return 3;break;
        case 23:if(buy)return 3; else return 2;break;
        case 24:if(buy)return 5; else return 3;break;
        case 25:if(buy)return 7; else return 4;break;
        case 26:if(buy)return 1; else return 1;break;
        case 27:if(buy)return 2; else return 1;break;
        case 28:if(buy)return 3; else return 2;break;
        case 29:if(buy)return 2; else return 1;break;
        case 30:if(buy)return 5; else return 3;break;
        case 31:if(buy)return 9; else return 5;break;
        case 32:if(buy)return 2; else return 1;break;
        case 33:if(buy)return 4; else return 2;break;
        case 34:if(buy)return 8; else return 4;break;
        case 35:if(buy)return 2; else return 1;break;
        case 36:if(buy)return 4; else return 2;break;
        case 37:if(buy)return 2; else return 1;break;
        case 38:if(buy)return 4; else return 2;break;
        case 39:if(buy)return 2; else return 1;break;
        case 40:if(buy)return 4; else return 2;break;
        case 100:if(buy)return 5;else return 1;break;
        case 101:if(buy)return 5;else return 1;break;
        case 102:if(buy)return 5;else return 1;break;
        case 103:if(buy)return 10;else return 1;break;
        case 104:if(buy)return 10;else return 1;break;
        case 105:if(buy)return 3;else return 1;break;
        default: return 0;
    }
}
void Buy(int *&inve, int cnt){
    int a=FreeSlot(), b=-1,tmp=0;
    bool flag=false;
    char c;
    if(a>=0 && a<slots){
        for(int i=0;i<cnt;i++){
            cout<<"Slot "<<(i+1)<<": ";
            whatItem(inve[i]);
            cout << "(" <<Cost(inve[i],true)<<" gold coins)"<<endl;    
            }
        while(1){
            cout<< "Choose slot you want to buy from.(type number of slot or 0 to exit): ";
            flag=cin>>b;    
            while(!flag){cin.clear();cin.ignore(100,'\n');flag=cin>>b;}
                cin.ignore(100,'\n');
                cout<<b;
                if(b==0)break;
                else if(b>0 && b<(cnt+1)){
                    b--;
                    tmp=Cost(inve[b],true);
                    if(gold>=tmp){
                        cout<<"Do you really want to buy ";
                        whatItem(inve[b]);
                        cout << " for "<<tmp<<"? (Y or N)"<<endl;
                        cin >> c;
                        cin.ignore(100, '\n');
                        c = tolower(c);
                        if(c=='y'){
                            bag[a]=inve[b];
                            inve[b]=0;
                            gold-=tmp;
                            break;
                        }
                        else if(c=='n'){
                            cout<<"Come again if you need anything."<<endl;
                            break;
                        }
                        else cout<< "Invalid option."<<endl;
                    }else {cout<<"You don't have enough gold coins to buy that."<<endl;break;}
                }else cout << "Invalid Slot."<<endl;
        }
    }
    else cout << "You don't have a free slot in your backpack."<<endl;
}
void Sell(int down,int up){
    int a=-1;
    bool flag=false;
    for(int i=0;i<slots;i++){
        if(bag[i]>= down && bag[i] <= up){
                cout<<"Slot "<<(i+1)<<": ";
                whatItem(bag[i]);
                cout << " ("<<Cost(bag[i],false)<<" gold coins)"<<endl;
        }
    }
    cout << "What item do you want to sell? (Type number of the slot or 0 to exit): ";
    flag=cin >> a;
    while(!flag){cin.clear();cin.ignore(100,'\n');flag=cin >> a;}
    cin.ignore(100,'\n');
    if(a==0)return;
    if(a>0 && a<=slots){
        cout<<"Do you want to sell it?(Y or N)"<<endl;
        if(YesNo()){
            a--;
            gold+=Cost(bag[a],false);
            bag[a]=0;
        }else {
            cout << "Come again if you change your mind."<<endl;
        }
    }else cout<< "Invalid Slot."<<endl;
}
void tradeTalk(int down,int up, int *&inve, int cnt){
    char a;
    while(1){
        cout << "Do you want to buy or sell?(B or S or X)"<<endl;
        cin>>a;
        cin.ignore(100, '\n');
        a=tolower(a);
        if(a=='b'){
            Buy(inve,cnt);
        }
        else if(a=='s'){
            Sell(down,up);
        }
        else if(a=='x')break;
        else {
            cout<<"Invalid option."<<endl;
        }
    }
}
void Blacksmith(){
    cout << "Greetings ";
    int se;
    if(cl==1)cout<<"Warrior. What weapon or armor would you like?"<<endl;
    else if(cl==2)cout<<"Mage. I am sorry but I don't have any spells, only weapons and armors. Would you like a weapon or armor?"<<endl;
    else if(cl==3)cout<<"Archer. What bow would you like to buy?"<<endl;
    int cnt=8;
    int *inve=new int[cnt];
        for(int i=0;i<cnt;i++){
            do{se=randomNumber(1,28);}
            while(se==7);
            inve[i]=se;
        }
    tradeTalk(1,28, inve,cnt);
}
void Weaponsmith(){
    cout << "Greetings ";
    if(cl==1)cout<<"Warrior. What weapon would you like?"<<endl;
    else if(cl==2)cout<<"Mage. I am sorry but I don't have any spells, only weapons. Would you like a weapon?"<<endl;
    else if(cl==3)cout<<"Archer. What bow would you like to buy?"<<endl;
    int cnt=4,se;
    int *inve=new int[cnt];
        for(int i=0;i<cnt;i++){
            se=randomNumber(1,6);
            inve[i]=se;
        }
    tradeTalk(1,6, inve,cnt);
}
void Armorsmith(){
    cout << "Greetings ";
    if(cl==1)cout<<"Warrior. What armor would you like?"<<endl;
    else if(cl==2)cout<<"Mage. I am sorry but I don't have any spells, only armors. Would you like an armor?"<<endl;
    else if(cl==3)cout<<"Archer. What armor would you like to buy?"<<endl;
    int cnt=4,se;
    int *inve=new int[cnt];
        for(int i=0;i<cnt;i++){
            se=randomNumber(8,28);
            inve[i]=se;
        }
    tradeTalk(8,28, inve,cnt);
}
void Store(){
    cout << "Greetings, traveler. ";
    int cnt=3,se;
    int *inve=new int[cnt];
        for(int i=0;i<cnt;i++){
            se=randomNumber(35,40);
            inve[i]=se;
        }
    tradeTalk(35,40, inve,cnt);
}
void JewellerShop(){
    cout << "Greetings, traveler. ";
    int cnt=3,se;
    int *inve=new int[cnt];
        for(int i=0;i<cnt;i++){
            se=randomNumber(29,34);
            inve[i]=se;
        }
    tradeTalk(29,34, inve,cnt);
}
void WizardShop(){
    cout << "Greetings, ";
    if(cl==1)cout<<"Warrior.";
    else if(cl==2)cout<<"Mage.";
    else if(cl==3)cout<<"Archer.";
    cout << "What spell so you want to learn?"<<endl;
    int cnt=3,se;
    int *inve=new int[cnt];
        for(int i=0;i<cnt;i++){
            se=randomNumber(100,106);
            inve[i]=randomNumber(100,106);
        }
    tradeTalk(100,106, inve,cnt);
}
void AlchemistShop(){
    cout << "Greetings, young traveler."<<endl;
    int cnt=3,se;
    int *inve=new int[cnt];
        for(int i=0;i<cnt;i++){
            se=randomNumber(35,40);
            inve[i]=se;
        }
    tradeTalk(35,40, inve,cnt);
}
void Port(){
    string def = "\033[0m";
    string y = "\033[1;33m";
    cout<<"\"Ahoy, seadog. Do you need some coins? Come work for me. I'll give 'ya 1 coin for an hour of work.\""<<endl;
    cout<<"\"So, do you want to work?\" (Y or N)";
    if(YesNo()){
        cout<< "How many hours do you want to work?"<<endl;
        int n;
        while(!(cin >> n)){
            cin.clear();
            cin.ignore(100,'\n');
        }
        cin.ignore(100,'\n');
        if(n>0){
            if(n>12){
                cout<<"You can't work for more than 12 hours."<<endl;
                n=12;
            }
            cout << "You have started working for "<<n<<" hours."<<endl;
            SleepFor(n);
            cout<<"Work is half done."<<endl;
            SleepFor(n);
            cout<<"Work Done! "<<y<<"(+"<< n << " gold coins)"<<def<<endl;
            gold+=n;
            int fs=FreeSlot();
            if(fs>=0 && fs<slots){
                if(randomNumber(1,1000)<10*n){
                    int coins=randomNumber(1,10);
                    gold+=coins;
                    cout<<"You have found "<<coins<< " gold coins."<<endl;
                }
            }
        }else {
            cout << "Can't work for "<<n<<" hours!"<< endl;
        }
    }
    else {
        cout << "Then get out of here you lazy landlubber!"<<endl;
    }
}
void cityMove(){
    char actioncity;
    while(1){
        cout << "You are in the city. There is Tavern(T), blacksmith(B), General Goods store(G) and three houses."<<endl<<
                "(X to exit)"<<endl;
        cin >> actioncity;
        cin.ignore(100, '\n');
        actioncity=tolower(actioncity);
        if(actioncity=='t'){
            Tavern();
        }
        else if(actioncity=='b'){
            Blacksmith();
        }
        else if(actioncity=='g'){
            Store();
        }
        else if(actioncity=='x'){
            cout << "You went out of the city. (To enter the city type L)"<<endl;
            break;
        }
    }
}
void portMove(){
    char actioncity;
    cout <<"You are in the big city. There is a Tavern(T), Jeweller's Store(J),"<<
           " Weapon merchant(W), Armor merchant(A), General Goods Store(G), a wizard(D),"<<
           " Alchemist(S),a port(P) and fifteen houses.(X to exit)"<<endl;
    cin >> actioncity;
    cin.ignore(100, '\n');
    actioncity=tolower(actioncity);
    if(actioncity=='t'){
        Tavern();
    }
    else if(actioncity=='w'){
        Weaponsmith();
    }
    else if(actioncity=='a'){
        Armorsmith();
    }
    else if(actioncity=='j'){
        JewellerShop();
    }
    else if(actioncity=='d'){
        WizardShop();
    }
    else if(actioncity=='s'){
        AlchemistShop();
    }
    else if(actioncity=='p'){
        Port();
    }
    else if(actioncity=='g'){
        Store();
    }
    else if(actioncity=='x'){
        cout << "You went out of the city. (To enter the city type L)"<<endl;
        return;
    }
}
void doMove(char move,int &mapnr){
    if(!checkMove(move,mapnr)){
             cout << "You can't go there." << endl;
             return;
        }
    if(move=='n'){
        mapnr-=3;
    }
    else if(move=='s'){
           mapnr+=3;
         }
    else if(move=='e'){
           mapnr++;
         }
    else if(move=='w'){
           mapnr--;
         }
    Minute+=30;
    if(Minute>59){
        Minute-=60;
        Hour++;
        if(Hour>23){
            Hour-=24;
            Day++;
        }
    }
    if(mapnr==5){
        checkPos(mapnr);
        char a;
        do{
            cin >> a;
            cin.ignore(100, '\n');
            a=tolower(a);
        }while(!checkMove(a,mapnr));
        if(!doMovefrom5(move,a,mapnr)){
            doMove(a, mapnr);
        }
    }
    else if(mapnr==3){
        cityMove();
    }
    else if(mapnr==8)
        portMove();
    else {
        rEncounter(mapnr);
    }
}
void Help(){
    cout << "------------------------------" << endl <<
            "Movement: Type N(n) or S(s) or E(e) or W(w) to move in direction respectively "<<
            "North or South or East or West." << endl <<
            "Position: Type L(l) to look around.(might cost you stamina)" << endl << 
            "Equip: To look to what you have equipped type I(i)." << endl<<
            "Backpack: To look to your backpack type B(b)."<<endl<<
            "Health: To see your current health, stamina and mana type U(u)."<< endl <<
            "Resting: To rest type T(t). resting will replenish you all stamina and 1 health and 1 mana."<<endl<<
            "You will need at least 1 stamina to light up the fire or you will need 3 mana to use a spell to do it."<<endl<<
            "Clear all text: To clear the console type C(c)."<< endl <<
            "End the game: If your health drop to 0 or less you will die and the game will be over"<<
            " or you can commit suicide by typing Q(q)."<<endl<<
            "!WARNING!: The Death is permanent and cannot be undone!"<<endl<<
            "------------------------------" << endl;
}
int FreeSlot(){
    int a=-1;
    for(int i=0;i<slots;i++){
        if(bag[i]==0){
           a=i;
           break;
        }
    }
    return a;
}
bool unequipOff(){
    int a=FreeSlot();
    if(a>=0 && a<slots){
        bag[a]=offhand;
        offhand=0;
    }
    else {
        cout<<"No free slot to store ";
        whatItem(offhand);
        cout<<"."<<endl;
        return false;
    }
    return true;
}
void Equip(int a){
    int b,tmp=0;
    bool flag=true, flag_cin=false;
    switch (bag[a]){
        case 1:cout<<"In which hand do you want to equip One-Handed Sword? Main Hand(1) or Off Hand(2): ";
            cin>>b;
            cin.ignore(100, '\n');
            if(!flag_cin){cin.clear();cin.ignore(100, '\n');}
            if(b==1){
                tmp=mainhand;
                mainhand=bag[a];
                bag[a]=tmp;
            }else if(b==2){
                if(mainhand==0 || mainhand == 1){
                    tmp=offhand;
                    offhand=bag[a];
                    bag[a]=tmp;
                }
            }
            break;
        case 2:
        case 4:
            if(offhand!=0)flag=unequipOff();
            if(flag){
                tmp=mainhand;
                mainhand=bag[a];
                bag[a]=tmp;
            }
            break;
        case 3:
            if(offhand!=0 || offhand!=6)flag=unequipOff();
            if(flag){
                tmp=mainhand;
                mainhand=bag[a];
                bag[a]=tmp;
            }
            break;
        case 5:
            if(mainhand==0 || mainhand ==1){
                tmp=offhand;
                offhand=bag[a];
                bag[a]=offhand;
            }
            else
                cout<<"You can't equip that."<<endl;
            break;
        case 6:
            if(mainhand==0 || mainhand ==1 || mainhand==3){
                tmp=offhand;
                offhand=bag[a];
                bag[a]=offhand;
            }
            else
                cout<<"You can't equip that."<<endl;
            break;
        case 8:
        case 9:
        case 10:
            tmp=head;
            head=bag[a];
            bag[a]=tmp;
            break;
        case 11:
        case 12:
        case 13:
            tmp=chest;
            chest=bag[a];
            bag[a]=tmp;
            break;
        case 14:
        case 15:
        case 16:
            tmp=legs;
            legs=bag[a];
            bag[a]=tmp;
            break;
        case 17:
        case 18:
        case 19:
            tmp=waist;
            waist=bag[a];
            bag[a]=tmp;
            break;
        case 20:
        case 21:
        case 22:
            tmp=boots;
            boots=bag[a];
            bag[a]=tmp;
        case 23:
        case 24:
        case 25:
            tmp=gloves;
            gloves=bag[a];
            bag[a]=tmp;
            break;
        case 26:
        case 27:
        case 28:
            tmp=wrists;
            wrists=bag[a];
            bag[a]=tmp;
            break;
        case 29:
        case 30:
        case 31:
            tmp=necklace;
            necklace=bag[a];
            bag[a]=tmp;
            break;
        case 32:
        case 33:
        case 34:
            cout<<"Do you want to equip the ring to your Right hand(1) or Left Hand(2)?"<<endl;
            flag_cin=false;
            flag_cin=cin >> b;
            if(!flag_cin){cin.clear();cin.ignore(100, '\n');cout<<"Can't do that."<<endl;}
            cin.ignore(100, '\n');
            if(b==1){
                tmp=mring;
                mring=bag[a];
                bag[a]=tmp;
            }else if(b==2){
                tmp=oring;
                oring=bag[a];
                bag[a]=tmp;
            }else
                cout<<"Can't do that."<<endl;
            break;
        case 35: if(health<maxhealth){health++;bag[a]=0;}
                 else cout<<"You have full Health."<<endl;break;
        case 36: if(health+3<=maxhealth){health+=3;bag[a]=0;}
                 else if(health<maxhealth)health=maxhealth;
                 else cout<<"You have full Health."<<endl;break;
        case 37: if(mana<maxmana){mana++;bag[a]=0;}
                 else cout<<"You have full Mana."<<endl;break;
        case 38: if(mana+3<=maxmana){mana+=3;bag[a]=0;}
                 else if(mana<maxmana)mana=maxmana;
                 else cout<<"You have full Mana."<<endl;break;
        case 39: if(stamina<maxstamina){stamina++;bag[a]=0;}
                 else cout<<"You have full Stamina."<<endl;break;
        case 40: if(stamina+3<=maxstamina){stamina+=3;bag[a]=0;}
                 else if(stamina<maxstamina)stamina=maxstamina;
                 else cout<<"You have full Stamina."<<endl;break;
        case 100:if(spellbook[1]!=100){spellbook[1]=100;bag[a]=0;}
                 else  cout<<"You already know that spell."<<endl;break;
        case 101:if(spellbook[2]!=101){spellbook[2]=101;bag[a]=0;}
                 else  cout<<"You already know that spell."<<endl;break;
        case 102:if(spellbook[3]!=102){spellbook[3]=102;bag[a]=0;}
                 else  cout<<"You already know that spell."<<endl;break;
        case 103:if(spellbook[4]!=103){spellbook[4]=103;bag[a]=0;}
                 else  cout<<"You already know that spell."<<endl;break;
        case 104:if(spellbook[5]!=104){spellbook[5]=104;bag[a]=0;}
                 else  cout<<"You already know that spell."<<endl;break;
        case 105:if(spellbook[6]!=105){spellbook[6]=105;bag[a]=0;}
                 else  cout<<"You already know that spell."<<endl;break;
        case 106:if(spellbook[0]!=106){spellbook[0]=106;bag[a]=0;}
                 else  cout<<"You already know that spell."<<endl;break;
    }
}
void DestroyItem(int a){
    char b;
    if(bag[a]==0){cout<<"Nothing to destroy."<<endl;return;}
    cout << "Do you really want to destroy ";
    whatItem(bag[a]);
    cout<< " in slot "<<(a+1)<<"? (Y or N)"<<endl;
    cin >> b;
    cin.ignore(100, '\n');
    b=tolower(b);
    if(b=='y'){
        bag[a]=0;
    }
}
void Backpack(){
    int j=0,a=0;
    bool flag=false;
    cout << "You have "<<slots<<" slots in your backpack."<<endl;
    for(int i=0;i<slots;i++){
        if(bag[i]){
                cout<<"Slot "<<(i+1)<<": ";
                whatItem(bag[i]);
                cout<<", ";
        }else j++;
    }
    if(j>0){
        if(j==slots)cout<<"You have ";
        cout<<j<<" free slots."<<endl;
    }
    do{
        cout << "Type number of slot you want to manipulate or type 0 to close backpack: ";
        flag=cin >> a;
        cin.ignore(100, '\n');
        if(!flag){cin.clear();cin.ignore(100, '\n');cout << "Invalid slot."<<endl;continue;}
        if(a==0)break;
        else if(a>slots || a<1){
            cout << "Invalid slot."<<endl;
        }
        else {
            char b;
            a--;
            cout << "What do you want to do? Equip item(E) or Destroy item(D) or Choose another slot(X): "<<endl;
            cin>>b;
            cin.ignore(100, '\n');
            b=tolower(b);
            if(b=='e')Equip(a);
            else if(b=='d')DestroyItem(a);
            else if(b=='x')break;
            else cout<<"Invalid option."<<endl;
        }
    }while(1);
}
void inventoryCheck(){
    string def = "\033[0m";
    string r = "\033[0;31m";
    string g = "\033[0;32m";
    string b = "\033[0;34m";
    cout << "Main hand: ";
    if(mainhand==0)cout << "Unarmed"<<endl;
    else if(mainhand==1)cout << "One-Handed Sword"<<endl;
    else if(mainhand==2)cout << "Two-Handed Sword" <<endl;
    else if(mainhand==3)cout << "Bow" <<endl;
    else if(mainhand==4)cout << "Staff" <<endl;
    cout << "Off hand: ";
    if(offhand == 0)cout<< "Unarmed" <<endl;
    else if(offhand == 1)cout<< "One-Handed Sword" <<endl;
    else if(offhand == 5)cout<< "Shield" <<endl;
    else if(offhand == 6)cout<< "Quiver" <<endl;
    //helm: unarmored 0, light 8, medium 9, heavy 10
    cout << "Helmet: ";
    if(head == 0)cout << "Unarmored" <<endl;
    else if(head == 8)cout <<b<< "Cloth" <<def<<endl;
    else if(head == 9)cout <<g<< "Leather" <<def<<endl;
    else if(head == 10)cout <<r<< "Steel" <<def<<endl;
    //chest: unarmored 0, light 11, medium 12, heavy 13
    cout << "Chest: ";
    if(chest == 0)cout << "Unarmored" <<endl;
    else if(chest == 11)cout <<b<< "Cloth" <<def<<endl;
    else if(chest == 12)cout <<g<< "Leather" <<def<<endl;
    else if(chest == 13)cout <<r<< "Steel" <<def<<endl;
    //pants: unarmored 0, light 14, medium 15, heavy 16
    cout << "Pants: ";
    if(legs == 0)cout << "Unarmored" <<endl;
    else if(legs == 14)cout <<b<< "Cloth" <<def<<endl;
    else if(legs == 15)cout <<g<< "Leather" <<def<<endl;
    else if(legs == 16)cout <<r<< "Steel" <<def<<endl;
    //waist: unarmored 0, light 17, medium 18, heavy 19
    cout << "Waist: ";
    if(waist == 0)cout << "Unarmored" <<endl;
    else if(waist == 17)cout <<b<< "Cloth" <<def<<endl;
    else if(waist == 18)cout <<g<< "Leather" <<def<<endl;
    else if(waist == 19)cout <<r<< "Steel" <<def<<endl;
    //boots: unarmored 0, light 20, medium 21, heavy 22
    cout << "Boots: ";
    if(boots == 0)cout << "Unarmored" <<endl;
    else if(boots == 20)cout <<b<< "Cloth" <<def<<endl;
    else if(boots == 21)cout <<g<< "Leather" <<def<<endl;
    else if(boots == 22)cout <<r<< "Steel" <<def<<endl;
    //Gloves: unarmored 0, light 23, medium 24, heavy 25
    cout << "Gloves: ";
    if(gloves == 0)cout << "Unarmored" <<endl;
    else if(gloves == 23)cout <<b<< "Cloth" <<def<<endl;
    else if(gloves == 24)cout <<g<< "Leather" <<def<<endl;
    else if(gloves == 25)cout <<r<< "Steel" <<def<<endl;
    //wrists: unarmored 0, light 26, medium 27, heavy 28
    cout << "Wrists: ";
    if(wrists == 0)cout << "Unarmored" <<endl;
    else if(wrists == 26)cout <<b<< "Cloth" <<def<<endl;
    else if(wrists == 27)cout <<g<< "Leather" <<def<<endl;
    else if(wrists == 28)cout <<r<< "Steel" <<def<<endl;
    //necklace: no 0, iron 29, silver 30, gold 31
    if(necklace == 0)cout << "You have no amulet."<<endl;
    else {
        cout << "Amulet: ";
        if(necklace ==29)cout<< "Iron"<<endl;
        else if(necklace == 30)cout<< "Silver"<<endl;
        else if(necklace ==31)cout << "Golden"<<endl;
    }
    //ring: no 0, iron 32, silver 33, gold 34
    if(mring == 0)cout << "You have no Right Ring."<<endl;
    else {
        cout << "Right Ring: ";
        if(mring ==32)cout<< "Iron"<<endl;
        else if(mring == 33)cout<< "Silver"<<endl;
        else if(mring ==34)cout << "Golden"<<endl;
    }
    if(oring == 0)cout << "You have no Left Ring."<<endl;
    else {
        cout << "Left Ring: ";
        if(oring ==32)cout<< "Iron"<<endl;
        else if(oring == 33)cout<< "Silver"<<endl;
        else if(oring ==34)cout << "Golden"<<endl;
    }
    string yellow = "\033[1;33m";
    cout << "You have "<<yellow<<gold<<" gold coins."<<def<<endl;
}
void Status(){
    //black-30; red-31; green-32; brown-33; blue-34; magenta-35; cyan-36; light gray-37
    string def = "\033[0m";//default color in console
    string red = "\033[1;31m";//Color of text 31=red; options [0 text; [1 text is bold;[7 background
    string redbold = "\033[0;31m";
    string green = "\033[1;32m";
    string greenbold = "\033[0;32m";
    string blue = "\033[1;34m";
    string bluebold = "\033[0;34m";
    string cyan = "\033[0;36m";
    cout << "Your health is: "<<red<<health<<def<<"/"<<redbold<<maxhealth<<def<<endl<<
            "Your stamina is: "<<green<<stamina<<def<<"/"<<greenbold<<maxstamina<<def<<endl<<
            "Your mana is: "<<blue<<mana<<def<<"/"<<bluebold<<maxmana<<def<<endl<<
            "Level: "<<cyan<<level<<def<<endl<<"XP: "<<cyan<<XP<<def<<endl;
}
void Rest(){
    string d = "\033[0m";
    string r = "\033[1;31m";
    string g = "\033[1;32m";
    string bl = "\033[1;34m";
    int a=0;
    int b=maxstamina-stamina;
    int c=0;
    if(health<maxhealth)a=1;
    if(mana<maxmana)c=1;
    if(stamina>0){
        cout<<"You are trying light up fire with TinderBox. ("<<g<<" -1 stamina"<<d<<" )"<<endl;
        system("sleep 1");
        cout<<"You lit up the fire. You are now resting."<<endl;
        SleepFor(a+b+1+c);
        cout<<"You replenished "<< g << b+1<<" stamina"<<d;
        stamina=maxstamina;
        if(health<maxhealth){health++;cout<<","<<r<<" 1 health"<<d;}
        if(mana<maxmana){mana++;cout<<","<<bl<<" 1 mana"<<d;}
        if(mana>maxmana)mana=maxmana;
        if(health>maxhealth)health=maxhealth;
        cout<<"."<<endl;
    }
    else if(mana>=3){
        cout<<"You lit up the fire with spell. You are now resting."<<endl;
        SleepFor(a+b+c);
        cout<<"You replenished "<< g << b<<" stamina"<<d;
        mana-=3;
        stamina=maxstamina;
        if(health<maxhealth){health++;cout<<","<<r<<" 1 health"<<d;}
        if(mana<maxmana){mana++;cout<<","<<bl<<" 1 mana"<<d;}
        if(mana>maxmana)mana=maxmana;
        if(health>maxhealth)health=maxhealth;
        cout<<"."<<endl;
    }
    else{
        cout << "You are exhausted and you don't have enough "<<
                "mana to cast the spell to light up fire for you to rest."<<endl<<
                "Head to tavern and rest there."<<endl;
    }
    Minute+=5*(a+b+c);
    if(Minute>59){
        Minute-=60;
        Hour++;
        if(Hour>23){
            Hour-=24;
            Day++;
        }
    }
}
void SpellBook(){
    string def = "\033[0m";
    string blue = "\033[0;34m";
    for(int i=0;i<nrspell;i++){
         if(spellbook[i]>0){
             cout<<"Spell "<<(i+1)<<": ";
             whatItem(spellbook[i]);
             cout <<" ("<<blue<< ManaCost(spellbook[i])<<def<<" mana) ";
         }
    }
    cout<<endl;
}
int checkAction(char move, int mapnr){
    if(move=='h')Help();
    else if(move=='l')checkPos(mapnr);
    else if(move =='n' || move =='s' 
         || move =='e' || move =='w')
         return 1;
    else if(move=='q')return 2;
    else if(move=='t')Rest();
    else if(move=='p')SpellBook();
    else if(move=='i')inventoryCheck();
    else if(move=='b')Backpack();
    else if(move=='u')Status();
    else if(move=='c')system("clear");
    else cout << "You can't do it." << endl;
    return 0;
}

int main(int argc, char** argv) {
    char move;
    srand(time(NULL));
    int mapnr=1, action=0;
    bool flag_cin=0;
    for(int i=0; i<nrspell;i++){
                spellbook[i]=0;
            }
    while(1){
        cout << "Choose class you want to play. type 1 or 2 or 3 for Warrior or Mage or Archer."<<endl;
        flag_cin = cin >> cl;
        cin.ignore(100, '\n');
        if(cl==1){
            maxhealth = health = 8;
            maxmana = mana = 3;
            maxstamina = stamina = 5;
            mainhand = 1;
            break;
        }
        else if(cl==2){
            maxhealth = health = 4;
            maxmana = mana = 9;
            maxstamina = stamina = 3;
            mainhand = 4;
            spellbook[0]=106;
            break;
        }
        else if(cl==3){
            maxhealth = health = 5;
            maxmana = mana = 3;
            maxstamina = stamina = 8;
            mainhand = 3;
            break;
        }
        else{
            cout << "Wrong input."<<endl;
            system("sleep 1");
            system("clear");
        }
        if(!flag_cin){cin.clear();cin.ignore(100, '\n');}
    }
    system("clear");
    Help();
    cout << "Game will start in 5 seconds. For Help in game type H(h)" << endl;
    system("sleep 5");
    system("clear");
    cout << "You woke up and the only thing you remember is that you were " <<
            "ambushed by bandits and left for dead here." << endl;
    cout << "What do You want to do? (H(help), N,S,E,W(movements), "
            "L(look around), I(equipped items and gold), B(backpack),"
            " U(Health/mana/stamina status), T(rest): ";
    while(health>0){
        cin >> move;
        cin.ignore(100, '\n');
        move = tolower(move);
        action=checkAction(move,mapnr);
        if(action==1)
            doMove(move, mapnr);
        else if(action==2){
            health=0;
            cout << "You couldn't handle it so you committed suicide." << endl;
            break;
        }
        move=',';
    }
    string def = "\033[0m";
    string red = "\033[2;31m";
    string cyan = "\033[1;36m";
    cout <<red<<"You died."<<def<<endl<<"At day "<<Day<<" at "<<Hour<<
            ":";
    if(Minute<10)cout<<"0";
    cout<<Minute<< endl << "GAME OVER." << endl <<"Statistics: "<< endl;
    cout<< "You were Level "<<cyan<< level<<def;
            if(cl==1)cout<<" Warrior.";
            else if(cl==2)cout<<" Mage.";
            else if(cl==3)cout<<" Archer.";
            cout << endl;
    red="\033[1;31m";
    string redbold = "\033[0;31m";
    string green = "\033[1;32m";
    string greenbold = "\033[0;32m";
    string blue = "\033[1;34m";
    string bluebold = "\033[0;34m";
    string yellow = "\033[1;33m";
    cout << "Your health is: "<<red<<health<<def<<"/"<<redbold<<maxhealth<<def<<endl<<
            "Your stamina is: "<<green<<stamina<<def<<"/"<<greenbold<<maxstamina<<def<<endl<<
            "Your mana is: "<<blue<<mana<<def<<"/"<<bluebold<<maxmana<<def<<endl<<
            "Gold: "<<yellow<<gold<<def<<endl;
    return 0;
}

