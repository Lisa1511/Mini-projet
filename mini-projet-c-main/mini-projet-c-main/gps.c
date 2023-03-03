#include <stdio.h>
#include <stdlib.h>
#define MAXINPUT 256
#define TIMEFORMAT 20
#define COORDFORMAT 10
#define ORIENTATIONFORMAT 2


int isNorme(char message[]){

    char car = message[0], norme[] = {'$', 'G', 'P', 'G', 'G', 'A'};
    int i = 0;
    while (car != ','){
        if (car != norme[i]){
            return 0;
        }
        i++;
        car = message[i];
    }
    return 1;
}

int getIndice(char message[], int nbr){

    char car = message[0];
    int virgule = 0, i = 0;

    while (car != ',' || virgule != nbr-1){
        if (car == ',' ){
            virgule ++;
        }
        i++;
        car = message[i];
    }
    return i+1;
}

void getInfo(char message[], char data[], int dataIndice){

    int i = getIndice(message, dataIndice), j = 0;
    char car = message[i];
    while (car != ','){
        data[j] = car;
        j++;
        i++;
        car = message[i];
    }
}

int editNumber(float *nombre, int first, int second){

    int i = 0, j = 0;

    while (*nombre > first){
        i++;
        *nombre -= first;
    }
    while (*nombre > second){
        j++;
        *nombre -= second;
    }

    return i*10+j;
}

void setTime(char time[]){

    float timeT = strtof(time, NULL), seconds;
    int hours, minutes;
    hours = editNumber(&timeT, 100000, 10000);
    minutes = editNumber(&timeT, 1000, 100);
    seconds = timeT;

    printf("Time : %dh%dm%.3fs\n", hours, minutes, seconds);
}

void setCoordinates(char data[], int info, char orientation[]){

    float angle = strtof(data, NULL), coord = strtof(data, NULL);
    int partEntier = 0, anglePartEntier;

    anglePartEntier = editNumber(&angle, 1000, 100);
    editNumber(&coord, 1000, 100);
    partEntier = editNumber(&coord, 10, 1);

    angle = angle/60 + anglePartEntier;
    coord *= 60;

    if (info == 0){
        printf("Latitude : %f° %s = %d°%d'%.2f %s\n", angle, orientation, anglePartEntier, partEntier, coord, orientation);
    }
    if (info == 1){
        printf("Longitude : %f° %s = %d°%d'%.3f %s\n", angle, orientation, anglePartEntier, partEntier, coord, orientation);
    }
}

int main(void){


    char message[MAXINPUT], time[TIMEFORMAT], longitude[COORDFORMAT], latitude[COORDFORMAT], orientationLong[ORIENTATIONFORMAT], orientationLat[ORIENTATIONFORMAT];
    int isFormatOk;

    
    scanf("%s", message);

    
    isFormatOk = isNorme(message);

    if (isFormatOk == 1){
        

        getInfo(message, time, 1);
        getInfo(message, longitude, 2);
        getInfo(message, orientationLong, 3);
        getInfo(message, latitude, 4);
        getInfo(message, orientationLat, 5);

        

        setTime(time);

        
        setCoordinates(longitude, 0, orientationLong);
        setCoordinates(latitude, 1, orientationLat);
    } else {
        
        printf("Désolé mais le format n'est pas valide, il nous le faut sous la forme suivante :\nNMEA 0183\n");
    }
    

    return 0;
}

// $GPGGA,064036.289,4836.5375,N,00740.9373,E,1,04,3.2,200.2,M,,,,0000*0E
