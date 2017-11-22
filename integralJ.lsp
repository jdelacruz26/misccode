/***************************************************************************/
/**										  						          **/
/**			                   Jorge De La Cruz            	              **/
/**	                 	   jorge.cruzarcia@utp.ac.pa	             	  **/	
/**					    Universidad Tecnológica de Panamá				  **/		
/***************************************************************************/


/* Fichero para calcular la integral J */

kill(all);
/* Definiendo constantes */
nu:0.3;  								/* Relación de Posisson*/
E:210e9; 								/* Modulo de Elasticidad del Material en Pa */ 
sigma:100e6;  							/* Carga Aplicada en Pa */
a:0.012;     							/* Lingitud de la grieta en metros */
G:E/(2*(1+nu));							/* Módulo de rigidez */

z:x+%i*y;
phi:sigma/sqrt(1-(a/z)^2);
phibarra:sigma*z*sqrt(1-(a/z)^2);
phiprim:-a^2*sigma/(z^3*(1-(a/z)^2)^(3/2));
sigmaxx:realpart(phi)-y*imagpart(phiprim);
sigmayy:realpart(phi)+y*imagpart(phiprim);
sigmaxy:-y*realpart(phiprim);

 /* desplazamientos en dirección X */
u:((1+nu)/E)*((1-2*nu)*realpart(phibarra)-y*imagpart(phi)); 

 /* desplazamientos en dirección Y */
v:((1+nu)/E)*(2*(1-nu)*imagpart(phibarra)-y*realpart(phi));
upx:diff(u,x);	/* derivada de u respecto de x */
vpx:diff(v,x);	/* derivada de v respecto de x */

/* Deformaciones en dirección xx */
epxx:(1/E)*((1-nu^2)*sigmaxx-nu*(1+nu)*sigmayy);	

/* Deformaciones en dirección yy */
epyy:(1/E)*((1-nu^2)*sigmayy-nu*(1+nu)*sigmaxx);	

/* Deformaciones cortantes  xy */
gxy:sigmaxy/G;										

/* Primer término de energía de la integral J, sólo integra en dy */
W:0.5*(sigmaxx*epxx+sigmayy*epyy+sigmaxy*gxy);	
/* Componentes del segundo término de la integral J, en este caso integración en dy */
Ty:sigmaxx*upx+sigmaxy*vpx;	
/* Componentes del segundo término de la integral J, en este caso integración en dx */
Tx:sigmaxy*upx+sigmayy*vpx;	

/*Creamos los encabezados de las columnas de los ficheros de salida */
file_output_append:false;
with_stdout("Desplazamientos1.txt",print("Coordenada Y","	","Desplazamiento UX","	","Desplazamiento UY"));
with_stdout("Esfuerzos1.txt",print("Coordenada Y","	","Esfuerzos SXX","	","Esfuerzos SYY","	","Esfuerzos SXY"));
with_stdout("Desplazamientos2.txt",print("Coordenada X","	","Desplazamiento UX","	","Desplazamiento UY"));
with_stdout("Esfuerzos2.txt",print("Coordenada X","	","Esfuerzos SXX","	","Esfuerzos SYY","	","Esfuerzos SXY"));
with_stdout("Desplazamientos3.txt",print("Coordenada Y","	","Desplazamiento UX","	","Desplazamiento UY"));
with_stdout("Esfuerzos3.txt",print("Coordenada Y","	","Esfuerzos SXX","	","Esfuerzos SYY","	","Esfuerzos SXY"));
with_stdout("Desplazamientos4.txt",print("Coordenada X","	","Desplazamiento UX","	","Desplazamiento UY"));
with_stdout("Esfuerzos4.txt",print("Coordenada X","	","Esfuerzos SXX","	","Esfuerzos SYY","	","Esfuerzos SXY"));
with_stdout("Desplazamientos5.txt",print("Coordenada Y","	","Desplazamiento UX","	","Desplazamiento UY"));
with_stdout("Esfuerzos5.txt",print("Coordenada Y","	","Esfuerzos SXX","	","Esfuerzos SYY","	","Esfuerzos SXY"));

/* Se crean los ficheros con los valores de x, y, W, Tx, Ty para cada lado del camino rectangular 
para luego procesarlos y realizar la integral J de forma numérica*/

