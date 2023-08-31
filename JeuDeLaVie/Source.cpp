#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <time.h>

#include "olcConsoleGameEngine.h"

using namespace std;


class JeuDeLaVie : public olcConsoleGameEngine
{
private:
	const int NB_CASES = 60;
	vector<vector<int>> grille;

	void init(vector<vector<int>>& tab) {
		for (int i = 0; i < tab.size(); i++) {
			for (int j = 0; j < tab[i].size(); j++) {
				tab[i][j] = rand() % 2;
			}
		}
	}

	vector<vector<int>> calculeVoisins(const vector<vector<int>>& grille) {
		vector<vector<int>> voisins(grille.size(), vector<int>(grille[0].size()));
		for (int i = 0; i < voisins.size(); i++) {
			for (int j = 0; j < voisins[i].size(); j++) {
				voisins[i][j] = 0;
				if (i > 0) {
					voisins[i][j] += grille[i - 1][j];
				}
				if (i < grille.size() - 1) {
					voisins[i][j] += grille[i + 1][j];
				}
				if (j > 0) {
					voisins[i][j] += grille[i][j - 1];
				}
				if (j < 9) {
					voisins[i][j] += grille[i][j + 1];
				}
				if (i > 0 && j > 0) {
					voisins[i][j] += grille[i - 1][j - 1];
				}
				if (i > 0 && j < grille.size() - 1) {
					voisins[i][j] += grille[i - 1][j + 1];
				}
				if (i < grille.size() - 1 && j > 0) {
					voisins[i][j] += grille[i + 1][j - 1];
				}
				if (i < grille.size() - 1 && j < grille.size() - 1) {
					voisins[i][j] += grille[i + 1][j + 1];
				}
			}
		}
		return voisins;
	}

public:
	JeuDeLaVie()
	{
		m_sAppName = L"Game Life";
	}

	void affiche() 
	{
		for (int i = 0; i < grille.size(); i++)
		{
			for (int j = 0; j < grille[i].size(); j++)
			{
				if (grille[i][j] == 1)
				{
					Draw(i, j ,PIXEL_SOLID, FG_WHITE);
				}
				else
				{
					Draw(i, j, PIXEL_SOLID, FG_BLACK);
				}
			}
		}
	}

protected:
	virtual bool OnUserCreate()
	{
		grille.resize(NB_CASES, vector<int>(NB_CASES));
		init(grille);

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		this_thread::sleep_for(50ms);
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		vector<vector<int>> voisins = calculeVoisins(grille);

		for (int i = 0; i < grille.size(); i++) {
			for (int j = 0; j < grille[i].size(); j++) {
				if (grille[i][j] == 1) {
					if (voisins[i][j] < 2 || voisins[i][j] > 3) {
						grille[i][j] = 0;
					}
				}
				else {
					if (voisins[i][j] == 3) {
						grille[i][j] = 1;
					}
				}
			}
		}

		affiche();
		return true;
	}
};

int main() {
	srand(time(NULL));

	JeuDeLaVie jeu;
	if (jeu.ConstructConsole(60, 60, 14, 14)) {
		jeu.Start();
	}
			
	return 0;
}
