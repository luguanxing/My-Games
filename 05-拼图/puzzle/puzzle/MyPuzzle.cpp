#include "stdafx.h"
#include "MyPuzzle.h"
#include "puzzle.h"
#include "puzzleDlg.h"

////////////////////////////////////////////////////////////////////////////
MyPuzzle *pmz;
HANDLE hmovepic[4];
bool g_lock = false;
int mx, my;
DWORD WINAPI MovePicUp(LPVOID lpParam) {
	while (true) {
		int id = pmz->puzzles[my][mx]-1;
		RECT pos;
		pmz->pics[id]->GetWindowRect(&pos);
		pmz->dlg->ScreenToClient(&pos);
		for (int i = 1; i <= 91 ; i += 1) {
			pos.top -= 1;
			pos.bottom -= 1;
			pmz->pics[id]->MoveWindow(&pos);
			::Sleep(2);
		}
		g_lock = false;
		pmz->EraseBlank();
		::SuspendThread(hmovepic[0]);
	}
	return 0;
}
DWORD WINAPI MovePicDown(LPVOID lpParam) {
	while (true) {
		int id = pmz->puzzles[my][mx]-1;
		RECT pos;
		pmz->pics[id]->GetWindowRect(&pos);
		pmz->dlg->ScreenToClient(&pos);
		for (int i = 1; i <= 91 ; i += 1) {
			pos.top += 1;
			pos.bottom += 1;
			pmz->pics[id]->MoveWindow(&pos);
			::Sleep(2);
		}
		g_lock = false;
		pmz->EraseBlank();
		::SuspendThread(hmovepic[1]);
	}
	return 0;
}
DWORD WINAPI MovePicLeft(LPVOID lpParam) {
	while (true) {
		int id = pmz->puzzles[my][mx]-1;
		RECT pos;
		pmz->pics[id]->GetWindowRect(&pos);
		pmz->dlg->ScreenToClient(&pos);
		for (int i = 1; i <= 91 ; i += 1) {
			pos.left -= 1;
			pos.right -= 1;
			pmz->pics[id]->MoveWindow(&pos);
			::Sleep(2);
		}
		g_lock = false;
		pmz->EraseBlank();
		::SuspendThread(hmovepic[2]);
	}
	return 0;
}
DWORD WINAPI MovePicRight(LPVOID lpParam) {
	while (true) {
		int id = pmz->puzzles[my][mx]-1;
		RECT pos;
		pmz->pics[id]->GetWindowRect(&pos);
		pmz->dlg->ScreenToClient(&pos);
		for (int i = 1; i <= 91 ; i += 1) {
			pos.left += 1;
			pos.right += 1;
			pmz->pics[id]->MoveWindow(&pos);
			::Sleep(2);
		}
		g_lock = false;
		pmz->EraseBlank();
		::SuspendThread(hmovepic[3]);
	}
	return 0;
}
int random(int max) {
	CTime t = CTime::GetCurrentTime();
	int n = t.GetMinute() * 60 + t.GetSecond();
	while(n-- > 0)
		rand();
	return rand()%max;
}

/////////////////////////////////////////////////////////////////////////
MyPuzzle::MyPuzzle() {
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			puzzles[y][x] = 4*y+x+1;
	puzzles[3][3] = 0;
	by = bx = 3;
	dx = dy = -1;
	pmz = this;
	hmovepic[0] = ::CreateThread(NULL, 0, MovePicUp, NULL, CREATE_SUSPENDED, NULL);
	hmovepic[1] = ::CreateThread(NULL, 0, MovePicDown, NULL, CREATE_SUSPENDED, NULL);
	hmovepic[2] = ::CreateThread(NULL, 0, MovePicLeft, NULL, CREATE_SUSPENDED, NULL);
	hmovepic[3] = ::CreateThread(NULL, 0, MovePicRight, NULL, CREATE_SUSPENDED, NULL);
}
void MyPuzzle::SetDlg(CpuzzleDlg *wnddlg) {
	this->dlg = wnddlg;
	for (int i = 0; i < 16; i++)
		this->pics[i] = (CStatic *)wnddlg->GetDlgItem(IDC_STATIC1+i);
}
int kx = 0;	//不在一个相反方向反复移
int  ky = 0;
void MyPuzzle::RandomMove() {
	int rx, ry;
	do {
		rx = random(3)-1;
		if (rx == -1 || rx == 1)
			ry = 0;
		else
			ry = random(2) == 0 ? 1: -1;
	} while (bx+rx<0 || 4<=bx+rx || by+ry<0 || 4<=by+ry || (ky == ry && kx == rx*-1) || (ky == ry*-1 && kx == rx));
	kx = rx;
	ky = ry;
	MovePic(bx+rx, by+ry);
}
int MyPuzzle::GetBlankDirection(int x, int y) {
	if (x == bx && y == by+1) {
		return 0;
	} else if (x == bx && y == by-1) {
		return 1;
	} else if (x == bx+1 && y == by) {
		return 2;
	} else if (x == bx-1 && y == by) {
		return 3;
	}
	return -1;
}

