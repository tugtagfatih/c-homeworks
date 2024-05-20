int numHospitals(char cities[], int n){
    int i;
    if (cities[0] == '\0') return 0;
    int count = 0, bestHospitalIndex = -1, bestCount = 0;
    for (i = 0; i < n; i++){
        if (cities[0] == hospitals[i].citiesServed[0] || cities[0] == hospitals[i].citiesServed[1] || cities[0] == hospitals[i].citiesServed[2]){
            count++;
            if (count > bestCount){
                bestCount = count;
                bestHospitalIndex = i;
            }
        }
    }
    if (hospitals[bestHospitalIndex].citiesServed[0] != '\0'){
        for (i = 0; i < 3; i++){
            deletefromarrayifsame(cities, hospitals[bestHospitalIndex].citiesServed[i]);
            printf("%s\n", cities);
        }
    }
    if (cities[0] == '\0') return 0;
    return 1 + numHospitals(cities, n);
}

void deletefromarrayifsame(char cities[], char c){
    int i = 0, j;
    while (cities[i] != '\0'){
        if (cities[i] == c){
            for (j = i; cities[j] != '\0' && cities[j+1] != '\0'; j++){
                cities[j] = cities[j + 1];
            }
            cities[j] = '\0';
        }
        i++;
    }
}
