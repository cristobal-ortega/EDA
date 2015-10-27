/* ****************************************************************** */
/* IMPORTANT! Write here the name of your player.                     */
/* ****************************************************************** */

#define NAMEPLAYER Demo_1


/* ****************************************************************** */
/* Add any standard header you need here.                             */
/* ****************************************************************** */

#include "aibase.h"                           // Do not change this line
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
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

		map<int,int> dfs;
		typedef map<int,int>::iterator Iterator;
        int dir;
        //bool atacar;

		bool comprobar_enemigo(queue<pair<int,int> >& cola,vector< vector<int> >& map,int x,int y,int i,int j,int& direccion){
			if( existeix(x+i,y+j) ){
				t_robot r = robot(x+i,y+j);
				//cerr << "CREO EL ROBOT A COMPARAR"<<endl;
				if(r.equip!=-1){
					if(r.equip!=1){
						//cerr << "ENCONTRE TARGET"<<endl;
						direccion=map[x][y];
						return true;
					}
					else{
						//cerr << "es de mi equipo"<<endl;
						 map[x+i][y+j]=-1;
						 //cerr << "cabron"<<endl;
						 return false;
					 }
				}
			}
			map[x+i][y+j]=map[x][y];
			pair<int,int> next;
			next.first=x+i;
			next.second=y+j;
			cola.push(next);
			//cerr<< "AVANZO 2"<<endl;
			return false;
			
		}	



		int bfs2(int id,int min, int max){
			vector< vector<int> > map(50,vector<int>(50,0));
			t_robot r=robot(id);
			int i=r.i; int j=r.j;
			if(i>=max and j>=max) return 6;
			else if(i>=max) return 7;
			else if(j>=max) return 5;
			queue< pair <int,int> > cola;
			//cola.push(pair<int,int>(i,j));
			map[i][j]=-1;
			bool libre=false;
				if((color(i,j+1)!=-1)){
					if(existeix(i,j+1)){
						if(robot(i,j+1).equip!=1) return 1;
						else map[i][j+1] = -1;
					}
					else{
						map[i][j+1] = 1;
						cola.push(pair<int,int>(i,j+1));
					}
				}
				
				if((color(i+1,j+1)!=-1)){
					if(existeix(i+1,j+1)){
						if(robot(i+1,j+1).equip!=1) return 2;
						else map[i+1][j+1] = -1;
					}
					else{
						map[i+1][j+1] = 2;
						cola.push(pair<int,int>(i+1,j+1));
					}
				}
				
				if((color(i+1,j)!=-1)){
					if(existeix(i+1,j)){
						if(robot(i+1,j).equip!=1) return 3;
						else map[i+1][j] = -1;
					}
					else{
						map[i+1][j] = 3;
						cola.push(pair<int,int>(i+1,j));
					}
				}
				
				if((color(i+1,j-1)!=-1)){
					if(existeix(i+1,j-1)){
						if(robot(i+1,j-1).equip!=1) return 4;
						else map[i+1][j-1] = -1;
					}
					else{
						map[i+1][j-1] = 4;
						cola.push(pair<int,int>(i+1,j-1));
					}
				}
				
				if((color(i,j-1)!=-1)){
					if(existeix(i,j-1)){
						if(robot(i,j-1).equip!=1) return 5;
						else map[i][j-1] = -1;
					}
					else{
						map[i][j-1] = 5;
						cola.push(pair<int,int>(i,j-1));
					}
				}
				
				if((color(i-1,j-1)!=-1)){
					if(existeix(i-1,j-1)){
						if(robot(i-1,j-1).equip!=1) return 6;
						else map[i-1][j-1] = -1;
					}
					else{
						map[i-1][j-1] = 6;
						cola.push(pair<int,int>(i-1,j-1));
					}
				}
				
				if((color(i-1,j)!=-1)){
					if(existeix(i-1,j)){
						if(robot(i-1,j).equip!=1) return 7;
						else map[i-1][j] = -1;
					}
					else{
						map[i-1][j] = 7;
						cola.push(pair<int,int>(i-1,j));
					}
				}
				
				if((color(i-1,j+1)!=-1)){
					if(existeix(i-1,j+1)){
						if(robot(i-1,j+1).equip!=1) return 8;
						else map[i-1][j+1] = -1;
					}
					else{
						map[i-1][j+1] = 8;
						cola.push(pair<int,int>(i-1,j+1));
					}
				}
			

			int res=9;
			int it=0;
			while(not libre and not cola.empty()){
				//cerr << "ENTRO EN EL WHILE"<<endl;
				pair<int,int> aux = cola.front();
				cola.pop();
				int x=aux.first; int y=aux.second;
				if(x<max and y<max and x>min and y>min){
					bool este = ((color(x,y+1)!=-1) and map[x][y+1]==0);
					bool se = ((color(x+1,y+1)!=-1) and map[x+1][y+1]==0);
					bool sur = ((color(x+1,y)!=-1) and map[x+1][y]==0);
					bool so = ((color(x+1,y-1)!=-1) and map[x+1][y-1]==0);
					bool oeste = ((color(x,y-1)!=-1) and map[x][y-1]==0);
					bool no = ((color(x-1,y-1)!=-1) and map[x-1][y-1]==0);
					bool norte = ((color(x-1,y)!=-1 and map[x-1][y]==0));
					bool ne = ((color(x-1,y+1)!=-1 and map[x-1][y+1]==0));
					//cerr << "BOOLEANOS CREADOS"<<endl;
					
					if(este) libre=comprobar_enemigo(cola,map,x,y,0,1,res);
					if(se and not libre) libre = comprobar_enemigo(cola,map,x,y,1,1,res);
					if(sur and not libre)  libre = comprobar_enemigo(cola,map,x,y,1,0,res);
					if(so and not libre)  libre = comprobar_enemigo(cola,map,x,y,1,-1,res);
					if(oeste and not libre)  libre = comprobar_enemigo(cola,map,x,y,0,-1,res);
					if(no and not libre) libre = comprobar_enemigo(cola,map,x,y,-1,-1,res);
					if(norte and not libre)  libre = comprobar_enemigo(cola,map,x,y,-1,0,res);
					if(ne and not libre)  libre = comprobar_enemigo(cola,map,x,y,-1,1,res);
					//cerr << "FINAL DE COMPROBACIONES"<<endl;
					++it;
					//if(it>800) return 1+random(8);
				}
			}
			return res;
			/*if(res==0) return random(8)+1;
			else return res;*/
			
		}








		bool comprobar_casilla(queue<pair<int,int> >& cola,vector< vector<int> >& map,int x,int y,int i,int j,int& direccion){
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

		int bfs(int id, int min, int max){
			vector< vector<int> > map(50,vector<int>(50,0));
			t_robot r=robot(id);
			if(r.id==-1) return 0;
			int i=r.i; int j=r.j;
			queue< pair <int,int> > cola;
			if(i>=max and j>=max) return 6;
			else if(i>=max) return 7;
			else if(j>=max) return 5;
			bool libre=false;
			int res=9;
			if(i>0 and i<49 and j>0 and j<49){
				if((color(i,j+1)!=-1)){
					if(not existeix(i,j+1)){
						if(color(i,j+1)!=1) return 1;
						else{ 
							map[i][j+1] = 1;
							cola.push(pair<int,int>(i,j+1));
						}
					}
					else map[i][j+1] = -1;
				}
				
				if((color(i+1,j+1)!=-1)){
					if(not existeix(i+1,j+1)){
						if(color(i+1,j+1)!=1) return 2;
						else{ 
							map[i+1][j+1] = 2;
							cola.push(pair<int,int>(i+1,j+1));
						}
					}
					else map[i+1][j+1] = -1;
				}
				
				if((color(i+1,j)!=-1)){
					if(not existeix(i+1,j)){
						if(color(i+1,j)!=1) return 3;
						else{ 
							map[i+1][j] = 3;
							cola.push(pair<int,int>(i+1,j));
						}
					}
					else map[i+1][j] = -1;
				}
				
				if((color(i+1,j-1)!=-1)){
					if(not existeix(i+1,j-1)){
						if(color(i+1,j-1)!=1) return 4;
						else{ 
							map[i+1][j-1] = 4;
							cola.push(pair<int,int>(i+1,j-1));
						}
					}
					else map[i+1][j-1] = -1;
				}
				
				if((color(i,j-1)!=-1)){
					if(not existeix(i,j-1)){
						if(color(i,j-1)!=1) return 5;
						else{ 
							map[i][j-1] = 5;
							cola.push(pair<int,int>(i,j-1));
						}
					}
					else map[i][j-1] = -1;
				}
				
				if((color(i-1,j-1)!=-1)){
					if(not existeix(i-1,j-1)){
						if(color(i-1,j-1)!=1) return 6;
						else{ 
							map[i-1][j-1] = 6;
							cola.push(pair<int,int>(i-1,j-1));
						}
					}
					else map[i-1][j-1] = -1;
				}
				
				if((color(i-1,j)!=-1)){
					if(not existeix(i-1,j)){
						if(color(i-1,j)!=1) return 7;
						else{ 
							map[i-1][j] = 7;
							cola.push(pair<int,int>(i-1,j));
						}
					}
					else map[i-1][j] = -1;
				}
				
				if((color(i-1,j+1)!=-1)){
					
					if(not existeix(i-1,j+1)){
						if(color(i-1,j+1)!=1) return 8;
						else{ 
							map[i-1][j+1] = 8;
							cola.push(pair<int,int>(i-1,j+1));
						}
					}
					else map[i-1][j+1] = -1;

				}
			}

			int it=0;
			while(not libre and not cola.empty()){
				pair<int,int> aux = cola.front();
				cola.pop();
				int x=aux.first; int y=aux.second;
				if(x<max and y<max and x>min and y>min){
					bool este = ((color(x,y+1)!=-1) and not existeix(x,y+1) and map[x][y+1]==0);
					bool se = ((color(x+1,y+1)!=-1) and not existeix(x+1,y+1) and map[x+1][y+1]==0);
					bool sur = ((color(x+1,y)!=-1) and not existeix(x+1,y)and map[x+1][y]==0);
					bool so = ((color(x+1,y-1)!=-1) and not existeix(x+1,y-1) and map[x+1][y-1]==0);
					bool oeste = ((color(x,y-1)!=-1) and not existeix(x,y-1) and map[x][y-1]==0);
					bool no = ((color(x-1,y-1)!=-1) and not existeix(x-1,y-1) and map[x-1][y-1]==0);
					bool norte = ((color(x-1,y)!=-1 and not existeix(x-1,y) and map[x-1][y]==0));
					bool ne = ((color(x-1,y+1)!=-1 and not existeix(x-1,y+1) and map[x-1][y+1]==0));
					
					if(este) libre=comprobar_casilla(cola,map,x,y,0,1,res);
					if(se and not libre) libre = comprobar_casilla(cola,map,x,y,1,1,res);
					if(sur and not libre)  libre = comprobar_casilla(cola,map,x,y,1,0,res);
					if(so and not libre)  libre = comprobar_casilla(cola,map,x,y,1,-1,res);
					if(oeste and not libre)  libre = comprobar_casilla(cola,map,x,y,0,-1,res);
					if(no and not libre) libre = comprobar_casilla(cola,map,x,y,-1,-1,res);
					if(norte and not libre)  libre = comprobar_casilla(cola,map,x,y,-1,0,res);
					if(ne and not libre)  libre = comprobar_casilla(cola,map,x,y,-1,1,res);
					++it;
					//cout << "ITERACIONES: "<< it<<endl;
				}
			}
			
			return res;
			
		}

        void fes_torn() {
            // Escull una direcció inicial entre EST, SE, i SUD.
            //if (torn_actual()==1) dir = 1 + random(3);

            // Pintors: cap a dir
            vector<int> pag = pagesos(1); //1: el meu equip
            for (int i = 0; i < (int)pag.size(); ++i) {
				/*t_robot r = robot(pag[i]);
				int x,y;
				x=r.i; y=r.j;
				if(dir==EST) x+=1;
				else if(dir==SE){ x+=1; y-=1;}
				else if (dir==SUD) y-=1;
				if(comprueba_casilla(x,y)==(-1)) dir=1+random(3);
                else*/ 
                t_robot r=robot(pag[i]);
                int aux;
				if(torn_actual()<=200) aux = bfs(pag[i],0,23);
				else aux = bfs(pag[i],0,50);
				ordena(pag[i], aux);

				
            }

            // Soldats: direcció a l'atzar
            vector<int> cav = cavallers(1);
            for (int i = 0; i < (int)cav.size(); ++i) {
				t_robot r=robot(cav[i]);
				//cerr << "MUEVO CAB"<<endl;
				int aux;
					//if(r.vida >=200) ordena(r.id,retirada());
					//if(torn_actual()==1)atacar=false;
					//if( (int)cav.size() > 35) atacar=true;
					//if(torn_actual()<=200 or not atacar) 
					aux = bfs2(cav[i],0,50);
					//else aux = bfs2(cav[i],0,50);
					ordena(r.id, aux);
					
			}
          }
        


  };                                          // Do not change this line
  AIstruct::Static_Initializer init;          // Do not change this line
};                                            // Do not change this line



