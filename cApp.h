#pragma once

#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();

private:
	cMain* m_frame1 = nullptr;

    wxTextCtrl** textCtrls;
    int* nField;

public:
	virtual bool OnInit();
};

