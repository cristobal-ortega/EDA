/* ****************************************************************** */
/* IMPORTANT! Write here the name of your player.                     */
/* ****************************************************************** */

#define NAMEPLAYER Camp


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

		map<int,int> dircamp;
		typedef map<int,int>::iterator Iterator;
       // int dir;
		//int id;
        //vector< vector<int> > mapa(50,vector<int>(50));
        
        
      /*  void crear_mapa(){
			for(int i=0; i<50; ++i){
				for(int j=0; j<50; ++j){
					if(color(i,j)==-1) mapa[i][j] = -1;
				}
			}
		}*/
        
       /*	int comprueba_casilla(int x, int y){
			int c=color(x,y);
			t_robot r=robot(x,y);
			if(c==-1) return -10;
			else if(r.id!=-1){
				 if(r.model==1) return -1;
				 else return -50;
			 }
			else if(c==1) return 0;
			else return 10;
			}
		}
			 */
        
        
        /*int mover_camp(int id){
			Iterator i;
			t_robot r=robot(id);
			int x=r.i;
			int y=r.j;
			vector<int> nivel (8,0);
			//i=dircamp.find(id);
			//hacia 1 (este)
			nivel[0]=comprueba_casilla(x,y+1);
			if(nivel[0]<=-50){
				nivel[1]+=-10;
				nivel[7]+=-10;
			}
			nivel[1]=comprueba_casilla(x+1,y+1);
			if(nivel[1]<=-50){
				nivel[2]+=-10;
				nivel[0]+=-10;
			}
			nivel[2]=comprueba_casilla(x+1,y);
			if(nivel[2]<=-50){
				nivel[1]+=-10;
				nivel[4]+=-10;
			}
			nivel[3]=comprueba_casilla(x+1,y-1);
			if(nivel[3]<=-50){
				nivel[4]+=-10;
				nivel[2]+=-10;
			}
			nivel[4]=comprueba_casilla(x,y-1);
			if(nivel[4]<=-50){
				nivel[3]+=-10;
				nivel[5]+=-10;
			}			
			nivel[5]=comprueba_casilla(x-1,y-1);
			if(nivel[5]<=-50){
				nivel[6]+=-10;
				nivel[4]+=-10;
			}			
			nivel[6]=comprueba_casilla(x-1,y);
			if(nivel[6]<=-50){
				nivel[5]+=-10;
				nivel[7]+=-10;
			}			
			nivel[7]=comprueba_casilla(x-1,y+1);
			if(nivel[7]<=-50){
				nivel[0]+=-10;
				nivel[6]+=-10;
			}
			int zeros=0;
			int max=-1;
			int maxj=-1;
			for(int j=0;j<8; ++j){
				if(nivel[j]>max){
					max=nivel[j];
					maxj=j;
				}
				if(nivel[j]==0) ++zeros;
			}
			if(max==0){
				int aux=random(zeros);
				for(int k=0; zeros>aux; ++k){
					if(nivel[k]==0){
						 maxj=k;
						 --zeros;
					}
				}
			}
			maxj++;
			int dir_antic=dircamp[id];
			if(nivel[dir_antic]==max){
				maxj=dir_antic;
				dircamp.insert( pair<int,int>(id,maxj) );
			}
			return maxj;
		}*/
			
		
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
			/*for(int k=0; k<50; ++k){
				for(int q=0; q<50; ++q){
					if(color(k,q)==-1) map[k][q] = -1;
				}
			}*/
			queue< pair <int,int> > cola;
			pair<int,int> aux;
			aux.first=i; aux.second=j;
			cola.push(aux);
			bool libre=false;
			int direccion;
			bool begin=true;
			bool pnorte,pne,peste,pse,psud,pso,poeste,pno;
			pnorte=pne=peste=pse=psud=pso=poeste=pno=false;
			while( not libre and not cola.empty()){
				pair<int,int> actual;
				actual = cola.front();
				int x= actual.first; int y=actual.second;
				if(map[x][y]<1){
					//Camino libre
					bool norte=false;
					if(x>0) norte = (color(x-1,y)!=-1) and (robot(x-1,y).id == -1) and (map[x-1][y]<1);
					bool ne=false;
					if(x>0 and y <49) ne = (color(x-1,y+1)!=-1) and (robot(x-1,y+1).id == -1) and (map[x-1][y+1]<1);
					bool este=false;
					if(y < 49) este = (color(x,y+1)!=-1) and (robot(x,y+1).id == -1) and (map[x][y+1]<1);
					bool se=false;
					if(x<49 and y < 49) se = (color(x+1,y+1)!=-1)  and (robot(x+1,y+1).id == -1) and (map[x+1][y+1]<1);
					bool sud=false;
					if(x<49)sud = (color(x+1,y)!=-1) and (robot(x+1,y).id == -1) and (map[x+1][y]<1);
					bool so=false;
					if(x<49 and y>0)so = (color(x+1,y-1)!=-1) and (robot(x+1,y-1).id == -1) and (map[x+1][y-1]<1);
					bool oeste=false;
					if(y>0) oeste = (color(x,y-1)!=-1) and (robot(x,y-1).id == -1) and (map[x][y-1]<1);
					bool no=false;
					if(x>0 and y>0) no = (color(x-1,y+1)!=-1) and (robot(x-1,y-1).id == -1) and (map[x-1][y-1]<1);

					/*if(begin){
						begin=false;
						map[i-1][j] = 7;
						map[i-1][j+1] = 8;
						map[i][j+1] = 1;
						map[i+1][j+1] = 2;
						map[i+1][j]=3;
						map[i+1][j-1]=4;
						map[i][j-1]=5;
						map[i-1][j-1]=6;
					}*/
			

					//if(norte and not libre) libre = comprobar_orientacion(cola,map,x,y,-1,0,direccion);
					if(norte){
						if(color(x-1,y)!=1){
							 libre=true;
							 if(not pnorte) direccion=7;
							 else direccion=map[x][y];
						}
						else{
							if(not pnorte){
								pnorte=true;
								map[x-1][y]=7;
							}
							else map[x-1][y]=map[x][y];
							pair<int,int> next;
							next.first=x-1;
							next.second=y;
							cola.push(next);
						}
					}
					//comprobar_orientacion(cola,map,libre,ne,x,y,-1,1,direccion);
					if(ne and not libre){
						if(color(x-1,y+1)!=1){
							 libre=true;
							 if(not pne) direccion=8;
							 else direccion=map[x][y];
						 }
						else{
							if(not pne){
								pne=true;
								map[x-1][y+1]=8;
							}
							else map[x-1][y+1]=map[x][y];
							pair<int,int> next;
							next.first=x;
							next.second=y+1;
							cola.push(next);
						}
					}
					//comprobar_orientacion(cola,map,libre,este,x,y,0,1,direccion);
					if(este and not libre){
						if(color(x,y+1)!=1){
							 libre=true;
							 if(not peste) direccion=1;
							 else direccion=map[x][y];
						 }
						 else{
							if(not peste){
								peste=true;
								map[x][y+1]=1;
							}
							else map[x][y+1]=map[x][y];
							pair<int,int> next;
							next.first=x-1;
							next.second=y+1;
							cola.push(next);
						}
					}
					//comprobar_orientacion(cola,map,libre,se,x,y,1,1,direccion);
					if(se and not libre){
						if(color(x+1,y+1)!=1){
							 libre=true;
							 if(not pse) direccion=2;
							 else direccion=map[x][y];
						 }
						else{
							if(not pse){
								pse=true;
								map[x+1][y+1]=2;
							}
							else map[x+1][y+1]=map[x][y];
							pair<int,int> next;
							next.first=x+1;
							next.second=y+1;
							cola.push(next);
						}
					}
					//comprobar_orientacion(cola,map,libre,sud,x,y,1,0,direccion);
					if(sud and not libre){
						if(color(x+1,y)!=1){
							 libre=true;
							 if(not psud) direccion=3;
							 else direccion=map[x][y];
						 }
						else{
							if(not psud){
								psud=true;
								map[x+1][y]=3;
							}
							else map[x+1][y]=map[x][y];
							pair<int,int> next;
							next.first=x+1;
							next.second=y;
							cola.push(next);
						}
					}
					//comprobar_orientacion(cola,map,libre,so,x,y,1,-1,direccion);
					if(so and not libre){
						if(color(x+1,y-1)!=1){
							 libre=true;
							 if(not pso) direccion=4;
							 else direccion=map[x][y];
						 }
						else{
							if(not pso){
								pso=true;
								map[x+1][y-1]=4;
							}
							else map[x+1][y-1]=map[x][y];
							pair<int,int> next;
							next.first=x+1;
							next.second=y-1;
							cola.push(next);
						}
					}
					//comprobar_orientacion(cola,map,libre,oeste,x,y,0,-1,direccion);
					if(oeste and not libre){
						if(color(x,y-1)!=1){
							 libre=true;
							 if(not poeste) direccion=5;
							 else direccion=map[x][y];
						 }
						else{
							if(not poeste){
								poeste=true;
								map[x][y+1]=5;
							}
							else map[x][y-1]=map[x][y];
							pair<int,int> next;
							next.first=x;
							next.second=y+1;
							cola.push(next);
						}
					}
					//comprobar_orientacion(cola,map,libre,no,x,y,-1,1,direccion);
					if(no and not libre){
						if(color(x-1,y+1)!=1){
							 libre=true;
							 if(not pno) direccion=6;
							 else direccion=map[x][y];
						 }
						else{
							if(not pno){
								pno=true;
								map[x-1][y-1]=6;
							}
							else map[x-1][y+1]=map[x][y];
							pair<int,int> next;
							next.first=x-1;
							next.second=y-1;
							cola.push(next);
						}
					}
				}
				cola.pop();
			}
			return direccion;
		}		
			
			
			
			
			
			
		/*void turno_1(){
			crear_mapa();
		}*/


        void fes_torn() {
            // Escull una direcció inicial entre EST, SE, i SUD.
           // if (torn_actual()==1) turno_1();

            // Pintors: cap a dir
            vector<int> pag = pagesos(1); //1: el meu equip
            for (int i = 0; i < (int)pag.size(); ++i) {

                /*Iterator j=dircamp.begin();
                dircamp.find(pag[i]);
                if(j==dircamp.end()){
					dircamp.insert( pair<int,int>(pag[i],1));
				}*/
				//int aux = mover_camp(pag[i]);
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



