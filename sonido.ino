/*
 * Procesador de musica basico
 * Lo cual lee la entrada de audio, la procesa, intenta reducir el ruido al maximo 
 *y luego lo envia a 8 LEDS para ver el resultado de la entrada; ademas se puede ver el plotter
 * 
 * 
 * @author Alex Vargas Benamburg <avargas at vbalex.com>
 * @assistent Bertha Brenes Brenes 
 */
#define NUM_UMBRALES 8 // Igual a la cantidad de LEDS
#define GAIN 50//rango en la escala de 0-512. Cambiar con respecto al volumen
const int pines[] = {3,4,5,6,7,8,9,10};//pines que van a los LEDS
void setup() {
 Serial.begin(9600);
 //pinMode output para cada pin
 for(int i=0;i<NUM_UMBRALES;++i){
  pinMode(pines[i],OUTPUT);
 }
}
void loop() {
  int vLeft = procesAudio(analogRead(A0)); 
  Serial.println(vLeft);
  //Escribe el valor de la entrada de Audio procesada en los LEDS
  for(int i=0;i<NUM_UMBRALES;++i){
    digitalWrite(pines[i],i<vLeft);
  }
}
int procesAudio(int input){ 
  
  int valAbsoluto = input-512; //obtener valor real de la onda
  if(valAbsoluto<0){
    valAbsoluto *= -1; //Al recibir valores negativos los convierte en valores positivos en la onda.
  }
  int v = (valAbsoluto*NUM_UMBRALES+1)/GAIN; // Regla de 3, divido la onda en la cantidad de umbrales especificados
  if(v>(NUM_UMBRALES+1)){ //si el valor obtenidos es mayor a la cantidad de umbrales los mandamos a 0 para evitar ruido
    v = 0;
  }
  return v; //retornamos el valor
}

