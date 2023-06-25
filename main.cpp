//
//  main.cpp
//  prisera_bludiste
//
/*V bludišti reprezentovaném maticí políček se nachází příšera. Příšera je v každém kroku na jednom políčku a je otočená jedním ze čtyř možných směrů - nahoru, doprava, dolů nebo doleva.
 
 V každém kroku výpočtu příšera udělá jeden tah, možné tahy jsou: otočit se doprava, otočit se doleva nebo postoupit kupředu, tj. přejít na sousední políčko ve směru otočení. Na začátku má příšera po pravé ruce zeď a pohybuje se tak, aby pravou rukou stále sledovala tuto zeď (viz příklad).

 Vstup programu obsahuje nejdříve šířku a výšku a potom mapu bludiště. Jednotlivé znaky představují jednotlivá políčka mapy: 'X' znamená zeď, '.' znamená volné políčko a znaky '^', '>', 'v' nebo '<' znamenají volné políčko, na kterém právě teď stojí příšera, otočená směrem nahoru, doprava, dolů nebo doleva, v tomto pořadí.

 Program načte popis bludiště a potom dvacetkrát pohne příšerou a po každém pohybu vytiskne mapu bludiste ve stejném tvaru, jako ji načetl. Výpis mapy bude vždy ukončen prázdným řádkem.

 Proveďte objektový návrh a ten implementujte.

 Pozor: První vypsaná poloha a orientace je až po prvním tahu příšery!
 Vstup:   10
    6
    XXXXXXXXXX
    X....X...X
    X....X...X
    X.X..X.X.X
    X.X.>..X.X
    XXXXXXXXXX*/
//  Created by Natálie Smolíková on 02.12.2021.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>


class Bludiste{
public:
    int sirka, vyska; // př 3x4
    char *bl;
    
    void vytvor_pole(){
        bl = (char*)malloc(sizeof(char)*vyska*sirka);
    }
    
    void getdata(){
        for(int j=0; j< vyska;j++)
        {
            for (int i=0;i<sirka;i++)
                std::cin>>bl[j*sirka+i];
        }
        
    }
    void vypis(){
        int it = 0;
        for (int j = 0;j<vyska;j++)
            { for (int i=0;i<sirka;i++)
                { printf("%c", bl[j*sirka+i]);
                    it++;
                    if (it%sirka == 0)
                        printf("\n");
                }
            
            
            }
        printf("\n");
                
        }
    
};
    

class Prisera{
public:
    int posx, posy;
    char smer;
    int it;
    Bludiste *maze;
    Prisera(Bludiste *m){
       maze = m;
    };
    
   
    void zjisti_pos(){
        for (int j=0; j<(this -> maze->vyska); j++)
        {
            for(int i=0; i< (this ->maze ->sirka);i++)
            {if (maze->bl[j* (this -> maze->sirka) + i] == '>')
            {       posx =i;
                    posy =j;
                    smer = '>';
                    
                }
            if (maze->bl[j* (this -> maze->sirka) + i] =='<')
            {
                posx =i;
                posy =j;
                smer = '<';
            }
            if(maze->bl[j*(this -> maze->sirka) + i] =='v')
            {
                posx =i;
                posy =j;
                smer = 'v';
            }
            if(maze->bl[j* (this -> maze->sirka) + i] =='^')
            {
                posx =i;
                posy =j;
                smer = '^';
            }
            }
                }
            
        }
    int otoceno() {
      return 1;
    }
    void otoc_doprava(){
        if (smer == '>')
            smer = 'v';
        else if (smer == '<')
            smer = '^';
        else if (smer == 'v')
            smer = '<';
        else if (smer == '^')
            smer = '>';
        maze->bl[posy*(this -> maze->sirka) + posx] = smer;
        
    }
    void otoc_doleva(){
        if (smer == '>')
            smer = '^';
        else if (smer == '<')
            smer = 'v';
        else if (smer == 'v')
            smer = '>';
        else if (smer == '^')
            smer = '<';
        maze->bl[posy*(this -> maze->sirka) + posx] = smer;

    }
    void posun(){
        if (smer == '>')
        {   maze->bl[posy*(this -> maze->sirka)+ posx] ='.';
            posx +=1;
            maze->bl[posy*(this -> maze->sirka) + posx] = '>';
        }
        if (smer == '<')
        {       maze->bl[posy*(this -> maze->sirka) + posx] ='.';
                posx -=1;
                maze->bl[posy*(this -> maze->sirka) + posx] = '<';
        }
        if (smer == 'v')
            {       maze->bl[posy*(this -> maze->sirka) + posx] ='.';
                    posy +=1;
                    maze->bl[posy*(this -> maze->sirka) + posx] = 'v';
            }
        if (smer == '^')
        {       maze->bl[posy*(this -> maze->sirka) + posx] ='.';
                posy -=1;
                maze->bl[posy*(this -> maze->sirka) + posx] = '^';
        }
    
    }
    void kontrola() {
        if (smer == '>')
        {
            if ((maze->bl[(posy +1)*(this -> maze->sirka) + posx] == 'X')|| it)
            {   if (maze->bl[posy*(this -> maze->sirka) + posx+1] == '.')
                {
                    posun();
                    it = 0;
                }
                else {
                    otoc_doleva();
                    it =otoceno();
                }
            }
            else { otoc_doprava();
                it =otoceno();
            }
        }
        else if (smer == '<') {
            if ((maze->bl[(posy -1)*(this -> maze->sirka) + posx] == 'X')||it)
            {   if (maze->bl[posy*(this -> maze->sirka) + posx-1] == '.')
                {
                    posun();
                    it = 0;
                }
                else {
                    otoc_doleva();
                   it = otoceno();
                    
                }
            }
            else { otoc_doprava();
                it =otoceno();
            }
        }
       else if (smer == 'v'){
            if ((maze->bl[posy*(this -> maze->sirka) + posx-1] == 'X')|| it) //
            {   if (maze->bl[(posy+1)*(this -> maze->sirka) + posx] == '.')
                {
                    posun();
                    it = 0;
                    
                }
                else {
                    otoc_doleva();
                   it = otoceno();
                }
            }
            else { otoc_doprava();
               it = otoceno();
            }
        }
        else if (smer == '^') {
            if ((maze->bl[posy *(this -> maze->sirka) + posx+1] == 'X')|| it)
            {   if (maze->bl[(posy-1)*(this -> maze->sirka) + posx] == '.')
                {
                    posun(); it = 0;
                }
                else {
                    otoc_doleva();
                    it =otoceno();
                }
            }
            else { otoc_doprava();
                it = otoceno();
            }
        }
    }
    
    
    
    
};

int main() {
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);
    Bludiste* maze = new Bludiste();

    Prisera* beast = new Prisera(maze);
    maze->sirka =x;
    maze->vyska = y;
    maze->vytvor_pole();
    maze->getdata();
        
    beast->zjisti_pos();
    
    
    for (int i= 0; i<20;i++)
    {  beast->kontrola();
        maze->vypis();
        
    }
    return 0;
}
