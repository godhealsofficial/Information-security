// CryptoAPI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "CryptoAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma comment(lib, "crypt32.lib")

CWinApp theApp;

class CryptoAPI
{
	HCRYPTPROV m_hCP = NULL;
	HCRYPTKEY m_hExchangeKey = NULL; //���� ��������/��������
	HCRYPTKEY m_hSessionKey = NULL; //���������� ������
	HCRYPTKEY m_hExportKey = NULL; //���� ������ �� �������
public:

	HCRYPTKEY GetExchangeKey()
	{
		return m_hExchangeKey;
	}

	HCRYPTKEY GetSessionKey()
	{
		return m_hSessionKey;
	}

	HCRYPTKEY GetExportKey()
	{
		return m_hExportKey;
	}

	CryptoAPI()
	{
		if (!CryptAcquireContext(&m_hCP, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))	//������ � ���������������� RSA
			PrintError();
		if (!CryptAcquireContext(&m_hCP, "My Container", MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0))
		{
			if (GetLastError() == NTE_BAD_KEYSET)
			{
				if (!CryptAcquireContext(&m_hCP, "My Container", MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET))
					PrintError();
			}
		}
	}
	
	~CryptoAPI()
	{
		DestroyKeys();
		if (m_hCP)
		{
			if (!CryptReleaseContext(m_hCP, 0))//������� ��� ���������������� �� ���������� ���������
				PrintError();
		}
	}

	void GenKeyPair()//��������� ���� ������ (��������/��������)
	{
		if (!CryptGenKey(m_hCP, CALG_RSA_KEYX, CRYPT_EXPORTABLE, &m_hExchangeKey))//�������� ��������� ������
			PrintError();
	}

	void GenSessionKey()//��������� ���������� ������
	{
		if (!CryptGenKey(m_hCP, CALG_AES_256, CRYPT_EXPORTABLE, &m_hSessionKey))
			PrintError();
	}

	void GenExportKey(const string& sPassword)
	{
		HCRYPTHASH hHash;
		if (!CryptCreateHash(m_hCP, CALG_SHA_256, NULL, 0, &hHash))
		{
			PrintError();
			return;
		}
		if(!CryptHashData(hHash, (BYTE*)sPassword.c_str(), sPassword.length(), 0))
		{
			PrintError();
			return;
		}

		if (!CryptDeriveKey(m_hCP, CALG_AES_256, hHash, CRYPT_EXPORTABLE, &m_hExportKey))
			PrintError();

		CryptDestroyHash(hHash);
	}

	void DestroyKey(HCRYPTKEY& hKey)//����������� ������
	{
		if (hKey)
		{
			if (!CryptDestroyKey(hKey))
				PrintError();
			hKey = NULL;
		}
	}

	void DestroyKeys()
	{
		DestroyKey(m_hExchangeKey);
		DestroyKey(m_hSessionKey);
		DestroyKey(m_hExportKey);
	}
	//��������������� ����� �� ������� ����������
	void DoExportKey(vector<char>& v, HCRYPTKEY hKey, HCRYPTKEY hExpKey, DWORD dwType)
	{
		DWORD dwLen = 0;
		if (!CryptExportKey(hKey, hExpKey, dwType, 0, NULL, &dwLen))
		{
			PrintError();
			return;
		}
		v.resize(dwLen);
		if (!CryptExportKey(hKey, hExpKey, dwType, 0, (BYTE*)v.data(), &dwLen))
			PrintError();
		v.resize(dwLen);		// ��������� ��� ��������� ������ �������� ������ ���������������� ������ 
								// ����� ���� ������ �������, ������������ ��� ��������
	}

	void DoImportKey(vector<char>& v, HCRYPTKEY& hKey, HCRYPTKEY hPubKey, DWORD dwType)
	{
		if (!CryptImportKey(m_hCP, (BYTE*)v.data(), v.size(), hPubKey, CRYPT_EXPORTABLE, &hKey))
			PrintError();
	}

	void ExportPublicKey(vector<char>& v)//������� ��������� �����
	{
		DoExportKey(v, m_hExchangeKey, NULL, PUBLICKEYBLOB);
	}

	void ExportPrivateKey(vector<char>& v)//������� ��������� �����
	{
		DoExportKey(v, m_hExchangeKey, m_hExportKey, PRIVATEKEYBLOB);
	}

	void ExportSessionKey(vector<char>& v)//������� ���������� ������ 
	{
		DoExportKey(v, m_hSessionKey, m_hExchangeKey, SIMPLEBLOB);
	}

	void ImportPublicKey(vector<char>& v)//������ ��������� �����
	{
		DoImportKey(v, m_hExchangeKey, NULL, PUBLICKEYBLOB);
	}

	void ImportPrivateKey(vector<char>& v)//������ ��������� �����
	{
		DoImportKey(v, m_hExchangeKey, m_hExportKey, PRIVATEKEYBLOB);
	}

