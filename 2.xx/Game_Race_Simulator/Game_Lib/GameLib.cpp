#define BUILD_DLL
#include "GameLib.h"
#include "Camel.h"
#include "FastCamel.h"
#include "Centaur.h"
#include "AllTerrainBoots.h"
#include "FlyingCarpet.h"
#include "Eagle.h"
#include "Broom.h"

double Camel::getTime(double distance) {
    double time = distance / getSpeed();
    time += (distance / getSpeed() / 30) * 5 + 8 * ((distance / getSpeed() / 30) - 1);
    return time;
}

double FastCamel::getTime(double distance) {
    double time = distance / getSpeed();
    time += (distance / getSpeed() / 10) * 5 + 6.5 * ((distance / getSpeed() / 10) - 1);
    return time;
}

double Centaur::getTime(double distance) {
    double time = distance / getSpeed();
    time += 2 * (distance / getSpeed() / 8);
    return time;
}

double AllTerrainBoots::getTime(double distance) {
    double time = distance / getSpeed();
    time += (distance / getSpeed() / 60) * 10 + 5 * ((distance / getSpeed() / 60) - 1);
    return time;
}

double FlyingCarpet::getTime(double distance) {
    double time = distance / getSpeed();
    if (distance < 1000) {
    }
    else if (distance < 5000) {
        time -= time * 0.03;
    }
    else if (distance < 10000) {
        time -= time * 0.1;
    }
    else {
        time -= time * 0.05;
    }
    return time;
}

double Eagle::getTime(double distance) {
    double time = distance / getSpeed();
    time -= time * 0.06;
    return time;
}

double Broom::getTime(double distance) {
    double time = distance / getSpeed();
    double reduction = 0.01 * (distance / 1000);
    time -= time * reduction;
    return time;
}