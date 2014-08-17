//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TLabel *Label1;
	TButton *Button2;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TGroupBox *GroupBox2;
	TButton *Button3;
	TButton *Button_show1;
	TLabel *Label5;
	TGroupBox *GroupBox1;
	TEdit *Edit1;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TLabel *Label10;
	TButton *Button4;
	TGroupBox *GroupBox3;
	TComboBox *ComboBox1;
	TComboBox *ComboBox2;
	TButton *Button5;
	TButton *Button6;
	TGroupBox *GroupBox4;
	TButton *Button7;
	TEdit *Edit6;
	TLabel *Label11;
	TButton *Button8;
	TButton *Button9;
	TEdit *Edit7;
	TLabel *Label12;
	TButton *Button10;
	TEdit *Edit8;
	TLabel *Label13;
	TEdit *Edit9;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button_show1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
private:	// User declarations
	DWORD psopid;
	void ModifyHP(HANDLE);
	void ModifyTP(HANDLE);
	void ModifyHK(HANDLE);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
