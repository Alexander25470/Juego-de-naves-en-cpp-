#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <list>
#include <iostream>


using namespace std;

#define arriba 72
#define izquierda 75
#define derecha 77
#define abajo 80
#define ENTER 13

void gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hCon, dwPos);
    printf;
}
void eliminarCosito(){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize=100; //tama�o del cursor
    cci.bVisible=FALSE; //hace lo que dice su nombre
    SetConsoleCursorInfo(hCon, &cci); //hay que usar un & antes del parametro del cursor
}
class COSO{
int x,y;
int health;
int lifes;
public:
    COSO(int _x, int _y, int _health, int _lifes);
    int x_navePublica(){return x;}
    int y_navePublica(){return y;}
    int lifes_pub(){return lifes;}
    void dibujar();//dibuja la nave
    void borrar();//borra la nave
    void mover();//mueve la nave
    void dibujar_vida();
    void perder_vida();
    void perder_health();
};
COSO::COSO(int _x, int _y, int _health, int _lifes){
x=_x;
y=_y;
health=_health;
lifes=_lifes;
};
 void COSO::perder_health(){
     health--;
    }


class COSOSQUECAEN{
    int x,y;
public:
    COSOSQUECAEN(int _x, int _y):x(_x),y(_y){}
        void pintar();
        void mover();
        void chocar(class COSO &cosita);
        int x_cosopub(){return x;}
        int y_cosopub(){return y;}

};
void COSOSQUECAEN::chocar(class COSO &cosita){
    if(x>=cosita.x_navePublica()&& x<=cosita.x_navePublica()+2 && y>=cosita.y_navePublica() && y<=cosita.y_navePublica()+1){
        //Sleep(500);
        cosita.perder_health();
        cosita.borrar();
        cosita.dibujar();
        cosita.dibujar_vida();
        x=rand()%76+2;
        y=2;

    }
}

void COSOSQUECAEN::pintar(){
    gotoxy(x,y);printf("*");
}

void COSOSQUECAEN::mover(){
    gotoxy(x,y);printf(" ");
    y++;
    if(y>32){
        x=rand()%76+2;
        y=2;
    }
    pintar();
}


void COSO::dibujar(){
    gotoxy(x,y);printf(" %c", 94);
    gotoxy(x,y+1);printf("%c%c%c", 201,202,187);
};
void COSO::borrar(){
    gotoxy(x,y);printf("   ");
    gotoxy(x,y+1);printf("   ");
};
void COSO::mover(){
    if(kbhit()){
            borrar();
            char tecla=getch();
            if(tecla==0)tecla=getch();

            if((tecla==97 || tecla==izquierda)&& x>2){x--;};       //a=97
            if((tecla==100 || tecla==derecha)&& x<75){x++;};        //d=100
            if((tecla==119 || tecla==arriba)&& y>2){y--;};          //w=119
            if((tecla==115 || tecla==abajo) && y<31){y++;};         //s=115
            if(tecla=='e' || tecla=='E')health--;
            dibujar();
            dibujar_vida();


        };
};
void pintar_bordes(){
    for(int i=2;i<78;i++){
        gotoxy(i,1); printf("%c",205);
        gotoxy(i,33); printf("%c",205);

    };
    for(int i=2;i<33;i++){
        gotoxy(1,i); printf("%c",186);
        gotoxy(78,i); printf("%c",186);
    };
    gotoxy(1,1); printf("%c",201);
    gotoxy(1,33); printf("%c",200);
    gotoxy(78,1); printf("%c",187);
    gotoxy(78,33); printf("%c",188);
};
void COSO::perder_vida(){
    if(health==0){
       borrar();


        gotoxy(x-1,y);printf(" **");
        gotoxy(x-1,y+1);printf("****");
        Sleep(300);

        borrar();
        gotoxy(x-3,y);printf("   * * ");
        gotoxy(x-3,y+1);printf(" * * * * ");

        Sleep(300);
        gotoxy(x-3,y);printf("      ");
        gotoxy(x-3,y+1);printf("         ");

        gotoxy(x-3,y);printf("Te moriste");
        Sleep(300);
        gotoxy(x-3,y);printf("          ");

        lifes--;
        health=3;
        dibujar_vida();
        dibujar();
    }
}

