#include "stdafx.h"
#include "Solider.h"
Solider::Solider() {
	this->pic = NULL;
	this->hbs =NULL;
}
void Solider::Set(CStatic *dlgpic, HBITMAP *dlghbs) {
	this->pic = dlgpic;
	this->hbs = dlghbs;
}
void Solider::SetPic(int num) {
	this->pic->SetBitmap(this->hbs[num]);
}
void Solider::Stand() {
	this->SetPic(0);   
	::Sleep(300);
	this->SetPic(1);
	::Sleep(300);
	this->SetPic(2);   
	::Sleep(300);
	this->SetPic(3);   
	::Sleep(300);
}	
void Solider::Up() {
	this->SetPic(12);   
	::Sleep(300);
	this->SetPic(13);
	::Sleep(300);
	this->SetPic(14);   
	::Sleep(300);
	this->SetPic(15);   
	::Sleep(300);
}	    
void Solider::Down() {
	this->Stand();
}	    
void Solider::Left() {
	this->SetPic(4);   
	::Sleep(300);
	this->SetPic(5);
	::Sleep(300);
	this->SetPic(6);   
	::Sleep(300);
	this->SetPic(7);   
	::Sleep(300);
}	    
void Solider::Right() {
	this->SetPic(8);   
	::Sleep(300);
	this->SetPic(9);
	::Sleep(300);
	this->SetPic(10);   
	::Sleep(300);
	this->SetPic(11);   
	::Sleep(300);
}

Knight::Knight() {
	this->pic = NULL;
	this->hbs =NULL;
}
void Knight::Set(CStatic *dlgpic, HBITMAP *dlghbs) {
	this->pic = dlgpic;
	this->hbs = dlghbs;
}
void Knight::SetPic(int num) {
	this->pic->SetBitmap(this->hbs[num]);
}
void Knight::Stand() {
	this->SetPic(0);   
	::Sleep(300);
	this->SetPic(1);
	::Sleep(300);
}