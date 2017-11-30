#include <time.h>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

//funkcja, która przestawia kursor konsoli w dowolne miejsce
void gotoxy( const int x, const int y )
{
    COORD coord = { x, y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

void HideCursor()
{
    ::HANDLE hConsoleOut =::GetStdHandle( STD_OUTPUT_HANDLE );
    ::CONSOLE_CURSOR_INFO hCCI;
    ::GetConsoleCursorInfo( hConsoleOut, & hCCI );
    hCCI.bVisible = FALSE;
    ::SetConsoleCursorInfo( hConsoleOut, & hCCI );
}

void Snake(){
int wysokosc, szerokosc, szybkosc;
char poziom=196,pion=179,gp=191,gl=218,dp=217,dl=192;
char waz=219,jedz=222,puste=0;
int wsplXweza,wsplYweza,wsplXjedz,wsplYjedz;
int dlugosc=4,historiaX[99999],historiaY[1000],ile=1,ile1=1;
int gora, dol, lewo, prawo,gora1=0,dol1=0,lewo1=0,prawo1=0;
char kierunek='l',zajete[70][70];
int przycisk;

    do{
    cout << "Podaj Wysokosc planszy z zakresu 5-22!" << endl;
    cin>>wysokosc;
    }while((wysokosc<5)||(wysokosc>22));
    do{
    cout << "Podaj Szerokosc planszy z zakresu 5-22!" << endl;
    cin>>szerokosc;
    }while((szerokosc<5)||(szerokosc>22));

    do{
    cout<<"Podaj szybkosc z jaka bedzie sie poruszal waz z zakresu 1-10!"<<endl;
    cin>>szybkosc;
    }while((szybkosc<0)&&(szybkosc>11));

    cout<<endl<<"Podaj przyciski jakimi bedziesz gral:"<<endl<<"GORA"<<endl;
    gora=getch();
    if(gora==224)gora+=getch();

    cout<<"DOL"<<endl;
    dol=getch();
    if(dol==224)dol+=getch();

    cout<<"LEWO"<<endl;
    lewo=getch();
    if(lewo==224)lewo+=getch();

    cout<<"PRAWO"<<endl;
    prawo=getch();
    if(prawo==224)prawo+=getch();

    system("cls");
    ///rysowanie planszy
    cout<<gl; ///gorna ramka
    for(int i=0;i<2*szerokosc;i++){
        cout<<poziom;
    }
    cout<<gp<<endl;

    for(int i=0;i<wysokosc;i++){ ///boczne ramki
        cout<<pion;
        for(int j=0;j<szerokosc;j++){
            cout<<"  ";
        }
        cout<<pion<<endl;
    }

    cout<<dl; ///dolna ramka
    for(int i=0;i<2*szerokosc;i++){
        cout<<poziom;
    }
    cout<<dp;
       ///Koniec rysowania ramki

srand(time(NULL));
wsplXweza=rand()%szerokosc+1; ///rozlosowanie pozycji wyjsciowej weza i jedzenia
wsplXweza=2*wsplXweza-1;
wsplYweza=rand()%wysokosc+1;
wsplXjedz=rand()%szerokosc+1;
wsplXjedz=2*wsplXjedz-1;
wsplYjedz=rand()%wysokosc+1;

    historiaX[0]=wsplXweza; ///pierwsze wartosci weza
    historiaY[0]=wsplYweza;



            HideCursor(); ///ukrycie kursora

    for(;;){ ///glowna petla programu

    if(ile>30){
        for(int i=0;i<dlugosc+1;i++)
        {
          historiaX[i]=historiaX[ile-dlugosc+i-1];
          historiaY[i]=historiaY[ile-dlugosc+i-1];
        }
        ile=dlugosc+1;
    }

    gotoxy(wsplXjedz,wsplYjedz); ///rysowanie jedzenia
    cout<<jedz<<jedz;
        if(ile>7){      ///warunek konca gry
        for(int i=0;i<dlugosc-1;i++){
            if((historiaX[ile-1]==historiaX[ile-2-i])&&(historiaY[ile-1]==historiaY[ile-2-i])){
            gotoxy(0,wysokosc+4);
            cout<<"KONIEC GRY! :("<<endl<<"Dlugosc weza: "<<dlugosc;
            Sleep(3000);
            cout<<endl<<endl<<endl<<"Po nacisnieciu dowolnego klawisza zostaniesz przeniesiony do menu";
            getch();
            goto koniec;
            }
        }
        }

        if(ile<5){
        for(int i=0;i<dlugosc;i++){ ///rysowanie weza
        gotoxy(historiaX[ile-i-1],historiaY[ile-i-1]);
        zajete[historiaX[ile-i-1]][historiaY[ile-i-1]]='z';
        cout<<waz<<waz;
        if((ile-i)==1)break;
        }
        }

        gotoxy(historiaX[ile-1],historiaY[ile-1]); ///rysowanie glowy weza
        zajete[historiaX[ile-1]][historiaY[ile-1]]='z';
        cout<<waz<<waz;

                if((historiaX[ile-1]==wsplXjedz)&&(historiaY[ile-1]==wsplYjedz)){ ///rysowanie jedzenia
                dlugosc++;
                for(;;){
                    wsplXjedz=rand()%szerokosc+1;
                    wsplXjedz=2*wsplXjedz-1;
                    wsplYjedz=rand()%wysokosc+1;
                    if(zajete[wsplXjedz][wsplYjedz]!='z'){
                            break;
                            }
                        }

                }

        Sleep(1100-100*szybkosc); ///szybkosc ruchu weza



        if(kbhit()){///zmiana kierunku
        przycisk=getch();
        if(przycisk==224)przycisk+=getch();
        if(przycisk==lewo&&(kierunek=='g'||kierunek=='d'))kierunek='l';
        if(przycisk==prawo&&(kierunek=='g'||kierunek=='d'))kierunek='p';
        if(przycisk==dol&&(kierunek=='p'||kierunek=='l'))kierunek='d';
        if(przycisk==gora&&(kierunek=='p'||kierunek=='l'))kierunek='g';
        }






        if(kierunek=='p'){historiaX[ile]=historiaX[ile-1]+2; historiaY[ile]=historiaY[ile-1];} ///nowa glowa weza
        if(kierunek=='l'){historiaX[ile]=historiaX[ile-1]-2; historiaY[ile]=historiaY[ile-1];}
        if(kierunek=='g'){historiaX[ile]=historiaX[ile-1]; historiaY[ile]=historiaY[ile-1]-1;}
        if(kierunek=='d'){historiaX[ile]=historiaX[ile-1]; historiaY[ile]=historiaY[ile-1]+1;}

        if(ile1>3){ ///ucinanie ogona
        gotoxy(historiaX[ile-dlugosc],historiaY[ile-dlugosc]);
        zajete[historiaX[ile-dlugosc]][historiaY[ile-dlugosc]]='e';
        cout<<puste<<puste;
        }
        if(historiaX[ile]==2*szerokosc+1&&kierunek=='p')historiaX[ile]=1;  ///przechodzenie przez sciany
        if(historiaX[ile]==-1&&kierunek=='l')historiaX[ile]=2*szerokosc-1;
        if(historiaY[ile]==wysokosc+1&&kierunek=='d')historiaY[ile]=1;
        if(historiaY[ile]==0&&kierunek=='g')historiaY[ile]=wysokosc;




    ile++;
    ile1++;

    }
    koniec:
cout<<'a';
}



int main()
{
    int wybor;
    int poprzedniWybor;
    bool wykonujPetle;

    //pêtla g³ówna programu
    while( 1 )
    {
        start:
        wybor = 0;
        poprzedniWybor = wybor;
        wykonujPetle = true;
            HideCursor(); ///ukrycie kursora

        //rysowanie menu
        system( "cls" );
        gotoxy( 3, 1 );
        cout << "Graj!";
        gotoxy( 3, 3 );
        cout << "Instrukcja";
        gotoxy( 3, 5 );
        cout << "Exit";
        gotoxy( 46, 10 );
        cout<<"Artur Szczypta "<<char(1);
        gotoxy( 46, 11 );
        cout<<"Kontakt: szczypta.artur@gmail.com";
        gotoxy( 46, 1);
        cout<<"Nacisnij strzalke w prawo";

        ///przesuwanie strzalki

        //przesuwanie strza³ki
        while( wykonujPetle )
        {
            //rysowanie strza³ki wyboru
            gotoxy( 1, wybor * 2 + 1 );
            cout << static_cast < char >( 16 );

            //obs³uga klawiatury
            poprzedniWybor = wybor;
            switch( getch() )
            {
            case 224: //STRZA£KI
                switch( getch() )
                {
                case 72: //strza³ka w górê
                    if( 0 < wybor ) wybor--;
                    else wybor = 2;

                    break;

                case 80: //strza³ka w dó³
                    if( wybor < 2 ) wybor++;
                    else wybor = 0;

                    break;

                case 77: //strza³ka w prawo
                    //je¿eli wciœniêto strza³kê w prawo, sprawdŸ wybran¹ opcjê i wykonaj odpowiedni¹ akcjê
                    switch( wybor )
                    {
                    case 0:
                        system("cls");
                        Snake();
                        getch();
                        goto start;
                        break;

                    case 1:
                     //   OpcjaB();
                        break;

                    case 2:
                        return 0;
                    }
                }
                break;
            }

            //czyszczenie strza³ki wyboru
            gotoxy( 1, poprzedniWybor * 2 + 1 );
            cout << " ";
        }
    }
    return 0;
}