void COSO::dibujar_vida(){
    gotoxy(50,0);printf("Vidas: %d", lifes);
    gotoxy(65,0);printf("Health: ");
    gotoxy(73,0);printf("   ");
    for(int i=0;i<health;i++){
        gotoxy(72+i,0);printf("%c",229);
    }
}

class BALA{
    int x,y;
public:
    BALA(int _x, int _y):x(_x),y(_y){}
    int x_balapub(){return x;}
    int y_balapub(){return y;}
    void mover();
    bool limite();
};
void BALA::mover(){
    gotoxy(x,y);printf(" ");
    y--;
    gotoxy(x,y);printf("%c",94);
}
bool BALA::limite(){
    if(y==2) return true;
    return false;
}
void finalJuego(){
    system("cls");
    pintar_bordes();
    gotoxy(33,16);printf("Fin del juego");
    gotoxy(25,17);system("pause");
};
void prepararJuego();
void juego();
int menu();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------ACA-EST�-EL-MAIN-----------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(){



   system("color 06");
    system("mode con: cols=80 lines=35");
menu();

if( menu()==11 ){
    juego();
finalJuego();

}






    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------ACA-EST�-EL-MAIN-----------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void juego(){
    COSO cosa1(38,20,3,3);
    cosa1.dibujar();
    cosa1.dibujar_vida();


    list<COSOSQUECAEN*>A;
    list<COSOSQUECAEN*>::iterator itCosito;
    for(int i=0; i<5;i++){
        A.push_back(new COSOSQUECAEN( rand()%76+2,rand()%20+4  ));
    }


    int puntos=0;


    list<BALA*>B;
    list<BALA*>::iterator it;
    bool game_over=false;
    while(!game_over){

    gotoxy(1,0); printf("Puntos: %d", puntos);

            if(kbhit()){
                 char tecla=getch();
                 if((tecla=='v' || tecla=='V')){
                    B.push_back(new BALA(cosa1.x_navePublica()+1, cosa1.y_navePublica()-1));

                 }

            };
            for(it=B.begin();it!=B.end();it++){
                (*it)->mover();
                if((*it)->limite() ){
                    gotoxy( (*it)->x_balapub(),(*it)->y_balapub() );printf(" ");
                    delete(*it);
                    it = B.erase(it);
                }
            }

            for(itCosito=A.begin();itCosito!=A.end();itCosito++){
                (*itCosito)->mover();
                (*itCosito)->chocar(cosa1);
            }

            for(itCosito=A.begin();itCosito!=A.end();itCosito++){
                for(it=B.begin();it!=B.end();it++){
                        if( (*itCosito)->x_cosopub()==(*it)->x_balapub()&&( (*itCosito)->y_cosopub()==(*it)->y_balapub() || (*itCosito)->y_cosopub()+1==(*it)->y_balapub() ) ){

                            gotoxy((*it)->x_balapub(),(*it)->y_balapub());printf(" "); //elimina la bala de pantalla
                            delete(*it);
                            it = B.erase(it); //elimina la bala de la lista

                            A.push_back(new COSOSQUECAEN( rand()%76+2,rand()%20+4  ));
                             gotoxy((*itCosito)->x_cosopub(),(*itCosito)->y_cosopub());printf(" ");
                             delete(*itCosito);
                             itCosito=A.erase(itCosito);

                            puntos++;

                        }
                }

            }


        if(cosa1.lifes_pub()==0){
            game_over=true;
        }

        cosa1.perder_vida();
        cosa1.mover();

        Sleep(30);
    }
};
void prepararJuego(){


    eliminarCosito();
    pintar_bordes();

};
int menu(){

    prepararJuego();

    gotoxy(2,3);printf("Presione la tecla ENTER para iniciar el juego \n");
    gotoxy(2,5);printf("Presione la tecla I para ver las instrucciones");
    gotoxy(2,7);printf("Presione otra tecla para salir \n");
    char tecla=getch();
     if(tecla==ENTER){
        system("cls");
        prepararJuego();
        return 11;
    }else{
        if(tecla=='i'){
            gotoxy(2,3);printf("Presione las teclas de flechas para moverse          ");
            gotoxy(2,5);printf("Presione la v para disparar                            ");
            gotoxy(2,7);printf("Presione la tecla e para perder uno de salud");
            gotoxy(2,9);system("pause");
            return 11;
        }
    }





};