void MyPuzzle::MovePic(int x, int y) {
	int direction = GetBlankDirection(x,y);
	if (direction == -1 || g_lock) {
		return;
	} else  {
		g_lock = true;
		int id = puzzles[y][x]-1;
		RECT pos;
		pics[id]->GetWindowRect(&pos);
		dlg->ScreenToClient(&pos);
		bx = x;
		by = y;
		if (direction == 0) {
			::ResumeThread(hmovepic[0]);
			puzzles[y-1][x] =  puzzles[y][x];
			puzzles[y][x] = 0;
			mx = x;
			my = y-1;
		} else if (direction == 1) {
			::ResumeThread(hmovepic[1]);
			puzzles[y+1][x] =  puzzles[y][x];
			puzzles[y][x] = 0;
			mx = x;
			my = y+1;
		} else if (direction == 2) {
			::ResumeThread(hmovepic[2]);
			puzzles[y][x-1] =  puzzles[y][x];
			puzzles[y][x] = 0;
			mx = x-1;
			my = y;
		} else if (direction == 3) {
			::ResumeThread(hmovepic[3]);
			puzzles[y][x+1] =  puzzles[y][x];
			puzzles[y][x] = 0;
			mx = x+1;
			my = y;
		}
		if (IsWin() && !israndom)
			::MessageBox(NULL, L"赢了", L"赢了", MB_ICONINFORMATION);
	}
}
bool MyPuzzle::IsSamePoint(int x, int y) {
	if (this->dx != x || this->dy != y)
		return false;
	else
		return true;
}
bool MyPuzzle::IsWin() {
	for (int i = 0; i < 15; i++)
		if (puzzles[i/4][i%4] != i+1)
			return false;
	if (puzzles[3][3] != 0)
		return false;
	return true;
}
void MyPuzzle::DrawFrame(int x, int y) {
	if (x == bx && y == by) {
		dx = bx;
		dy = by;
		return;
	}

	HDC hdc = ::GetDC(dlg->m_hWnd);
	HPEN hpen = ::CreatePen(PS_SOLID, 2.5, RGB(255,0,0));
	HPEN holdpen = (HPEN)::SelectObject(hdc, hpen);

	RECT rect;
	if (puzzles[y][x])
		pics[puzzles[y][x]-1]->GetWindowRect(&rect);
	dlg->ScreenToClient(&rect);
	rect.left += 1;
	rect.top += 1;
	rect.bottom -= 1;
	rect.right -=1;


	::MoveToEx(hdc, rect.left, rect.top, NULL);
	::LineTo(hdc, rect.right, rect.top);
	::LineTo(hdc, rect.right, rect.bottom);
	::LineTo(hdc, rect.left, rect.bottom);
	::LineTo(hdc, rect.left, rect.top);

	::SelectObject(hdc, holdpen);
	::DeleteObject(hpen);
	::ReleaseDC(dlg->m_hWnd, hdc);

	this->dx = x;
	this->dy = y;
}
void MyPuzzle::EraseFrame() {
	if (dx < 0 || dx > 3 || dy < 0 || dy > 3)
		return;
	RECT rect;
	if (puzzles[dy][dx])
		pics[puzzles[dy][dx]-1]->GetWindowRect(&rect);
	dlg->ScreenToClient(&rect);
	rect.left -= 1;
	rect.top -= 1;
	rect.bottom += 1;
	rect.right +=1;
	dlg->InvalidateRect(&rect, true);
}
void MyPuzzle::EraseBlank() {
	if (mx < 0 || mx > 3 || my < 0 || my > 3)
		return;
	RECT rect;
	if (puzzles[my][mx])
		pics[puzzles[my][mx]-1]->GetWindowRect(&rect);
	dlg->ScreenToClient(&rect);
	rect.left -= 1;
	rect.top -= 1;
	rect.bottom += 1;
	rect.right +=1;
	dlg->InvalidateRect(&rect, true);
}