//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <windows.h>
#include <psapi.h>
#pragma comment(lib,"psapi.lib")
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	TOKEN_PRIVILEGES Privileges;
	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken)){
		MessageBox(NULL,"��ȡ��������ʧ��!","PSOCheat",MB_OK);
		Form1->Close();
		}
	LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&Privileges.Privileges[0].Luid);
	Privileges.PrivilegeCount = 1;
	Privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &Privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	DWORD pid[1024],cbNeeded;
	char pname[260];
	if ( !EnumProcesses( pid, sizeof(pid), &cbNeeded )){
		Label1->Caption="�޷����ҽ���";
		MessageBox(NULL,"ö�ٽ���ʧ��!","PSOCheat",MB_OK);
		return;
	}
	int num=cbNeeded/sizeof(DWORD);
	for (int i = 0; i < num; i++) {
		HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE, pid[i]);
		if ( hProcess ){
		HMODULE hMod;
		DWORD cbNeeded;
		if ( EnumProcessModules( hProcess,&hMod,sizeof(hMod),&cbNeeded) )
		   GetModuleBaseName( hProcess, hMod, pname,sizeof(pname) );
		   if (0!=strcmp(pname,"RayPSO1000.exe")) {
			   CloseHandle(hMod);
			   CloseHandle(hProcess);
		   }else{
			   psopid=pid[i];
			   CloseHandle(hMod);
			   CloseHandle(hProcess);
			   Button2->Enabled=true;
			   Button3->Enabled=true;
			   Button4->Enabled=true;
			   Button_show1->Enabled=true;
			   Button5->Enabled=true;
			   Label1->Caption="�ҵ�pso����";
			   return;
		   }
		}
	}
	Label1->Caption="û���ҵ�pso����";
	MessageBox(NULL,"û���ҵ�pso���̣���ȷ����Ϸ�Ƿ�������","PSOCheat",MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"�޸�ʧ�ܣ��޷��򿪽���","PSOCheat",MB_OK);
		return ;
	}
	ModifyHP(hProcess);
	ModifyTP(hProcess);
	ModifyHK(hProcess);
	CloseHandle ( hProcess ) ;
}
void TForm1::ModifyHP(HANDLE hProcess){
   DWORD Addr=0x00778200;
   BYTE ori[]={0x2b,0xd0};
   BYTE code[]={0x90,0x90};
   BYTE tmp[2];
   DWORD dwWriteBytes = 0, dwOldProtect ;
   VirtualProtectEx ( hProcess, (LPVOID)Addr, sizeof(DWORD), PAGE_READWRITE, &dwOldProtect ) ;
   ReadProcessMemory ( hProcess, (LPVOID)Addr, tmp, sizeof(tmp), &dwWriteBytes);
   if (CheckBox1->Checked ==true) {
		if ((tmp[0]==ori[0])&&(tmp[1]==ori[1])){
			WriteProcessMemory ( hProcess, (LPVOID)Addr, code, sizeof(code), &dwWriteBytes ) ;
			Label2->Caption="����HP�ɹ�!";
		}
		else if ((tmp[0]!=code[0])||(tmp[1]!=code[1])) {
			Label2->Caption="��ȷ����Ϸ�汾�Ƿ���ȷ���Ƿ����˳���Ϸ";
		}else
			Label2->Caption="���޸�";
   } else {
		if ((tmp[0]==code[0])&&(tmp[1]==code[1])) {
			WriteProcessMemory ( hProcess, (LPVOID)Addr, ori, sizeof(ori), &dwWriteBytes ) ;
			Label2->Caption="����HP�ɹ�!";
		}else if ((tmp[0]!=ori[0])||(tmp[1]!=ori[1])) {
			Label2->Caption="��ȷ����Ϸ�汾�Ƿ���ȷ���Ƿ����˳���Ϸ";
		}else
			Label2->Caption="���޸�";
   }
   VirtualProtectEx ( hProcess, (LPVOID)Addr, sizeof(DWORD), dwOldProtect, NULL ) ;

}
void TForm1::ModifyTP(HANDLE hProcess){
   DWORD Addr=0x006a03f6;
   BYTE ori[]={0x2b,0xc2};
   BYTE code[]={0x90,0x90};
   BYTE tmp[2];
   DWORD dwWriteBytes = 0, dwOldProtect ;
   VirtualProtectEx ( hProcess, (LPVOID)Addr, sizeof(DWORD), PAGE_READWRITE, &dwOldProtect ) ;
   ReadProcessMemory ( hProcess, (LPVOID)Addr, tmp, sizeof(tmp), &dwWriteBytes);
   if (CheckBox2->Checked ==true) {
		if ((tmp[0]==ori[0])&&(tmp[1]==ori[1])){
			WriteProcessMemory ( hProcess, (LPVOID)Addr, code, sizeof(code), &dwWriteBytes ) ;
			Label3->Caption="����TP�ɹ�!";
		}
		else if ((tmp[0]!=code[0])||(tmp[1]!=code[1])) {
			Label3->Caption="��ȷ����Ϸ�汾�Ƿ���ȷ���Ƿ����˳���Ϸ";
		}else
			Label3->Caption="���޸�";
   } else {
		if ((tmp[0]==code[0])&&(tmp[1]==code[1])) {
			WriteProcessMemory ( hProcess, (LPVOID)Addr, ori, sizeof(ori), &dwWriteBytes ) ;
			Label3->Caption="����TP�ɹ�!";
		}else if ((tmp[0]!=ori[0])||(tmp[1]!=ori[1])) {
			Label3->Caption="��ȷ����Ϸ�汾�Ƿ���ȷ���Ƿ����˳���Ϸ";
		}else
			Label3->Caption="���޸�";
   }
   VirtualProtectEx ( hProcess, (LPVOID)Addr, sizeof(DWORD), dwOldProtect, NULL ) ;


}
void TForm1::ModifyHK(HANDLE hProcess){
   DWORD Addr=0x007874c0;
   BYTE ori[]={0x2b,0xd0};
   BYTE code[]={0x29,0xd2};
   BYTE tmp[2];
   DWORD dwWriteBytes = 0, dwOldProtect ;
   VirtualProtectEx ( hProcess, (LPVOID)Addr, sizeof(DWORD), PAGE_READWRITE, &dwOldProtect ) ;
   ReadProcessMemory ( hProcess, (LPVOID)Addr, tmp, sizeof(tmp), &dwWriteBytes);
   if (CheckBox3->Checked ==true) {
		if ((tmp[0]==ori[0])&&(tmp[1]==ori[1])){
			WriteProcessMemory ( hProcess, (LPVOID)Addr, code, sizeof(code), &dwWriteBytes ) ;
			Label4->Caption="�趨һ����ɱ�ɹ�!";
		}
		else if ((tmp[0]!=code[0])||(tmp[1]!=code[1])) {
			Label4->Caption="��ȷ����Ϸ�汾�Ƿ���ȷ���Ƿ����˳���Ϸ";
		}else
			Label4->Caption="���޸�";
   } else {
		if ((tmp[0]==code[0])&&(tmp[1]==code[1])) {
			WriteProcessMemory ( hProcess, (LPVOID)Addr, ori, sizeof(ori), &dwWriteBytes ) ;
			Label4->Caption="���һ����ɱ�ɹ�!";
		}else if ((tmp[0]!=ori[0])||(tmp[1]!=ori[1])) {
			Label4->Caption="��ȷ����Ϸ�汾�Ƿ���ȷ���Ƿ����˳���Ϸ";
		}else
			Label4->Caption="���޸�";
   }
   VirtualProtectEx ( hProcess, (LPVOID)Addr, sizeof(DWORD), dwOldProtect, NULL ) ;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_show1Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"�޸�ʧ�ܣ��޷��򿪽���","PSOCheat",MB_OK);
		return ;
	}
	DWORD Addr1=0x00a91dd4, Addr2, Addr3, Addr4;
	DWORD dwWriteBytes = 0;

	ReadProcessMemory ( hProcess, (LPVOID)Addr1, &Addr2, sizeof(DWORD), &dwWriteBytes);

	Addr2+=0x320;
	ReadProcessMemory ( hProcess, (LPVOID)Addr2, &Addr3, sizeof(DWORD), &dwWriteBytes);


	WORD g=0;
	Addr4=Addr3+0x2;
	ReadProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes);
	Edit5->Text=g;

	g=0;
	Addr4=Addr3+0x4;
	ReadProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes);
	Edit4->Text=g;

	g=0;
	Addr4=Addr3+0x6;
	ReadProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes);
	Edit3->Text=g;

	g=0;
	Addr4=Addr3+0xa;
	ReadProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes);
	Edit2->Text=g;

	g=0;
	Addr4=Addr3+0x8;
	ReadProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes);
	Edit1->Text=g;

	CloseHandle ( hProcess ) ;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"�޸�ʧ�ܣ��޷��򿪽���","PSOCheat",MB_OK);
		return ;
	}
	DWORD Addr1=0x00a91dd4, Addr2, Addr3;
	DWORD dwWriteBytes = 0, dwOldProtect ;

	ReadProcessMemory ( hProcess, (LPVOID)Addr1, &Addr2, sizeof(DWORD), &dwWriteBytes);
	Addr2+=0x320;
	ReadProcessMemory ( hProcess, (LPVOID)Addr2, &Addr3, sizeof(DWORD), &dwWriteBytes);
	DWORD Address1=Addr3;

	VirtualProtectEx ( hProcess, (LPVOID)Address1, 6*sizeof(WORD), PAGE_READWRITE, &dwOldProtect ) ;

	WORD g;
	g=Edit1->Text.ToInt();
	WriteProcessMemory ( hProcess, (LPVOID)(Address1+0x8), &g, sizeof(WORD), &dwWriteBytes ) ;

	g=Edit2->Text.ToInt();
	WriteProcessMemory ( hProcess, (LPVOID)(Address1+0xa), &g, sizeof(WORD), &dwWriteBytes ) ;

	g=Edit3->Text.ToInt();
	WriteProcessMemory ( hProcess, (LPVOID)(Address1+0x6), &g, sizeof(WORD), &dwWriteBytes ) ;

	g=Edit4->Text.ToInt();
	WriteProcessMemory ( hProcess, (LPVOID)(Address1+0x4), &g, sizeof(WORD), &dwWriteBytes ) ;

	g=Edit5->Text.ToInt();
	WriteProcessMemory ( hProcess, (LPVOID)(Address1+0x2), &g, sizeof(WORD), &dwWriteBytes ) ;

	VirtualProtectEx ( hProcess, (LPVOID)Address1, 6*sizeof(WORD), dwOldProtect, NULL ) ;
	CloseHandle ( hProcess ) ;

	Button_show1->Click();
	//ShowMessage("�޸����,�ؽ��������Ҫ�����޸�!");
	//Button_show1->Click();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"�޸�ʧ�ܣ��޷��򿪽���","PSOCheat",MB_OK);
		return ;
	}
	DWORD Addr1=0x00a91dd4, Addr2, Addr3;
	DWORD dwWriteBytes = 0, dwOldProtect ;

	ReadProcessMemory ( hProcess, (LPVOID)Addr1, &Addr2, sizeof(DWORD), &dwWriteBytes);

	Addr2+=0x320;
	ReadProcessMemory ( hProcess, (LPVOID)Addr2, &Addr3, sizeof(DWORD), &dwWriteBytes);
	DWORD Address1=Addr3;

	VirtualProtectEx ( hProcess, (LPVOID)Address1, 6*sizeof(WORD), PAGE_READWRITE, &dwOldProtect ) ;

	WORD g=9999;
	WriteProcessMemory ( hProcess, (LPVOID)(Address1+0x8), &g, sizeof(WORD), &dwWriteBytes ) ;
	WriteProcessMemory ( hProcess, (LPVOID)(Address1+0xa), &g, sizeof(WORD), &dwWriteBytes ) ;
	WriteProcessMemory ( hProcess, (LPVOID)(Address1+0x6), &g, sizeof(WORD), &dwWriteBytes ) ;
	WriteProcessMemory ( hProcess, (LPVOID)(Address1+0x4), &g, sizeof(WORD), &dwWriteBytes ) ;
	WriteProcessMemory ( hProcess, (LPVOID)(Address1+0x2), &g, sizeof(WORD), &dwWriteBytes ) ;

	VirtualProtectEx ( hProcess, (LPVOID)Address1, 6*sizeof(WORD), dwOldProtect, NULL ) ;
	CloseHandle ( hProcess ) ;

	Button_show1->Click();
	//ShowMessage("�޸����,�ؽ��������Ҫ�����޸�!");
	//Button_show1->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	ComboBox2->Clear();
	ComboBox2->Items->Add("������2��");
	switch (ComboBox1->ItemIndex) {
		case 0:
			ComboBox2->Items->Add("ɭ�ֵش�1");
			ComboBox2->Items->Add("ɭ�ֵش�2");
			ComboBox2->Items->Add("���ߵش�1");
			ComboBox2->Items->Add("���ߵش�2");
			ComboBox2->Items->Add("���ߵش�3");
			ComboBox2->Items->Add("�ӵ��ش�1");
			ComboBox2->Items->Add("�ӵ��ش�2");
			ComboBox2->Items->Add("�ż��ش�1");
			ComboBox2->Items->Add("�ż��ش�2");
			ComboBox2->Items->Add("�ż��ش�3");
			ComboBox2->Items->Add("���׾���");
			ComboBox2->Items->Add("�ϡ��������");
			ComboBox2->Items->Add("��֩��");
			ComboBox2->Items->Add("���ڷ�");
			break;
		case 1:
			ComboBox2->Items->Add("�������1");
			ComboBox2->Items->Add("�������2");
			ComboBox2->Items->Add("��������ɴ�1");
			ComboBox2->Items->Add("��������ɴ�2");
			ComboBox2->Items->Add("���������");
			ComboBox2->Items->Add("���ֵ��� ��");
			ComboBox2->Items->Add("���ֵ��� ��");
			ComboBox2->Items->Add("��ɽ����");
			ComboBox2->Items->Add("��������");
			ComboBox2->Items->Add("������ʩ �ϲ�");
			ComboBox2->Items->Add("������ʩ �²�");
			ComboBox2->Items->Add("�Ӷ���ʨ��");
			ComboBox2->Items->Add("���ڷ�����");
			ComboBox2->Items->Add("�Ͷ�������");
			ComboBox2->Items->Add("���뱩��");
			break;
		case 2:
			ComboBox2->Items->Add("��ʯ���ܱ� ����·��");
			ComboBox2->Items->Add("��ʯ���ܱ� ����·��");
			ComboBox2->Items->Add("��ʯ���ܱ� �ϲ�·��");
			ComboBox2->Items->Add("��ʯ���ܱ� ����·��");
			ComboBox2->Items->Add("��ʯ���ڲ�");
			ComboBox2->Items->Add("����ɳĮ1");
			ComboBox2->Items->Add("����ɳĮ2");
			ComboBox2->Items->Add("����ɳĮ3");
			ComboBox2->Items->Add("����");
			break;
	default:
		;
	}

	ComboBox2->ItemIndex=0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button5Click(TObject *Sender)
{
	DWORD Addr1=0x00ac78d8,Addr2=0x00aa8f00;
	DWORD dwWriteBytes = 0, dwOldProtect, dwOldProtect1 ;
	HANDLE hProcess = INVALID_HANDLE_VALUE;

	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"�޸�ʧ�ܣ��޷��򿪽���","PSOCheat",MB_OK);
		return ;
	}

	VirtualProtectEx ( hProcess, (LPVOID)Addr1, sizeof(BYTE), PAGE_READWRITE, &dwOldProtect ) ;
	VirtualProtectEx ( hProcess, (LPVOID)Addr2, sizeof(BYTE), PAGE_READWRITE, &dwOldProtect1 ) ;

	BYTE g=ComboBox2->ItemIndex;
	BYTE h=1;
	WriteProcessMemory ( hProcess, (LPVOID)Addr1, &g, sizeof(BYTE), &dwWriteBytes ) ;
	WriteProcessMemory ( hProcess, (LPVOID)Addr2, &h, sizeof(BYTE), &dwWriteBytes ) ;

	VirtualProtectEx ( hProcess, (LPVOID)Addr1, sizeof(BYTE), dwOldProtect, NULL ) ;
	VirtualProtectEx ( hProcess, (LPVOID)Addr2, sizeof(BYTE), dwOldProtect1, NULL ) ;

	CloseHandle ( hProcess ) ;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button6Click(TObject *Sender)
{   DWORD pid[1024],cbNeeded;
	char pname[260];
	if ( !EnumProcesses( pid, sizeof(pid), &cbNeeded )){
		Label1->Caption="�޷����ҽ���";
		MessageBox(NULL,"ö�ٽ���ʧ��!","PSOCheat",MB_OK);
		return;
	}
	int num=cbNeeded/sizeof(DWORD);
	for (int i = 0; i < num; i++) {
		HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE, pid[i]);
		if ( hProcess ){
		HMODULE hMod;
		DWORD cbNeeded;
		if ( EnumProcessModules( hProcess,&hMod,sizeof(hMod),&cbNeeded) )
		   GetModuleBaseName( hProcess, hMod, pname,sizeof(pname) );
		   if (0!=strcmp(pname,"SHPsoBBw.exe")) {
			   CloseHandle(hMod);
			   CloseHandle(hProcess);
		   }else{
			   psopid=pid[i];
			   CloseHandle(hMod);
			   CloseHandle(hProcess);
			   Button2->Enabled=false;
			   Button3->Enabled=true;
			   Button4->Enabled=true;
			   Button_show1->Enabled=true;
			   Button5->Enabled=true;
			   Label1->Caption="�ҵ�pso����";
			   return;
		   }
		}
	}
	Label1->Caption="û���ҵ�pso����";
	MessageBox(NULL,"û���ҵ�pso���̣���ȷ����Ϸ�Ƿ�������","PSOCheat",MB_OK);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"�޸�ʧ�ܣ��޷��򿪽���","PSOCheat",MB_OK);
		return ;
	}
	DWORD Addr1=0x00a91dd4, Addr2, Addr3, Addr4;
	DWORD dwWriteBytes = 0;

	ReadProcessMemory ( hProcess, (LPVOID)Addr1, &Addr2, sizeof(DWORD), &dwWriteBytes);
	Addr2+=0x2b4;
	ReadProcessMemory ( hProcess, (LPVOID)Addr2, &Addr3, sizeof(DWORD), &dwWriteBytes);
	Addr4=Addr3+0x26 ;//������

	WORD g=0;
	ReadProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes);
	Edit6->Text=g;

	g=0;
	Addr4=Addr3+0x28;
	ReadProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes);
	Edit7->Text=g;

	g=0;
	Addr4=Addr3+0x2;
	ReadProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes);
	Edit8->Text=g;

	CloseHandle ( hProcess ) ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{  	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"�޸�ʧ�ܣ��޷��򿪽���","PSOCheat",MB_OK);
		return ;
	}
	DWORD Addr1=0x00a91dd4, Addr2, Addr3, Addr4;
	DWORD dwWriteBytes = 0, dwOldProtect ;

	ReadProcessMemory ( hProcess, (LPVOID)Addr1, &Addr2, sizeof(DWORD), &dwWriteBytes);
	Addr2+=0x2b4;
	ReadProcessMemory ( hProcess, (LPVOID)Addr2, &Addr3, sizeof(DWORD), &dwWriteBytes);

	VirtualProtectEx ( hProcess, (LPVOID)Addr3, sizeof(DWORD), PAGE_READWRITE, &dwOldProtect ) ;

	WORD g=30000;//32245;
	Addr4=Addr3+0x26 ;//������
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;

	g=30000;//32765;  //����
	Addr4+=0x2;
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;

	g=15000;         //������
	Addr4=Addr3+0x2;
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;
	VirtualProtectEx ( hProcess, (LPVOID)Addr3, sizeof(DWORD), dwOldProtect, NULL ) ;

	CloseHandle ( hProcess ) ;
	Button7->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{   DWORD pid[1024],cbNeeded;
	char pname[260];
	if ( !EnumProcesses( pid, sizeof(pid), &cbNeeded )){
		Label1->Caption="�޷����ҽ���";
		MessageBox(NULL,"ö�ٽ���ʧ��!","PSOCheat",MB_OK);
		return;
	}
	int num=cbNeeded/sizeof(DWORD);
	for (int i = 0; i < num; i++) {
		HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE, pid[i]);
		if ( hProcess ){
		HMODULE hMod;
		DWORD cbNeeded;
		if ( EnumProcessModules( hProcess,&hMod,sizeof(hMod),&cbNeeded) )
		   GetModuleBaseName( hProcess, hMod, pname,sizeof(pname) );
		   if (0!=AnsiCompareText( pname ,Edit9->Text.c_str())){
//		   if (0!=strcmp(pname,Edit9->Text.t_str())) {
			   CloseHandle(hMod);
			   CloseHandle(hProcess);
		   }else{
			   psopid=pid[i];
			   CloseHandle(hMod);
			   CloseHandle(hProcess);
			   Button2->Enabled=true;
			   Button3->Enabled=true;
			   Button4->Enabled=true;
			   Button_show1->Enabled=true;
			   Button5->Enabled=true;
			   Label1->Caption="�ҵ�pso����";
			   return;
		   }
		}
	}
	Label1->Caption="û���ҵ�pso����";
	MessageBox(NULL,"û���ҵ�pso���̣���ȷ����Ϸ�Ƿ�������","PSOCheat",MB_OK);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"�޸�ʧ�ܣ��޷��򿪽���","PSOCheat",MB_OK);
		return ;
	}
	DWORD Addr1=0x00a91dd4, Addr2, Addr3, Addr4;
	DWORD dwWriteBytes = 0, dwOldProtect ;

	ReadProcessMemory ( hProcess, (LPVOID)Addr1, &Addr2, sizeof(DWORD), &dwWriteBytes);
	Addr2+=0x2b4;
	ReadProcessMemory ( hProcess, (LPVOID)Addr2, &Addr3, sizeof(DWORD), &dwWriteBytes);

	VirtualProtectEx ( hProcess, (LPVOID)Addr3, sizeof(DWORD), PAGE_READWRITE, &dwOldProtect ) ;

	WORD g=Edit6->Text.ToInt();
	Addr4=Addr3+0x26 ;//������
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;

	g=Edit7->Text.ToInt();
	Addr4+=0x2;       //����
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;

	g=Edit8->Text.ToInt();
	Addr4=Addr3+0x2;   //������
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;

	VirtualProtectEx ( hProcess, (LPVOID)Addr3, sizeof(DWORD), dwOldProtect, NULL ) ;
	CloseHandle ( hProcess ) ;
	Button7->Click();

}
//---------------------------------------------------------------------------

