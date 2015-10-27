/* ****************************************************************** */
/* IMPORTANT! Write here the name of your player.                     */
/* ****************************************************************** */

#define NAMEPLAYER start


/* ****************************************************************** */
/* Add any standard header you need here.                             */
/* ****************************************************************** */

#include "aibase.h"                           // Do not change this line
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


namespace NAMEPLAYER {                        // Do not change this line


    /* ************************************************************** */
    /* IMPORTANT! Do not use global variables.                        */
    /* However, it is okay to define const variables, functions       */
    /* typedefs, or structs/classes. Please do it here.               */
    /* ************************************************************** */


    struct AIstruct: public AIbase {          // Do not change this line

        #include "initializer.h"              // Do not change this line


        /* ********************************************************** */
        /* Implement the function 'fes_torn' here.                    */
        /* ********************************************************** */
		

        int dir;
		
		struct Paja{
			//Identificador del campesino
			int id;
			//Posicion del campesino
			pair<int,int> posicion;
			// 1 si debe de huir, 0 si no hay amenazas
			int huir;
        };
        
        struct Soldier{
			//Identificador del soldado
			int id;
			//Posicion del soldado
			pair<int,int> posicion;
			//1 si debe de perseguir, 0 si no hay victimas cerca
			int hunt;
			// 1 si debe descansar, 0 si tiene suficiente vida
			int res;
			//Vida del soldado
			int vida;
		};
		
		typedef map<int,Paja>::iterator Itcamp;
		typedef map<int,Soldier>::iterator Itsold;


		
		//Mapa de Campesinos
		map<int,Paja> Campesinos;
		
		//Map de Caballeros
		map<int,Soldier> Caballeros;
		
		void turno_1(){
			vector<int> pag = pagesos(1);
			for(int i=0; i< (int)pag.size(); ++i){
				/*
				Un t_robot es un struct amb diversos camps de tipus enter: id (identificador),
				i, j (la posicio actual), model (1 per als pagesos, 2 per als cavallers),
				equip (entre 1 i 4), i vida (els punts de vida, que sempre son 0 per
				als pagesos, i estan entre 1 i 400 per als cavallers). Un robot “nul” te tots
				els camps a -1.
				*/
				t_robot aux= robot(i);
				Paja c;
				c.id=aux.id;
				pair<int, int> pos;
				pos.first=aux.i;
				pos.second=aux.j;
				c.posicion=pos;
				c.huir=0;
				Campesinos.insert( std::pair<int,Paja>(aux.id,c));
			}
			vector<int> cav = cavallers(1);
			for(int i=0; i< (int)cav.size(); ++i){
				/*
				Un t_robot es un struct amb diversos camps de tipus enter: id (identificador),
				i, j (la posicio actual), model (1 per als pagesos, 2 per als cavallers),
				equip (entre 1 i 4), i vida (els punts de vida, que sempre son 0 per
				als pagesos, i estan entre 1 i 400 per als cavallers). Un robot “nul” te tots
				els camps a -1.
				*/
				t_robot aux= robot(i);
				Soldier c;
				c.id=aux.id;
				pair<int, int> pos;
				pos.first=aux.i;
				pos.second=aux.j;
				c.posicion=pos;
				c.hunt=0;
				c.vida=aux.vida;
				c.res=0;
				Caballeros.insert( std::pair<int, Soldier>(aux.id,c));

			}
		}

        void fes_torn() {
            // Escull una direcció inicial entre EST, SE, i SUD.
            if (torn_actual()==1) turno_1();//dir = 1 + random(3);

            // Pintors: cap a dir
            vector<int> pag = pagesos(1); //1: el meu equip
            for (int i = 0; i < (int)pag.size(); ++i) {
                ordena(pag[i], dir);
            }

            // Soldats: direcció a l'atzar
            vector<int> cav = cavallers(1);
            for (int i = 0; i < (int)cav.size(); ++i) {
                ordena(cav[i], 1 + random(8));
            }
        }


  };                                          // Do not change this line
  AIstruct::Static_Initializer init;          // Do not change this line
};                                            // Do not change this line