with_stdout("Path1.txt",print("Coordenada Y","	","Valor de W","	","Valor de Ty"));
with_stdout("Path2.txt",print("Coordenada X","	","Valor de Tx"));
with_stdout("Path3.txt",print("Coordenada Y","	","Valor de W","	","Valor de Ty"));
with_stdout("Path4.txt",print("Coordenada X","	","Valor de Tx"));
with_stdout("Path5.txt",print("Coordenada Y","	","Valor de W","	","Valor de Ty"));


fpprintprec : 7;



file_output_append:true;
/* Para el Primer segmento de la integral J */

/* se fija la cordenada X correspondiente al lado izquierdo */
x:0.005;				
/* se varia Y a lo largo del lado X fijado previamente */						
for y:0 thru 0.02 step 0.0001 do 			
(uu:ev(u,numer),
vv:ev(v,numer),
sigxx:ev(sigmaxx,numer),
sigyy:ev(sigmayy,numer),
sigxy:ev(sigmaxy,numer),
Wnum:ev(W,numer),
Tynum:ev(Ty,numer),
with_stdout("Desplazamientos1.txt",print(y,"	",uu,"	",vv)),		
with_stdout("Esfuerzos1.txt",print(y,"	",sigxx,"	",sigyy,"	",sigxy)),
with_stdout("Path1.txt",print(y,"	",Wnum,"	",Tynum)))$


/* Para el Segundo segmento de la integral J */
/* se fija la cordenada Y correspondiente al lado superior */
y:0.02;		
/* se varia X a lo largo del lado Y fijado previamente */									
for x:0.005 thru 0.02 step 0.0001 do				
(uu:ev(u,numer),
vv:ev(v,numer),
sigxx:ev(sigmaxx,numer),
sigyy:ev(sigmayy,numer),
sigxy:ev(sigmaxy,numer),
Txnum:ev(Tx,numer),
with_stdout("Desplazamientos2.txt",print(x,"	",uu,"	",vv)),		
with_stdout("Esfuerzos2.txt",print(x,"	",sigxx,"	",sigyy,"	",sigxy)),
with_stdout("Path2.txt",print(x,"	",Txnum)))$




/* Para el Tercer segmento de la integral J */

/* se fija la cordenada X correspondiente al lado derecho */
x:0.02;					
/* se varia Y a lo largo del lado X fijado previamente */						
for y:0.02 thru -0.02 step -0.0001 do 			
(uu:ev(u,numer),
vv:ev(v,numer),
sigxx:ev(sigmaxx,numer),
sigyy:ev(sigmayy,numer),
sigxy:ev(sigmaxy,numer),
Wnum:ev(W,numer),
Tynum:ev(Ty,numer),
with_stdout("Desplazamientos3.txt",print(y,"	",uu,"	",vv)),		
with_stdout("Esfuerzos3.txt",print(y,"	",sigxx,"	",sigyy,"	",sigxy)),
with_stdout("Path3.txt",print(y,"	",Wnum,"	",Tynum)))$



/* Para el Cuarto segmento de la integral J */

/* se fija la cordenada Y correspondiente al lado inferior */
y:-0.02;						
/* se varia X a lo largo del lado Y fijado previamente */				
for x:0.02 thru 0.005 step -0.0001 do			
(uu:ev(u,numer),
vv:ev(v,numer),
sigxx:ev(sigmaxx,numer),
sigyy:ev(sigmayy,numer),
sigxy:ev(sigmaxy,numer),
Txnum:ev(Tx,numer),
with_stdout("Desplazamientos4.txt",print(x,"	",uu,"	",vv)),		
with_stdout("Esfuerzos4.txt",print(x,"	",sigxx,"	",sigyy,"	",sigxy)),
with_stdout("Path4.txt",print(x,"	",Txnum)))$



/* Para el Quinto segmento de la integral J */
/* se fija la cordenada X correspondiente al lado izquierdo */
x:0.005;				
/* se varia Y a lo largo del lado X fijado previamente */						
for y:-0.02 thru 0 step 0.0001 do 			
(uu:ev(u,numer),
vv:ev(v,numer),
sigxx:ev(sigmaxx,numer),
sigyy:ev(sigmayy,numer),
sigxy:ev(sigmaxy,numer),
Wnum:ev(W,numer),
Tynum:ev(Ty,numer),
with_stdout("Desplazamientos5.txt",print(y,"	",uu,"	",vv)),		
with_stdout("Esfuerzos5.txt",print(y,"	",sigxx,"	",sigyy,"	",sigxy)),
with_stdout("Path5.txt",print(y,"	",Wnum,"	",Tynum)))$
