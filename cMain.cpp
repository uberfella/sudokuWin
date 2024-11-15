#include "cMain.h"

//linking specific button clicked to function call using macro
wxBEGIN_EVENT_TABLE(cMain, wxFrame)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Sudoku", wxPoint(30, 30), wxSize(800, 600))
{

    gridParser(gridSource);

    gridDeleter(gridSource, gameDifficulty);

    //organizing widgets in rows and columns
    wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

    // Allocate memory for textCtrls and nField
    //textCtrls = new wxTextCtrl * [nFieldWidth * nFieldHeight];


    wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

    for (int i = 0; i < collectionSize; i++)
    {
        for (int q = 0; q < collectionSize; q++)
        {
            int index = i * nFieldWidth + q;

            // Create a wxTextCtrl with an initial value of "0"
            auto textCtrl = new wxTextCtrl(this, 10000 + index, "", wxDefaultPosition, wxSize(30, 30), wxTE_CENTER);
            if (!textCtrl)
            {
                wxMessageBox("Failed to create text control", "Error", wxOK | wxICON_ERROR);
                continue;
            }

            textCtrl->SetFont(font);
            textCtrl->SetMaxLength(1); // Allow only 1 character

            // Add the wxTextCtrl to the grid sizer
            grid->Add(textCtrl, 1, wxEXPAND | wxALL);


            // Bind text entry event
            textCtrl->Bind(wxEVT_TEXT, &cMain::OnTextChanged, this);
            if (gridSource[i][q] != -1) {
                textCtrl->SetValue(wxString::Format("%d", gridSource[i][q]));
            }
            
            textCtrls.push_back(textCtrl);
            

		}
	}


	this->SetSizer(grid);
	this->Layout();
}

int cMain::getIndex(int i, int q)
{
	return (i + q);
}

cMain::~cMain()
{

}

void cMain::OnTextChanged(wxCommandEvent& evt)
{

	int id = evt.GetId() - 10000;
    if (auto textCtrl = getTextCtrl(id))
    {
        wxString value = textCtrl->GetValue();

        // Validate input
        if (!value.IsEmpty() && (value < "1" || value > "9")) {
            wxMessageBox("Please enter a number between 1 and 9", "Invalid Input", wxOK | wxICON_WARNING);
            textCtrl->ChangeValue("");  // ChangeValue avoids triggering another event
            evt.Skip();
            return;
        }

        if (winCondition()) {
            wxMessageBox("Congratulations! You win! Restart the game?", "Win Condition", wxOK | wxICON_INFORMATION);
        }

        evt.Skip();
    }

}

std::vector <int>& cMain::pickLine(int index)
{
    switch (index)
    {
    case 0:
        return firstLine;
        break;
    case 1:
        return secondLine;
        break;
    case 2:
        return thirdLine;
        break;
    case 3:
        return fourthLine;
        break;
    case 4:
        return fifthLine;
        break;
    case 5:
        return sixthLine;
        break;
    case 6:
        return seventhLine;
        break;
    case 7:
        return eighthLine;
        break;
    case 8:
        return ninthLine;
        break;
    default:
        wxLogError("Invalid line index: %d", index);
        return firstLine; // Fallback in case of error
    }
}

std::vector <int>& cMain::pickRow(int index)
{
    switch (index)
    {
    case 0:
        return firstRow;
        break;
    case 1:
        return secondRow;
        break;
    case 2:
        return thirdRow;
        break;
    case 3:
        return fourthRow;
        break;
    case 4:
        return fifthRow;
        break;
    case 5:
        return sixthRow;
        break;
    case 6:
        return seventhRow;
        break;
    case 7:
        return eighthRow;
        break;
    case 8:
        return ninthRow;
        break;
    default:
        wxLogError("Invalid line index: %d", index);
        return firstLine; // Fallback in case of error
    }
}

std::vector <int>& cMain::pickBox(int i, int q)
{
    if (i < 3)
    {
        if (q < 3)
        {
            return firstBox;
        }
        else if (q < 6)
        {
            return secondBox;
        }
        else if (q < 9)
        {
            return thirdBox;
        }
    }
    else if (i < 6)
    {
        if (q < 3)
        {
            return fourthBox;
        }
        else if (q < 6)
        {
            return fifthBox;
        }
        else if (q < 9)
        {
            return sixthBox;
        }
    }
    else if (i < 9)
    {
        if (q < 3)
        {
            return seventhBox;
        }
        else if (q < 6)
        {
            return eighthBox;
        }
        else if (q < 9)
        {
            return ninthBox;
        }
    }
    else
    {
        wxLogError("Invalid line index: %d");
        return firstLine; // Fallback in case of error
    }
    return ninthBox;

}

