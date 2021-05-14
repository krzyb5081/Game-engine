#include "Mapa.h"

#include <iostream>

Mapa::Mapa(){
	loadMap(new Player, new Collision, new Background, new GameItems);
}

Mapa::Mapa(Player * player, Collision * collision, Background * background, GameItems * gameItems){
	loadMap(player, collision, background, gameItems);
}

void Mapa::loadMap(Player * player, Collision * collision, Background * background, GameItems * gameItems){
	
	// ustawianie wlasciwosci mapy ////////////////////////////////////////////////////////////////////////
	wielkoscX = 1000;
	wielkoscY = 1000;
	this->najwyzszaWarstwa = 20;
	this->iloscObiektow = 6;

	this->obiekty = new Obiekt[iloscObiektow];

	// LOADING PLAYER /////////////////////////////////////////////////////////////////////////////////////
	this->obiekty[0].load("Bohater.bmp", 650, 520, 0.2, 20, Obiekt::INTERACTION_TYPE_NONE, 0, false);
	this->obiekty[0].setScale(0.15, 0.15);

	this->player = player;
	player->copy(this->obiekty[0]);

	// LOADING BACKGROUND /////////////////////////////////////////////////////////////////////////////////
	this->obiekty[1].load("Niebo.bmp", -400, 0, 0.004, 0, Obiekt::INTERACTION_TYPE_NONE, 0, true);//za scena
	this->obiekty[2].load("Gory.bmp", -400, 200, 0.008, 1, Obiekt::INTERACTION_TYPE_NONE, 0, true);//za scena
	this->obiekty[3].load("trawa.bmp", -400, 350, 0, 2, Obiekt::INTERACTION_TYPE_NONE, 0, false);//pierwsza zerowa warstwa 'przed scena' bo ten obiekt jest scena

	background->initiate(player, 3);
	background->obiekty[0].copy(this->obiekty[1]);
	background->obiekty[1].copy(this->obiekty[2]);
	background->obiekty[2].copy(this->obiekty[3]);
	
	// LOADING GAMEITEMS //////////////////////////////////////////////////////////////////////////////////
	this->obiekty[4].load("Cytadela.bmp", 350, 520, 0, 3, Obiekt::INTERACTION_TYPE_WALL, 0, false);
	this->obiekty[4].setScale(4, 3);
	this->obiekty[5].load("bohater.png", 50, 500, 0, 3, Obiekt::INTERACTION_TYPE_USABLE, 1337, false);
	this->obiekty[5].setScale(0.15, 0.15);

	gameItems->initiate(player, 2);
	gameItems->items[0].copy(this->obiekty[4]);
	gameItems->items[1].copy(this->obiekty[5]);

	// LOADING GAMEITEMS TO COLLISION /////////////////////////////////////////////////////////////////////
	collision->load(player, gameItems->items, gameItems->iloscItems);

	//CHECKING GAMEITEMS VISIBILITY ///////////////////////////////////////////////////////////////////////
	gameItems->checkingVisibility();

}

Obiekt * Mapa::sortowanieObiektow(){
	
	Obiekt *posortowaneObiekty = new Obiekt[this->iloscObiektow];//najdalsza warstwa lezy za scena, czyli plansz� po kt�rej chodzi gracz, jezeli obiekt ma warstw� 12 ale ma ustawiony parametr isBehindScene na true to b�dzie pierwszy w sortowaniu przed warstw� 0. Dzi�ki temu ka�dy obiekt zachowa swoj� warstw� nawet za scen�, sprawi to ze obiekty stojace jeden na drugim beda wychodzic zza sceny w odpowiedniej kolejnosci
	int iloscPosortowanychObiektow = 0;//ilosc posortowanych obiektow
	
	for (int warstwa = 0; warstwa <= this->najwyzszaWarstwa; warstwa++) {//sortowanie najpierw obiektow za scena (parametr isBehindScene = true)
		for (int i = 0; i < this->iloscObiektow; i++){
			if (*this->obiekty[i].isBehindScene == true) {
				if (*this->obiekty[i].warstwa == warstwa) {
					posortowaneObiekty[iloscPosortowanychObiektow].copy(this->obiekty[i]);
					iloscPosortowanychObiektow++;
				}
			}
		}
	}
	for (int warstwa = 0; warstwa <= this->najwyzszaWarstwa; warstwa++) {//sortowanie obiektow przed scena (parametr isBehindScene = false)
		for (int i = 0; i < this->iloscObiektow; i++) {
			if (*this->obiekty[i].isBehindScene == false) {
				if (*this->obiekty[i].warstwa == warstwa) {
					posortowaneObiekty[iloscPosortowanychObiektow].copy(this->obiekty[i]);
					iloscPosortowanychObiektow++;
				}
			}
		}
	}

	
	for (int i = 0; i < iloscPosortowanychObiektow; i++) {
		this->obiekty[i].copy(posortowaneObiekty[i]);
	}
	delete[] posortowaneObiekty;
	
	return this->obiekty;
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
	return this->obiekty;
}
