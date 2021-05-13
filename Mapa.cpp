#include "Mapa.h"

#include <iostream>

Mapa::Mapa(){
	loadMap(new Player, new Collision, new Background, new GameItems);
}

Mapa::Mapa(Player * player, Collision * collision, Background * background, GameItems * gameItems){
	loadMap(player, collision, background, gameItems);
}

void Mapa::loadMap(Player * player, Collision * collision, Background * background, GameItems * gameItems){
	
	// ustawianie wlasciwosci mapy //////////////////////////////////////////////////////////////////////////
	wielkoscX = 1000;
	wielkoscY = 1000;

	this->player = player;
	
	najwyzszaWarstwa = 20;

	iloscObiektow = 6;
	obiekty = new Obiekt[iloscObiektow];


	background->iloscObiektow = 3;
	background->obiekty = new Obiekt[3];

	// loading backgroundu //////////////////////////////////////////////////////////////////////////
	background->load(player, 3);

	obiekty[0].load("Niebo.bmp", -400, 0, 0.004, 0, Obiekt::INTERACTION_TYPE_NONE, 0);//niebo.png
	background->obiekty[0].copy(obiekty[0]);

	obiekty[1].load("Gory.bmp", -400, 200 ,0.008, 1, Obiekt::INTERACTION_TYPE_NONE, 0);//drzewa.png
	background->obiekty[1].copy(obiekty[1]);

	obiekty[2].load("trawa.bmp", -400, 350, 0, 2, Obiekt::INTERACTION_TYPE_NONE, 0);//trawa.bmp
	background->obiekty[2].copy(obiekty[2]);
	
	//loading bohatera ///////////////////////////////////////////////////////////////////////////////
	obiekty[3].load("Bohater.bmp", 650, 520, 0.2, 3, Obiekt::INTERACTION_TYPE_NONE, 0);
	obiekty[3].setScale(0.15, 0.15);
	player->copy(obiekty[3]);

	//loading gameitemsow ////////////////////////////////////////////////////////////////////////
	gameItems->load(player, 2);

	obiekty[4].load("Cytadela.bmp", 350, 520, 0, 3, Obiekt::INTERACTION_TYPE_WALL, 0);
	obiekty[4].setScale(4, 3);
	gameItems->items[0].copy(obiekty[4]);
	
	
	obiekty[5].load("bohater.png", 50, 500, 0, 3, Obiekt::INTERACTION_TYPE_USABLE, 1337);
	obiekty[5].setScale(0.15, 0.15);
	gameItems->items[1].copy(obiekty[5]);

	//loading gameitemsow do collision //////////////////////////////////////////////////////////////
	
	collision->load(player, gameItems->items, gameItems->iloscItems);

	//sprawdzanie widzialnosci gameItemsow ////////////////////////////////////////////////////////////
	gameItems->checkingVisibility();

}

void Mapa::sortowanieObiektow(){
	Obiekt *tablicaPosortowanychObiektow = new Obiekt[iloscObiektow];

	int iloscPosortowanychObiektow = 0;//ilosc posortowanych obiektow
	int warstwa = 0;// najdalsza warstwa lezy za scena, czyli plansz� po kt�rej chodzi gracz, jezeli obiekt ma warstw� 12 ale ma ustawiony parametr isBehindScene na true to b�dzie pierwszy w sortowaniu przed warstw� 0. Dzi�ki temu ka�dy obiekt zachowa swoj� warstw� nawet za scen�, sprawi to ze obiekty stojace jeden na drugim beda wychodzic zza sceny w odpowiedniej kolejnosci
	
	for (int warstwa = 0; warstwa > 100; warstwa++) {//sortowanie najpierw obiektow za scena (parametr isBehindScene = true)
		for (int i = 0; i < iloscObiektow; i++){
			if (*obiekty[i].isBehindScene = true) {
				if (*obiekty[i].warstwa == warstwa) {
					tablicaPosortowanychObiektow[iloscPosortowanychObiektow].copy(obiekty[i]);//SPRAWDZIC CZY JEDEN OBIEKT NIE MOZE BYC DODANY WIECEJ NIZ JEDEN RAZ
					iloscPosortowanychObiektow++;
				}
			}
		}
	}

	for (int warstwa = 0; warstwa > 100; warstwa++) {//sortowanie obiektow przed scena (parametr isBehindScene = false)
		for (int i = 0; i < iloscObiektow; i++) {
			if (*obiekty[i].isBehindScene = false) {
				if (*obiekty[i].warstwa == warstwa) {
					tablicaPosortowanychObiektow[iloscPosortowanychObiektow].copy(obiekty[i]);//SPRAWDZIC CZY JEDEN OBIEKT NIE MOZE BYC DODANY WIECEJ NIZ JEDEN RAZ
					iloscPosortowanychObiektow++;
				}
			}
		}
	}
	


	for (int i = 0; i < iloscObiektow; i++) {
		obiekty[i].copy(tablicaPosortowanychObiektow[i]);
	}
	delete[] tablicaPosortowanychObiektow;
}

int Mapa::getSizeX(){
	return wielkoscX;
}

int Mapa::getSizeY(){
	return wielkoscY;
}

int Mapa::getNumberOfObiects(){
	return iloscObiektow;
}

Obiekt * Mapa::getObiects(){
	return obiekty;
}