int cMain::pickBoxIndex(int i, int q)
{

    if (i == 0 || i == 3 || i == 6)
    {
        if (q == 0 || q == 3 || q == 6)
        {
            return 0;
        }
        else if (q == 1 || q == 4 || q == 7)
        {
            return 1;
        }
        else if (q == 2 || q == 5 || q == 8)
        {
            return 2;
        }
    }
    else if (i == 1 || i == 4 || i == 7)
    {
        if (q == 0 || q == 3 || q == 6)
        {
            return 3;
        }
        else if (q == 1 || q == 4 || q == 7)
        {
            return 4;
        }
        else if (q == 2 || q == 5 || q == 8)
        {
            return 5;
        }
    }
    else if (i == 2 || i == 5 || i == 8)
    {
        if (q == 0 || q == 3 || q == 6)
        {
            return 6;
        }
        else if (q == 1 || q == 4 || q == 7)
        {
            return 7;
        }
        else if (q == 2 || q == 5 || q == 8)
        {
            return 8;
        }
    }
    return 0;
}

void cMain::gridParser(int grid[][9]) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 9);

    do
    {
        notOk = false;
        int iterationCount = 0;
        for (int i = 0; i < collectionSize; i++)
        {
            for (int q = 0; q < collectionSize; q++)
            {
                int index = i * nFieldWidth + q;
                grid[i][q] = distr(gen); 
                iterationCount = 0;
                while (matchCheck(grid[i][q], pickLine(i), collectionSize) || matchCheck(grid[i][q], pickRow(q), collectionSize) || matchCheck(grid[i][q], pickBox(i, q), collectionSize))
                {
                    iterationCount++;
                    grid[i][q] = distr(gen); 
                    if (iterationCount == 30) {
                        notOk = true;
                        break;
                    }
                }
                pickLine(i)[q] = grid[i][q]; pickRow(q)[i] = grid[i][q]; pickBox(i, q)[pickBoxIndex(i, q)] = grid[i][q];

                if (notOk)
                {
                    pickLine(i)[q] = 11; pickRow(q)[i] = 11; pickBox(i, q)[pickBoxIndex(i, q)] = 11;
                }

                gridFilled[i][q] = grid[i][q];
            }
        }
    } while (notOk);

}

bool cMain::matchCheck(int number, std::vector <int>  collection, int collectionSize) 
{
    for (int i = 0; i < collectionSize; i++) {
        if (number == collection[i]) {
            return true;
        }
    }
    return false;
}

void cMain::gridDeleter(int gridSource[][9], int gameDifficulty)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, gameDifficulty); 

    for (int i = 0; i < collectionSize; i++)
    {
        for (int q = 0; q < collectionSize; q++)
        {
            //int quota = distr(gen);
            int chance = distr(gen);
            if (chance != 0)
            {
                continue;
            }
            else
            {
                gridSource[i][q] =  -1;
            }
        }
    }
    //gridSource[0][0] = -1;
}

bool cMain::winCondition()
{
    

    for (int i = 0; i < collectionSize; i++)
    {
        for (int q = 0; q < collectionSize; q++)
        {
            int index = i * nFieldWidth + q;

            if (auto textCtrl = getTextCtrl(index))
            {


                if (textCtrl->GetValue().IsEmpty()) {
                    return false;  // Player has not won if any cell is empty
                }

                // Convert value to integer and check against the gridFilled array
                int value = wxAtoi(textCtrl->GetValue());

                // Safely check the gridFilled value
                if (i >= collectionSize || q >= collectionSize) {
                    wxLogError("gridFilled[%d][%d] is out of bounds.", i, q);
                    return false;
                }

                if (value != gridFilled[i][q]) {
                    return false;  // Mismatch found, player has not won
                }
            }
        }
    }

    return true;  // All cells are filled correctly, player wins
}

wxTextCtrl* cMain::getTextCtrl(int index)
{
    if (textCtrls.size() > index)
    {
        return textCtrls[index];
    }
    return nullptr;
}

/*
Row (y)	Column (x)	Computed Index (y * nFieldWidth + x)
0	0	0
0	1	1
0	2	2
...	...	...
0	8	8
1	0	9
1	1	10
1	2	11
...	...	...
1	8	17
2	0	18
...	...	...
8	8	80
*/