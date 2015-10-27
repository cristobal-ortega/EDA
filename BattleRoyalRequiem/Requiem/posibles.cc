/* ****************************************************************** */
/* IMPORTANT! Write here the name of your player.                     */
/* ****************************************************************** */

#define NAMEPLAYER yeah


/* ****************************************************************** */
/* Add any standard header you need here.                             */
/* ****************************************************************** */

#include "aibase.h"                           // Do not change this line
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
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

		
			
		
		bool comprobar_orientacion(queue<pair<int,int> >& cola,vector< vector<int> >& map,int x,int y,int i,int j,int& direccion){
			if(color(x+i,y+j)!=1){
				direccion=map[x][y];
				return true;
			}
			else{
				map[x+i][y+j]=map[x][y];
				pair<int,int> next;
				next.first=x+i;
				next.second=y+j;
				cola.push(next);
				return false;
			}
		}	
			
		int bfs1(int id,int i, int j){
			vector< vector<int> > map(50,vector<int>(50,0));
			queue< pair <int,int> > cola;
			map[i][j]=-1;
			bool libre=false;
			int direccion;
			bool begin=true;
			

			map[i][j+1] = 1;
			if((color(i,j+1)!=-1) and (robot(i,j+1).id == -1))cola.push(pair<int,int>(i,j+1));

			map[i+1][j+1] = 2;
			if((color(i+1,j+1)!=-1) and (robot(i+1,j+1).id == -1))cola.push(pair<int,int>(i+1,j+1));
			
			map[i+1][j]=3;
			if((color(i+1,j)!=-1) and (robot(i+1,j).id == -1))cola.push(pair<int,int>(i+1,j));
			
			map[i+1][j-1]=4;
			if((color(i+1,j-1)!=-1) and (robot(i+1,j-1).id == -1))cola.push(pair<int,int>(i+1,j-1));
			
			map[i][j-1]=5;
			if((color(i,j-1)!=-1) and (robot(i,j-1).id == -1))cola.push(pair<int,int>(i,j-1));
			
			map[i-1][j-1]=6;
			if((color(i-1,j-1)!=-1) and (robot(i-1,j-1).id == -1))cola.push(pair<int,int>(i-1,j-1));	
						
			map[i-1][j] = 7;
			if((color(i-1,j)!=-1) and (robot(i-1,j).id == -1))cola.push(pair<int,int>(i-1,j));
			
			map[i-1][j+1] = 8;
			if((color(i-1,j+1)!=-1) and (robot(i-1,j+1).id == -1))cola.push(pair<int,int>(i-1,j+1));

			
			while( not libre and not cola.empty()){
				pair<int,int> actual;
				actual = cola.front();
				int x= actual.first; int y=actual.second;
				//Camino libre

				bool este=false;
				este = (color(x,y+1)!=-1) and (robot(x,y+1).id == -1) and map[x][y+1]==0;
				bool se=false;
				se = (color(x+1,y+1)!=-1) and (robot(x+1,y+1).id == -1) and map[x+1][y+1]==0;
				bool sud=false;
				sud = (color(x+1,y)!=-1) and (robot(x+1,y).id == -1) and map[x+1][y]==0;
				bool so=false;
				so = (color(x+1,y-1)!=-1) and (robot(x+1,y-1).id == -1) and map[x+1][y-1]==0;
				bool oeste=false;
				 oeste = (color(x,y-1)!=-1) and (robot(x,y-1).id == -1) and map[x][y-1]==0;
				bool no=false;
				no = (color(x-1,y-1)!=-1) and (robot(x-1,y-1).id == -1) and map[x-1][y-1]==0;
				
				bool norte=false;
				norte = (color(x-1,y)!=-1) and (robot(x-1,y).id == -1) and map[x-1][y]==0;
				bool ne=false;
				ne = (color(x-1,y+1)!=-1) and (robot(x-1,y+1).id == -1) and map[x-1][y+1]==0;


				if(norte and not libre) libre = comprobar_orientacion(cola,map,x,y,-1,0,direccion);
				/*if(norte){
					if(color(x-1,y)!=1){
						 libre=true;
						 direccion=map[x][y];
					}
					else{
						map[x-1][y]=map[x][y];
						pair<int,int> next;
						next.first=x-1;
						next.second=y;
						cola.push(next);
					}
				}*/
				if(ne and not libre) libre=comprobar_orientacion(cola,map,x,y,-1,1,direccion);
				/*if(ne and not libre){
					if(color(x-1,y+1)!=1){
						 libre=true;
							direccion=map[x][y];
					 }
					else{
						map[x-1][y+1]=map[x][y];
						pair<int,int> next;
						next.first=x-1;
						next.second=y+1;
						cola.push(next);
					}
				}*/
				if(este and not libre) libre=comprobar_orientacion(cola,map,x,y,0,1,direccion);
				/*if(este and not libre){
					if(color(x,y+1)!=1){
						 libre=true;
						 direccion=map[x][y];
					 }
					 else{
						map[x][y+1]=map[x][y];
						pair<int,int> next;
						next.first=x;
						next.second=y+1;
						cola.push(next);
					}
				}*/
				if(se and not libre) libre = comprobar_orientacion(cola,map,x,y,1,1,direccion);
				/*if(se and not libre){
					if(color(x+1,y+1)!=1){
						 libre=true;
						 direccion=map[x][y];
					 }
					else{
						map[x+1][y+1]=map[x][y];
						pair<int,int> next;
						next.first=x+1;
						next.second=y+1;
						cola.push(next);
					}
				}*/
				if(sud and not libre) libre = comprobar_orientacion(cola,map,x,y,1,0,direccion);
				/*if(sud and not libre){
					if(color(x+1,y)!=1){
						 libre=true;
						 direccion=map[x][y];
					 }
					else{
						map[x+1][y]=map[x][y];
						pair<int,int> next;
						next.first=x+1;
						next.second=y;
						cola.push(next);
					}
				}*/
				if(so and not libre) libre=comprobar_orientacion(cola,map,x,y,1,-1,direccion);
				/*if(so and not libre){
					if(color(x+1,y-1)!=1){
						 libre=true;
						 direccion=map[x][y];
					 }
					else{
						map[x+1][y-1]=map[x][y];
						pair<int,int> next;
						next.first=x+1;
						next.second=y-1;
						cola.push(next);
					}
				}*/
				if(oeste and not libre) libre=comprobar_orientacion(cola,map,x,y,0,-1,direccion);
				/*if(oeste and not libre){
					if(color(x,y-1)!=1){
						 libre=true;
						 direccion=map[x][y];
					 }
					else{
						map[x][y-1]=map[x][y];
						pair<int,int> next;
						next.first=x;
						next.second=y-1;
						cola.push(next);
					}
				}*/
				if(no and not libre) libre=comprobar_orientacion(cola,map,x,y,-1,-1,direccion);
				/*if(no and not libre){
					if(color(x-1,y-1)!=1){
						 libre=true;
						 direccion=map[x][y];
					 }
					else{
						map[x-1][y-1]=map[x][y];
						pair<int,int> next;
						next.first=x-1;
						next.second=y-1;
						cola.push(next);
					}
				}*/
				cola.pop();
			}
			return direccion;
		}		
			
			
			
			
			



        void fes_torn() {

            vector<int> pag = pagesos(1); //1: el meu equip
            for (int i = 0; i < (int)pag.size(); ++i) {
				t_robot r = robot(pag[i]);
				bool done = ordena(pag[i],bfs1(r.id,r.i,r.j));
				/*if( not done) {
					cerr << "OJITO CABRON, ID: "<<pag[i]<<"ESTA EN "<< robot(pag[i]).j << " "<< robot(pag[i]).i <<endl;
				}*/
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

























			/*map[i][j+1] = -1;
			if((color(i,j+1)!=-1){
				if (robot(i,j+1).id != -1))encontrado=robot(i,j+1).id;
				else cola.push(pair<int,int>(i,j+1));
			}

			map[i+1][j+1] = -1;
			if((color(i+1,j+1)!=-1){
				if(robot(i+1,j+1).id != -1)) encontrado=robot(i,j+1).id;
				else cola.push(pair<int,int>(i+1,j+1));
			}
			
			map[i+1][j]=-1;
			if((color(i+1,j)!=-1) and (robot(i+1,j).id != -1))cola.push(pair<int,int>(i+1,j));
			
			map[i+1][j-1]=-1;
			if((color(i+1,j-1)!=-1) and (robot(i+1,j-1).id != -1))cola.push(pair<int,int>(i+1,j-1));
			
			map[i][j-1]=-1;
			if((color(i,j-1)!=-1) and (robot(i,j-1).id != -1))cola.push(pair<int,int>(i,j-1));
			
			map[i-1][j-1]=-1;
			if((color(i-1,j-1)!=-1) and (robot(i-1,j-1).id != -1))cola.push(pair<int,int>(i-1,j-1));	
						
			map[i-1][j] = -1;
			if((color(i-1,j)!=-1) and (robot(i-1,j).id != -1))cola.push(pair<int,int>(i-1,j));
			
			map[i-1][j+1] = -1;
			if((color(i-1,j+1)!=-1) and (robot(i-1,j+1).id != -1))cola.push(pair<int,int>(i-1,j+1));
			*/

----------
			inicio(cola,map,i,j+1);
			inicio(cola,map,i+1,j+1);
			inicio(cola,map,i+1,j);
			inicio(cola,map,i+1,j-1);
			inicio(cola,map,i+1,j-1);
			inicio(cola,map,i,j-1);
			inicio(cola,map,i-1,j-1);
			inicio(cola,map,i-1,j);
			inicio(cola,map,i-1,j+1);
			
			
					void inicio(queue< pair<int,int> > cola, vector< vector<int> >& map, i,j){
			if((color(i,j)!=-1))
				if(robot(i,j).id==-1){
					if(color(i,j)!=1) return 1;
					else{ 
						map[i][j] == 1;
						cola.push(pair<int,int>(i,j));
					}
				}
				else map[i][j] == -1;
			}	
		}
