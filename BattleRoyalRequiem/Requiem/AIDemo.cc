/* ****************************************************************** */
/* IMPORTANT! Write here the name of your player.                     */
/* ****************************************************************** */

#define NAMEPLAYER Demo


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

        void fes_torn() {
            // Escull una direcció inicial entre EST, SE, i SUD.
            if (torn_actual()==1) dir = 1 + random(3);

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