	void ImportSessionKey(vector<char>& v)//������ ���������� ������
	{
		DoImportKey(v, m_hSessionKey, NULL, SIMPLEBLOB);
	}

	void EncryptData(ifstream& in, ofstream& out, DWORD dwSize, HCRYPTKEY hKey = NULL, bool bRSA = false)
		// CryptGetKeyParam � KP_BLOCKLEN ���������� ������ ����� � �����, 
		// ��� ����������� ���������� ����� ������������ ������� ��������,
		// �� RSA ������� ������� ������������ ����� ����� � ������,
		// ������ 11 ���� ����� ��� ������������� ����������� (padding)
	{
		if (!hKey)
			hKey = m_hSessionKey;

		DWORD dwBlockLen = 0;
		DWORD dwDataLen = sizeof(DWORD);
		if (!CryptGetKeyParam(hKey, KP_BLOCKLEN, (BYTE*)&dwBlockLen, &dwDataLen, 0))
			PrintError();
		writeln("Block length: ", dwBlockLen);

		if (bRSA)
		{
			dwBlockLen >>= 3;
			dwBlockLen -= 11;
		}

		DWORD dwDone = 0;
		vector<char> v(dwBlockLen);

		bool bDone = false;
		while (!bDone)
		{
			in.read(v.data(), dwBlockLen);
			DWORD dwRead = (DWORD)in.gcount();
			dwDone += dwRead;
			bDone = (dwDone == dwSize);
			dwDataLen = dwRead;
			if (!CryptEncrypt(hKey, NULL, bDone, 0, NULL, &dwDataLen, 0))
				PrintError();
			if (dwDataLen > v.size())
				v.resize(dwDataLen);
			if (!CryptEncrypt(hKey, NULL, bDone, 0, (BYTE*)v.data(), &dwRead, v.size()))
				PrintError();
			out.write(v.data(), dwRead);
		}
	}

	void DecryptData(ifstream& in, ofstream& out, DWORD dwSize, HCRYPTKEY hKey = NULL, bool bRSA = false)
	{
		if (!hKey)
			hKey = m_hSessionKey;

		DWORD dwBlockLen = 0;
		DWORD dwDataLen = sizeof(DWORD);
		if (!CryptGetKeyParam(hKey, KP_BLOCKLEN, (BYTE*)&dwBlockLen, &dwDataLen, 0))
			PrintError();
		writeln("Block length: ", dwBlockLen);

		if (bRSA)
		{
			dwBlockLen >>= 3;
		}

		DWORD dwDone = 0;
		vector<char> v(dwBlockLen);

		bool bDone = false;
		while (!bDone)
		{
			in.read(v.data(), dwBlockLen);
			DWORD dwRead = (DWORD)in.gcount();
			dwDone += dwRead;
			bDone = (dwDone == dwSize);
			if (!CryptDecrypt(hKey, NULL, bDone, 0, (BYTE*)v.data(), &dwRead))
				PrintError();
			out.write(v.data(), dwRead);
		}
	}

	void EncryptData(vector<char>& vIn, vector<char>& vOut, HCRYPTKEY hKey = NULL, bool bRSA = false)
	{
		if (!hKey)
			hKey = m_hSessionKey;

		DWORD dwBlockLen = 0;
		DWORD dwDataLen = sizeof(DWORD);
		if (!CryptGetKeyParam(hKey, KP_BLOCKLEN, (BYTE*)&dwBlockLen, &dwDataLen, 0))
			PrintError();
		writeln("Encrypt block length: ", dwBlockLen);

		if (bRSA)
		{
			dwBlockLen >>= 3;
			dwBlockLen -= 11;
		}

		DWORD dwDone = 0;
		vector<char> v(dwBlockLen);

		bool bDone = false;
		while (!bDone)
		{
			DWORD dwRead = min(dwBlockLen, vIn.size() - dwDone);
			memcpy(v.data(), vIn.data() + dwDone, dwRead);
			dwDone += dwRead;
			bDone = (dwDone == vIn.size());
			dwDataLen = dwRead;
			if (!CryptEncrypt(hKey, NULL, bDone, 0, NULL, &dwDataLen, 0))
				PrintError();
			if (dwDataLen > v.size())
				v.resize(dwDataLen);
			if (!CryptEncrypt(hKey, NULL, bDone, 0, (BYTE*)v.data(), &dwRead, v.size()))
				PrintError();
			vOut.insert(vOut.end(), v.begin(), v.begin() + dwRead);
		}
	}

