#include "stdafx.h"
#include "Solider.h"


///////////////////////////////播放线程/////////////////////////////
Solider *psolider;
DWORD WINAPI SetSoliderUp(LPVOID lpParam) {
	while (true) {
		for (int i = 12; i < 16; i++) {
			psolider->m_cs_solider->SetBitmap(psolider->hbs[i]);
			::Sleep(300);
		}
		::Sleep(20);
	}
	return 0;
}
DWORD WINAPI SetSoliderDown(LPVOID lpParam) {
	while (true) {
		for (int i = 0; i < 4; i++) {
			psolider->m_cs_solider->SetBitmap(psolider->hbs[i]);
			::Sleep(300);
		}
		::Sleep(20);
	}
	return 0;
}
DWORD WINAPI SetSoliderLeft(LPVOID lpParam) {
	while (true) {
		for (int i = 4; i < 7; i++) {
			psolider->m_cs_solider->SetBitmap(psolider->hbs[i]);
			::Sleep(300);
		}
		::Sleep(20);
	}
	return 0;
}
DWORD WINAPI SetSoliderRight(LPVOID lpParam) {
	while (true) {
		for (int i = 8; i < 12; i++) {
			psolider->m_cs_solider->SetBitmap(psolider->hbs[i]);
			::Sleep(300);
		}
		::Sleep(20);
	}
	return 0;
}

/////////////////////////////////初始化/////////////////////////////////
Solider::Solider() {
	//初始化solider数据
	psolider = this;
	directions = 1;
	for (int i = 0; i < 16; i++)
		hbs[i] = NULL;
	for (int i = 0; i < 4; i++) {
		runnings[i] = false;
		hthreads[i] = NULL;
	}

	//加载图片资源
	for (int i = 0; i < 16; i++)
		hbs[i] = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(129+i),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE) ;

	//加载播放线程，设solider初始状态为Down
	hthreads[0] = ::CreateThread(NULL, 0, SetSoliderUp, NULL, CREATE_SUSPENDED, NULL);
	hthreads[1] = ::CreateThread(NULL, 0, SetSoliderDown, NULL,  CREATE_SUSPENDED, NULL);
	hthreads[2] = ::CreateThread(NULL, 0, SetSoliderLeft, NULL, CREATE_SUSPENDED, NULL);
	hthreads[3] = ::CreateThread(NULL, 0, SetSoliderRight, NULL, CREATE_SUSPENDED, NULL);	

}

void Solider::SetCStatic(CStatic *m_solider) {
	this->m_cs_solider = m_solider;
	PlaySoliderDirection(1);
}

void Solider::SetSoliderDirection(int direction) {
	for (int i = 0; i < 4; i++) {
		if (runnings[i]) {
			::SuspendThread(hthreads[i]);
			runnings[i] = false;
		}
	}
	if (this->directions == 0) {
		this->m_cs_solider->SetBitmap(hbs[12]);
	} else if (this->directions == 1) {
		this->m_cs_solider->SetBitmap(hbs[0]);
	} else if (this->directions == 2) {
		this->m_cs_solider->SetBitmap(hbs[4]);
	} else if (this->directions == 3) {
		this->m_cs_solider->SetBitmap(hbs[8]);
	}
}

void Solider::PlaySoliderDirection(int direction) {
	for (int i = 0; i < 4; i++) {
		if (runnings[i]) {
			::SuspendThread(hthreads[i]);
			runnings[i] = false;
		}
	}
	runnings[direction] = true;
	directions = direction;
	::ResumeThread(hthreads[direction]);
}
