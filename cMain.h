#pragma once
#include "wx/wx.h"
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <iostream>
#include <random>
#include <vector>
#include <thread>
#include <chrono>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int nFieldWidth = 9;
	int nFieldHeight = 9;
	//wxButton** btn;
	std::vector <wxTextCtrl*>  textCtrls;
	wxTextCtrl* getTextCtrl(int index);
	bool bFirstClick = true;
	bool victory = false;

	const int collectionSize = 9;
	bool notOk = false;

	//void OnButtonClicked(wxCommandEvent& evt);
	void OnTextChanged(wxCommandEvent& evt);
	//void resetGame(bool victory);
	int getIndex(int i, int q);

	int gridSource[9][9]{};
	int gridFilled[9][9]{};

	int gameDifficulty = 1; //1 is ok 2 gives exception

	bool matchCheck(int number, std::vector <int> collection, int collectionSize);
	void gridParser(int grid[][9]);
	void gridDeleter(int gridSource[][9], int gameDifficulty);
	std::vector <int>& pickLine(int index);
	std::vector <int>& pickRow(int index);
	std::vector <int>& pickBox(int i, int q);
	int pickBoxIndex(int i, int q);
	bool winCondition();
	std::vector <int> firstLine = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> secondLine = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> thirdLine = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> fourthLine = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> fifthLine = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> sixthLine = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> seventhLine = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> eighthLine = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> ninthLine = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };

	std::vector <int> firstRow = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> secondRow = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> thirdRow = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> fourthRow = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> fifthRow = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> sixthRow = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> seventhRow = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> eighthRow = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> ninthRow = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };

	std::vector <int> firstBox = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> secondBox = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> thirdBox = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> fourthBox = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> fifthBox = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> sixthBox = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> seventhBox = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> eighthBox = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };
	std::vector <int> ninthBox = { 11, 11, 11, 11, 11, 11, 11, 11, 11 };


	wxDECLARE_EVENT_TABLE();
};