	void DecryptData(vector<char>& vIn, vector<char>& vOut, HCRYPTKEY hKey = NULL, bool bRSA = false)
	{
		if (!hKey)
			hKey = m_hSessionKey;
		DWORD dwBlockLen = 0;
		DWORD dwDataLen = sizeof(DWORD);
		if (!CryptGetKeyParam(hKey, KP_BLOCKLEN, (BYTE*)&dwBlockLen, &dwDataLen, 0))
			PrintError();
		writeln("Decrypt block length: ", dwBlockLen);

		if (bRSA)
		{
			dwBlockLen >>= 3;
		}

		DWORD dwDone = 0;
		vector<char> v(dwBlockLen);

		bool bDone = false;
		while (!bDone)
		{
			DWORD dwRead = min(dwBlockLen, vIn.size() - dwDone);
			memcpy(v.data(), vIn.data() + dwDone, dwRead);
			dwDone += dwRead;
			bDone = (dwDone == vIn.size());
			if (!CryptDecrypt(hKey, NULL, bDone, 0, (BYTE*)v.data(), &dwRead))
				PrintError();
			vOut.insert(vOut.end(), v.begin(), v.begin() + dwRead);
		}
	}
};

void menu()
{
	cout << "1. Generate Keys" << endl
		 << "2. Code file" << endl
		 << "3. Decode file" << endl
	     << "0. Exit\n" << endl;
}
#if defined(max)
#undef max
#endif

//�������� �����
template<class T>
T userInputValidator(T min, T max)
{
	cout << "Enter the number from " << min << " to " << max << ": ";
	T val;
	cin >> val;
	while ((!cin >> val) || (val < min) || (val > max))
	{
		cout << "The value has entered incorrectly. Enter the number from " << min << " to " << max << ": ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*��� ������� ������ ������� ������. ���������� ��������� cin, ��� ���������� ������������ �������� �� ����������.*/
		cin >> val;
	}
	return val;
}

void CryptoTest()
{
	CryptoAPI crypto;

	while (true)
	{
		menu();
		int choice;
		choice = userInputValidator(0, 3);
		switch (choice)
		{
		case 0:
		{
			return;
		}
		case 1://��������� ������
		{
			system("cls");
			crypto.GenKeyPair();//��������� ���� ������ (��������/��������)
			crypto.GenSessionKey();//��������� ���������� ������
			
			cout << "Enter export password: ";
			string password;
			cin >> password;
			crypto.GenExportKey(password);

			{
				vector<char> v;//�������� ����
				crypto.ExportPrivateKey(v);//��� ������ �� ������� ����������
				ofstream out("private.key", ios::binary);
				out << v.size() << endl;
				out.write(v.data(), v.size()); 
			}

			{
				vector<char> v;//�������� ����
				crypto.ExportPublicKey(v);//��� ������ �� ������� ����������
				ofstream out("public.key", ios::binary);
				out.write(v.data(), v.size()); 
			}

			// CryptExportKey �� �������, � ����������� ���������� �����, ������� ����� ������������ ��������� ����
			{
				vector<char> v;//���������� ����
				crypto.ExportSessionKey(v);//��� ������ �� ������� ����������
				ofstream out("session.key", ios::binary);
				out.write(v.data(), v.size()); 
			}

			{
				vector<char> v1; //���������� ����
				vector<char> v2; //������������� ���������� ����
				crypto.ExportSessionKey(v1);
				crypto.EncryptData(v1, v2, crypto.GetExchangeKey(), true);
				ofstream out("code.txt", ios::binary);
				out << v2.size() << endl;
				out.write(v2.data(), v2.size()); 
			}

			break;
		}
		case 2://���� ��� ���������
		{
			system("cls");
			ifstream in("input.txt", ios::binary);//������� �����
			ofstream out("code.txt", ios::binary);//�������� ����
			crypto.EncryptData(in, out, (DWORD)filesystem::file_size("input.txt"));//���������� ���������� ������
			crypto.DestroyKeys();//����������� ������
			
			cout << "Enter export password: ";
			string password;
			cin >> password;
			crypto.GenExportKey(password);

			break;
		}
		case 3://���� ��� �������������
		{
			system("cls");

			{
				ifstream in("private.key", ios::binary);//�������� ����
				vector v(istreambuf_iterator<char>{in}, {});
				crypto.ImportPrivateKey(v); 
			}

			{
				ifstream in("session.key", ios::binary); //���������� ���� (������������)
				vector v(istreambuf_iterator<char>{in}, {});
				crypto.ImportSessionKey(v);
			}

			{
				ifstream in("public.key", ios::binary);//������� ����
				vector v(istreambuf_iterator<char>{in}, {});
				crypto.ImportPublicKey(v); 
			}

			{
				ifstream in("code.txt", ios::binary);//����������� ����������� �����

				int size;
				in >> size;

				vector<char> v1;
				for (int i = 0; i < size; i++) {
					char c;
					in >> c;
					v1.push_back(c);
				}

				vector<char> v2;
				crypto.DecryptData(v1, v2, crypto.GetExchangeKey(), true);
			}

			{
				ifstream in("code.txt", ios::binary);
				ofstream out("decode.txt", ios::binary);
				crypto.DecryptData(in, out, (DWORD)filesystem::file_size("code.txt")); //����������� � �������	����������� �����
			}

			break;
		}
		default:
		{
			break;
		}
		}
	}
}

int main()
{     
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: code your application's behavior here.
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
			CryptoTest();
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}

	return nRetCode;
}
