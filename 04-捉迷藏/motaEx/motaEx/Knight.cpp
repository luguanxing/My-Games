#include "stdafx.h"
#include "Knight.h"

Knight *pknight;
DWORD WINAPI SetKnightUp(LPVOID lpParam) {
	while (true) {
		for (int i = 12; i < 16; i++) {
			pknight->m_cs_knight->SetBitmap(pknight->hbk[i]);
			::Sleep(300);
		}
		::Sleep(20);
	}
	return 0;
}
DWORD WINAPI SetKnightDown(LPVOID lpParam) {
	while (true) {
		for (int i = 0; i < 4; i++) {
			pknight->m_cs_knight->SetBitmap(pknight->hbk[i]);
			::Sleep(300);
		}
		::Sleep(20);
	}
	return 0;
}
DWORD WINAPI SetKnightLeft(LPVOID lpParam) {
	while (true) {
		for (int i = 4; i < 7; i++) {
			pknight->m_cs_knight->SetBitmap(pknight->hbk[i]);
			::Sleep(300);
		}
		::Sleep(20);
	}
	return 0;
}
DWORD WINAPI SetKnightRight(LPVOID lpParam) {
	while (true) {
		for (int i = 8; i < 12; i++) {
			pknight->m_cs_knight->SetBitmap(pknight->hbk[i]);
			::Sleep(300);
		}
		::Sleep(20);
	}
	return 0;
}

Knight::Knight() {
	pknight = this;
	directionk = 1;
	for (int i = 0; i < 16; i++)
		hbk[i] = NULL;
	for (int i = 0; i < 4; i++) {
		runningk[i] = false;
		hthreadk[i] = NULL;
	}

	for (int i = 0; i < 16; i++)
		hbk[i] = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(145+i),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE) ;

	hthreadk[0] = ::CreateThread(NULL, 0, SetKnightUp, NULL, CREATE_SUSPENDED, NULL);
	hthreadk[1] = ::CreateThread(NULL, 0, SetKnightDown, NULL,  CREATE_SUSPENDED, NULL);
	hthreadk[2] = ::CreateThread(NULL, 0, SetKnightLeft, NULL, CREATE_SUSPENDED, NULL);
	hthreadk[3] = ::CreateThread(NULL, 0, SetKnightRight, NULL, CREATE_SUSPENDED, NULL);	

}

void Knight::SetCStatic(CStatic *m_knight) {
	this->m_cs_knight = m_knight;
	PlayKnightDirection(1);
}


void Knight::PlayKnightDirection(int direction) {
	for (int i = 0; i < 4; i++) {
		if (runningk[i]) {
			::SuspendThread(hthreadk[i]);
			runningk[i] = false;
		}
	}
	runningk[direction] = true;
	directionk = direction;
	::ResumeThread(hthreadk[direction]);
}