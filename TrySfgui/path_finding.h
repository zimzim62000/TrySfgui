#ifndef PATHFINDING

#define PATHFINDING

#pragma once

class MapGame;

#include <list>
#include <map>
#include <memory>

struct noeud {
	float cout_g, cout_h, cout_f;
	std::pair<int, int> parent;
};

struct point {
	int x, y;
};

typedef std::map< std::pair<int, int>, noeud> l_noeud;

class PathFinding{

public:
	PathFinding();
	bool deja_present_dans_liste(std::pair<int, int> n, l_noeud& l);
	std::pair<int, int> meilleur_noeud(l_noeud& l);
	void ajouter_cases_adjacentes(std::pair <int, int>& n, std::shared_ptr<MapGame> map);
	void findRoad(std::shared_ptr<MapGame> map, const int start_x, const int start_y, const int end_x, const int end_y);
	void ajouter_liste_fermee(std::pair<int, int>& p);
	void retrouver_chemin();
	float distance(int x1, int y1, int x2, int y2);
	void resetPath();

	l_noeud liste_ouverte;
	l_noeud liste_fermee;
	std::list<point> chemin;

	struct point arrivee;
	noeud depart;

private:
};

#endif PATHFINDING