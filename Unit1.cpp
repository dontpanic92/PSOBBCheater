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
		MessageBox(NULL,"获取访问令牌失败!","PSOCheat",MB_OK);
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
		Label1->Caption="无法查找进程";
		MessageBox(NULL,"枚举进程失败!","PSOCheat",MB_OK);
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
			   Label1->Caption="找到pso进程";
			   return;
		   }
		}
	}
	Label1->Caption="没有找到pso进程";
	MessageBox(NULL,"没有找到pso进程，请确认游戏是否已运行","PSOCheat",MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"修改失败，无法打开进程","PSOCheat",MB_OK);
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
			Label2->Caption="锁定HP成功!";
		}
		else if ((tmp[0]!=code[0])||(tmp[1]!=code[1])) {
			Label2->Caption="请确认游戏版本是否正确或是否已退出游戏";
		}else
			Label2->Caption="已修改";
   } else {
		if ((tmp[0]==code[0])&&(tmp[1]==code[1])) {
			WriteProcessMemory ( hProcess, (LPVOID)Addr, ori, sizeof(ori), &dwWriteBytes ) ;
			Label2->Caption="解锁HP成功!";
		}else if ((tmp[0]!=ori[0])||(tmp[1]!=ori[1])) {
			Label2->Caption="请确认游戏版本是否正确或是否已退出游戏";
		}else
			Label2->Caption="已修改";
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
			Label3->Caption="锁定TP成功!";
		}
		else if ((tmp[0]!=code[0])||(tmp[1]!=code[1])) {
			Label3->Caption="请确认游戏版本是否正确或是否已退出游戏";
		}else
			Label3->Caption="已修改";
   } else {
		if ((tmp[0]==code[0])&&(tmp[1]==code[1])) {
			WriteProcessMemory ( hProcess, (LPVOID)Addr, ori, sizeof(ori), &dwWriteBytes ) ;
			Label3->Caption="解锁TP成功!";
		}else if ((tmp[0]!=ori[0])||(tmp[1]!=ori[1])) {
			Label3->Caption="请确认游戏版本是否正确或是否已退出游戏";
		}else
			Label3->Caption="已修改";
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
			Label4->Caption="设定一击必杀成功!";
		}
		else if ((tmp[0]!=code[0])||(tmp[1]!=code[1])) {
			Label4->Caption="请确认游戏版本是否正确或是否已退出游戏";
		}else
			Label4->Caption="已修改";
   } else {
		if ((tmp[0]==code[0])&&(tmp[1]==code[1])) {
			WriteProcessMemory ( hProcess, (LPVOID)Addr, ori, sizeof(ori), &dwWriteBytes ) ;
			Label4->Caption="解除一击必杀成功!";
		}else if ((tmp[0]!=ori[0])||(tmp[1]!=ori[1])) {
			Label4->Caption="请确认游戏版本是否正确或是否已退出游戏";
		}else
			Label4->Caption="已修改";
   }
   VirtualProtectEx ( hProcess, (LPVOID)Addr, sizeof(DWORD), dwOldProtect, NULL ) ;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_show1Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"修改失败，无法打开进程","PSOCheat",MB_OK);
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
		MessageBox(NULL,"修改失败，无法打开进程","PSOCheat",MB_OK);
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
	//ShowMessage("修改完成,重建房间后需要重新修改!");
	//Button_show1->Click();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"修改失败，无法打开进程","PSOCheat",MB_OK);
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
	//ShowMessage("修改完成,重建房间后需要重新修改!");
	//Button_show1->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	ComboBox2->Clear();
	ComboBox2->Items->Add("先驱者2号");
	switch (ComboBox1->ItemIndex) {
		case 0:
			ComboBox2->Items->Add("森林地带1");
			ComboBox2->Items->Add("森林地带2");
			ComboBox2->Items->Add("洞窟地带1");
			ComboBox2->Items->Add("洞窟地带2");
			ComboBox2->Items->Add("洞窟地带3");
			ComboBox2->Items->Add("坑道地带1");
			ComboBox2->Items->Add("坑道地带2");
			ComboBox2->Items->Add("遗迹地带1");
			ComboBox2->Items->Add("遗迹地带2");
			ComboBox2->Items->Add("遗迹地带3");
			ComboBox2->Items->Add("赤炎巨龙");
			ComboBox2->Items->Add("迪·洛尔·雷");
			ComboBox2->Items->Add("狂蜘蛛");
			ComboBox2->Items->Add("暗黑佛");
			break;
		case 1:
			ComboBox2->Items->Add("虚拟神殿1");
			ComboBox2->Items->Add("虚拟神殿2");
			ComboBox2->Items->Add("虚拟宇宙飞船1");
			ComboBox2->Items->Add("虚拟宇宙飞船2");
			ComboBox2->Items->Add("中央管理区");
			ComboBox2->Items->Add("密林地区 北");
			ComboBox2->Items->Add("密林地区 东");
			ComboBox2->Items->Add("高山地区");
			ComboBox2->Items->Add("海岸地区");
			ComboBox2->Items->Add("海底设施 上层");
			ComboBox2->Items->Add("海底设施 下层");
			ComboBox2->Items->Add("加尔·狮鹫");
			ComboBox2->Items->Add("暗黑佛罗文");
			ComboBox2->Items->Add("巴尔·巴雷");
			ComboBox2->Items->Add("数码暴龙");
			break;
		case 2:
			ComboBox2->Items->Add("陨石坑周边 东部路线");
			ComboBox2->Items->Add("陨石坑周边 西部路线");
			ComboBox2->Items->Add("陨石坑周边 南部路线");
			ComboBox2->Items->Add("陨石坑周边 北部路线");
			ComboBox2->Items->Add("陨石坑内部");
			ComboBox2->Items->Add("地下沙漠1");
			ComboBox2->Items->Add("地下沙漠2");
			ComboBox2->Items->Add("地下沙漠3");
			ComboBox2->Items->Add("近藤");
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
		MessageBox(NULL,"修改失败，无法打开进程","PSOCheat",MB_OK);
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
		Label1->Caption="无法查找进程";
		MessageBox(NULL,"枚举进程失败!","PSOCheat",MB_OK);
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
			   Label1->Caption="找到pso进程";
			   return;
		   }
		}
	}
	Label1->Caption="没有找到pso进程";
	MessageBox(NULL,"没有找到pso进程，请确认游戏是否已运行","PSOCheat",MB_OK);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"修改失败，无法打开进程","PSOCheat",MB_OK);
		return ;
	}
	DWORD Addr1=0x00a91dd4, Addr2, Addr3, Addr4;
	DWORD dwWriteBytes = 0;

	ReadProcessMemory ( hProcess, (LPVOID)Addr1, &Addr2, sizeof(DWORD), &dwWriteBytes);
	Addr2+=0x2b4;
	ReadProcessMemory ( hProcess, (LPVOID)Addr2, &Addr3, sizeof(DWORD), &dwWriteBytes);
	Addr4=Addr3+0x26 ;//攻击力

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
		MessageBox(NULL,"修改失败，无法打开进程","PSOCheat",MB_OK);
		return ;
	}
	DWORD Addr1=0x00a91dd4, Addr2, Addr3, Addr4;
	DWORD dwWriteBytes = 0, dwOldProtect ;

	ReadProcessMemory ( hProcess, (LPVOID)Addr1, &Addr2, sizeof(DWORD), &dwWriteBytes);
	Addr2+=0x2b4;
	ReadProcessMemory ( hProcess, (LPVOID)Addr2, &Addr3, sizeof(DWORD), &dwWriteBytes);

	VirtualProtectEx ( hProcess, (LPVOID)Addr3, sizeof(DWORD), PAGE_READWRITE, &dwOldProtect ) ;

	WORD g=30000;//32245;
	Addr4=Addr3+0x26 ;//攻击力
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;

	g=30000;//32765;  //命中
	Addr4+=0x2;
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;

	g=15000;         //精神力
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
		Label1->Caption="无法查找进程";
		MessageBox(NULL,"枚举进程失败!","PSOCheat",MB_OK);
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
			   Label1->Caption="找到pso进程";
			   return;
		   }
		}
	}
	Label1->Caption="没有找到pso进程";
	MessageBox(NULL,"没有找到pso进程，请确认游戏是否已运行","PSOCheat",MB_OK);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE,psopid );
	if ( hProcess == NULL ){
		MessageBox(NULL,"修改失败，无法打开进程","PSOCheat",MB_OK);
		return ;
	}
	DWORD Addr1=0x00a91dd4, Addr2, Addr3, Addr4;
	DWORD dwWriteBytes = 0, dwOldProtect ;

	ReadProcessMemory ( hProcess, (LPVOID)Addr1, &Addr2, sizeof(DWORD), &dwWriteBytes);
	Addr2+=0x2b4;
	ReadProcessMemory ( hProcess, (LPVOID)Addr2, &Addr3, sizeof(DWORD), &dwWriteBytes);

	VirtualProtectEx ( hProcess, (LPVOID)Addr3, sizeof(DWORD), PAGE_READWRITE, &dwOldProtect ) ;

	WORD g=Edit6->Text.ToInt();
	Addr4=Addr3+0x26 ;//攻击力
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;

	g=Edit7->Text.ToInt();
	Addr4+=0x2;       //命中
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;

	g=Edit8->Text.ToInt();
	Addr4=Addr3+0x2;   //精神力
	WriteProcessMemory ( hProcess, (LPVOID)Addr4, &g, sizeof(WORD), &dwWriteBytes ) ;

	VirtualProtectEx ( hProcess, (LPVOID)Addr3, sizeof(DWORD), dwOldProtect, NULL ) ;
	CloseHandle ( hProcess ) ;
	Button7->Click();

}
//---------------------------------------------------------------------------

